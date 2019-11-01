#version 460 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

out vec2 outTexCoord;

void main(){
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertexPosition, 1.0);
    outTexCoord = texCoord;
}