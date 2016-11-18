#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class MRender : public Module
{
public:
	MRender();
	~MRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // __MRENDER_H__