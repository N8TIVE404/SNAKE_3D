#include <cglm/vec3.h>
#include <glad/glad.h>

#include "camera.h"
#include "input.h"
#include "logger.h"
#include "mesh.h"
#include "mvp.h"
#include "primitives.h"
#include "shaders.h"
#include "window.h"

/*
const float triangles[] = {0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
                           0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0};

const unsigned int indices[] = {0, 1, 2, 1, 2, 3};
*/

int main(void) {
  GLFWwindow *window = initilaize_window();

  GLuint shader =
      create_program("../assets/shaders", "shader.vert", "shader.frag");
  INFO_LOG("Created a shader program with ID %d.", shader);
  glUseProgram(shader);
  float lastTime = 0.0f;
  Camera cam = initialize_camera(45.0f, (vec3){0.0f, 0.0f, 3.0f});

  Cube cube = setup_cube();

  glfwSetWindowUserPointer(window, &cam);

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

  glBindVertexArray(0);

  Position pos;
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, pos.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos.axis);
  glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, pos.scale);
  pos.angle = 20.0f;

  GLuint uniformMvp = glGetUniformLocation(shader, "mvp");

  while (!glfwWindowShouldClose(window)) {
    float current = glfwGetTime();
    cam.deltaTime = current - lastTime;
    lastTime = current;

    mat4 mvp;
    calculate_mvp(&cam, &pos, &mvp);
    pos.angle += 1.0f;

    glClearColor(0.6f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(vao);

    glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, (float *)mvp);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    process_kbinput(window);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  INFO_LOG("Destroying window and terminating GLFW...");
  destroy_window(window);

  return 0;
}
