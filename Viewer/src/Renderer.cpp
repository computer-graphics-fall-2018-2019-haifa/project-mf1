#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportX, viewportY);
}

Renderer::~Renderer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void Renderer::putPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewportWidth) return;
	if (j < 0) return; if (j >= viewportHeight) return;
	colorBuffer[INDEX(viewportWidth, i, j, 0)] = color.x;
	colorBuffer[INDEX(viewportWidth, i, j, 1)] = color.y;
	colorBuffer[INDEX(viewportWidth, i, j, 2)] = color.z;
}

void Renderer::createBuffers(int viewportWidth, int viewportHeight)
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}

	colorBuffer = new float[3* viewportWidth * viewportHeight];
	for (int x = 0; x < viewportWidth; x++)
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			putPixel(x, y, glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewportWidth; i++)
	{
		for (int j = 0; j < viewportHeight; j++)
		{
			putPixel(i, j, color);
		}
	}
}

void Renderer::SetViewport(int viewportWidth, int viewportHeight, int viewportX, int viewportY)
{
	this->viewportX = viewportX;
	this->viewportY = viewportY;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	createBuffers(viewportWidth, viewportHeight);
	createOpenGLBuffer();
}









void Renderer::plotLineHigh(int x0, int y0, int x1, int y1, const glm::vec3& color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	int D = 2 * dx - dy;
	int y = y0;
	int x = x0;

	while (y <= y1)
	{
		putPixel(x, y, color);
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
		y++;
	}
}



void Renderer::plotLineLow(int x0, int y0, int x1, int y1, const glm::vec3& color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int D = 2 * dy - dx;
	int y = y0;
	int x = x0;

	while (x <= x1)
	{
		putPixel(x, y, color);
		if (D > 0)
		{
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
		x++;
	}
}



void Renderer::DrawLineBresenhamAlgorithm(float _x0, float _y0, float _x1, float _y1, const glm::vec3& color)
{
	int x0 = int(_x0);
	int y0 = int(_y0);
	int x1 = int(_x1);
	int y1 = int(_y1);


	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
		{
			plotLineLow(x1, y1, x0, y0, color);
		}
		else
		{
			plotLineLow(x0, y0, x1, y1, color);
		}
	}
	else
	{
		if (y0 > y1)
		{
			plotLineHigh(x1, y1, x0, y0, color);
		}
		else
		{
			plotLineHigh(x0, y0, x1, y1, color);
		}
	}
}


void Renderer::DrawFace(Face curr_face, std::vector<glm::vec4> curr_vertices)
{
	const glm::vec3 color(1,0,1);

	int vertex_index_0 = curr_face.GetVertexIndex(0);
	vertex_index_0 -= 1;
	glm::vec4 curr_vertex_0 = curr_vertices[vertex_index_0];

	int vertex_index_1 = curr_face.GetVertexIndex(1);
	vertex_index_1 -= 1;
	glm::vec4 curr_vertex_1 = curr_vertices[vertex_index_1];

	int vertex_index_2 = curr_face.GetVertexIndex(2);
	vertex_index_2 -= 1;
	glm::vec4 curr_vertex_2 = curr_vertices[vertex_index_2];

	// The relevant data is vertex.x and vertex.y
	DrawLineBresenhamAlgorithm(curr_vertex_0[0] * viewportWidth, curr_vertex_0[1] * viewportHeight, curr_vertex_1[0] * viewportWidth, curr_vertex_1[1] * viewportHeight, color);
	DrawLineBresenhamAlgorithm(curr_vertex_0[0] * viewportWidth, curr_vertex_0[1] * viewportHeight, curr_vertex_2[0] * viewportWidth, curr_vertex_2[1] * viewportHeight, color);
	DrawLineBresenhamAlgorithm(curr_vertex_1[0] * viewportWidth, curr_vertex_1[1] * viewportHeight, curr_vertex_2[0] * viewportWidth, curr_vertex_2[1] * viewportHeight, color);
}



// Simply iterate all over the vertecies and muliply in tranform matrix
std::vector<glm::vec4> Renderer::TransformVertecies(std::vector<glm::vec3> curr_vertices, glm::mat4x4 curr_tran)
{
	std::vector<glm::vec4> transed_vetricies;

	glm::mat4 _curr_tran(curr_tran);

	for (std::vector<glm::vec3>::iterator it = curr_vertices.begin(); it != curr_vertices.end(); ++it)
	{
		glm::vec4 tmp(1.0);
		tmp[0] = it->x;
		tmp[1] = it->y;
		tmp[2] = it->z;

		glm::vec4 res_vertex = _curr_tran * tmp;
		transed_vetricies.push_back(res_vertex);
	}

	return transed_vetricies;
}





// Get all world transformed matricies and calc them together
glm::mat4x4 getScenceTransMat(Scene& scene)
{
	glm::mat4x4 trans_mat = scene.GetActiveModelTransMat();
	glm::mat4x4 scale_mat = scene.GetActiveModelScaleMat();
	glm::mat4x4 rot_mat_x = scene.GetActiveModelRotationMatX();
	glm::mat4x4 rot_mat_y = scene.GetActiveModelRotationMatY();
	glm::mat4x4 rot_mat_z = scene.GetActiveModelRotationMatZ();

	glm::mat4x4 res_mat = trans_mat  * rot_mat_x * rot_mat_y * rot_mat_z* scale_mat;

	return res_mat;
}


