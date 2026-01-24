#include "primitives.h"
#include "textures.h"
#include <glad/glad.h>
#include <string.h>

// Cube co-ordinates
const float cubeVertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, // 0
    0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f, // 1
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, // 2
    -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f, // 3

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // 4
    0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // 5
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // 6
    -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // 7

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, // 8
    -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, // 9
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, // 10
    -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, // 11

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // 12
    0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // 13
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // 14
    0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // 15

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, // 16
    0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f, // 17
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, // 18
    -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, // 19

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // 20
    0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // 21
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // 22
    -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f  // 23
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

// Texture co-ordinates for the skybox cubemap
const float skyboxVertices[] = {
    // Positions
    -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
    1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

    -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
    -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

    1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
    1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f};

const size_t skyboxVertexCount = 108;

Skybox setup_skybox(GLuint shader) {
  Skybox box;
  box.vertices = malloc(sizeof(float) * skyboxVertexCount);
  box.textures = malloc(sizeof(Texture));

  memcpy(box.vertices, skyboxVertices, sizeof(skyboxVertices));

  glUseProgram(shader);

  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), box.vertices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

  box.vao = vao;
  box.vertexCount = 36;
  box.textures[0] = load_cubemap("../assets/textures/SKYBOX/clear_sky/");

  glBindVertexArray(0);

  return box;
}
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
      vertices[current].position[0] = xy * cosf(sectorAngle) * GLOBAL_SCALE;
      vertices[current].position[1] = xy * sinf(sectorAngle) * GLOBAL_SCALE;
      vertices[current].position[2] = r * sinf(stackAngle) * GLOBAL_SCALE;

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

Sphere populate_sphere(int sectors, int stacks) {
  Sphere sphere;
  unsigned int vertexCount = (sectors + 1) * (stacks + 1);
  unsigned int indexCount = sectors * stacks * 6;
  sphere.textureCount = 1;

  sphere.vertices = malloc(vertexCount * sizeof(Vertex));
  sphere.indices = malloc(sizeof(unsigned int) * indexCount);
  sphere.textures = malloc(sizeof(Texture) * sphere.textureCount);
  sphere.vertexCount = generate_vertices(sphere.vertices, sectors, stacks);
  sphere.indexCount = generate_indices(sphere.indices, sectors, stacks);

  for (int i = 0; i < sphere.textureCount; i++) {
    sphere.textures[i] = load_texture("../assets/textures", "textureimage.jpg");
  }

  return sphere;
}
