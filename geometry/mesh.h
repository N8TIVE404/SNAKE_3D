#ifndef MESH_H
#define MESH_H

#include "primitives.h"
#include <cglm/cglm.h>

struct Vertex;
typedef struct Mesh {
  struct Vertex *vertices;
  unsigned int *indices;
} Mesh;

Cube setup_cube();

#endif
