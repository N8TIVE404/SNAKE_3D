# include <glad/glad.h>
# include <stdio.h>

# include "models.h"
# include "render.h"
# include "camera.h"
# include "logger.h"
# include "geometry_calculation.h"

const char *textureStrings[] = {
    "DIFFUSE_TEX", "SPECULAR_TEX"
};

void draw_mesh(Camera *cam, Position *pos, Mesh *mesh, GLuint shader){
    DEBUG_LOG("Drawing mesh with VAO: %u, VBO: %u, EBO: %u and Shader: %u. The mesh has %zu vertices and %zu indices.", mesh->vao, mesh->vbo, mesh->ebo, shader, mesh->vertexCount, mesh->indexCount);
    glUseProgram(shader);

    int dCount = 1;
    int sCount = 1;

    for(int i = 0; i < mesh->textureCount; i++){
        glActiveTexture(GL_TEXTURE + i);
        char uniformName[200] = {0};
        if(mesh->textures[i].type == DIFFUSE_TEX)
            snprintf(uniformName, sizeof(uniformName), "%s%u", textureStrings[mesh->textures[i].type], dCount++);
        if(mesh->textures[i].type == SPECULAR_TEX)
            snprintf(uniformName, sizeof(uniformName), "%s%u", textureStrings[mesh->textures[i].type], sCount++);

        GLint uniformLoc = glGetUniformLocation(shader, uniformName);
        if(uniformLoc < 0){
            ERROR_LOG("Unable to get texture uniform location for %s.", uniformName);
        }

        glUniform1i(uniformLoc, i);
        glBindTexture(GL_TEXTURE_2D, mesh->textures[i].textureID);
    }

    GLint viewLoc = glGetUniformLocation(shader, "glView");
    GLint modelLoc = glGetUniformLocation(shader, "glModel");
    GLint projectionLoc = glGetUniformLocation(shader, "glProjection");

    calculate_mvp(cam, pos);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float *)pos->view);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)pos->model);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float *)pos->projection);

    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (void *)0);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);
}
