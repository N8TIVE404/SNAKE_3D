# include <math.h>

# include "primitives.h"
# include "logger.h"

Sphere generate_sphere(int sectors, int stacks){
    Sphere s;
    size_t maxVertices = (sectors + 1) * (stacks + 1);
    s.vertices = malloc(sizeof(VertexEntry) * maxVertices);
    size_t maxIndex = sectors * stacks * 6;
    s.indices = malloc(sizeof(unsigned int) * maxIndex);

    float r = 0.5f;
    float cStack = PI / stacks;
    float cSector = 2 * PI / sectors;
    float sectorAngle, stackAngle;
    float lengthInverse = 1.0f / r;
    float xy;
    size_t vertexCount = 0;

    for(int i = 0; i <= stacks; i++){
        stackAngle = (PI / 2) - (i - cStack);
        xy = r * cosf(stackAngle);

        for(int j = 0; j <= sectors; j++){
            sectorAngle = j * cSector;
            s.vertices[vertexCount].position[0] = xy * cosf(sectorAngle);
            s.vertices[vertexCount].position[1] = xy * sinf(sectorAngle);
            s.vertices[vertexCount].position[2] = r * sinf(stackAngle);

            s.vertices[vertexCount].normals[0] = s.vertices[vertexCount].position[0] * lengthInverse;
            s.vertices[vertexCount].normals[1] = s.vertices[vertexCount].position[1] * lengthInverse;
            s.vertices[vertexCount].normals[2] = s.vertices[vertexCount].position[2] * lengthInverse;
            float s = (float)j / sectors;
            float t = (float)i / stacks;
            
            vertexCount++;
        }
    }

    size_t indexCount = 0;
    int k1, k2;
    for(int i = 0; i < stacks; ++i){
        k1 = i * (sectors + 1);     // beginning of current stack
        k2 = k1 + sectors + 1;      // beginning of next stack

        for(int j = 0; j < sectors; ++j, ++k1, ++k2){
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0){
                s.indices[indexCount++] = (k1);
                s.indices[indexCount++] = (k2);
                s.indices[indexCount++] = (k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stacks - 1)){
                s.indices[indexCount++] = (k1 + 1);
                s.indices[indexCount++] = (k2);
                s.indices[indexCount++] = (k2 + 1);
            }

        }
    }

    s.vertexCount = vertexCount;
    s.indexCount = indexCount;

    INFO_LOG("Generated a sphere with %d vertices and %d indices.", vertexCount, indexCount);
    return s;
}
