# version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

out vec2 tex;
uniform mat4 glModel;
uniform mat4 glView;
uniform mat4 glProjection;

void main(){
    gl_Position = glProjection * glView * glModel * vec4(aPosition, 1.0f);
    tex = aTexture;
}

