#version 430
layout( local_size_x = 8, local_size_y = 16, local_size_z = 1 ) in;
layout( binding = 0, rgba8ui ) uniform uimage2D tridentStorage;

uniform vec3 basisX;
uniform vec3 basisY;
uniform vec3 basisZ;

// what to draw at the center
uniform int mode;

#define MAXSTEPS 40
#define MAXDIST 2.5
#define EPSILON 0.001

// version without materials
float SdSmoothMin( float a, float b ) {
	// float k = 0.12;
	float k = 0.1;
	float h = clamp( 0.5 + 0.5 * ( b - a ) / k, 0.0, 1.0 );
	return mix( b, a, h ) - k * h * ( 1.0 - h );
}

// version with materials
float SdSmoothMin( float a, float b, vec3 mtl1, vec3 mtl0, inout vec3 mtl ) {
	// float k = 0.12;
	float k = 0.1;
	float h = clamp( 0.5 + 0.5 * ( b - a ) / k, 0.0, 1.0 );
	float s = mix( b, a, h ) - k * h * ( 1.0 - h );
	float sA = s - a;
	float sB = s - b;
	float r = sA / ( sA + sB );
	mtl = mix( mtl1, mtl0, r );
	return s;
}

float deRoundedCone ( vec3 p, vec3 a, vec3 b ) {
	float r1 = 0.1; // radius at b
	float r2 = 0.02; // radius at a

	vec3  ba = b - a;
	float l2 = dot( ba, ba );
	float rr = r1 - r2;
	float a2 = l2 - rr * rr;
	float il2 = 1.0 / l2;

	vec3 pa = p - a;
	float y = dot( pa, ba );
	float z = y - l2;
	vec3 d2 =  pa * l2 - ba * y;
	float x2 = dot( d2, d2 );
	float y2 = y * y * l2;
	float z2 = z * z * l2;

	float k = sign( rr ) * rr * rr * x2;
	if( sign( z ) * a2 * z2 > k )
		return sqrt( x2 + z2 ) * il2 - r2;
	if( sign( y ) * a2 * y2 < k )
		return sqrt( x2 + y2 ) * il2 - r1;
	return ( sqrt( x2 * a2 * il2 ) + y * rr ) * il2 - r1;
}

float deF ( vec3 p ){
	// float scalar = 6.0;
		float scalar = 4.0;
		mat3 transform = inverse( mat3( basisX, basisY, basisZ ) );
		p = transform * p;

		p *= scalar;
    float a=1.;
    for(int i=0;i<5;i++){ // adjust iteration count here
      p=abs(p)-1./3.;
      if(p.y>p.x)p.xy=p.yx;
      if(p.z>p.y)p.yz=p.zy;
      p.z=abs(p.z);
      p*=3.;
      p-=1.;
      a*=3.;
    }
    return (length(max(abs(p)-1.,0.))/a) / scalar;
 }

// core distance
float cDist ( vec3 p ) {
	switch ( mode ) {
		case 0:	// menger core
			return deF( p );
		case 1: // sphere core
			return distance( vec3( 0.0 ), p ) - 0.18;
		// etc...
	}
}

// with materials
vec4 deMat ( vec3 p ) {
	// return value has .rgb color and .a is distance
	vec4 result = vec4( 1000.0 );
	float x = deRoundedCone( p, vec3( 0.0 ), basisX / 2.0 );
	vec3 xc = vec3( 1.0, 0.0, 0.0 );
	float y = deRoundedCone( p, vec3( 0.0 ), basisY / 2.0 );
	vec3 yc = vec3( 0.0, 1.0, 0.0 );
	float z = deRoundedCone( p, vec3( 0.0 ), basisZ / 2.0 );
	vec3 zc = vec3( 0.0, 0.0, 1.0 );
	float c = cDist( p );
	// vec3 cc = vec3( 0.16 );
	// vec3 cc = vec3( 0.32 );
	vec3 cc = vec3( 0.64 );
	result.a = SdSmoothMin( 1000.0, x, vec3( 0.0 ), xc, result.rgb );
	result.a = SdSmoothMin( result.a, y, result.rgb, yc, result.rgb );
	result.a = SdSmoothMin( result.a, z, result.rgb, zc, result.rgb );
	result.a = SdSmoothMin( result.a, c, result.rgb, cc, result.rgb );
	return result;
}

// without materials
float de ( vec3 p ) {
	float x = deRoundedCone( p, vec3( 0.0 ), basisX / 2.0 );
	float y = deRoundedCone( p, vec3( 0.0 ), basisY / 2.0 );
	float z = deRoundedCone( p, vec3( 0.0 ), basisZ / 2.0 );
	float c = cDist( p );
	return SdSmoothMin( SdSmoothMin( SdSmoothMin( x, y ), z ), c );
}

