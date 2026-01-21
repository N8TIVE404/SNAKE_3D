# version 330 core

out vec4 color;

uniform samplerCube cubeSampler;
in vec3 textureCoords;

void main(){
  color = texture(cubeSampler, textureCoords);
}
