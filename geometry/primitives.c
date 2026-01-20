#include "primitives.h"

const float cubeVertices[] = {
    // ---- Front face (Z+) ----
    -0.5f,
    -0.5f,
    0.5f,
    0,
    0,
    1,
    0,
    0,
    0.5f,
    -0.5f,
    0.5f,
    0,
    0,
    1,
    1,
    0,
    0.5f,
    0.5f,
    0.5f,
    0,
    0,
    1,
    1,
    1,
    -0.5f,
    0.5f,
    0.5f,
    0,
    0,
    1,
    0,
    1,
    // ---- Back face (Z-) ----
    0.5f,
    -0.5f,
    -0.5f,
    0,
    0,
    -1,
    0,
    0,
    -0.5f,
    -0.5f,
    -0.5f,
    0,
    0,
    -1,
    1,
    0,
    -0.5f,
    0.5f,
    -0.5f,
    0,
    0,
    -1,
    1,
    1,
    0.5f,
    0.5f,
    -0.5f,
    0,
    0,
    -1,
    0,
    1,

    // ---- Left face (X-) ----
    -0.5f,
    -0.5f,
    -0.5f,
    -1,
    0,
    0,
    0,
    0,
    -0.5f,
    -0.5f,
    0.5f,
    -1,
    0,
    0,
    1,
    0,
    -0.5f,
    0.5f,
    0.5f,
    -1,
    0,
    0,
    1,
    1,
    -0.5f,
    0.5f,
    -0.5f,
    -1,
    0,
    0,
    0,
    1,

    // ---- Right face (X+) ----
    0.5f,
    -0.5f,
    0.5f,
    1,
    0,
    0,
    0,
    0,
    0.5f,
    -0.5f,
    -0.5f,
    1,
    0,
    0,
    1,
    0,
    0.5f,
    0.5f,
    -0.5f,
    1,
    0,
    0,
    1,
    1,
    0.5f,
    0.5f,
    0.5f,
    1,
    0,
    0,
    0,
    1,

    // ---- Bottom face (Y-) ----
    -0.5f,
    -0.5f,
    -0.5f,
    0,
    -1,
    0,
    0,
    0,
    0.5f,
    -0.5f,
    -0.5f,
    0,
    -1,
    0,
    1,
    0,
    0.5f,
    -0.5f,
    0.5f,
    0,
    -1,
    0,
    1,
    1,
    -0.5f,
    -0.5f,
    0.5f,
    0,
    -1,
    0,
    0,
    1,

    // ---- Top face (Y+) ----
    -0.5f,
    0.5f,
    0.5f,
    0,
    1,
    0,
    0,
    0,
    0.5f,
    0.5f,
    0.5f,
    0,
    1,
    0,
    1,
    0,
    0.5f,
    0.5f,
    -0.5f,
    0,
    1,
    0,
    1,
    1,
    -0.5f,
    0.5f,
    -0.5f,
    0,
    1,
    0,
    0,
    1,
};

const size_t verticesSize = sizeof(cubeVertices);
const size_t vertexCount = 24;

unsigned int cubeIndices[] = {
    0,  1,  2,  2,  3,  0,  // Front
    4,  5,  6,  6,  7,  4,  // Back
    8,  9,  10, 10, 11, 8,  // Left
    12, 13, 14, 14, 15, 12, // Right
    16, 17, 18, 18, 19, 16, // Bottom
    20, 21, 22, 22, 23, 20  // Top
};

const size_t indicesSize = sizeof(cubeIndices);
size_t indexCount = 36;

static size_t generate_vertices(Vertex *vertices, int sectors, int stacks) {
  float stackAngle, sectorAngle, xy;
  float r = 1.0f;
  float lengthInv = 1.0f / r;
  float cStack = PI / stacks;
  float cSector = (2 * PI) / sectors;
  size_t current = 0;

  for (int i = 0; i <= stacks; i++) {
    stackAngle = (PI / 2) - (i * cStack);
    xy = r * cosf(stackAngle);

    for (int j = 0; j <= sectors; j++) {
      sectorAngle = j * cSector;

      // Set the vertices
      vertices[current].position[0] = xy * cosf(sectorAngle);
      vertices[current].position[1] = xy * sinf(sectorAngle);
      vertices[current].position[2] = r * sinf(stackAngle);

      vertices[current].normal[0] = vertices[current].position[0] / lengthInv;
      vertices[current].normal[1] = vertices[current].position[1] / lengthInv;
      vertices[current].normal[2] = vertices[current].position[2] / lengthInv;

      vertices[current].textureCoordinates[0] = (float)j / sectors;
      vertices[current].textureCoordinates[1] = (float)i / stacks;
      current++;
    }
  }

  return current;
}

static size_t generate_indices(unsigned int *indices, int sectors, int stacks) {
  size_t current = 0;
  int k1, k2;

  for (int i = 0; i < stacks; i++) {
    k1 = i * (sectors + 1);
    k2 = k1 + (sectors + 1);

    for (int j = 0; j < sectors; j++, k1++, k2++) {
      if (i != 0) {
        indices[current++] = k1;
        indices[current++] = k2;
        indices[current++] = k1 + 1;
      }

      if (i != (stacks - 1)) {
        indices[current++] = k1 + 1;
        indices[current++] = k2;
        indices[current++] = k2 + 1;
      }
    }
  }

  return current;
}

void populate_sphere(Sphere *sphere, int sectors, int stacks) {
  unsigned int vertexCount = (sectors + 1) * (stacks + 1);
  unsigned int indexCount = sectors * stacks * 6;

  sphere->vertices = malloc(vertexCount * sizeof(Vertex));
  sphere->indices = malloc(sizeof(unsigned int) * indexCount);
  sphere->vertexCount = generate_vertices(sphere->vertices, sectors, stacks);
  sphere->indexCount = generate_indices(sphere->indices, sectors, stacks);
}
