# include <glad/glad.h>

# include "models.h"
# include "textures.h"
# include "logger.h"

void setup_mesh(Mesh *mesh){
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexEntry) * mesh->vertexCount, mesh->vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &mesh->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->indexCount, mesh->indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexEntry), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexEntry), (void *)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexEntry), (void *)(sizeof(float) * 6));
    glBindVertexArray(0);
}

Mesh sphere_mesh(int sectors, int stacks, const char *path){
    Mesh mesh;
    Sphere s = generate_sphere(sectors, stacks);
    mesh.indexCount = s.indexCount;
    mesh.vertexCount = s.vertexCount;
    mesh.indices = s.indices;
    mesh.vertices = s.vertices;
    mesh.textureCount = 1;
    mesh.textures = malloc(sizeof(Texture) * 1);
    mesh.textures[0].textureID = load_texture("../assets/sphere", path);
    mesh.textures[0].type = DIFFUSE_TEX;

    INFO_LOG("Setting up sphere mesh...");
    setup_mesh(&mesh);
    INFO_LOG("Sphere mesh set up.");

    return mesh;
}


