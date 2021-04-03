#if 0  // self-compiling code
gcc -std=c99 -Wall -Wextra -pedantic -Werror -g -O4 -march=native $0 -lm || exit 1
exec time ./a.out
#endif

// Blue Noise texture generation using the void-and-cluster algorithm
// implemented by Martin Fiedler <keyj@emphy.de>
// using an algorithm description written by Alan Wolfe:
// https://blog.demofox.org/2019/06/25/generating-blue-noise-textures-with-void-and-cluster/


#ifndef BLUENOISE
#define BLUENOISE

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <vector>

// <parameter> log2 image size; 8 = 256x256 pixels
#define LOG2_SIZE 6

// <parameter> energy function falloff (Gaussian sigma value)
#define SIGMA 1.9

// <parameter> fraction of the image area to "seed" with initial random points
#define INITIAL_POINT_DENSITY 10


#define SIZE (1 << LOG2_SIZE)              // image size (width = height)
#define AREA (SIZE * SIZE)                 // image area (wifth * height)
#define POINT_SHIFT ((2 * LOG2_SIZE) - 8)  // shift amount between point ID and grayscale value
#define XY_MASK ((1 << LOG2_SIZE) - 1)     // coordinate mask

#define I2X(i) ((i) & XY_MASK)                // extract X coordinate from point index
#define I2Y(i) ((i) >> LOG2_SIZE)             // extract Y coordinate from point index
#define XY2I(x,y) (((y) << LOG2_SIZE) + (x))  // build point index from coordinates

// structure representing the current processing state
struct map_state {
    uint32_t bitmap[AREA / 32];  // dot occupancy bitmap
    float emap[AREA];            // energy map
    int imin, imax;              // index of minimum and maximum energy spots
    int points;                  // number of active points in the bitmap
} static state1, state2, *state = &state1;

// get/set/clear individual bits in the current state bitmap
#define BMP_GET(i) ((state->bitmap[((i) >> 5)] >> ((i) & 31)) & 1u)
#define BMP_SET(i) do { state->bitmap[(i) >> 5] |=   1u << ((i) & 31);  } while (0)
#define BMP_CLR(i) do { state->bitmap[(i) >> 5] &= ~(1u << ((i) & 31)); } while (0)

// energy distribution LUT
// (twice the image dimensions so that we can sample from a window)
static float etab[(SIZE * 2) * (SIZE * 2)];
// TODO: Maybe it's faster to shrink the LUT to image size and handle wrap-
//       around in update_map()? The large LUT might be cache-unfriendly ...

// resulting noise image
static uint8_t noise[AREA];


// update the current energy map (and imax/imin) after adding (sign=+1)
// or removing (sign=-1) a point at index
inline void update_map(int index, float sign) {
    int px = I2X(index);
    int py = I2Y(index);
    const float* pt = &etab[((SIZE - py) * (SIZE * 2)) + (SIZE - px)];
    float* pm = state->emap;
    float emin = 1e9f, emax = 0.0f;
    int i = 0;
    for (int y = 0;  y < SIZE;  ++y) {
        for (int x = 0;  x < SIZE;  ++x) {
            float e = (*pm++ += *pt++ * sign);
            if (BMP_GET(i)) {
                if (e > emax) { emax = e; state->imax = i; }
            } else {
                if (e < emin) { emin = e; state->imin = i; }
            }
            ++i;
        }
        pt += SIZE;
    }
}


