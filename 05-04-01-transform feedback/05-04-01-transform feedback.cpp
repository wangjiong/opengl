// 01-01-Triangles.cpp: 定义控制台应用程序的入口点。
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
// wangjiong
#include <iostream>

const GLchar* vertexShaderSrc = R"glsl(
	#version 150 core

    in float inValue;
    out float outValue;

    void main()
    {
        outValue = sqrt(inValue);
    }
)glsl";

void init()
{
	GLuint shader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( shader, 1, &vertexShaderSrc, nullptr );
	glCompileShader( shader );

	GLuint program = glCreateProgram();
	glAttachShader( program, shader );

	const GLchar* feedbackVaryings[] = { "outValue" };
	glTransformFeedbackVaryings( program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS );

	glLinkProgram( program );
	glUseProgram( program );

	GLuint vao;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	GLuint vbo;
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW );

	GLint inputAttrib = glGetAttribLocation( program, "inValue" );
	glEnableVertexAttribArray( inputAttrib );
	glVertexAttribPointer( inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0 );

	GLuint tbo;
	glGenBuffers( 1, &tbo );
	glBindBuffer( GL_ARRAY_BUFFER, tbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof(data), nullptr, GL_STATIC_READ );

	glEnable(GL_RASTERIZER_DISCARD);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, 5);
	glEndTransformFeedback();
	

	glFlush();

	GLfloat feedback[5];
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
	printf("%f %f %f %f %f\n", feedback[0], feedback[1], feedback[2], feedback[3], feedback[4]);
}

void display()
{
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
		// display
		display();

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
