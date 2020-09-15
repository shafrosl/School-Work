#include <cstdio>		// for C++ i/o
#include <iostream>
#include <string>
#include <cstddef>
#include <stdlib.h>
#include <time.h>
using namespace std;	// to avoid having to use std::

#define GLEW_STATIC		// include GLEW as a static library
#include <GLEW/glew.h>	// include GLEW
#include <GLFW/glfw3.h>	// include GLFW (which includes the OpenGL header)
#include <glm/glm.hpp>	// include GLM (ideally should only use the GLM headers that are actually used)
#include <glm/gtx/transform.hpp>
using namespace glm;	// to avoid having to use glm::

#define PI 3.14159265
#define G_SLICES 32
#define MAX_VERTICES (G_SLICES+2)*3	// a triangle fan should have a minimum of 3 vertices
#define CIRCLE_RADIUS 0.5
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MOVEMENT_SENSITIVITY 0.02f		// camera movement sensitivity
#define ROTATION_SENSITIVITY 0.001f		// camera rotation sensitivity
#define ZOOM_SENSITIVITY 0.01f			// camera zoom sensitivity

#include "Camera.h"
#include "shader.h"

// struct for vertex attributes
struct Vertex
{
	GLfloat position[3];
	GLfloat color[3];
};

// global variables
Vertex g_vertices[] = {
	// vertex 1
	-0.5f, 0.5f, 0.5f,	// position
	1.0f, 0.0f, 1.0f,	// colour
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 3
	0.5f, 0.5f, 0.5f,	// position
	1.0f, 1.0f, 1.0f,	// colour
	// vertex 4
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 1.0f, 0.0f,	// colour
	// vertex 5
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, 1.0f,	// colour
	// vertex 6
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, 0.0f,	// colour
	// vertex 7
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 1.0f,	// colour
	// vertex 8
	0.5f, -0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// colour
};

GLuint g_indices[] = {
	0, 1, 2,	// triangle 1
	2, 1, 3,	// triangle 2
	4, 5, 0,	// triangle 3
	0, 5, 1,	// ...
	2, 3, 6,
	6, 3, 7,
	4, 0, 6,
	6, 0, 2,
	1, 5, 3,
	3, 5, 7,
	5, 4, 7,
	7, 4, 6,	// triangle 12
};

GLfloat g_vertices_circle[MAX_VERTICES] = {
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f
};

GLfloat g_colors_circle[MAX_VERTICES] = {
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f
};

GLfloat g_colors_ring[MAX_VERTICES] = {
	0.3f, 0.7f, 0.7f,
	0.3f, 0.7f, 0.7f
};

GLuint g_IBO_cube = 0;				// index buffer object identifier
GLuint g_VBO_cube = 0;				// vertex buffer object identifier
GLuint g_VAO_cube = 0;				// vertex array object identifier

GLuint g_VBO_path1 = 0;				// vertex buffer object identifier
GLuint g_VBO_path2 = 0;				// vertex buffer object identifier
GLuint g_VAO_path = 0;				// vertex array object identifier

GLuint g_VBO_ring1 = 0;				// vertex buffer object identifier
GLuint g_VBO_ring2 = 0;				// vertex buffer object identifier
GLuint g_VAO_ring = 0;				// vertex array object identifier

GLuint g_shaderProgramID = 0;		// shader program identifier
GLuint g_MVP_Index = 0;				// location in shader
GLuint g_alphaIndex;				// for transparency of 4th planet

glm::mat4 g_modelMatrix[6];			// object model matrices
glm::mat4 g_modelMatrixCircle[5];	// circle model matrices
glm::mat4 g_projectionMatrix;		// projection matrix

glm::vec3 mPositionCam1 = glm::vec3(0.0f, 15.0f, 30.0f);
glm::vec3 mPositionCam2 = glm::vec3(0.0f, 40.0f, 3.5f);
glm::vec3 mLookAtCam = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 mUpCam = glm::vec3(0.0f, 1.0f, 0.0f);

