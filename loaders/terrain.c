#include <glad/glad.h>

#include "camera.h"
#include "primitives.h"
#include "shaders.h"
#include "stb_image.h"
#include "terrain.h"
#include "textures.h"

Terrain load_terrain() {
  Terrain t;
  GLuint shaderProgram =
      create_program("../assets/shaders", "terrain.vert", "terrain.frag");

  t.vertexCount = IMAGE_HEIGHT * IMAGE_WIDTH;
  t.vertices = malloc(sizeof(VertexEntry) * t.vertexCount);
  float yScale = 16.0f;

  for (int i = 0; i < IMAGE_HEIGHT; i++) {
    for (int j = 0; j < IMAGE_WIDTH; j++) {
      int index = i * IMAGE_WIDTH + j;
      t.vertices[index].position[2] = (float)i * GLOBAL_SCALE;
      t.vertices[index].position[1] = 0.0f * GLOBAL_SCALE;
      t.vertices[index].position[0] = (float)j * GLOBAL_SCALE;

      t.vertices[index].texture[0] = (float)i / IMAGE_HEIGHT;
      t.vertices[index].texture[1] = (float)j / IMAGE_WIDTH;
    }
  }

  t.indexCount = (IMAGE_WIDTH - 1) * (IMAGE_HEIGHT - 1) * 6;
  t.indices = malloc(sizeof(unsigned int) * t.indexCount);

  int counter = 0;
  for (int i = 0; i < IMAGE_HEIGHT - 1; i++) {
    for (int j = 0; j < IMAGE_WIDTH - 1; j++) {
      int topLeft = i * IMAGE_WIDTH + j;
      int bottomLeft = (i + 1) * IMAGE_WIDTH + j;
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

  t.textureCount = 1;
  t.textures = malloc((sizeof(Texture)) * t.textureCount);
  t.textures[0] =
      load_texture("../assets/textures/TERRAIN/textures", "forest_ground.jpg");

  glUseProgram(shaderProgram);
  GLuint vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexEntry) * t.vertexCount, t.vertices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * t.indexCount,
               t.indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexEntry),
                        (void *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexEntry),
                        (void *)(3 * sizeof(float)));

  t.vao = vao;
  t.vbo = vbo;
  t.ebo = ebo;
  t.shader = shaderProgram;

  return t;
}

void render_terrain(Terrain *t, Camera *cam, Position *pos, GLuint terrainMvp) {
  glUseProgram(t->shader);
  glBindVertexArray(t->vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, t->textures[0].textureID);
  mat4 mvp;
  glUniformMatrix4fv(terrainMvp, 1, GL_FALSE, (float *)mvp);

  glDrawElements(GL_TRIANGLES, t->indexCount, GL_UNSIGNED_INT, 0);
}
