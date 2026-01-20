#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cglm/cglm.h>
#include <stddef.h>
#include <stdlib.h>

#define LOCATION_COMPONENTS 3

extern const float cubeVertices[];
extern const size_t verticesSize;
extern const size_t vertexCount;

extern unsigned int cubeIndices[];
extern const size_t indicesSize;
extern size_t indexCount;

extern const float cubeLocations[][LOCATION_COMPONENTS];

typedef struct Vertex {
  vec3 position;
  vec3 normal;
  vec2 textureCoordinates;
} Vertex;

typedef struct Cube {
  size_t vertexCount;
  size_t indexCount;
  Vertex vertices[24];
  unsigned int indices[36];
} Cube;

#endif