Camera g_camera;					// camera

float g_orbitSpeed[4];
float g_rotationSpeed[5];
float g_planetSize[4];
float g_orbitPath[4];
float g_alpha;    
float g_alpha_default = 1.0f;
float g_frameTime = 0.0f;
float g_pitch1 = -0.5f;
float g_pitch2 = -1.5f;
float g_yaw1 = 0.0f;
float g_yaw2 = 0.0f;
bool g_pPress = false;
bool g_moveCamera = false;
int view = 1;

////////////////////// R N G for speed/size ///////////////////////
float rng(int lo, int hi) 
{
	int cap = hi - lo;
	float x = (rand() % cap + lo); // to be able to be more customisable
	x /= 100;
	return x;
}

/////////////////// R N G for path offset ///////////////////////
float pathrng()
{
	float x = (rand() % 14 + 1); // 0.1 - 1.5 to prevent collision
	x /= 10;
	float num = rng(1, 100); // rng for negative/positive chance
	int y = num * 100;
	if (y % 2 == 0)
	{
		x *= -1; // allows for negative number to offset the other direction
	}
	return x;
}

/////////////////// generates path ///////////////////////
void generate_circle()
{
	float angle = PI * 2 / static_cast<float>(G_SLICES);    // used to generate x and y coordinates
	float scale_factor = static_cast<float>(WINDOW_HEIGHT) / WINDOW_WIDTH;  // scale to make it a circle instead of an elipse
	int index = 0;  // vertex index

	g_vertices_circle[3] = CIRCLE_RADIUS * scale_factor;    // set x coordinate of vertex 1

	// generate vertex coordinates for triangle fan
	for (int i = 0; i < G_SLICES + 2; i++)
	{
		// multiply by 3 because a vertex has x, y, z coordinates
		index = i * 3;

		g_vertices_circle[index] = CIRCLE_RADIUS * cos(angle) * scale_factor;
		g_vertices_circle[index + 1] = CIRCLE_RADIUS * sin(angle);
		g_vertices_circle[index + 2] = 0.0f;

		// Color for edges. See stackoverflow
		g_colors_circle[index] = 1.0f;
		g_colors_circle[index + 1] = 0.0f;
		g_colors_circle[index + 2] = 0.0f;
		
		// update to next angle
		angle += PI * 2 / static_cast<float>(G_SLICES);
	}
}

/////////////////// main ///////////////////////

