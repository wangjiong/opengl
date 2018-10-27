#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include <learnopengl/camera.h>

#define BUFFER_OFFSET(offset) ((void*)(offset))

void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void mouse_callback( GLFWwindow* window, double xpos, double ypos );
void scroll_callback( GLFWwindow* window, double xoffset, double yoffset );
void processInput( GLFWwindow* window );

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera( glm::vec3( 0.0f, 0.0f, 4.0f ) );
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

enum VAO_IDs { Triangles, NumVAOs };

enum Buffer_IDs { ArrayBuffer, NumBuffers };

enum Attrib_IDs
{
	vPosition = 0,
	vColor = 1
};

GLuint vao[NumVAOs];
GLuint Buffers[NumBuffers];

Shader shader;

GLuint ebo[1];
GLuint vbo[1];

void init()
{
	// 设置立方体的8个顶点，边长为2，中心为原点
	static const GLfloat cube_positions[] = {
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, -1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};
	// 每个顶点的颜色
	static const GLfloat cube_colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,
	};
	// 三角形条带的索引
	static const GLushort cube_indices[] = {
		0, 1, 2, 3, 6, 7, 4, 5,
		0xFFFF,
		2, 6, 0, 4, 1, 5, 3, 7
	};


	// 设置索引缓存
	glGenBuffers( 1, ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[0] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW );

	// 设置顶点属性
	glGenVertexArrays( 1, vao );
	glBindVertexArray( vao[0] );

	glGenBuffers( 1, vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(cube_colors) + sizeof(cube_colors), NULL, GL_STATIC_DRAW );

	glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors );


	// 顶点属性
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( vPosition );
	// 顶点颜色
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(cube_positions) );
	glEnableVertexAttribArray( vColor );

	// Shader
	shader.init( "shader.vs", "shader.fs" );
	shader.use();
}

void display()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor( 0, 1, 1, 0 );
	glClear( GL_COLOR_BUFFER_BIT );

	glm::mat4 model( 1 );
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective( glm::radians( camera.Zoom ), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f );
	shader.use();
	shader.setMat4( "view", view );
	shader.setMat4( "projection", projection );
	model = glm::translate( model, glm::vec3( -1.0f, 0.0f, -1.0f ) );
	shader.setMat4( "model", model );

	glBindVertexArray( vao[0] );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[0] );

#if 1
	glEnable( GL_PRIMITIVE_RESTART );
	glPrimitiveRestartIndex( 0xFFFF );
	glDrawElements( GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL );
#else
	glDrawElements( GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL );
	glDrawElements( GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, (const GLvoid *)(9 * sizeof( GLushort )) );
#endif
}


int main()
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL );
	if( window == NULL )
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent( window );
	glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );
	glfwSetCursorPosCallback( window, mouse_callback );
	glfwSetScrollCallback( window, scroll_callback );

	// tell GLFW to capture our mouse
	glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

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

void processInput( GLFWwindow* window )
{
	if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window, true );

	if( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
		camera.ProcessKeyboard( FORWARD, deltaTime );
	if( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
		camera.ProcessKeyboard( BACKWARD, deltaTime );
	if( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
		camera.ProcessKeyboard( LEFT, deltaTime );
	if( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
		camera.ProcessKeyboard( RIGHT, deltaTime );
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback( GLFWwindow* window, int width, int height )
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport( 0, 0, width, height );
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback( GLFWwindow* window, double xpos, double ypos )
{
	if( firstMouse )
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement( xoffset, yoffset );
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback( GLFWwindow* window, double xoffset, double yoffset )
{
	camera.ProcessMouseScroll( yoffset );
}
