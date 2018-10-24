#version 460 core
out vec4 color;
uniform float test;
const float PI = 3.1415;
void main(){
    color = vec4(test, sin(test * PI), cos(test * PI), 1.0);
}