static void init(GLFWwindow* window)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	// set clear background colour

	glEnable(GL_DEPTH_TEST);			// enable depth buffer test
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// create and compile our GLSL program from the shader files
	g_shaderProgramID = loadShaders("MVP_VS.vert", "ColorFS.frag");

	// find the location of shader variables
	GLuint positionIndex = glGetAttribLocation(g_shaderProgramID, "aPosition");
	GLuint colorIndex = glGetAttribLocation(g_shaderProgramID, "aColor");
	g_MVP_Index = glGetUniformLocation(g_shaderProgramID, "uModelViewProjectionMatrix");
	g_alphaIndex = glGetUniformLocation(g_shaderProgramID, "uAlpha");

	// initialise model matrix to the identity matrix
	g_modelMatrix[0] = g_modelMatrix[1] = g_modelMatrix[2] = g_modelMatrix[3] = g_modelMatrix[4] = g_modelMatrix[5] = glm::mat4(1.0f);
	g_modelMatrixCircle[0] = g_modelMatrixCircle[1] = g_modelMatrixCircle[2] = g_modelMatrixCircle[3] = g_modelMatrixCircle[4] = glm::mat4(1.0f);

	// set camera's view matrix
	g_camera.setViewMatrix(mPositionCam1, mLookAtCam, mUpCam);
	g_camera.setPitch(g_pitch1);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / height;

	// set camera's projection matrix
	g_camera.setProjection(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

	// initialise projection matrix
	g_projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
	
	//////////////////////////////////////// C U B E ////////////////////////////////////////////
	// generate identifier for VBO and copy data to GPU
	glGenBuffers(1, &g_VBO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);

	// generate identifier for IBO and copy data to GPU
	glGenBuffers(1, &g_IBO_cube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_cube);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_cube);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_cube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_cube);

	// interleaved attributes
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

	glEnableVertexAttribArray(positionIndex);   // enable vertex attributes
	glEnableVertexAttribArray(colorIndex);

	generate_circle();

	//////////////////////////////////////// P A T H ////////////////////////////////////////////
	// create VBO and buffer the data
	glGenBuffers(1, &g_VBO_path1);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_path1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * (G_SLICES + 2), g_vertices_circle, GL_STATIC_DRAW);

	glGenBuffers(1, &g_VBO_path2);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_path2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * (G_SLICES + 2), g_colors_circle, GL_STATIC_DRAW);

	// create VAO and specify VBO data
	glGenVertexArrays(1, &g_VAO_path);
	glBindVertexArray(g_VAO_path);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_path1);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);  // specify the form of the data
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_path2);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0); // specify the form of the data

	glEnableVertexAttribArray(positionIndex);   // enable vertex attributes
	glEnableVertexAttribArray(colorIndex);

	//////////////////////////////////////// R I N G ////////////////////////////////////////////
	// create VBO and buffer the data
	glGenBuffers(1, &g_VBO_ring1);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_ring1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * (G_SLICES + 2), g_vertices_circle, GL_STATIC_DRAW);

	glGenBuffers(1, &g_VBO_ring2);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_ring2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * (G_SLICES + 2), g_colors_ring, GL_STATIC_DRAW);

	// create VAO and specify VBO data
	glGenVertexArrays(1, &g_VAO_ring);
	glBindVertexArray(g_VAO_ring);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_ring1);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);  // specify the form of the data
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_ring2);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0); // specify the form of the data

	glEnableVertexAttribArray(positionIndex);   // enable vertex attributes
	glEnableVertexAttribArray(colorIndex);

}

