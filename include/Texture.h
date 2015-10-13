#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "Common.h"

GLuint loadTextureFromFile(const string& filename);

GLuint convertSDLSurfaceToTexture(SDL_Surface * surface);

#endif