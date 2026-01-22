# version 330 core

in float height;
out vec4 fragColor;

void main(){
  float h = clamp(height / 164.0f, 0.0f, 1.0f);
  vec3 color = mix(vec3(0.1f, 0.2f, 0.1f), vec3(1.0f, 1.0f, 1.0f), h);
  fragColor = vec4(color, 1.0f);
}
