#version 430 core

out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 color;

void main()
{
    FragColor = color;
//    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f) * color;
}