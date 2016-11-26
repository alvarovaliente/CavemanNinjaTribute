#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/include/SDL_rect.h"
#include "SDL/include/SDL.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned __int32 uint32;

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};



// Deletes a buffer
#define RELEASE( x ) \
    { \
       if( x != nullptr ) \
	          { \
         delete x; \
	     x = nullptr; \
	          } \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
		{  \
       if( x != nullptr ) \
	          { \
           delete[] x; \
	       x = nullptr; \
	   		 } \
		 }

// Configuration -----------
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240
#define TILE_WIDTH 20
#define TILE_HEIGHT 20
#define PLAYER_COLLIDER_BODY_HEIGHT 47
#define PLAYER_CROUCH_COLLIDER_BODY_HEIGHT 33
#define PLAYER_COLLIDER_BODY_WIDTH 27
#define GRAVITY 2.4
#define GRAVITY_SMOOTH 1.2
#define PLAYER_JUMP_TIME 350
#define PLAYER_FLYING_TIME 4000
#define PLAYER_NORMAL_SPEED 1.2
#define PLAYER_HIGH_SPEED 3
#define ENEMY_COLLIDER_BODY_WIDTH 35
#define ENEMY_COLLIDER_BODY_HEIGHT 40
#define ENEMY_COLLIDER_FOOT_HEIGHT 2
#define ENEMY_COLLIDER_FOOT_WIDTH 22
#define POTION_COLLIDER_BODY_WIDTH 15
#define POTION_COLLIDER_BODY_HEIGHT 15
#define ENEMY_JUMPING_TIME 200
#define ENEMY_TRAPPED_TIME 3000
#define LEVELFROZENTIME 2000
#define GROUND 280
#define SCREEN_SIZE 3
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Caveman Ninja"

#endif //__GLOBALS_H__