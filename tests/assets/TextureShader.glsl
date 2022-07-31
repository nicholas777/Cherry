@shader vertex
#version 330 core
		
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_UV;

out vec2 o_UV;

uniform mat4 ModelMatrix;
uniform mat4 VPMatrix;

void main() 
{
	o_UV = a_UV;
	gl_Position = VPMatrix * ModelMatrix * vec4(a_Position, 0.0, 1.0);
}

@shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 o_UV;

uniform sampler2D u_Sampler;

void main() 
{
	color = texture(u_Sampler, o_UV);
}
