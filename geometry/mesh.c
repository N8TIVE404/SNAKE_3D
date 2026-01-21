#include <glad/glad.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"
#include "mesh.h"
#include "primitives.h"
#include "textures.h"

Mesh setup_cube() {
  Cube cube;
  cube.vertexCount = 24;
  cube.indexCount = 36;
  cube.textureCount = 1;

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

  cube.textures = malloc(sizeof(Texture) * cube.textureCount);
  for (int i = 0; i < cube.textureCount; i++) {
    cube.textures[i] = load_texture("../assets/textures", "textureimage.jpg");
  }

  memcpy(cube.indices, cubeIndices, sizeof(unsigned int) * 36);

  GLuint vao, vbo, ebo;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);

  glBindVertexArray(vao);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cube.indexCount,
               cube.indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cube.vertexCount,
               cube.vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 3));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 6));

  glBindVertexArray(0);

  Mesh mesh;
  mesh.vertices = cube.vertices;
  mesh.indices = cube.indices;
  mesh.textures = cube.textures;
  mesh.textureCount = cube.textureCount;
  mesh.vertexCount = cube.vertexCount;
  mesh.indexCount = cube.indexCount;
  mesh.vao = vao;

  return mesh;
}

Mesh setup_sphere() {
  Sphere sphere = populate_sphere(30, 15);
  INFO_LOG("Created a sphere with %zu vertices, %zu indices and %zu textures.",
           sphere.vertexCount, sphere.indexCount, sphere.textureCount);

  GLuint vao, vbo, ebo;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * sphere.vertexCount,
               sphere.vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * sphere.indexCount, sphere.indices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 3));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(sizeof(float) * 6));

  glBindVertexArray(0);

  Mesh mesh;
  mesh.vertices = sphere.vertices;
  mesh.indices = sphere.indices;
  mesh.textures = sphere.textures;
  mesh.textureCount = sphere.textureCount;
  mesh.vertexCount = sphere.vertexCount;
  mesh.indexCount = sphere.indexCount;
  mesh.vao = vao;

  return mesh;
}