vec3 normal ( vec3 p ) { // to get the normal vector for a point in space, this function evaluates the gradient of the distance function
#define METHOD 2
#if METHOD == 0
	// tetrahedron version, unknown source - 4 evaluations
	vec2 e = vec2( 1, -1 ) * EPSILON;
	return normalize( e.xyy * de( p + e.xyy ) + e.yyx * de( p + e.yyx ) + e.yxy * de( p + e.yxy ) + e.xxx * de( p + e.xxx ) );
#elif METHOD == 1
	// by iq = more efficient, 4 evaluations
	vec2 e = vec2( EPSILON, 0.0 ); // computes the gradient of the estimator function
	return normalize( vec3( de( p ) ) - vec3( de( p - e.xyy ), de( p - e.yxy ), de( p - e.yyx ) ) );
#elif METHOD == 2
// by iq - less efficient, 6 evaluations
	vec3 eps = vec3( EPSILON, 0.0, 0.0 );
	return normalize( vec3(
		de( p + eps.xyy ) - de( p - eps.xyy ),
		de( p + eps.yxy ) - de( p - eps.yxy ),
		de( p + eps.yyx ) - de( p - eps.yyx ) ) );
#endif
}

float calcAO ( in vec3 pos, in vec3 nor ) {
	float occ = 0.0;
	float sca = 1.0;
	for( int i = 0; i < 5; i++ ) {
		float h = 0.001 + 0.15 * float( i ) / 4.0;
		float d = de( pos + h * nor );
		occ += ( h - d ) * sca;
		sca *= 0.95;
	}
	return clamp( 1.0 - 1.5 * occ, 0.0, 1.0 );
}

void main () {
	ivec2 loc = ivec2( gl_GlobalInvocationID.xy );
	vec2 position = vec2( loc ) / vec2( imageSize( tridentStorage ).xy );
	uvec4 colorResult = uvec4( 0 );

	// ray starting location comes from mapped location on the texture
	position = ( 2.0 * position ) - vec2( 1.0 );
	position.x *= ( float( imageSize( tridentStorage ).x ) / float( imageSize( tridentStorage ).y ) );

	vec3 rayOrigin = vec3( position * 0.55, -1.0 );
	vec3 rayDirection = vec3( 0.0, 0.0, 1.0 );

	float t = 0.1;
	for ( int i = 0; i < MAXSTEPS; i++ ) {
		vec3 p = rayOrigin + t * rayDirection;
		float dist = de( p );
		if ( dist < EPSILON || t > MAXDIST ) {
			break;
		}
		t += dist;
	}

	vec3 hitPoint = rayOrigin + t * rayDirection;
	vec3 surfaceNormal = normal( hitPoint );
	vec4 wCol = deMat( hitPoint ); // albedo + distance

	// go go gadget phong
	vec3 light1Position = vec3( -1.4, -0.8, -0.15 );
	vec3 light2Position = vec3( 1.8, -0.3,  0.25 );
	vec3 eyePosition = vec3( 0.0, 0.0, -1.0 );
	vec3 l1 = normalize( hitPoint - light1Position );
	vec3 l2 = normalize( hitPoint - light2Position );
	vec3 v = normalize( hitPoint - eyePosition );
	vec3 n = normalize( surfaceNormal );
	vec3 r1 = normalize( reflect( l1, n ) );
	vec3 r2 = normalize( reflect( l2, n ) );
	vec3 pixcol = wCol.xyz;
	float ambient = -0.0;
	pixcol += ambient * vec3( 0.1, 0.1, 0.2 );
	float diffuse1 = ( 1.0 / ( pow( 0.25 * distance( hitPoint, light1Position ), 2.0 ) ) ) * 0.18 * max( dot( n,  l1 ), 0.0 );
	float diffuse2 = ( 1.0 / ( pow( 0.25 * distance( hitPoint, light2Position ), 2.0 ) ) ) * 0.18 * max( dot( n,  l2 ), 0.0 );
	pixcol += diffuse1 * vec3( 0.09, 0.09, 0.04 );
	pixcol += diffuse2 * vec3( 0.09, 0.09, 0.04 );
	float specular1 = ( 1.0 / ( pow( 0.25 * distance( hitPoint, light1Position ), 2.0 ) ) ) * 0.4 * pow( max( dot( r1, v), 0.0 ), 60.0 );
	float specular2 = ( 1.0 / ( pow( 0.25 * distance( hitPoint, light2Position ), 2.0 ) ) ) * 0.4 * pow( max( dot( r2, v), 0.0 ), 80.0 );
	if ( dot( n, l1 ) > 0.0 ) pixcol += specular1 * vec3( 0.4, 0.2, 0.0 );
	if ( dot( n, l2 ) > 0.0 ) pixcol += specular2 * vec3( 0.4, 0.2, 0.0 );

	pixcol *= calcAO( hitPoint, surfaceNormal );

	// colorResult = uvec4( uvec3( wCol.rgb * 255 ), wCol.a < ( EPSILON * 5.0 ) ? 255 : 0 );
	colorResult = uvec4( uvec3( pixcol * 255 ), wCol.a < ( EPSILON * 5.0 ) ? 255 : 0 );
	imageStore( tridentStorage, loc, colorResult );
}
