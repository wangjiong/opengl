#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_OFFSET(offset) ((void*)(offset))

enum VAO_IDs { Triangles, NumVAOs };

enum Buffer_IDs { ArrayBuffer, NumBuffers };

enum Attrib_IDs { vPosition = 0, vColor = 1 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

int TypeSize(GLenum type) {
	int size;
#define  CASE(Enum , Count , Type) \
	case Enum: size = Count * sizeof(Type); break

	switch (type) {
		CASE(GL_FLOAT, 1, GLfloat);
		CASE(GL_FLOAT_VEC2, 2, GLfloat);
		CASE(GL_FLOAT_VEC3, 3, GLfloat);
		CASE(GL_FLOAT_VEC4, 4, GLfloat);

		CASE(GL_INT, 1, GLint);
		CASE(GL_INT_VEC2, 2, GLint);
		CASE(GL_INT_VEC3, 3, GLint);
		CASE(GL_INT_VEC4, 4, GLint);

		CASE(GL_UNSIGNED_INT, 1, GLuint);
		CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
		CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
		CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);

		CASE(GL_BOOL, 1, GLboolean);
		CASE(GL_BOOL_VEC2, 2, GLboolean);
		CASE(GL_BOOL_VEC3, 3, GLboolean);
		CASE(GL_BOOL_VEC4, 4, GLboolean);

		CASE(GL_FLOAT_MAT2, 4, GLfloat);
		CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
		CASE(GL_FLOAT_MAT2x4, 8, GLfloat);

		CASE(GL_FLOAT_MAT3, 9, GLfloat);
		CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
		CASE(GL_FLOAT_MAT3x4, 12, GLfloat);

		CASE(GL_FLOAT_MAT4, 16, GLfloat);
		CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
		CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
#undef CASE

	default:
		fprintf(stderr, "Unknown type : 0x%x\n", type);
		exit(EXIT_FAILURE);
		break;
	}
	return size;
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(512, 512, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// VAO
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	// VBO
	GLfloat vertices[NumVertices][2] = {
		{-0.90, -0.90},
		{0.85, -0.90},
		{-0.90, 0.85},

		{0.90, -0.85},
		{0.90, 0.90},
		{-0.85, 0.90},
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Shader
	Shader shader("shader.vs", "shader.fs");
	shader.use();

	// uniform¿é
	GLuint uboIndex;
	GLint uboSize;
	uboIndex = glGetUniformBlockIndex(shader.ID, "Uniforms");
	glGetActiveUniformBlockiv(shader.ID, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);

	GLvoid* buffer;
	buffer = malloc(uboSize);

	if (buffer == NULL) {
		fprintf(stderr, "Unable to allocate buffer\n");
		exit(EXIT_FAILURE);
	}
	else {
		enum { Translation, Scale, Rotation, Enabled, NumUniforms };

		GLfloat scale = 1.0;
		GLfloat translation[] = {0.0f, 0.0f, 0.0f};
		GLfloat rotation[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLboolean enabled = GL_FALSE;

		const char* names[NumUniforms] = {
			"translation",
			"scale",
			"enabled",
			"rotation",
		};
		GLuint indices[NumUniforms];
		GLint size[NumUniforms];
		GLint offset[NumUniforms];
		GLint type[NumUniforms];

		glGetUniformIndices(shader.ID, NumUniforms, names, indices);
		glGetActiveUniformsiv(shader.ID, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
		glGetActiveUniformsiv(shader.ID, NumUniforms, indices, GL_UNIFORM_SIZE, size);
		glGetActiveUniformsiv(shader.ID, NumUniforms, indices, GL_UNIFORM_TYPE, type);

		memcpy((char *)buffer + offset[Scale], &scale, size[Scale] * TypeSize(type[Scale]));
		memcpy((char *)buffer + offset[Translation], &translation, size[Translation] * TypeSize(type[Translation]));
		memcpy((char *)buffer + offset[Enabled], &enabled, size[Enabled] * TypeSize(type[Enabled]));
		memcpy((char *)buffer + offset[Rotation], &rotation, size[Rotation] * TypeSize(type[Rotation]));

		GLuint ubo;
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo);
	}


	// ¶¥µãÊôÐÔ
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAOs[Triangles]);


		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
