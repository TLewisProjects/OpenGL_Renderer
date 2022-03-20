#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform vec4 ourColor;
uniform sampler2D ourTexture;

void main()
{
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//FragColor = vec4(TexCoord.x, TexCoord.y, 0.0, 0.5);
	//FragColor = ourColor;
	FragColor = texture2D(ourTexture, TexCoord);
}