# version 330 core

out vec4 color;
in vec2 textureCoord;

uniform sampler2D tex;

void main(){
  color = texture(tex, textureCoord);
}
