@shader vertex
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_UV;
layout(location = 3) in float a_TexSlot;
layout(location = 4) in float a_EntityID;

out float o_EntityID;
out vec2 o_UV;
out vec4 o_Color;
out float o_TexSlot;

uniform mat4 VPMatrix;

void main() 
{
    o_UV = a_UV;
    o_Color = a_Color;
    o_TexSlot = a_TexSlot;
    o_EntityID = a_EntityID;
    gl_Position = VPMatrix * vec4(a_Position, 0.0, 1.0);
}

@shader fragment
#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) out int color2;

in float o_EntityID;
in vec2 o_UV;
in vec4 o_Color;
in float o_TexSlot;

uniform sampler2D u_Samplers[16];

void main() 
{
    switch (int(o_TexSlot)) {
        case 0:  color = texture(u_Samplers[0], o_UV) * o_Color; break;
        case 1:  color = texture(u_Samplers[1], o_UV) * o_Color; break;
        case 2:  color = texture(u_Samplers[2], o_UV) * o_Color; break;
        case 3:  color = texture(u_Samplers[3], o_UV) * o_Color; break;
        case 4:  color = texture(u_Samplers[4], o_UV) * o_Color; break;
        case 5:  color = texture(u_Samplers[5], o_UV) * o_Color; break;
        case 6:  color = texture(u_Samplers[6], o_UV) * o_Color; break;
        case 7:  color = texture(u_Samplers[7], o_UV) * o_Color; break;
        case 8:  color = texture(u_Samplers[8], o_UV) * o_Color; break;
        case 9:  color = texture(u_Samplers[9], o_UV) * o_Color; break;
        case 10: color = texture(u_Samplers[10], o_UV) * o_Color; break;
        case 11: color = texture(u_Samplers[11], o_UV) * o_Color; break;
        case 12: color = texture(u_Samplers[12], o_UV) * o_Color; break;
        case 13: color = texture(u_Samplers[13], o_UV) * o_Color; break;
        case 14: color = texture(u_Samplers[14], o_UV) * o_Color; break;
        case 15: color = texture(u_Samplers[15], o_UV) * o_Color; break;
    }

    color2 = int(o_EntityID);
}
