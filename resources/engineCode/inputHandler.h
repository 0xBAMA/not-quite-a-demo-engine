#ifndef INPUT_H
#define INPUT_H
#include "includes.h"


enum class keyState {
	KEYDOWN,
	HELD,
	KEYUP,
	UNPRESSED
};

// this is not really working as of yet, tbd
class inputHandler {
public:
	inputHandler () {
		const uint8_t * state = SDL_GetKeyboardState( &numKeys ); (void)state;
		previousState = ( uint8_t * ) malloc( numKeys );
		currentState = ( uint8_t * ) malloc( numKeys );
		Update(); // some ineffiency here, deleting previousState immediately
	} // but it's only once on startup, so probably not a huge concern

	void Update () {
		// currentState becomes previousState
		delete( previousState );
		previousState = currentState;
		// get new state and memcpy to new currentState array
		SDL_PumpEvents();
		const uint8_t * state = SDL_GetKeyboardState( NULL );
		currentState = ( uint8_t * ) malloc( numKeys );
		memcpy( ( void * ) state, currentState, numKeys );
	}

	keyState GetKeystate ( SDL_Scancode key ) {
		if ( currentState[ key ] && !previousState[ key ] ) {
			return keyState::KEYDOWN;
		} else if ( currentState[ key ] && previousState[ key ] ) {
			return keyState::HELD;
		} else if ( !currentState[ key ] && previousState[ key ] ) {
			return keyState::KEYUP;
		} else {
			return keyState::UNPRESSED;
		}
	}

	// TODO: mouse button handling with SDL_GetMouseState()

	int numKeys;
private:
	uint8_t * previousState	= nullptr;
	uint8_t * currentState	= nullptr;
};

#endif
