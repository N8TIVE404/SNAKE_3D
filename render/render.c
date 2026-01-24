#include "render.h"
#include "camera.h"
#include "camera_system.h"
#include "mesh.h"
#include "primitives.h"
#include "textures.h"
#include <glad/glad.h>

void draw_mesh(Mesh *mesh, Camera *cam, Position *pos, GLuint shader,
               GLuint uniformMvp) {
  glUseProgram(shader);
  glBindVertexArray(mesh->vao);

  mat4 mvp;
  glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, (float *)mvp);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mesh->textures[0].textureID);

  glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void draw_skybox(Skybox *box, Camera *cam, Position *pos, GLuint shader,
                 GLuint uniformView, GLuint uniformProjection) {
  glDepthMask(GL_FALSE);

  glUseProgram(shader);
  glBindVertexArray(box->vao);
  glActiveTexture(GL_TEXTURE10);
  glBindTexture(GL_TEXTURE_CUBE_MAP, box->textures[0].textureID);

  mat4 skyboxView;
  camera_build_skybox_view(cam, skyboxView);
  glUniformMatrix4fv(uniformView, 1, GL_FALSE, (float *)skyboxView);
  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, (float *)pos->projection);

  glDrawArrays(GL_TRIANGLES, 0, box->vertexCount);

  glDepthMask(GL_TRUE);
  glBindVertexArray(0);
}
