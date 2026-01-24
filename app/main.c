#include <cglm/vec3.h>
#include <glad/glad.h>

#include "camera.h"
#include "logger.h"
#include "mesh.h"
#include "primitives.h"
#include "render.h"
#include "shaders.h"
#include "terrain.h"
#include "window.h"

int main(void) {
  GLFWwindow *window = initilaize_window();
  INFO_LOG("Created window successfully and initilaized GLFW.");

  Camera cam;
  initialize_camera(&cam, glm_rad(45.0f), (float)width / (float)height, 1.0f,
                    10000.0f, (vec3){10.0f, 5.0f, 5.0f});
  INFO_LOG("Initialized camera successfully.");
  glfwSetWindowUserPointer(window, &cam);

  GLuint shader =
      create_program("../assets/shaders", "shader.vert", "shader.frag");
  INFO_LOG("Created a shader program with ID %d.", shader);

  GLuint boxShader =
      create_program("../assets/shaders", "skybox.vert", "skybox.frag");
  INFO_LOG("Created a shader program with ID %d.", boxShader);

  float lastTime = 0.0f;

  Terrain terrain = load_terrain();
  Position base = {.scale = {1.0f, 1.0f, 1.0f},
                   .angle = 0.0f,
                   .location = {0.0f, 0.0f, -75.0f},
                   .axis = {1.0f, 0.0f, 1.0f}};
  glm_mat4_identity(base.projection);
  glm_mat4_identity(base.model);
  glm_mat4_identity(base.view);

  INFO_LOG("Loaded terrain successfully.");

  glUseProgram(terrain.shader);
  GLuint terrainMvp = glGetUniformLocation(terrain.shader, "mvp");

  Mesh cube = setup_cube();
  Position pos;
  glm_vec3_copy((vec3){25.0f, 25.0f, -10.0f}, pos.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos.axis);
  glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, pos.scale);
  pos.angle = 20.0f;

  Mesh sphere = setup_sphere();
  Position pos2;
  glm_vec3_copy((vec3){21.0f, 20.0f, -10.0f}, pos2.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, pos2.axis);
  glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, pos2.scale);
  pos2.angle = 20.0f;

  Skybox box = setup_skybox(boxShader);
  Position boxPos;
  glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, boxPos.location);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, boxPos.axis);
  glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, boxPos.scale);
  glm_mat4_identity(boxPos.view);
  glm_mat4_identity(boxPos.projection);

  INFO_LOG("Setup skybox successfully.");

  glUseProgram(shader);
  GLuint uniformMvp = glGetUniformLocation(shader, "mvp");
  GLuint uniformTex = glGetUniformLocation(shader, "tex");
  glUniform1i(uniformTex, 0);

  glUseProgram(boxShader);
  GLuint uniformCubeSampler = glGetUniformLocation(boxShader, "cubeSampler");
  GLuint uniformView = glGetUniformLocation(boxShader, "view");
  GLuint uniformProjection = glGetUniformLocation(boxShader, "projection");

  glUniform1i(uniformCubeSampler, 10);

  glEnable(GL_DEPTH_TEST);
  INFO_LOG("Enabled depth testing.");

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.6f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_skybox(&box, &cam, &boxPos, boxShader, uniformView, uniformProjection);

    draw_mesh(&cube, &cam, &pos2, shader, uniformMvp);
    pos2.angle += 1.0f;

    draw_mesh(&sphere, &cam, &pos, shader, uniformMvp);
    pos.angle += 1.0f;

    render_terrain(&terrain, &cam, &base, terrainMvp);

    //    process_kbinput(window);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  INFO_LOG("Destroying window and terminating GLFW...");
  destroy_window(window);
  free(sphere.vertices);
  free(sphere.indices);
  free(terrain.vertices);
  free(terrain.indices);
  free(terrain.textures);

  return 0;
}
