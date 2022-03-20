#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string textureLocation)
{
	//this->ID = 0;
	unsigned char* data = stbi_load(textureLocation.c_str(), &(this->width), &(this->height), &(this->nrChannels), 0);

	if (data)
	{
		// Create texture object
		glGenTextures(1, &(this->ID));

		// Bind target to GL_TEXTURE_2D target
		glBindTexture(GL_TEXTURE_2D, this->ID);

		// Arguments for this:
		// 1. Texture target - the currently bound GL_TEXTURE_2D
		// 2. Mipmap level - usually base level 0 if letting OpenGL generate mipmaps
		// 3. What format to store the texture in
		// 4. Texture width
		// 5. Texture height
		// 6. Legacy apparently - always 0
		// 7. Format of the source texture
		// 8. Datatype of the source texture - stored as bytes
		// 9. A pointer to the data itself
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		// Automatically create a mipmap chain from base texture
		// Can also manually create by calling glTexImage2D with different mipmap levels
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat in X direction
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repear in Y direction
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Minification filter - Linear interpolation between mipmaps levels
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Minification filter - Linear interpolation

		glBindTexture(GL_TEXTURE_2D, 0);
		

		std::cout << "Successfully loaded texture: " << textureLocation.c_str() << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture: " << textureLocation.c_str() << std::endl;
	}

	// Free texture data
	stbi_image_free(data);

}

Texture::~Texture()
{
	//glDeleteTextures(1, &(this->ID));
}