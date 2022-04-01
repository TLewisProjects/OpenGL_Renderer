#pragma once

#include <vector>
#include <string>

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Model
{
public:
	Model();
	Model(const char* path);
	~Model();

	void Draw(Shader& shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);

	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};