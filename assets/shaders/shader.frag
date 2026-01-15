# version 330 core

out vec4 fragColor;
in vec2 tex;

uniform sampler2D DIFFUSE_TEX1;

void main(){
    fragColor = texture(DIFFUSE_TEX1, tex);
}
