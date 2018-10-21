#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>

#define BUFFER_OFFSET(offset) ((void*)(offset))

enum VAO_IDs { Triangles, NumVAOs };

enum Buffer_IDs { ArrayBuffer, NumBuffers };

enum Attrib_IDs { vPosition = 0, vColor = 1 };

GLuint VAOs[NumVAOs];

const GLuint NumVertices = 3;

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
	// VAO
	glGenVertexArrays( NumVAOs, VAOs );
	glBindVertexArray( VAOs[Triangles] );

	// VBO
	static const GLfloat positions[] = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
	};
	static const GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
	GLuint buffer;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), NULL, GL_STATIC_DRAW );

	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(positions), positions );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors );

	// Shader
	Shader shader( "shader.vs", "shader.fs" );
	shader.use();

	// 顶点属性
	// 1.位置
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glEnableVertexAttribArray( vPosition );
	// 2.颜色
	glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(positions)) );
	glEnableVertexAttribArray( vColor );

	while( !glfwWindowShouldClose( window ) )
	{
		glClearColor( 1, 1, 1, 1 );
		glClear( GL_COLOR_BUFFER_BIT );

		glBindVertexArray( VAOs[Triangles] );
		glDrawArrays( GL_TRIANGLES, 0, NumVertices );

		glfwSwapBuffers( window );
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}
