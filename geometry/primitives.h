#ifndef PRIMITIVES_H
#define PRIMITIVES_H

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

struct Vertex;
typedef struct PrimitiveDefinition {
  size_t vertexCount;
  size_t indexCount;
  struct Vertex *vertices;
  unsigned int *indices;
} PrimitiveDefinition;

#endif
