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
	std::string type;
	std::string path;

	// Methods
	Texture();
	Texture(std::string textureLocation, std::string type);
	~Texture();



private:

};

#endif

