#version 460 core

in vec2 outTexCoord;

out vec4 color;

uniform sampler2D ambientTexture;

void main(){
    color = texture(ambientTexture, outTexCoord);
    //color = vec4(outTexCoord.x, outTexCoord.y, 0.0, 1.0);

}