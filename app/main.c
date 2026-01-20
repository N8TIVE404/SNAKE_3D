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

int main(void) {
  GLFWwindow *window = initilaize_window();

  GLuint shader =
      create_program("../assets/shaders", "shader.vert", "shader.frag");
  INFO_LOG("Created a shader program with ID %d.", shader);
  glUseProgram(shader);
  float lastTime = 0.0f;
  Camera cam = initialize_camera(45.0f, (vec3){0.0f, 0.0f, 3.0f});

  Cube cube = setup_cube();
  Sphere sphere;
  setup_sphere(&sphere);

  glfwSetWindowUserPointer(window, &cam);

  Position pos;
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, pos.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos.axis);
  glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, pos.scale);
  pos.angle = 20.0f;

  Position pos2;
  glm_vec3_copy((vec3){1.0f, 1.0f, 0.0f}, pos2.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos2.axis);
  glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, pos2.scale);
  pos2.angle = 20.0f;

  GLuint uniformMvp = glGetUniformLocation(shader, "mvp");
  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    float current = glfwGetTime();
    cam.deltaTime = current - lastTime;
    lastTime = current;

    glClearColor(0.6f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(sphere.vao);

    mat4 mvp;
    calculate_mvp(&cam, &pos2, &mvp);
    pos2.angle += 1.0f;

    glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, (float *)mvp);

    glDrawElements(GL_TRIANGLES, (int)sphere.indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(cube.vao);
    glm_mat4_identity(mvp);
    calculate_mvp(&cam, &pos, &mvp);
    pos2.angle += 2.0f;

    glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, (float *)mvp);

    glDrawElements(GL_TRIANGLES, (int)cube.indexCount, GL_UNSIGNED_INT, 0);

    process_kbinput(window);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  INFO_LOG("Destroying window and terminating GLFW...");
  destroy_window(window);
  free(sphere.vertices);
  free(sphere.indices);

  return 0;
}
