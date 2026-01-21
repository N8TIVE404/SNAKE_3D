#ifndef MESH_H
#define MESH_H

#include "primitives.h"
#include <cglm/cglm.h>
#include <stddef.h>

struct Vertex;
struct Texture;
typedef struct Mesh {
  struct Vertex *vertices;
  unsigned int *indices;
  struct Texture *textures;
  size_t textureCount, indexCount, vertexCount;
  unsigned int vao;
} Mesh;

Mesh setup_cube();
Mesh setup_sphere();
#endif
