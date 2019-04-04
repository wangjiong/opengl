// 01-01-Triangles.cpp: 定义控制台应用程序的入口点。
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>

#define BUFFER_OFFSET(offset) ((void*)(offset))

enum VAO_IDs { Triangles, NumVAOs };

enum Buffer_IDs { ArrayBuffer, NumBuffers };

enum Attrib_IDs { vPosition = 0, vColor = 1 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

enum
{
	Color,
	Depth,
	NumRenderbuffers
};

GLuint framebuffer, renderbuffer[NumRenderbuffers];

int windowWidth = 800, windowHeight = 600;

void init()
{

	/////////////////////////////////////////////////////////////////////// 1.绘制三角形 ///////////////////////////////////////////////////////////////////////
	// VAO
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	// VBO
	struct VertexData {
		GLubyte color[4];
		GLfloat position[4];
	};
	VertexData vertices[NumVertices] = {
		{{255, 0, 0, 255}, {-1, -1, 0}}, // 红
		{{255, 0, 0, 255}, {0, -1, 0}},
		{{255, 0, 0, 255}, {-0.5, 1, 0}},

		{{0, 0, 255, 255}, {0, -1, 0}}, // 蓝
		{{0, 0, 255, 255}, {1, -1, 0}},
		{{0, 0, 255, 255}, {0.5, 1, 0}}
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Shader
	Shader shader("shader.vs", "shader.fs");
	shader.use();

	// 顶点属性
	// 颜色
	glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vColor);
	// 位置
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(sizeof(vertices[0].color)));
	glEnableVertexAttribArray(vPosition);
	// 开启混合
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 深度测试
	glEnable(GL_DEPTH_TEST);
	/////////////////////////////////////////////////////////////////////// 1.绘制三角形 ///////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////// 2.帧缓冲对象 ///////////////////////////////////////////////////////////////////////
	// 1.帧缓冲对象
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

	// 2.渲染缓存(颜色、深度)
	glGenRenderbuffers( NumRenderbuffers, renderbuffer );
	// 2-1 颜色缓冲区
	glBindRenderbuffer( GL_RENDERBUFFER, renderbuffer[Color] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, 256, 256 );
	// 2-2 深度缓冲区
	glBindRenderbuffer( GL_RENDERBUFFER, renderbuffer[Depth] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 256, 256 );

	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer[Color] );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer[Depth] );
	/////////////////////////////////////////////////////////////////////// 2.帧缓冲对象 ///////////////////////////////////////////////////////////////////////

}

void display()
{
	/////////////////////////////////////////////////////////////////////// 1.自定义的帧缓冲区 ///////////////////////////////////////////////////////////////////////
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, framebuffer );
	glViewport( 0, 0, 256, 256 );
	glClearColor( 1, 1, 1, 1 ); // 1.白
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	/////////////////////////////////////////////////////////////////////// 1.自定义的帧缓冲区 ///////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////// 2.绘制三角形 ///////////////////////////////////////////////////////////////////////
	glBindVertexArray( VAOs[Triangles] );
	glDrawArrays( GL_TRIANGLES, 0, 3 );
	glDrawArrays( GL_TRIANGLES, 3, 3 );;
	/////////////////////////////////////////////////////////////////////// 2.绘制三角形 ///////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////// 3.默认的帧缓冲区 ///////////////////////////////////////////////////////////////////////
	glBindFramebuffer( GL_READ_FRAMEBUFFER, framebuffer ); // 3-1 从自定义帧缓冲区读数据
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );		   // 3-2 写入到默认的帧缓冲区(也就是屏幕)

	glViewport( 0, 0, windowWidth, windowHeight );
	glClearColor( 0, 1, 0, 1 ); // 2.绿
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// 执行拷贝操作
	glBlitFramebuffer( 0, 0, 255, 255, 0, 0, 255, 255, GL_COLOR_BUFFER_BIT, GL_NEAREST );
	/////////////////////////////////////////////////////////////////////// 3.默认的帧缓冲区 ///////////////////////////////////////////////////////////////////////
}


int main()
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	glfwWindowHint( GLFW_SAMPLES, 1 ); // 开启多重采样

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL );
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
		// display
		display();

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}