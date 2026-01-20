#include <glad/glad.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"
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

  memcpy(cube.indices, cubeIndices, sizeof(unsigned int) * 36);

  GLuint vao, vbo, ebo;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);

  glBindVertexArray(vao);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube.indices), cube.indices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube.vertices), cube.vertices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 3));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 6));

  cube.vao = vao;
  cube.ebo = ebo;
  cube.vbo = vbo;

  glBindVertexArray(0);

  return cube;
}

void setup_sphere(Sphere *sphere) {
  populate_sphere(sphere, 30, 15);
  INFO_LOG("Created a sphere with %zu vertices and %zu indices.",
           sphere->vertexCount, sphere->indexCount);

  GLuint vao, vbo, ebo;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * sphere->vertexCount,
               sphere->vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * sphere->indexCount, sphere->indices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 3));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 6));

  sphere->vao = vao;
  sphere->vbo = vbo;
  sphere->ebo = ebo;

  glBindVertexArray(0);
}
