#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <learnopengl/shader_m.h>
#include <learnopengl/filesystem.h>

void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void processInput( GLFWwindow* window );

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL );
	if( window == NULL )
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent( window );
	glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader( "shader.vs", "shader.fs" );

	//// set up vertex data (and buffer(s)) and configure vertex attributes
	//// ------------------------------------------------------------------
	//float vertices[] = {
	//	// positions                   // texture coords
	//	0.5f, 0.5f, 0.0f,  1.0f, 1.0f, // top right
	//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f,0.0f, 0.0f, 0.0f, // bottom left
	//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f // top left 
	//};
	//unsigned int indices[] = {
	//	0, 1, 3, // first triangle
	//	1, 2, 3 // second triangle
	//};
	//unsigned int VAO, VBO, EBO;
	//glGenVertexArrays( 1, &VAO );
	//glGenBuffers( 1, &VBO );
	//glGenBuffers( 1, &EBO );

	//glBindVertexArray( VAO );

	//glBindBuffer( GL_ARRAY_BUFFER, VBO );
	//glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
	//glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

	//glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)0 );
	//glEnableVertexAttribArray( 0 );
	//glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)(3 * sizeof( float )) );
	//glEnableVertexAttribArray( 1 );

	//// ÎÆÀí
	//static const GLubyte tex_checkerBoard_data[] = {
	//	0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00,
	//	0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF,
	//	0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00,
	//	0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF,
	//	0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00,
	//	0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF,
	//	0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00,
	//	0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF, 0X00, 0xFF,
	//};
	//static const GLfloat tex_color_data[] = {
	//	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	//	0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//};
	//// 1.
	//unsigned int tex_checkerBoard;
	//glGenTextures( 1, &tex_checkerBoard );
	//glBindTexture( GL_TEXTURE_2D, tex_checkerBoard );
	//glTexStorage2D( GL_TEXTURE_2D, 4, GL_R8, 8, 8 );
	//glTexSubImage2D( GL_TEXTURE_2D,
	//				 0,
	//				 0, 0,
	//				 8, 8,
	//				 GL_RED,GL_UNSIGNED_BYTE,
	//				 tex_checkerBoard_data
	//);
	//// 2.
	///*unsigned int tex_color;
	//glGenTextures( 1, &tex_color );
	//glBindTexture( GL_TEXTURE_2D, tex_color );
	//glTexStorage2D( GL_TEXTURE_2D, 2, GL_RGBA32F, 2, 2 );
	//glTexSubImage2D( GL_TEXTURE_2D,
	//				 0,
	//				 0, 0,
	//				 8, 8,
	//				 GL_RED, GL_UNSIGNED_BYTE,
	//				 tex_color_data );*/

	GLuint vao;
	GLuint quad_vbo;
	

	glGenBuffers(1, &quad_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);

	static const GLfloat quad_data[] =
	{
		0.75f, -0.75f,
		-0.75f, -0.75f,
		-0.75f, 0.75f,
		0.75f, 0.75f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(8 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	GLuint tex;
	glGenTextures( 1, &tex );
	glBindTexture( GL_TEXTURE_2D, tex );
	static const unsigned char texture_data[] =
	{
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
	};
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data );
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, 8, 8);
	/*glTexSubImage2D(GL_TEXTURE_2D,
		0,
		0, 0,
		8, 8,
		GL_RED, GL_UNSIGNED_BYTE,
		texture_data);*/

	while( !glfwWindowShouldClose( window ) )
	{
		processInput( window );

		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		ourShader.use();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

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
}

void framebuffer_size_callback( GLFWwindow* window, int width, int height )
{
	glViewport( 0, 0, width, height );
}
