#include "render.h"
#include "camera.h"
#include "mesh.h"
#include "mvp.h"
#include "primitives.h"
#include "textures.h"
#include <glad/glad.h>

void draw_mesh(Mesh *mesh, Camera *cam, Position *pos, GLuint shader,
               GLuint uniformMvp) {
  glUseProgram(shader);
  glBindVertexArray(mesh->vao);

  mat4 mvp;
  calculate_mvp(cam, pos, &mvp);

  glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, (float *)mvp);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mesh->textures[0].textureID);

  glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
}

void draw_skybox(Skybox *box, Camera *cam, Position *pos, GLuint shader,
                 GLuint uniformView, GLuint uniformProjection) {
  glDepthMask(GL_FALSE);

  glUseProgram(shader);
  glBindVertexArray(box->vao);
  glActiveTexture(GL_TEXTURE10);
  glBindTexture(GL_TEXTURE_CUBE_MAP, box->textures[0].textureID);

  mat4 viewNoTrans;
  glm_mat4_copy(pos->view, viewNoTrans);

  // Zero out the translation column (index 3)
  viewNoTrans[3][0] = 0.0f;
  viewNoTrans[3][1] = 0.0f;
  viewNoTrans[3][2] = 0.0f;

  glUniformMatrix4fv(uniformView, 1, GL_FALSE, (float *)viewNoTrans);
  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, (float *)pos->projection);

  glDrawArrays(GL_TRIANGLES, 0, box->vertexCount);

  glDepthMask(GL_TRUE);
  glBindVertexArray(0);
}
