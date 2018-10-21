#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <iostream>
#include <glm/gtc/matrix_transform.inl>

#define BUFFER_OFFSET(offset) ((void*)(offset))

void processInput( GLFWwindow* window );

enum VAO_IDs { Triangles, NumVAOs };

enum Buffer_IDs { ArrayBuffer, NumBuffers };

enum Attrib_IDs
{
	vPosition = 0,
	vColor = 1
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 3;

Shader shader;

void init()
{
	// 4个顶点
	static const GLfloat vertex_positions[] = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
	};
	// 每个顶点的颜色
	static const GLfloat vertex_colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
	};
	// 三个索引值
	static const GLushort vertex_indices[] = {
		0, 1, 2
	};

	// 设置顶点属性
	glGenVertexArrays( NumVAOs, VAOs );
	glBindVertexArray( VAOs[Triangles] );

	// 设置顶点数组缓存
	GLuint vbo[1];
	glGenBuffers( 1, vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW );

	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors );

	// 设置索引数组缓存
	GLuint ebo[1];
	glGenBuffers( 1, ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[0] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW );

	// 顶点属性
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glEnableVertexAttribArray( vPosition );
	// 顶点颜色
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glEnableVertexAttribArray( vColor );

	// Shader
	shader.init( "shader.vs", "shader.fs" );
	shader.use();
}

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);

	glm::mat4 model = glm::mat4(1);

	// DrawArrays
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f));
	shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// DrawElements
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(-0.2f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f));
	shader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

	// DrawElementsBaseVeretex
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f));
	shader.setMat4("model", model);
	glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

	// DrawArraysInstanced
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f));
	shader.setMat4("model", model);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
}


int main()
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	GLFWwindow* window = glfwCreateWindow( 512, 512, "LearnOpenGL", NULL, NULL );
	if( window == NULL )
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent( window );

	if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	init();
	while( !glfwWindowShouldClose( window ) )
	{
		processInput( window );
		// display
		display();

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

bool keyFlag = false;

void processInput( GLFWwindow* window )
{
}
