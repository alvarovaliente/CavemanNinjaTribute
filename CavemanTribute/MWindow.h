#ifndef __MWINDOW_H__
#define __MWINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class MWindow : public Module
{
public:

	MWindow();
	virtual ~MWindow();
	bool Init();
	bool CleanUp();

public:
	
	SDL_Window* window = nullptr;
	SDL_Surface* screen_surface = nullptr;
};

#endif // __MWINDOW_H__