inline std::vector<uint8_t> gen_blue_noise() {
    srand(time(NULL));
    //FILE *f;
    
    // initialize the noise image to white (saves us 1/256th of the work, yay!)
    memset(noise, 0xFF, AREA);

    // prepare energy look-up table, using symmetries and repetitions:
    // only create the upper-left 1/16th explicitly, then mirror it to get the
    // upper-left quarter, then repeat that again
    float *row = etab;
    for (int y = 0;  y < (SIZE / 2);  ++y) {
        for (int x = 0;  x < (SIZE / 2);  ++x) {
            row[x] = row[SIZE - x] = (float)exp((x * x + y * y) * (-0.5 / (SIGMA * SIGMA)));
        }
        memcpy(&row[SIZE], row, SIZE * sizeof(float));
        row += SIZE * 2;
    }
    for (int y = 0;  y < (SIZE / 2);  ++y) {
        memcpy(&etab[(SIZE - y) * (SIZE * 2)], &etab[y * (SIZE * 2)], (SIZE * 2) * sizeof(float));
    }
    memcpy(&etab[SIZE * (SIZE * 2)], etab, SIZE * (SIZE * 2) * sizeof(float));

    // debug: dump energy look-up table
    #if 0
    {
        uint8_t conv[(SIZE * 2) * (SIZE * 2)];
        for (int i = 0;  i < ((SIZE * 2) * (SIZE * 2));  ++i) {
            float f = etab[i];
            for (int contrast = 10;  contrast;  contrast--) {
                f = 1.0f - (1.0f - f) * (1.0f - f);
            }
            int v = (int)(f * 255.0 + 0.5);
            conv[i] = (v > 255) ? 255 : (v < 0) ? 0 : (uint8_t) v;
        }
        f = fopen("bluenoise_energy_lut.pgm", "wb");
        fprintf(f, "P5\n%d %d\n255\n", SIZE*2, SIZE*2);
        fwrite(conv, SIZE*2, SIZE*2, f);
        fclose(f);
    }
    #endif

    // set initial points
    while (state->points < (AREA / INITIAL_POINT_DENSITY)) {
        int i = XY2I(rand() & XY_MASK, rand() & XY_MASK);
        if (!BMP_GET(i)) {
            BMP_SET(i);  update_map(i, +1.0f);
            ++state->points;
        }
    }
    printf("set %d initial points\n", state->points);

    // re-distribute initial points
    int redist = 0;
    int last_point = AREA;
    while (state->imax != last_point) {
        BMP_CLR(state->imax);  update_map(state->imax, -1.0f);
        last_point = state->imin;
        BMP_SET(state->imin);  update_map(state->imin, +1.0f);
        ++redist;
    }
    printf("re-distributed initial points %d times\n", redist);

    // serialize initial points
    memcpy(&state2, &state1, sizeof(struct map_state));
    while (state->points) {
        noise[state->imax] = (--state->points) >> POINT_SHIFT;
        BMP_CLR(state->imax);  update_map(state->imax, -1.0f);
    }
    state = &state2;

    // create points until half full
    while (state->points < (AREA / 2)) {
        noise[state->imin] = (state->points++) >> POINT_SHIFT;
        BMP_SET(state->imin);  update_map(state->imin, +1.0f);
    }
    printf("filled to %d points\n", state->points);

    // invert energy map
    for (int i = 0;  i < (AREA / 32);  ++i) {
        state->bitmap[i] ^= (uint32_t)(-1);
    }
    memset(state->emap, 0, sizeof(state->emap));
    for (int i = 0;  i < AREA;  ++i) {
        if (BMP_GET(i)) { update_map(i, +1.0f); }
    }
    printf("inverted energy map\n");

    // create points until full
    while (state->points < (255 << POINT_SHIFT)) {
        noise[state->imax] = (state->points++) >> POINT_SHIFT;
        BMP_CLR(state->imax);  update_map(state->imax, -1.0f);
    }
    printf("filled to %d points\n", state->points);

    // debug: dump energy map
    #if 0
    {
        uint8_t conv[(SIZE * 2) * SIZE];
        float scale = 0.0f;
        for (int i = 0;  i < AREA;  ++i) {
            if (state->emap[i] > scale) { scale = state->emap[i]; }
        }
        printf("max energy in map: %g\n", scale);
        scale = 255.0f / scale;
        for (int i = 0;  i < AREA;  ++i) {
            int v = (int)(state->emap[i] * scale);
            conv[i] = (v > 255) ? 255 : (v < 0) ? 0 : (uint8_t) v;
        }
        f = fopen("bluenoise_energy_map.pgm", "wb");
        fprintf(f, "P5\n%d %d\n255\n", SIZE, SIZE);
        fwrite(conv, SIZE, SIZE, f);
        fclose(f);
    }
    #endif

    // write noise image
    //f = fopen("bluenoise.pgm", "wb");
    //fprintf(f, "P5\n%d %d\n255\n", SIZE, SIZE);
    //fwrite(noise, SIZE, SIZE, f);
    //fclose(f);
    
    std::vector<uint8_t> data;
    //data.resize(SIZE*SIZE);
    
  	 for(int x = 0; x < SIZE; x++)
  	 {
  	 	for(int y = 0; y < SIZE; y++)
  	 	{
  	 		data.push_back(noise[0+x*SIZE+y]);
  	 	}
  	 }
  	 
    return data;
}

#endif
