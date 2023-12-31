#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform bool hoverOver;

void main()
{
    if (hoverOver) {
        color = texture(image, vec2(0.03));
    } else {
        color = texture(image, TexCoords);
    }
}