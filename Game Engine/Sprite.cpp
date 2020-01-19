#include "Sprite.h"
#include <string>
#include<iostream>
#include "StateManager.h"
#include "Body.h"
#include "CollisionManager.h"
#include "Transform.h"



extern StateManager *gpStateManager;

extern ResourceManager* gpResourceManager;
Sprite::Sprite() : Component(SPRITE) {
	mpSurface = nullptr;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenTextures(1, &texture);

	glGenBuffers(1, &VBO_Circle);
	glGenBuffers(1, &VBO_Rectangle);


	prevShader_chage = 0;

	 vertexCount = 360;
	 radius = 1.0f;
	 center_x = 0.0f;
	center_y = 0.0f;

	// Create a buffer for vertex data
	// buffer = new float[vertexCount * 3]; // (x,y) for each vertex
	 idx = 0;
	 outerVertexCount = vertexCount - 1;
}
Sprite::~Sprite() 
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &EBO);

	glDeleteBuffers(1, &VBO_Circle);
	glDeleteBuffers(1, &VBO_Rectangle);
}

void Sprite::Serialize(FILE **fpp)
{
	
	char imageName[256];
	memset(imageName, 0, 256 * sizeof(char));
	std::string fullPath = "..\\Resource\\";
	fscanf_s(*fpp, "%255s\n", imageName, sizeof(imageName));
	
	fullPath += imageName;
	textureFile = fullPath;
	//mpSurface = gpResourceManager->LoadSurfaces( fullPath.c_str());
	this->LoadMesh();

}

void Sprite::DrawMesh()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	if (gpStateManager->Change_Shader == 0)
	{
		if (prevShader_chage != gpStateManager->Change_Shader)
		{

		
			// render container

			float vertices[] = {
				// positions          // colors           // texture coords
				 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
				 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left 
			};

			unsigned int indices[] = {
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
			};


			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

			prevShader_chage = gpStateManager->Change_Shader;
		}
		

		
		glBindTexture(GL_TEXTURE_2D, texture);

		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
		
	}
	else
	{

		if (prevShader_chage != gpStateManager->Change_Shader)
		{
		
			
			
			
			
			prevShader_chage = gpStateManager->Change_Shader;
		}



		
		Body *pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		//prevShader_chage = gpStateManager->Change_Shader;
		if(pBody->body_shape_type==1)
		{
			
			

			glBindBuffer(GL_ARRAY_BUFFER, VBO_Rectangle);


			glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);
			glEnableVertexAttribArray(0);

		

			
			

			glDrawArrays(GL_LINE_LOOP, 0, 6);
			glDisableVertexAttribArray(0);
		}
		else if(pBody->body_shape_type == 0)
		{
			

			glBindBuffer(GL_ARRAY_BUFFER, VBO_Circle);

			
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);
			glEnableVertexAttribArray(0);
			
			

			
			
			
			
			
			glDrawArrays(GL_LINE_LOOP, 0, 30);
		
			
			glDisableVertexAttribArray(0);
		}
		
	}

}

void Sprite::LoadMesh()
{
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(textureFile.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
///////////////////////////////////////////////////////

	// Center vertex for triangle fan
	

	// Outer vertices of the circle
	
	float outer_x = 0;
		float outer_y = 0;
		float buffer_circle[30 * 3];

	//	buffer_circle[idx++] = center_x;
	//	buffer_circle[idx++] = center_y;
	//	buffer_circle[idx++] = 0;
		int theta =0;
		while (theta < 360)
		{
		
		outer_x = 0.5 * cosf(theta );
		outer_y = 0.5 * sinf(theta);


		buffer_circle[idx++] = outer_x;
		buffer_circle[idx++] = outer_y;
		buffer_circle[idx++] = 0;

		theta = theta + (360 / 30);
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Circle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_circle), buffer_circle, GL_STATIC_DRAW);

	float rect_Buffer[18];
	rect_Buffer[0] = -0.5;
	rect_Buffer[1] = 0.5;
	rect_Buffer[2] = 0;

	rect_Buffer[3] = -0.5;
	rect_Buffer[4] = -0.5;
	rect_Buffer[5] = 0;

	rect_Buffer[6] = 0.5;
	rect_Buffer[7] = -0.5;
	rect_Buffer[8] = 0;

	rect_Buffer[9] = -0.5;
	rect_Buffer[10] = 0.5;
	rect_Buffer[11] = 0;

	rect_Buffer[12] = 0.5;
	rect_Buffer[13] = -0.5;
	rect_Buffer[14] = 0;

	rect_Buffer[15] = 0.5;
	rect_Buffer[16] = 0.5;
	rect_Buffer[17] = 0;

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Rectangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_Buffer), rect_Buffer, GL_STATIC_DRAW);
}

