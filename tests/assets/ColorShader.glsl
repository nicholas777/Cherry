@shader vertex
#version 330 core
		
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 o_Color;

uniform mat4 ModelMatrix;
uniform mat4 VPMatrix;

void main() 
{
	o_Color = a_Color;
	gl_Position = VPMatrix * ModelMatrix * vec4(a_Position, 0.0, 1.0);
}

@shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 o_Color;

void main() 
{
	color = o_Color;
}
