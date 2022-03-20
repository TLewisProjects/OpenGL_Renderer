#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "stb_image.h"

class Texture
{
public:
	// Members
	unsigned int ID;
	int width;
	int height;
	int nrChannels;

	// Methods
	Texture();
	Texture(std::string textureLocation);
	~Texture();



private:

};

#endif