// Apply camera projection
void SetCameraProjection(Scene& scene)
{
	float left= (-500.0f);
	float right = (500.0f);
	float bottom = (-500.0f);
	float top = (500.0f);
	float near_ = 1.0f;
	float far_ = 500.0f;
	scene.SetCameraProjection(left,
		right,
		bottom,
		top,
		near_,
		far_);
}


// Apply gui input on camera view
void SetCameraViewFromGui(Scene& scene)
{
	glm::vec3 eye(0,0,1.0f);
	glm::vec3 at(0,-1,(0.0f));
	glm::vec3 up(0,0,1);

	
	scene.SetCameraView(eye,at,up);
}



void Renderer::DrawBoundBox(std::vector<std::pair <glm::vec3, glm::vec3>>* curr_vertecies)
{
	const glm::vec3 color(0, 0, 0);

	for (std::vector<std::pair <glm::vec3, glm::vec3>>::iterator it = curr_vertecies->begin(); it != curr_vertecies->end(); ++it)
	{
		glm::vec3 curr_vertex_0(it->first.x, it->first.y, it->first.z);
		glm::vec3 curr_vertex_1(it->second.x, it->second.y, it->second.z);

		// The relevant data is vertex.x and vertex.y
		DrawLineBresenhamAlgorithm(curr_vertex_0[0] * viewportWidth, curr_vertex_0[1] * viewportHeight, curr_vertex_1[0] * viewportWidth, curr_vertex_1[1] * viewportHeight, color);

	}

	return;
}


std::vector<std::pair <glm::vec3, glm::vec3>> TransformVerteciesBoundBox(std::vector<std::pair <glm::vec3, glm::vec3>>* vertex_bound_box, glm::mat4x4* tarns_mat)
{
	std::vector<std::pair <glm::vec3, glm::vec3>> transed_vetricies;
	glm::mat4 _curr_tran(*tarns_mat);

	for (std::vector<std::pair <glm::vec3, glm::vec3>>::iterator it = vertex_bound_box->begin(); it != vertex_bound_box->end(); ++it)
	{
		glm::vec4 tmp1(1.0);
		tmp1[0] = it->first.x;
		tmp1[1] = it->first.y;
		tmp1[2] = it->first.z;
		glm::vec4 res_vertex1 = *tarns_mat * tmp1;
		glm::vec3 vertex_1 = glm::vec3(res_vertex1[0], res_vertex1[1], res_vertex1[2]);

		glm::vec4 tmp2(1.0);
		tmp2[0] = it->second.x;
		tmp2[1] = it->second.y;
		tmp2[2] = it->second.z;
		glm::vec4 res_vertex2 = *tarns_mat * tmp2;
		glm::vec3 vertex_2 = glm::vec3(res_vertex2[0], res_vertex2[1], res_vertex2[2]);

		transed_vetricies.push_back(std::pair <glm::vec3, glm::vec3>(vertex_1, vertex_2));
	}

	return transed_vetricies;
}

// Main function
void Renderer::Render(Scene& scene, ImGuiIO& io)
{
	// Draw all models
	int num_models = scene.GetModelCount();

	glm::mat4x4 tarns_mat;
	for (int x = 0; x < num_models; x++)
	{
		// iterate all models in scene
		scene.SetActiveModelIndex(x);
		

		// Get all verticies of this model
		std::vector<glm::vec3> curr_vetices = scene.GetActiveModelVerticies();


		// Handle world Trans mat 
		scene.SetWorldTranToActiveModel();
		glm::mat4x4 world_tran = getScenceTransMat(scene);


		// Handle view camera
		SetCameraViewFromGui(scene);
		//glm::mat4x4 viewCamera(1.0f);
		glm::mat4x4 viewCamera = scene.GetActiveCameraTransformation();
		



		// Handle projection
		SetCameraProjection(scene);
		//glm::mat4x4 projection(1.0f);
		glm::mat4x4 projection = scene.GetActiveCameraProjection();
		


		// Draw all faces
		int num_faces = scene.GetActiveModelNumFaces();
		for (int y = 0; y < num_faces; y++)
		{
			// Calc all maticies
			tarns_mat = world_tran * viewCamera * projection;


			// Apply on all faces
			Face curr_face = scene.GetActiveModelFace(y);
			std::vector<glm::vec4> transed_vertices = TransformVertecies(curr_vetices, tarns_mat);

			// Draw the faces lines
			DrawFace(curr_face, transed_vertices);
		}


		// Draw bound box
		if (scene.GetBoundBox())
		{
			std::vector<std::pair <glm::vec3, glm::vec3>> lines_bound_box = scene.GetActiveModelBoundBoxVerticies();
			std::vector<std::pair <glm::vec3, glm::vec3>> lines_bound_box_transed = TransformVerteciesBoundBox(&lines_bound_box, &tarns_mat);

			DrawBoundBox(&lines_bound_box_transed);
		}


		
	}
	






	
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::initOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &glScreenTex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &glScreenVtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(glScreenVtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::createOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewportWidth, viewportHeight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_RGB, GL_FLOAT, colorBuffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(glScreenVtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}