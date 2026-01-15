# ifndef MODELS_H
# define MODELS_H

# include <stdint.h>
# include <stdlib.h>

# include "primitives.h"

typedef enum{
    DIFFUSE_TEX, SPECULAR_TEX, TEXTURE_TYPE_COUNT
} TextureType;

typedef struct Texture{
    unsigned int textureID;
    TextureType type;
    char *name;
} Texture;

typedef struct Mesh{
    VertexEntry *vertices;
    unsigned int *indices;
    Texture *textures;
    size_t vertexCount;
    size_t indexCount;
    size_t textureCount;
    uint32_t hash;
    unsigned int vao, vbo, ebo;
} Mesh;

typedef struct Position{
    vec3 location;
    vec3 axis;
    vec3 scale;
    mat4 view, model, projection;
} Position;

void setup_mesh(Mesh*);
Mesh sphere_mesh(int, int, const char*);

# endif
