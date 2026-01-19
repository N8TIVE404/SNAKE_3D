#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"
#include "mesh.h"
#include "primitives.h"

#define CUBE_VERTEX_COUNT 24

PrimitiveDefinition setup_cube() {
  PrimitiveDefinition cube;

  cube.vertices = malloc(sizeof(float) * CUBE_VERTEX_COUNT * 8);
  if (!cube.vertices) {
    FATAL_LOG("Failed to allocate vertex buffer for cube!");
    _exit(EXIT_FAILURE);
  }
  cube.indices = malloc(sizeof(uint) * indexCount);

  int offset = 8;
  for (int i = 0; i < CUBE_VERTEX_COUNT; i++) {
    cube.vertices[i].position[0] = cubeVertices[offset * i + 0];
    cube.vertices[i].position[1] = cubeVertices[offset * i + 1];
    cube.vertices[i].position[2] = cubeVertices[offset * i + 2];

    cube.vertices[i].normal[0] = cubeVertices[offset * i + 3];
    cube.vertices[i].normal[1] = cubeVertices[offset * i + 4];
    cube.vertices[i].normal[2] = cubeVertices[offset * i + 5];

    cube.vertices[i].textureCoordinates[0] = cubeVertices[offset * i + 6];
    cube.vertices[i].textureCoordinates[1] = cubeVertices[offset * i + 7];
  }

  cube.vertexCount = CUBE_VERTEX_COUNT;
  memcpy(cube.indices, cubeIndices, sizeof(*cubeIndices));
  cube.indexCount = indexCount;

  return cube;
}
