// 01-01-Triangles.cpp: 定义控制台应用程序的入口点。
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
// wangjiong
#include <iostream>

#define BUFFER_OFFSET(offset) ((void*)(offset))

enum VAO_IDs { Triangles, NumVAOs };

enum Buffer_IDs { ArrayBuffer, NumBuffers };

enum Attrib_IDs { vPosition = 0, vColor = 1 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init()
{
	// VAO
	glGenVertexArrays( NumVAOs, VAOs );
	glBindVertexArray( VAOs[Triangles] );

	// VBO
	struct VertexData
	{
		GLubyte color[4];
		GLfloat position[4];
	};
	VertexData vertices[NumVertices] = {
		{ { 255, 0, 0, 255 }, { -1, -1, 0.5 } }, // 红
		{ { 255, 0, 0, 0 }, { 1, -1, 0.5 } },
		{ { 255, 0, 0, 255}, { 0, 1, 0.5 } },

		{ { 0, 0, 255, 0 }, { -1, 1, 0.9 } }, // 蓝
		{ { 0, 0, 255, 0}, { 0, -1, 0.9 } },
		{ { 0, 0, 255, 255}, { 1, 1, 0.9 } }
	};

	glGenBuffers( NumBuffers, Buffers );
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	// Shader
	Shader shader( "shader.vs", "shader.fs" );
	shader.use();

	// 顶点属性
	// 颜色
	glVertexAttribPointer( vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( VertexData ), BUFFER_OFFSET(0) );
	glEnableVertexAttribArray( vColor );
	// 位置
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, sizeof( VertexData ), BUFFER_OFFSET(sizeof(vertices[0].color)) );
	glEnableVertexAttribArray( vPosition );

	// 开启多重采样,默认是开启的
	glEnable( GL_MULTISAMPLE );
	// 剪切测试
	glEnable( GL_SCISSOR_TEST );

	// 剪切测试
	glScissor( 0, 0, 512, 512 );

	// 深度测试
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

	// 
}

void display()
{
	glClearColor( 0, 1, 1, 1 );
	glClearDepth( 1 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	glBindVertexArray( VAOs[Triangles] );

	// 模板测试
	// 绘制红三角形
	glDrawArrays( GL_TRIANGLES, 0, 3 );

	// 绘制蓝三角形
	//glDrawArrays( GL_TRIANGLES, 3, 3 );;

	glFinish();
}


int main()
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	glfwWindowHint( GLFW_SAMPLES, 1 ); // 开启多重采样

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
		// display
		display();

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
