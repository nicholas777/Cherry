@shader vertex
#version 330 core
		
layout(location = 0) in vec2 a_Position;

uniform mat4 ModelMatrix;
uniform mat4 VPMatrix;

void main() 
{
	gl_Position = VPMatrix * ModelMatrix * vec4(a_Position, 0.0, 1.0);
}

@shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() 
{
	color = u_Color;
}
