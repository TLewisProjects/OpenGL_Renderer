#version 330 core
out vec4 FragColor;

in vec3 vertexColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	//FragColor = vec4(vertexColor, 1.0);
	FragColor = texture(ourTexture, TexCoord);
	//FragColor = vec4(0.25,0.25,0.25,1.0);
}