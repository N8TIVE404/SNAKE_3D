#include <string.h>
#include <unistd.h>

#include "mesh.h"
#include "primitives.h"

Cube setup_cube() {
  Cube cube;
  cube.vertexCount = 24;
  cube.indexCount = 36;

  int offset = 8;
  for (int i = 0; i < cube.vertexCount; i++) {
    cube.vertices[i].position[0] = cubeVertices[offset * i + 0];
    cube.vertices[i].position[1] = cubeVertices[offset * i + 1];
    cube.vertices[i].position[2] = cubeVertices[offset * i + 2];

    cube.vertices[i].normal[0] = cubeVertices[offset * i + 3];
    cube.vertices[i].normal[1] = cubeVertices[offset * i + 4];
    cube.vertices[i].normal[2] = cubeVertices[offset * i + 5];

    cube.vertices[i].textureCoordinates[0] = cubeVertices[offset * i + 6];
    cube.vertices[i].textureCoordinates[1] = cubeVertices[offset * i + 7];
  }

  memcpy(cube.indices, cubeIndices, sizeof(unsigned int) * cube.indexCount);

  return cube;
}
