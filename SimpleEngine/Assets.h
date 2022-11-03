#pragma once
#include <map>
#include <string>
#include "Texture.h"

using std::map;
using std::string;

// A static singleton Assets class that hosts serveral
// functions to load resources. Each loaded resources is also
// stored for future refenrece by string handles. All functions
// and resources are static and no publi constructor is defined

class Assets
{
public:
	static map<string, Texture> textures;

	//Load a texture from file
	static Texture loadTexture(Renderer& renderer, const string& filename, const string& name);

	//Retrieve a stored texture
	static Texture& getTexture(const std::string& name);

	//Proprely de-allocates all loaded resources
	static void clear();

private:
	Assets() {}

	//Loads a single texture from file
	static Texture loadTextureFromFile(Renderer& renderer, const string& filename);
};