// function used to update the scene
static void update_scene(GLFWwindow* window)
{
	// static variables for rotation angles
	static float orbitAngle[4] = { 0.0f, 0.0f, 0.0f, 0.0f };				// orbit angle array
	static float rotationAngle[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };		// rotation angle array
	float scaleFactor = 0.1;

	// update rotation angles
	orbitAngle[0] += g_orbitSpeed[0] * scaleFactor;
	orbitAngle[1] += g_orbitSpeed[1] * scaleFactor;
	orbitAngle[2] += g_orbitSpeed[2] * scaleFactor;
	orbitAngle[3] += g_orbitSpeed[3] * scaleFactor;

	rotationAngle[0] += g_rotationSpeed[0] * scaleFactor;
	rotationAngle[1] += g_rotationSpeed[1] * scaleFactor;
	rotationAngle[2] += g_rotationSpeed[2] * scaleFactor;
	rotationAngle[3] += g_rotationSpeed[3] * scaleFactor;
	rotationAngle[4] += g_rotationSpeed[4] * scaleFactor;

	// update model matrix
	//Sun
	g_modelMatrix[0] = glm::rotate(rotationAngle[0], glm::vec3(0.0f, 1.0f, 0.0f));		// allows rotation on its own axis

	// Planet 1
	g_modelMatrix[1] = (glm::rotate(orbitAngle[0], glm::vec3(0.0f, 1.0f, 0.0f))			// allows orbiting around the Sun
		* glm::translate(glm::vec3(4.0f, 0.0f, 0.0f))									// offsets planet to it to orbit around the Sun
		* glm::rotate(rotationAngle[1], glm::vec3(0.0f, 1.0f, 0.0f))					// rotates on its own axis
		* glm::scale(glm::vec3(g_planetSize[0], g_planetSize[0], g_planetSize[0])));	// resizes the planet

	// Planet 2
	g_modelMatrix[2] = glm::rotate(orbitAngle[1], glm::vec3(0.0f, 1.0f, 0.0f))			// same
		* glm::translate(glm::vec3(8.0f, 0.0f, 0.0f))									// as
		* glm::rotate(rotationAngle[2], glm::vec3(0.0f, 1.0f, 0.0f))					// above
		* glm::scale(glm::vec3(g_planetSize[1], g_planetSize[1], g_planetSize[1]));		// !

	// Planet 3
	g_modelMatrix[3] = glm::rotate(orbitAngle[2], glm::vec3(0.0f, 1.0f, 0.0f))			// same
		* glm::translate(glm::vec3(12.0f, 0.0f, 0.0f))									// as
		* glm::rotate(rotationAngle[3], glm::vec3(0.0f, 1.0f, 0.0f))					// above
		* glm::scale(glm::vec3(g_planetSize[2], g_planetSize[2], g_planetSize[2]));		// !

	// Planet 3's Moon
	g_modelMatrix[5] = glm::rotate(orbitAngle[2], glm::vec3(0.0f, 1.0f, 0.0f))			// allows orbiting around the Sun
		* glm::translate(glm::vec3(12.0f, 0.0f, 0.0f))									// offsets Moon to position of planet 3
		* glm::rotate(rotationAngle[3] * 4.0f, glm::vec3(0.0f, 1.0f, 0.0f))				// rotates on its own axis
		* glm::scale(glm::vec3(g_planetSize[2], g_planetSize[2], g_planetSize[2]))		// resizes the Moon to be the same size as planet 3 (it is later rescaled down)
		* glm::rotate(orbitAngle[2] * 3.5f, glm::vec3(0.0f, 1.0f, 0.0f));				// allows orbiting around Planet 3

	// Planet 4
	g_modelMatrix[4] = glm::rotate(orbitAngle[3], glm::vec3(0.0f, 1.0f, 0.0f))			// same
		* glm::translate(glm::vec3(16.0f, 0.0f, 0.0f))									// as
		* glm::rotate(rotationAngle[4], glm::vec3(0.0f, 1.0f, 0.0f))					// planet 1
		* glm::scale(glm::vec3(g_planetSize[3], g_planetSize[3], g_planetSize[3]));		// !

	// update model matrix paths
	g_modelMatrixCircle[0] = glm::translate(glm::vec3(g_orbitPath[0], 0.0f, 0.0f))		// offset it to its planet's random path
		* glm::scale(glm::vec3(8.0f, 8.0f, 8.0f))										// scaled up to match the rotation of its planet around the Sun
		* glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));				// rotated so it will be flat side down

	g_modelMatrixCircle[1] = glm::translate(glm::vec3(g_orbitPath[1], 0.0f, 0.0f))		// same
		* glm::scale(glm::vec3(16.0f, 16.0f, 16.0f))									// as
		* glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));				// above

	g_modelMatrixCircle[2] = glm::translate(glm::vec3(g_orbitPath[2], 0.0f, 0.0f))		// same
		* glm::scale(glm::vec3(24.0f, 24.0f, 24.0f))									// as
		* glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));				// above

	g_modelMatrixCircle[3] = glm::translate(glm::vec3(g_orbitPath[3], 0.0f, 0.0f))		// same
		* glm::scale(glm::vec3(32.0f, 32.0f, 32.0f))									// as
		* glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));				// above

	g_modelMatrixCircle[4] = glm::rotate(orbitAngle[1], glm::vec3(0.0f, 1.0f, 0.0f))	// offset to the same random path as planet 2
		* glm::translate(glm::vec3(8.0f, 0.0f, 0.0f))									// move it to the same position as planet 2
		* glm::scale(glm::vec3(g_planetSize[1] + 1.0f, g_planetSize[1] + 1.0f, g_planetSize[1] + 1.0f)) // scale it to be bigger than planet 2
		* glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));				// rotated so it will be flat side down

	// variables to store forward/back and strafe movement
	float moveForward = 0;
	float strafeRight = 0;
	float zoom = 0;

	// update movement variables based on keyboard input
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		moveForward += 1 * (MOVEMENT_SENSITIVITY * 4);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		moveForward -= 1 * (MOVEMENT_SENSITIVITY * 4);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		strafeRight -= 1 * MOVEMENT_SENSITIVITY;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		strafeRight += 1 * MOVEMENT_SENSITIVITY;

	// update zoom based on keyboard input
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		zoom -= 1 * ZOOM_SENSITIVITY;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		zoom += 1 * ZOOM_SENSITIVITY;

	/*if (zoom > 0 || zoom < 0)
		g_camera.updateFOV(zoom);				// change camera FOV
	*/

	g_camera.update(moveForward, strafeRight);	// updates camera

	if (view == 1)
	{
		mPositionCam1 = g_camera.getPosition(); // stores position of cam 1
	}

	if (view == 2)
	{
		mPositionCam2 = g_camera.getPosition(); // stores position of cam 2
	}
}

