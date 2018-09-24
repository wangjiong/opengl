// 01-01-Triangles.cpp: 定义控制台应用程序的入口点。
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
// wangjiong
#include <iostream>

#define BUFFER_OFFSET(offset) ((void*)(offset))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(512, 512, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glfwSetFramebufferSizeCallback(window, display);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// VAO
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	// VBO
	GLfloat vertices[NumVertices][2] = {
		{ -0.90,-0.90 },
		{ 0.85,-0.90 },
		{ -0.90,0.85 },

		{ 0.90,-0.85 },
		{ 0.90,0.90 },
		{ -0.85,0.90 },
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Shader
	Shader shader("shader.vs", "shader.fs");
	shader.use();

	// uniform块
	GLuint uboIndex;
	GLint uboSize;
	GLuint ubo;
	GLvoid *buffer;

	uboIndex = glGetUniformBlockIndex(shader.ID, "Uniforms");
	glGetActiveUniformBlockiv(shader.ID , uboIndex , GL_UNIFORM_BLOCK_DATA_SIZE , &uboSize);

	buffer = malloc(uboSize);

	if (buffer == NULL) {
		fprintf(stderr , "Unable to allocate buffer\n");
		exit(EXIT_FAILURE);
	}
	else {
		enum {Translation , Scale , Rotation , Enabled , NumUniforms};

		GLfloat scale = 0.5;
		GLfloat translation[] = { 0.1f,0.1f,0.1f };
		GLfloat rotation[] = {90 , 0.0f ,0.0f,1.0f};
		GLboolean enabled = GL_TRUE;

		const char* names[NumUniforms] = {
			"translation",
			"scale",
			"rotation",
			"enabled",
		};
		GLuint indices[NumUniforms];
		GLint size[NumUniforms];
		GLint offset[NumUniforms];
		GLint type[NumUniforms];

		glGetUniformIndices(shader.ID , NumUniforms , names , indices);
		glGetActiveUniformsiv(shader.ID, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
		glGetActiveUniformsiv(shader.ID, NumUniforms, indices, GL_UNIFORM_OFFSET, size);
		glGetActiveUniformsiv(shader.ID , NumUniforms ,indices , GL_UNIFORM_OFFSET , type);

		memcpy(buffer + offset[Scale], &scale, size[Scale] * TypeSize(type[Scale]));
		memcpy(buffer + offset[Translation], &scale, size[Translation] * TypeSize(type[Translation]));
		memcpy(buffer + offset[Rotation], &scale, size[Rotation] * TypeSize(type[Rotation]));
		memcpy(buffer + offset[Enabled] , &scale ,size[Enabled] * TypeSize(type[Enabled]) );

		glGenBuffers(1,&ubo);
		glBindBuffer(GL_UNIFORM_BUFFER , ubo);
		glBufferData(GL_UNIFORM_BUFFER , uboSize , buffer , GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER , uboIndex , ubo);
	}


	// 顶点属性
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAOs[Triangles]);



		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		//glFlush();
		glFinish();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

