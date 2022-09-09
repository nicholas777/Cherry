@shader vertex
#version 330 core
		
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_UV;
layout(location = 3) in float a_TexSlot;

out vec2 o_UV;
out vec4 o_Color;
out float o_TexSlot;

uniform mat4 VPMatrix;

void main() 
{
	o_UV = a_UV;
	o_Color = a_Color;
	o_TexSlot = a_TexSlot;
	gl_Position = VPMatrix * vec4(a_Position, 0.0, 1.0);
}

@shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 o_UV;
in vec4 o_Color;
in float o_TexSlot;

uniform sampler2D u_Samplers[16];

void main() 
{
	color = texture(u_Samplers[int(o_TexSlot)], o_UV) * o_Color;
}