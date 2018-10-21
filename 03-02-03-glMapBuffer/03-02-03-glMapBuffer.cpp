//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <learnopengl/shader.h>
//#include <stdio.h>
//
//#define BUFFER_OFFSET(offset) ((void*)(offset))
//
//enum VAO_IDs { Triangles, NumVAOs };
//
//enum Buffer_IDs { ArrayBuffer, NumBuffers };
//
//enum Attrib_IDs { vPosition = 0, vColor = 1 };
//
//GLuint VAOs[NumVAOs];
//
//const GLuint NumVertices = 3;
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
//	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
//	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
//
//	GLFWwindow* window = glfwCreateWindow( 512, 512, "LearnOpenGL", NULL, NULL );
//	if( window == NULL )
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent( window );
//
//	if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	GLuint buffer;
//	std::FILE* f;
//	int filesize;
//	f = fopen( "data.dat", "rb" );
//	fseek( f, 0,SEEK_END );
//	filesize = ftell( f );
//
//	glGenBuffers( 1, &buffer );
//	glBindBuffer( GL_COPY_WRITE_BUFFER, buffer );
//	glBufferData( GL_COPY_WRITE_BUFFER, (GLsizei)filesize, NULL, GL_STATIC_DRAW );
//	void* data = glMapBuffer( GL_COPY_WRITE_BUFFER, GL_WRITE_ONLY );
//	fread( data, 1, filesize, f );
//	glUnmapBuffer( GL_COPY_WRITE_BUFFER );
//	fclose( f );
//
//
//	// VAO
//	glGenVertexArrays( NumVAOs, VAOs );
//	glBindVertexArray( VAOs[Triangles] );
//
//	// VBO
//	static const GLfloat positions[] = {
//		-1.0f, -1.0f, 0.0f, 1.0f,
//		1.0f, -1.0f, 0.0f, 1.0f,
//		0.0f, 1.0f, 0.0f, 1.0f,
//	};
//	static const GLfloat colors[] = {
//		1.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 1.0f,
//	};
//	glBindBuffer( GL_ARRAY_BUFFER, buffer );
//
//	// Shader
//	Shader shader( "shader.vs", "shader.fs" );
//	shader.use();
//
//	// 顶点属性
//	// 1.位置
//	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//	glEnableVertexAttribArray( vPosition );
//	// 2.颜色
//	glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(positions)) );
//	glEnableVertexAttribArray( vColor );
//
//	while( !glfwWindowShouldClose( window ) )
//	{
//		glClearColor( 1, 1, 1, 1 );
//		glClear( GL_COLOR_BUFFER_BIT );
//
//		glBindVertexArray( VAOs[Triangles] );
//		glDrawArrays( GL_TRIANGLES, 0, NumVertices );
//
//		glfwSwapBuffers( window );
//		glfwPollEvents();
//	}
//	glfwTerminate();
//
//	return 0;
//}


// 01-01-Triangles.cpp: 定义控制台应用程序的入口点。
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
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

bool flag = false;
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
			// 使用传统的方式改变缓存数据
			flag = !flag;
			if (flag) {
				GLfloat vertices[NumVertices][5] = {
					/*位置*/ /*颜色*/
					{-1, 0, 1, 0, 0},
					{1, 0, 1, 0, 0},
					{0, 1, 1, 0, 0},
				};
				glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			}
			else {
				GLfloat vertices[NumVertices][5] = {
					/*位置*/ /*颜色*/
					{-1, 0, 1, 0, 0},
					{1, 0, 0, 1, 0},
					{0, 1, 0, 0, 1},
				};
				glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			}
		}
		keyFlag = true;
	}
	if( glfwGetKey( window, GLFW_KEY_M ) == GLFW_RELEASE )
	{
		if( keyFlag )
		{
			// 2.第一次松开
			printf( "KeyUp\n" );
			// 使用glMapBuffer改变缓存数据
			glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );
			void* data = glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

			GLfloat vertices[NumVertices][5] = {
				/*位置*/ /*颜色*/
				{ -1, 0, 0, 1, 0 },
				{ 1, 0, 0, 1, 0 },
				{ 0, 1, 0, 1, 1 },
			};

			memcpy( data, vertices, sizeof(vertices) );
			// 记得告诉OpenGL我们不再需要这个指针了
			glUnmapBuffer( GL_ARRAY_BUFFER );
		}
		keyFlag = false;
	}
}