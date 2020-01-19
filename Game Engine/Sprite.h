#pragma once

#include "Component.h"
#include <stdio.h>
#include "ResourceManager.h"
#include <GL/glew.h>
#include "stb_image.h""
//#include <glad/glad.h>
class SDL_Surface;
#define MAX_VERTICES 500
class Sprite : public Component {
public:
	Sprite();
	~Sprite();

	void Update() {}
	void Serialize(FILE **fpp);

	void DrawMesh();
	void LoadMesh();

public:
	SDL_Surface* mpSurface;
	GLuint VAO, VBO, EBO, VBO_Circle, VBO_Rectangle;
	unsigned int texture;
	std::string textureFile;
	//GLfloat vertices[MAX_VERTICES];


	int vertexCount;
	float radius; 
	float center_x;
	float center_y;

	// Create a buffer for vertex data
	float *buffer;
		int idx;
		int outerVertexCount;

		int prevShader_chage;
};