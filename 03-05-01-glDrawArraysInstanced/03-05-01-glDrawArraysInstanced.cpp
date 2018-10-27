#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader shader("shader.vs", "shader.fs");

	// generate a list of 100 quad locations/translation-vectors
	// ---------------------------------------------------------
	glm::vec2 translations[100];
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2) {
		for (int x = -10; x < 10; x += 2) {
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}

	shader.use();
	for (unsigned int i = 0; i < 100; i++) {
		std::stringstream ss;
		std::string index;
		ss << i;
		index = ss.str();
		shader.setVec2(("offsets[" + index + "]").c_str(), translations[i]);
	}

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float quadVertices[] = {
		// positions     // colors
		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

		-0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		0.05f, 0.05f, 0.0f, 1.0f, 1.0f
	};

	unsigned int quadVAO, quadVBO;

	// �������
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	// ���㻺��
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	// ����λ��
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );
	// ������ɫ
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)(2 * sizeof( float )) );
	glEnableVertexAttribArray( 1 );


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw 100 instanced quads
		shader.use();
		glBindVertexArray(quadVAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
		glBindVertexArray(0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);

	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}