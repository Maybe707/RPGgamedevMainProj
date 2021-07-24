#version 410 core
out vec4 FragColor;

in vec2 TexCoord;
in float TexIndex;

// Текстурные сэмплеры
uniform sampler2DRect textures[2];

void main()
{
    int index = int(TexIndex);
    FragColor = texture(textures[index], TexCoord);
}
