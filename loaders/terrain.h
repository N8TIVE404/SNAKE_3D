#ifndef TERRAIN_H
#define TERRAIN_H

#include "camera.h"
#include <cglm/cglm.h>

#define IMAGE_HEIGHT 100
#define IMAGE_WIDTH 100

typedef struct VertexEntry {
  vec3 position;
  vec2 texture;
} VertexEntry;

typedef struct Terrain {
  unsigned int vao, vbo, ebo, shader;
  unsigned int *indices;
  int indexCount;
  VertexEntry *vertices;
  int vertexCount;
  struct Texture *textures;
  int textureCount;
} Terrain;

Terrain load_terrain();

struct Camera;
struct Position;
void render_terrain(Terrain *, struct Camera *, struct Position *,
                    unsigned int);

#endif