// function used to render the scene
static void render_scene()
{
	glm::mat4 MVP;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear colour buffer and depth buffer
	glUseProgram(g_shaderProgramID);					// use the shaders associated with the shader program
	glBindVertexArray(g_VAO_path);						// make VAO active

// Path 1
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* g_modelMatrixCircle[0];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawArrays(GL_LINE_LOOP, 0, G_SLICES + 2);    // display the vertices based on the primitive type

// Path 2                                              
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* g_modelMatrixCircle[1];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawArrays(GL_LINE_LOOP, 0, G_SLICES + 2);    // display the vertices based on the primitive type

// Path 3                                              
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* g_modelMatrixCircle[2];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawArrays(GL_LINE_LOOP, 0, G_SLICES + 2);    // display the vertices based on the primitive type

// Path 4                                              
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* g_modelMatrixCircle[3];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawArrays(GL_LINE_LOOP, 0, G_SLICES + 2);	// display the vertices based on the primitive type

	glBindVertexArray(g_VAO_ring);					// make VAO active

// Planet 2's Ring
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* glm::translate(glm::vec3(g_orbitPath[1], 0.0f, 0.0f)) // offset it to the path taken by its planet
		* g_modelMatrixCircle[4];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawArrays(GL_TRIANGLE_FAN, 0, G_SLICES + 2); // display the vertices based on the primitive type

	glBindVertexArray(g_VAO_cube);					// make VAO active

// Sun
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* g_modelMatrix[0];
	
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);	// set uniform model transformation matrix
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);		// display the vertices based on their indices and primitive type

// Planet 1
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* glm::translate(glm::vec3(g_orbitPath[0], 0.0f, 0.0f)) // offset its path in world space
		* (g_modelMatrix[1] * glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f)));

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type

// Planet 2
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* glm::translate(glm::vec3(g_orbitPath[1], 0.0f, 0.0f)) // offset its path in world space
		* g_modelMatrix[2];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type

// Planet 3
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* glm::translate(glm::vec3(g_orbitPath[2], 0.0f, 0.0f)) // offset its path in world space
		* g_modelMatrix[3];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type

// Planet 3's Moon
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* glm::translate(glm::vec3(g_orbitPath[2], 0.0f, 0.0f)) // offset to its planet's path in world space
		* (g_modelMatrix[5] * glm::translate(glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::vec3(0.3f, 0.3f, 0.3f))); // offsets the Moon away from its planet to allow orbiting and to avoid collision, scales the Moon down to 1/3 the size

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha_default);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type

