//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <vector>


enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
//enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint  NumVertices = 6;


//----------------------------------------------------------------------------
//
// init
//
#define BUFFER_OFFSET(a) ((void*)(a))

void init(std::vector<unsigned int> &indices)
{
	unsigned int EBO;
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glGenBuffers(1, &EBO);

	float vertices[] = {
	   -0.5f, -0.9f, 0.0f,  // Left Side Bottom Left
	   -0.5f,  0.9f, 0.0f,  // Left Side Top Left
	   -0.3f,  0.9f, 0.0f,  // Left Side Top right
	   -0.3f, -0.9f, 0.0f, // Left Side Bottom right
		0.5f,  0.9f, 0.0f,   // Right Side Top Right
		0.5f, -0.9f, 0.0f,  // Right Side Bottom Right
		0.3f,  0.9f, 0.0f,   // Right Side Top Left
		0.3f, -0.9f, 0.0f,  // Right Side Bottom Left
	   -0.9f, -0.5f, 0.0f, // Bot Side Bottom Left
		0.9f, -0.5f, 0.0f,  // Bot Side Bottom Right
		0.9f, -0.3f, 0.0f,  // Bot Side Top Right
	   -0.9f, -0.3f, 0.0f, // Bot Side Top left
		0.9f,  0.5f, 0.0f,   // Top Side Top Right
	   -0.9f,  0.5f, 0.0f,  // Top Side Top Left
	   -0.9f,  0.3f, 0.0f,  // Top Side Bottom Left
		0.9f,  0.3f, 0.0f,   // Top Side Bottom Right
	};
	
	indices = {
		1, 2, 3,
		0, 1, 3,
		4, 5, 6,
		5, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "media/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "media/triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	//glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(vPosition);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}


//----------------------------------------------------------------------------
//
// display
//

void display(std::vector<unsigned int> indices)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(VAOs[Triangles]);
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


//----------------------------------------------------------------------------
//
// main
//

int main(int argc, char** argv)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewInit();

	std::vector<unsigned int> indices;

	init(indices);

	while (!glfwWindowShouldClose(window))
	{
		display(indices);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}
