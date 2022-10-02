#version 330 core

out vec4 color;
in vec3 out_Color;

void main(){
	color = vec4(out_Color,1.0);
	
}