// Planet 4
	MVP = g_camera.getProjectionMatrix() 
		* g_camera.getViewMatrix() 
		* glm::translate(glm::vec3(g_orbitPath[3], 0.0f, 0.0f)) // offset its path in world space
		* g_modelMatrix[4];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniform1fv(g_alphaIndex, 1, &g_alpha);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type
	
	glFlush();	// flush the pipeline
}

// key press or release callback function
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// quit if the ESCAPE key was pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// set flag to close the window
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	// toggles bool when 'p' is pressed
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (g_pPress == false) 
		{
			g_pPress = true;
		}

		else if (g_pPress == true) 
		{
			g_pPress = false;
		}
	}

	// randomizes speed/size when 'r' is pressed
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		cout << "Rotation Speed: " << endl;
		for (int i = 0; i < 5; i++) {
			g_rotationSpeed[i] = rng(1, 65);

			if (i == 0) 
			{
				cout << "Sun: " << g_rotationSpeed[i] << endl;
			}

			else 
			{
				cout << "Planet " << i << ": " << g_rotationSpeed[i] << endl;
			}
		}
		cout << endl;

		cout << "Orbit Speed: " << endl;
		for (int i = 0; i < 4; i++) {
			g_orbitSpeed[i] = rng(1, 50);
			cout << "Planet " << i + 1 << ": " << g_orbitSpeed[i] << endl;
		}
		cout << endl;

		cout << "Planet Size: " << endl;
		for (int i = 0; i < 4; i++) {
			g_planetSize[i] = rng(20, 80);
			cout << "Planet " << i + 1 << ": " << g_planetSize[i] << endl;
		}
		cout << endl;

		cout << "Orbit Path Displacement: " << endl;
		for (int i = 0; i < 4; i++) {
			g_orbitPath[i] = pathrng();
			cout << "Planet " << i + 1 << ": " << g_orbitPath[i] << endl;
		}
		cout << endl;

		cout << "\n###########\n" << endl;
	}

	// changes camera view according to number
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		g_camera.setViewMatrix(mPositionCam1, mLookAtCam, mUpCam);
		g_camera.setPitch(g_pitch1);
		g_camera.setYaw(g_yaw1);
		view = 1;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		g_camera.setViewMatrix(mPositionCam2, mLookAtCam, mUpCam);
		g_camera.setPitch(g_pitch2);
		g_camera.setYaw(g_yaw2);
		view = 2;
	}

	// resets position if '0' is pressed
	if (view == 1 && key == GLFW_KEY_0 && action == GLFW_PRESS) {
		mPositionCam1 = glm::vec3(0, 15, 30);
		g_pitch1 = -0.5f;
		g_yaw1 = 0.0f;
		g_camera.setViewMatrix(mPositionCam1, mLookAtCam, mUpCam);
		g_camera.setPitch(g_pitch1);
		g_camera.setYaw(0);
	}

	if (view == 2 && key == GLFW_KEY_0 && action == GLFW_PRESS) {
		mPositionCam2 = glm::vec3(0, 40, 3.5);
		g_pitch2 = -1.5f;
		g_yaw2 = 0.0f;
		g_camera.setViewMatrix(mPositionCam2, mLookAtCam, mUpCam);
		g_camera.setPitch(g_pitch2);
		g_camera.setYaw(0);
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// variables to store mouse cursor coordinates
	static double previous_xpos = xpos;
	static double previous_ypos = ypos;
	double delta_x = previous_xpos - xpos;
	double delta_y = previous_ypos - ypos;

	if (g_moveCamera)
	{
		// pass mouse movement to camera class to update its yaw and pitch
		g_camera.updateRotation(delta_x * ROTATION_SENSITIVITY, delta_y * ROTATION_SENSITIVITY);
	}

	// update previous mouse coordinates
	previous_xpos = xpos;
	previous_ypos = ypos;

	if (view == 1) {
		g_pitch1 = g_camera.getPitch(); // stores pitch and yaw of cam 1
		g_yaw1 = g_camera.getYaw();
	}

	if (view == 2) {
		g_pitch2 = g_camera.getPitch(); // stores pitch and yaw of cam 2
		g_yaw2 = g_camera.getYaw();
	}
	
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		// use mouse to move camera, hence use disable cursor mode
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		g_moveCamera = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		// use mouse to move camera, hence use disable cursor mode
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		g_moveCamera = false;
	}
}

