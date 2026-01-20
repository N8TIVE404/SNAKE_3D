#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <cglm/cglm.h>
#include <stddef.h>
#include <stdlib.h>

#define LOCATION_COMPONENTS 3
#define PI 3.14159265358979323846

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
  Vertex vertices[24];
  size_t vertexCount;
  unsigned int indices[36];
  size_t indexCount;
  unsigned int vao, ebo, vbo;
} Cube;

typedef struct Sphere {
  Vertex *vertices;
  size_t vertexCount;
  unsigned int *indices;
  size_t indexCount;
  unsigned int vao, vbo, ebo;
} Sphere;

void populate_sphere(Sphere *, int, int);

#endif
