#version 460 core
out vec4 color;
uniform float test;
const float PI = 3.1415;

uniform sampler2D texture1;

void main(){
    color = vec4(texture(texture1, vec2(0.5, 0.5)).rgb, 1.0);
}