#version 330 core

out vec4 color;
in vec3 out_Color;

uniform vec3 rgb;

void main(){
	color = vec4(rgb,1.0);
}