#include <glad/glad.h>

#include "camera.h"
#include "mvp.h"
#include "shaders.h"
#include "stb_image.h"
#include "terrain.h"

Terrain load_terrain() {
  Terrain t;
  int imgWidth, imgHeight, nChannels;
  unsigned char *fileData = stbi_load("../assets/heightmaps/heightmap.png",
                                      &imgWidth, &imgHeight, &nChannels, 0);

  GLuint shaderProgram =
      create_program("../assets/shaders", "terrain.vert", "terrain.frag");

  t.vertexCount = imgHeight * imgWidth;
  t.vertices = malloc(sizeof(float) * t.vertexCount * 3);
  float yScale = 164.0f;

  for (int i = 0; i < imgHeight; i++) {
    for (int j = 0; j < imgWidth; j++) {
      int index = i * imgWidth + j;
      t.vertices[index][2] = (float)i;
      t.vertices[index][1] =
          ((float)fileData[index * nChannels] / 255.0f) * yScale;
      t.vertices[index][0] = (float)j;
    }
  }

  t.indexCount = (imgWidth - 1) * (imgHeight * 1) * 6;
  t.indices = malloc(sizeof(unsigned int) * t.indexCount);

  int counter = 0;
  for (int i = 0; i < imgHeight - 1; i++) {
    for (int j = 0; j < imgWidth - 1; j++) {
      int topLeft = i * imgWidth + j;
      int bottomLeft = (i + 1) * imgWidth + j;
      int topRight = topLeft + 1;
      int bottomRight = bottomLeft + 1;

      t.indices[counter++] = topLeft;
      t.indices[counter++] = bottomLeft;
      t.indices[counter++] = topRight;

      t.indices[counter++] = topRight;
      t.indices[counter++] = bottomLeft;
      t.indices[counter++] = bottomRight;
    }
  }

  glUseProgram(shaderProgram);
  GLuint vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.vertexCount * 3, t.vertices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * t.indexCount,
               t.indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void *)0);

  t.vao = vao;
  t.vbo = vbo;
  t.ebo = ebo;
  t.shader = shaderProgram;

  stbi_image_free(fileData);

  return t;
}

void render_terrain(Terrain *t, Camera *cam, Position *pos, GLuint terrainMvp) {
  glUseProgram(t->shader);
  glBindVertexArray(t->vao);

  mat4 mvp;
  calculate_mvp(cam, pos, &mvp);
  glUniformMatrix4fv(terrainMvp, 1, GL_FALSE, (float *)mvp);

  glDrawElements(GL_TRIANGLES, t->indexCount, GL_UNSIGNED_INT, 0);
}
