#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
// wangjiong
#include <iostream>
#include <stdio.h>

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

void init()
{
	// VAO
	glGenVertexArrays( NumVAOs, VAOs );
	glBindVertexArray( VAOs[Triangles] );

	// VBO
	GLfloat vertices[NumVertices][5] = {
		/*位置*/ /*颜色*/
		{ -1, 0, 1, 0, 0 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1 },
	};
	glGenBuffers( NumBuffers, Buffers );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	// Shader
	Shader shader( "shader.vs", "shader.fs" );
	shader.use();

	// 顶点属性
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 5, BUFFER_OFFSET(0) );
	glEnableVertexAttribArray( vPosition );
	// 顶点颜色
	glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 5, BUFFER_OFFSET(sizeof(float) * 2) );
	glEnableVertexAttribArray( vColor );
}

void display()
{
	glClearColor( 1, 1, 1, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

	glBindVertexArray( VAOs[Triangles] );
	glDrawArrays( GL_TRIANGLES, 0, NumVertices );
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
	//glfwSetFramebufferSizeCallback(window, display);

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
	if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window, true );

	if( glfwGetKey( window, GLFW_KEY_M ) == GLFW_PRESS )
	{
		if( !keyFlag )
		{
			// 1.第一次按下
			printf( "KeyDown\n" );
		}
		keyFlag = true;
	}
	if( glfwGetKey( window, GLFW_KEY_M ) == GLFW_RELEASE )
	{
		if( keyFlag )
		{
			// 2.第一次松开
			printf( "KeyUp\n" );
		}
		keyFlag = false;
	}
}
