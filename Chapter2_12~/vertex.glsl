#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 in_Color;

uniform mat4 transform;

out vec3 out_Color;

void main(){
	
	gl_Position = transform * vec4(vPos,1.0f);
	out_Color = in_Color;		
}