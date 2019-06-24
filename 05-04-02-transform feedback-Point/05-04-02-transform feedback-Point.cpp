#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main() {
	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 点的大小
	glPointSize(10);

	// 顶点
	float vertices[] = {
		0.0f, 0.0f,
		0.0f, 0.1f,
		0.1f, 0.0f,
		0.1f, 0.1f,
	};

	const int col = 5;
	const int row = 5;
	int index = 0;
	float* pVertices = new float[col * row * 2];
	for( int i = 0; i < col; i++ )
	{
		for( int j = 0; j < row; j++ )
		{
			pVertices[index++] = i * 0.1f;
			pVertices[index++] = j * 0.1f;

			//printf("%f %f\n" , i * 0.1f , j * 0.1f);
		}
	}

	// VAO
	unsigned int vaos[2];
	glGenVertexArrays( 2, vaos );
	unsigned int vbos[2];
	glGenBuffers( 2, vbos );
	for( int i = 0; i < 2; i++ )
	{
		glBindVertexArray( vaos[i] );
		glBindBuffer( GL_ARRAY_BUFFER, vaos[i] );
		//glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
		glBufferData(GL_ARRAY_BUFFER, col * row * 2 * sizeof(float), pVertices, GL_STATIC_DRAW);

		// 顶点规范
		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), (void*)0 );
		glEnableVertexAttribArray( 0 );
	}
	// Shader
	Shader shader("shader.vs", "shader.fs");
	shader.use();

	const GLchar* feedbackVaryings[] = { "outValue" };
	glTransformFeedbackVaryings( shader.ID, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS );
	glLinkProgram( shader.ID );

	index = 0;
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		int i = index++ % 2;
		glBindVertexArray( vaos[i] );
		glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbos[1 - i] );

		
		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, col * row);
		glEndTransformFeedback();



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}