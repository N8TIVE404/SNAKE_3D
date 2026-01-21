#ifndef TEXTURES_H
#define TEXTURES_H

typedef struct Texture {
  unsigned int textureID;
} Texture;

Texture load_texture(const char *, const char *);
Texture load_cubemap(const char *);
#endif
