#include <cglm/vec3.h>
#include <glad/glad.h>

#include "camera.h"
#include "logger.h"
#include "mvp.h"
#include "shaders.h"
#include "window.h"

const float triangle[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0};

const unsigned int indices[] = {0, 1, 2, 1, 2, 3};

int main(void) {
  GLFWwindow *window = initilaize_window();

  GLuint shader =
      create_program("../assets/shaders", "shader.vert", "shader.frag");
  INFO_LOG("Created a shader program with ID %d.", shader);

  Position cameraPosition;
  glm_vec3_copy((vec3){0.0f, 0.0f, 3.0f}, (float *)cameraPosition.projection);
  Camera cam = initilaize_camera(45.0f, &cameraPosition);

  Position pos;
  glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, pos.scale);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos.axis);
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, pos.location);
  pos.angle = 20.0f;

  GLuint vao, vbo, ebo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
  glEnableVertexAttribArray(0);

  glUseProgram(shader);
  GLuint uniformMvp = glGetUniformLocation(shader, "mvp");

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.2f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(vao);

    mat4 mvp;

    calculate_mvp(&cam, &pos, &mvp);
    DEBUG_LOG("Translation vector: %.2f %.2f %.2f", pos.location[0],
              pos.location[1], pos.location[2]);
    glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, (float *)mvp);

    pos.angle += 0.1f;

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  INFO_LOG("Destroying window and terminating GLFW...");
  destroy_window(window);

  return 0;
}
