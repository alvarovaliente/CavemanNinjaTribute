#ifndef __MTEXTURES_H__
#define __MTEXTURES_H__

#include<list>
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class MTextures : public Module
{
public:
	MTextures();
	~MTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __MTEXTURES_H__