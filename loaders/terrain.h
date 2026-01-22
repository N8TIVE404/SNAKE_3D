#ifndef TERRAIN_H
#define TERRAIN_H

#include "camera.h"
#include <cglm/cglm.h>

typedef struct Terrain {
  unsigned int vao, vbo, ebo, shader;
  unsigned int *indices;
  int indexCount;
  vec3 *vertices;
  int vertexCount;
} Terrain;

Terrain load_terrain();

struct Camera;
struct Position;
void render_terrain(Terrain *, struct Camera *, struct Position *,
                    unsigned int);

#endif
