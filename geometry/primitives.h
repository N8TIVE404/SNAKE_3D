# ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include <stdint.h>
# include <cglm/cglm.h>

# define PI 3.1415926536

typedef struct{
    vec3 position;
    vec3 normals;
    vec2 textureCoordinates;
} VertexEntry;

typedef struct{
    VertexEntry *vertices;
    size_t vertexCount;
    unsigned int *indices;
    size_t indexCount;
    uint32_t hash;
} Sphere;

Sphere generate_sphere(int, int);

# endif
