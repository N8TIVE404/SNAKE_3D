# version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;

uniform mat4 mvp;
out vec2 textureCoords;

void main(){
  textureCoords = aTexture;
  gl_Position = mvp * vec4(aPosition, 1.0f);
}
