#ifndef MESH_H
#define MESH_H

#include "primitives.h"
#include <cglm/cglm.h>

typedef struct Vertex {
  vec3 position;
  vec3 normal;
  vec2 textureCoordinates;
} Vertex;

typedef struct Mesh {
  Vertex *vertices;
  unsigned int *indices;
} Mesh;

PrimitiveDefinition setup_cube();

#endif
