#version 430 core

out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform vec4 color;

void main()
{
//    FragColor = color;
    FragColor = texture(texture1, TexCoord) * color;
}