// error callback function
static void error_callback(int error, const char* description)
{
	cerr << description << endl;			// output error description
}

int main(void)
{
	GLFWwindow* window = NULL;				// pointer to a GLFW window handle

	glfwSetErrorCallback(error_callback);	// set error callback function

	// initialise GLFW
	if (!glfwInit())
	{
		// if failed to initialise GLFW
		exit(EXIT_FAILURE);
	}

	// minimum OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// create a window and its OpenGL context
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment 1 -- Planets", NULL, NULL);

	// if failed to create window
	if (window == NULL)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);	// set window context as the current context
	glfwSwapInterval(1);			// swap buffer interval

	// initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		// if failed to initialise GLEW
		cerr << "GLEW initialisation failed" << endl;
		exit(EXIT_FAILURE);
	}

	// set key callback function
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// initialise rendering states
	init(window);

	// initialise speed & size variables
	srand(time(0));

	cout << "Rotation Speed: " << endl;
	for (int i = 0; i < 5; i++) {
		g_rotationSpeed[i] = rng(1, 65);

		if (i == 0)
		{
			cout << "Sun: " << g_rotationSpeed[i] << endl;
		}

		else
		{
			cout << "Planet " << i << ": " << g_rotationSpeed[i] << endl;
		}
	}
	cout << endl;

	cout << "Orbit Speed: " << endl;
	for (int i = 0; i < 4; i++) {
		g_orbitSpeed[i] = rng(1, 50);
		cout << "Planet " << i + 1 << ": " << g_orbitSpeed[i] << endl;
	}
	cout << endl;

	cout << "Planet Size: " << endl;
	for (int i = 0; i < 4; i++) {
		g_planetSize[i] = rng(20, 80);
		cout << "Planet " << i + 1 << ": " << g_planetSize[i] << endl;
	}
	cout << endl;

	cout << "Orbit Path Displacement: " << endl;
	for (int i = 0; i < 4; i++) {
		g_orbitPath[i] = pathrng();
		cout << "Planet " << i + 1 << ": " << g_orbitPath[i] << endl;
	}
	cout << endl;

	cout << "\n###########\n" << endl;

	// variables for simple time management
	float lastUpdateTime = glfwGetTime();
	float currentTime = lastUpdateTime;
	g_moveCamera = false;

	// the rendering loop
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();

		// only update if more than 0.02 seconds since last update
		if (currentTime - lastUpdateTime > 0.02)
		{
			if (g_pPress == true)
			{
				update_scene(window);		// update the scene
			}

			render_scene();					// render the scene

			glfwSwapBuffers(window);		// swap buffers
			glfwPollEvents();				// poll for events
			constexpr float factor = 2;										//Higher == faster fade, lower == slower fade
			g_alpha = (float(std::sin(glfwGetTime() * factor) + 1) / 2);	//Generates a Sine Wave in range [0, 1]

			lastUpdateTime = currentTime;	// update last update time
		}
	}

	// clean up
	glDeleteProgram(g_shaderProgramID);
	glDeleteBuffers(1, &g_IBO_cube);
	glDeleteBuffers(1, &g_VBO_cube);
	glDeleteBuffers(1, &g_VBO_path1);
	glDeleteBuffers(1, &g_VBO_path2);
	glDeleteBuffers(1, &g_VBO_ring1);
	glDeleteBuffers(1, &g_VBO_ring2);
	glDeleteVertexArrays(1, &g_VAO_cube);
	glDeleteVertexArrays(1, &g_VAO_cube);
	glDeleteVertexArrays(1, &g_VAO_ring);

	// close the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

