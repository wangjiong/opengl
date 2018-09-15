#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <vector>
#include <stdio.h>
#include <cmath>
using namespace std;

void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void processInput( GLFWwindow* window );

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct Point
{
	int x;
	int y;

	Point( int _x, int _y )
		: x( _x )
		, y( _y )
	{
	}
};

vector<Point> mVertices;
// 交换整数 a 、b 的值
inline void swap_int( int* a, int* b )
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

// Bresenham's line algorithm
void draw_line( int x1, int y1, int x2, int y2 )
{
	// 参数 c 为颜色值
	int dx = abs( x2 - x1 ),
		dy = abs( y2 - y1 ),
		yy = 0;

	if( dx < dy )
	{
		yy = 1;
		swap_int( &x1, &y1 );
		swap_int( &x2, &y2 );
		swap_int( &dx, &dy );
	}

	int ix = (x2 - x1) > 0 ? 1 : -1,
		iy = (y2 - y1) > 0 ? 1 : -1,
		cx = x1,
		cy = y1,
		n2dy = dy * 2,
		n2dydx = (dy - dx) * 2,
		d = dy * 2 - dx;

	if( yy )
	{
		// 如果直线与 x 轴的夹角大于 45 度
		while( cx != x2 )
		{
			if( d < 0 )
			{
				d += n2dy;
			}
			else
			{
				cy += iy;
				d += n2dydx;
			}
			//putpixel(img, cy, cx, c);
			mVertices.emplace_back( cy, cx );
			cx += ix;
		}
	}
	else
	{
		// 如果直线与 x 轴的夹角小于 45 度
		while( cx != x2 )
		{
			if( d < 0 )
			{
				d += n2dy;
			}
			else
			{
				cy += iy;
				d += n2dydx;
			}
			//putpixel(img, cx, cy, c);
			mVertices.emplace_back( cx, cy );
			cx += ix;
		}
	}
}

void line( int x0, int y0, int x1, int y1 )
{
	bool steep = abs( y1 - y0 ) > abs( x1 - x0 );
	if( steep )
	{
		swap( x0, y0 );
		swap( x1, y1 );
	}
	if( x0 > x1 )
	{
		swap( x0, x1 );
		swap( y0, y1 );
	}
	int deltax = x1 - x0;
	int deltay = abs( y1 - y0 );
	int error = deltax / 2;
	int ystep;
	int y = y0;
	if( y0 < y1 )
	{
		ystep = 1;
	}
	else
	{
		ystep = -1;
	}
	for( int x = x0; x <= x1; x++ )
	{
		if( steep )
		{
			//plot( y, x );
			mVertices.emplace_back( y, x );
		}
		else
		{
			//plot( x, y );
			mVertices.emplace_back( x, y );
		}
		error -= deltay;
		if( error < 0 )
		{
			y += ystep;
			error += deltax;
		}
	}
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

	if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//// 顶点
	//float vertices[] = {
	//	0.0f, 0.0f, 0.0f, // left  
	//	0.5f, 0.5f, 0.0f, // right 
	//};
	// 顶点

	// 生成顶点
	//draw_line(0, 0, 10, 60);
	line( 0, 0, 10, 60 );
	

	float* vertices = new float[mVertices.size() * 3];
	int size = mVertices.size();

	for( int i = 0; i < mVertices.size(); i++ )
	{
		const Point& point = mVertices[i];

		vertices[i * 3] = point.x / 100.0f;
		vertices[i * 3 + 1] = point.y / 100.0f;
		vertices[i * 3 + 2] = 0.0f;
	}

	for( int i = 0; i < mVertices.size(); i++ )
	{
		printf( "point : %f %f %f\n", vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2] );
	}

	// VAO
	unsigned int VAO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
	// VBO
	unsigned int VBO;
	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * size * 3, vertices, GL_STATIC_DRAW );
	// 顶点规范
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );
	// Shader
	Shader shader( "shader.vs", "shader.fs" );
	// 点的大小
	glPointSize( 2 );


	// 第二个点
	// 顶点
	float vertices2[] = {
		0.0f, 0.00f, 0.0f, // left  
		0.1f, 0.6f, 0.0f, // right 
	};
	// VAO
	unsigned int VAO2;
	glGenVertexArrays( 1, &VAO2 );
	glBindVertexArray( VAO2 );
	// VBO
	unsigned int VBO2;
	glGenBuffers( 1, &VBO2 );
	glBindBuffer( GL_ARRAY_BUFFER, VBO2 );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW );
	// 顶点规范
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	while( !glfwWindowShouldClose( window ) )
	{
		processInput( window );
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		shader.use();
		glBindVertexArray( VAO );
		glDrawArrays( GL_POINTS, 0, size );

		glBindVertexArray( VAO2 );
		glDrawArrays( GL_LINES, 0, 2 );

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
