# version 330 core

layout (location = 0) in vec3 aPosition;

out float height;
uniform mat4 mvp;

void main(){
  height = aPosition.y;
  gl_Position = mvp * vec4(aPosition, 1.0f);
}
