#include <cstdio>		// for C++ i/o
#include <iostream>
#include <string>
#include <cstddef>
#include <time.h>
#include <array>
using namespace std;	// to avoid having to use std::

#define GLEW_STATIC		// include GLEW as a static library
#include <GLEW/glew.h>	// include GLEW
#include <GLFW/glfw3.h>	// include GLFW (which includes the OpenGL header)
#include <glm/glm.hpp>	// include GLM (ideally should only use the GLM headers that are actually used)
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;	// to avoid having to use glm::

#include <AntTweakBar.h>
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "shader.h"
#include "Camera.h"

#define MOVEMENT_SENSITIVITY 3.0f		// camera movement sensitivity
#define ROTATION_SENSITIVITY 0.3f		// camera rotation sensitivity
#define MAX_LIGHTS 2

// struct for vertex attributes
typedef struct Vertex
{
	GLfloat position[3];
	GLfloat normal[3];
} Vertex;

// struct for line attributes
typedef struct Line
{
	GLfloat position[3];
	GLfloat color[3];
} Line;

// struct for mesh properties
typedef struct Mesh
{
	Vertex* pMeshVertices;		// pointer to mesh vertices
	GLint numberOfVertices;		// number of vertices in the mesh
	GLint* pMeshIndices;		// pointer to mesh indices
	GLint numberOfFaces;		// number of faces in the mesh
} Mesh;

// light and material structs
typedef struct PointLight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 attenuation;
	int type;
} PointLight;

typedef struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 attenuation;
	float cutoffAngle;
	int type;
} SpotLight;

typedef struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
} Material;

// Global variables
Line g_lines[] = {
	// vertex 1
	0.0f, 400.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 2
	850.0f, 400.0f, 0.0f,	// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 3
	0.0f, 800.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 4
	850.0f, 800.0f, 0.0f,	// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 5
	0.0f, 0.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 6
	850.0f, 0.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 7
	425.0f, 0.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 8
	425.0f, 800.0f, 0.0f,	// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 9
	1.0f, 0.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 10
	1.0f, 800.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 9
	850.0f, 0.0f, 0.0f,		// position
	1.0f, 1.0f, 1.0f,		// colour
	// vertex 10
	850.0f, 800.0f, 0.0f,	// position
	1.0f, 1.0f, 1.0f,		// colour
	
};

Vertex g_vertices_room[] = {
	// floor
	-2.0f, 0.0f, 2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	2.0f, 0.0f, 2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	-2.0f, 0.0f, -2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	-2.0f, 0.0f, -2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	2.0f, 0.0f, 2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	2.0f, 0.0f, -2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal

	// wall
	-2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
};

Vertex g_vertices_cube[] = {
	// cube
	-0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	0.5f, 0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.5f, 0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.5f, 0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.5f, -0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.5f, -0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, -1.0f,	// normal
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, -1.0f,	// normal
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	-0.5f, -0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	-0.5f, 0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	-0.5f, -0.5f, -0.5f,// position
	-1.0f, 0.0f, 0.0f,	// normal
	-0.5f, -0.5f, -0.5f,// position
	-1.0f, 0.0f, 0.0f,	// normal
	-0.5f, 0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	-0.5f, 0.5f, -0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	-0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	0.5f, -0.5f, -0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	0.5f, -0.5f, -0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	-0.5f, -0.5f, -0.5f,// position
	0.0f, -1.0f, 0.0f,	// normal
};

GLuint g_VBO_room = 0;				// vertex buffer object identifier
GLuint g_VAO_room = 0;				// vertex array object identifier

GLuint g_VBO_cube = 0;				// vertex buffer object identifier
GLuint g_VAO_cube = 0;				// vertex array object identifier

GLuint g_VBO_line = 0;				// vertex buffer object identifier
GLuint g_VAO_line = 0;				// vertex array object identifier

GLuint g_IBO_mesh1 = 0;				// index buffer object identifier
GLuint g_VBO_mesh1 = 0;				// vertex buffer object identifier
GLuint g_VAO_mesh1 = 0;				// vertex array object identifier

GLuint g_IBO_mesh2 = 0;				// index buffer object identifier
GLuint g_VBO_mesh2 = 0;				// vertex buffer object identifier
GLuint g_VAO_mesh2 = 0;				// vertex array object identifier

GLuint g_shaderProgramID = 0;		// shader program identifier
GLuint g_MVP_Index = 0;
GLuint g_MV_Index = 0;
GLuint g_V_Index = 0;

GLuint g_shaderProgramID_line = 0;
GLuint g_MVP_Index_line = 0;

GLuint g_materialAmbientIndex = 0;
GLuint g_materialDiffuseIndex = 0;
GLuint g_materialSpecularIndex = 0;

// locations in shader for point light
GLuint g_PL_lightPositionIndex[MAX_LIGHTS];
GLuint g_PL_lightDirectionIndex[MAX_LIGHTS];
GLuint g_PL_lightAmbientIndex[MAX_LIGHTS];
GLuint g_PL_lightDiffuseIndex[MAX_LIGHTS];
GLuint g_PL_lightSpecularIndex[MAX_LIGHTS];
GLuint g_PL_lightTypeIndex[MAX_LIGHTS];
GLuint g_PL_lightAttenuationIndex[MAX_LIGHTS];

// locations in shader for spot light
GLuint g_SL_lightPositionIndex = 0;
GLuint g_SL_lightDirectionIndex = 0;
GLuint g_SL_lightAmbientIndex = 0;
GLuint g_SL_lightDiffuseIndex = 0;
GLuint g_SL_lightSpecularIndex = 0;
GLuint g_SL_lightAttenuationIndex = 0;
GLuint g_SL_lightCutoffAngleIndex = 0;
GLuint g_SL_lightTypeIndex = 0;

PointLight g_light_point[MAX_LIGHTS];		// point light
SpotLight g_light_spot;						// spot light
Material g_material[13];					// material properties

mat4 g_modelMatrix[16];						// object's model matrix
mat4 g_projectionMatrix;					// projection matrix
mat4 g_viewMatrix;							// view matrix

GLuint g_windowWidth = 1210;				// window dimensions
GLuint g_windowHeight = 900;

float g_frameTime = 0.0f;
Camera g_camera[4];
bool g_moveCamera = false;
bool g_light1_switch = true;
bool g_light2_switch = true;
bool g_light3_switch = true;
bool g_mode_switch = false;
bool g_wireFrame = false;					// wireframe on or off
float g_scale = 1.0f;
float g_rotateAngleX = 0.0f;
float g_rotateAngleY = 0.0f;

vec3 ptLightpos1 = vec3(1.95f, 0.8f, 0.0f);
vec3 ptLightamb1 = vec3(0.3f, 0.3f, 0.3f);
vec3 ptLightspec1 = vec3(0.5f, 0.5f, 0.5f);
vec3 ptLightdiff1 = vec3(0.5f, 0.5f, 0.5f);
vec3 ptLightatten1 = vec3(1.0f, 0.0f, 0.0f);

vec3 ptLightpos2 = vec3(-1.95f, 0.8f, 0.0f);
vec3 ptLightamb2 = vec3(0.3f, 0.3f, 0.3f);
vec3 ptLightspec2 = vec3(0.5f, 0.5f, 0.5f);
vec3 ptLightdiff2 = vec3(0.5f, 0.5f, 0.5f);
vec3 ptLightatten2 = vec3(1.0f, 0.0f, 0.0f);

vec3 spotLightpos = vec3(1.95f, 0.8f, 0.0f);
vec3 spotLightamb = vec3(0.2f, 0.2f, 0.2f);
vec3 spotLightspec = vec3(0.5f, 0.5f, 0.5f);
vec3 spotLightdiff = vec3(0.3f, 0.3f, 0.3f);
vec3 spotLightatten = vec3(1.0f, 0.0f, 0.0f);

vec3 ptLightamb1curr;
vec3 ptLightspec1curr;
vec3 ptLightdiff1curr;
vec3 ptLightatten1curr;

vec3 ptLightamb2curr;
vec3 ptLightspec2curr;
vec3 ptLightdiff2curr;
vec3 ptLightatten2curr;

vec3 spotLightambcurr;
vec3 spotLightspeccurr;
vec3 spotLightdiffcurr;
vec3 spotLightattencurr;

// ornament info
vec3 orna1pos = vec3(0.0f, 0.45f, 0.2f);
float orna1rot = 0.0;
vec3 orna2pos = vec3(0.0f, 0.4f, -0.2f);
float orna2rot = 180.0;

int light1round = 1;
bool reset = false;
bool view = false;

Mesh g_mesh[2];								// meshes

/////////////// E T C - ///////////////

vec3 vec3rng(int lo, int hi, string abc)
{
	int cap = hi - lo; // to get maximum number
	float a, b, c;

	if (abc == "abc") // changes axis x, y, z
	{
		a = (rand() % cap + lo);
		a /= 100;
		b = (rand() % cap + lo);
		b /= 100;
		c = (rand() % cap + lo);
		c /= 100;
	}

	else if (abc == "ac") // changes axis x and z
	{
		a = (rand() % cap + lo);
		a /= 100;
		b = -1.0f; // ac is for direction thus axis y is set as such
		c = (rand() % cap + lo);
		c /= 100;
	}

	return vec3(a, b, c);
}

bool load_mesh(const char* fileName, Mesh* mesh)
{
	// load file with assimp 
	const aiScene* pScene = aiImportFile(fileName, aiProcess_Triangulate
		| aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	// check whether scene was loaded
	if (!pScene)
	{
		cout << "Could not load mesh." << endl;
		return false;
	}

	// get pointer to mesh 0
	const aiMesh* pMesh = pScene->mMeshes[0];

	// store number of mesh vertices
	mesh->numberOfVertices = pMesh->mNumVertices;

	// if mesh contains vertex coordinates
	if (pMesh->HasPositions())
	{
		// allocate memory for vertices
		mesh->pMeshVertices = new Vertex[pMesh->mNumVertices];

		// read vertex coordinates and store in the array
		for (int i = 0; i < pMesh->mNumVertices; i++)
		{
			const aiVector3D* pVertexPos = &(pMesh->mVertices[i]);

			mesh->pMeshVertices[i].position[0] = (GLfloat)pVertexPos->x;
			mesh->pMeshVertices[i].position[1] = (GLfloat)pVertexPos->y;
			mesh->pMeshVertices[i].position[2] = (GLfloat)pVertexPos->z;
		}
	}

	// if mesh contains normals
	if (pMesh->HasNormals())
	{
		// read normals and store in the array
		for (int i = 0; i < pMesh->mNumVertices; i++)
		{
			const aiVector3D* pVertexNormal = &(pMesh->mNormals[i]);

			mesh->pMeshVertices[i].normal[0] = (GLfloat)pVertexNormal->x;
			mesh->pMeshVertices[i].normal[1] = (GLfloat)pVertexNormal->y;
			mesh->pMeshVertices[i].normal[2] = (GLfloat)pVertexNormal->z;
		}
	}

	// if mesh contains faces
	if (pMesh->HasFaces())
	{
		// store number of mesh faces
		mesh->numberOfFaces = pMesh->mNumFaces;

		// allocate memory for vertices
		mesh->pMeshIndices = new GLint[pMesh->mNumFaces * 3];

		// read normals and store in the array
		for (int i = 0; i < pMesh->mNumFaces; i++)
		{
			const aiFace* pFace = &(pMesh->mFaces[i]);

			mesh->pMeshIndices[i * 3] = (GLint)pFace->mIndices[0];
			mesh->pMeshIndices[i * 3 + 1] = (GLint)pFace->mIndices[1];
			mesh->pMeshIndices[i * 3 + 2] = (GLint)pFace->mIndices[2];
		}
	}

	// release the scene
	aiReleaseImport(pScene);

	return true;
}

/////////////// D R A W ///////////////

void draw_lights()
{
	glUseProgram(g_shaderProgramID);	// use the shaders associated with the shader program

	// point light
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		glUniform3fv(g_PL_lightPositionIndex[i], 1, &g_light_point[i].position[0]);
		glUniform3fv(g_PL_lightAmbientIndex[i], 1, &g_light_point[i].ambient[0]);
		glUniform3fv(g_PL_lightDiffuseIndex[i], 1, &g_light_point[i].diffuse[0]);
		glUniform3fv(g_PL_lightSpecularIndex[i], 1, &g_light_point[i].specular[0]);
		glUniform3fv(g_PL_lightAttenuationIndex[i], 1, &g_light_point[i].attenuation[0]);
		glUniform1i(g_PL_lightTypeIndex[i], g_light_point[i].type);
	}

	// spot light
	glUniform3fv(g_SL_lightPositionIndex, 1, &g_light_spot.position[0]);
	glUniform3fv(g_SL_lightDirectionIndex, 1, &g_light_spot.direction[0]);
	glUniform3fv(g_SL_lightAmbientIndex, 1, &g_light_spot.ambient[0]);
	glUniform3fv(g_SL_lightDiffuseIndex, 1, &g_light_spot.diffuse[0]);
	glUniform3fv(g_SL_lightSpecularIndex, 1, &g_light_spot.specular[0]);
	glUniform3fv(g_SL_lightAttenuationIndex, 1, &g_light_spot.attenuation[0]);
	glUniform1f(g_SL_lightCutoffAngleIndex, g_light_spot.cutoffAngle);
	glUniform1i(g_SL_lightTypeIndex, g_light_spot.type);
}

void draw_room(int i, string s)
{
	glUseProgram(g_shaderProgramID);	// use the shaders associated with the shader program

	glBindVertexArray(g_VAO_room);		// make VAO active

	mat4 MVP;
	mat4 MV;
	mat4 V;

	if (s == "ceiling")
	{
		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[0];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[0];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[3].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[3].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[3].specular[0]);

		// draw floor
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[1];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[1];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall back
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[2];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[2];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall right
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[3];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[3];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall left
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[4];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[4];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall front
		glDrawArrays(GL_TRIANGLES, 6, 12);// set shader variables
	}

	if (s == "front")
	{
		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[0];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[0];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[3].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[3].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[3].specular[0]);

		// draw floor
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[1];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[1];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall back
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[2];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[2];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall right
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[3];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[3];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall left
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[15];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[15];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[12].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[12].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[12].specular[0]);

		// draw ceiling
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	if (s == "side")
	{
		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[0];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[0];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[3].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[3].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[3].specular[0]);

		// draw floor
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[1];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[1];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall back
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[2];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[2];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall right
		glDrawArrays(GL_TRIANGLES, 6, 12);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[15];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[15];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[12].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[12].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[12].specular[0]);

		// draw ceiling
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// set shader variables
		MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[4];
		MV = g_camera[i].getViewMatrix() * g_modelMatrix[4];
		V = g_camera[i].getViewMatrix();
		glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

		glUniform3fv(g_materialAmbientIndex, 1, &g_material[4].ambient[0]);
		glUniform3fv(g_materialDiffuseIndex, 1, &g_material[4].diffuse[0]);
		glUniform3fv(g_materialSpecularIndex, 1, &g_material[4].specular[0]);

		// draw wall front
		glDrawArrays(GL_TRIANGLES, 6, 12);
	}
}

void draw_objects(int i)
{
	mat4 MVP;
	mat4 MV;
	mat4 V;

	glUseProgram(g_shaderProgramID);	// use the shaders associated with the shader program

	glBindVertexArray(g_VAO_cube);		// make VAO active

	// set shader variables
	mat4 modelMatrix = mat4(1.0f);
	MVP = mat4(1.0f);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[5];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	V = g_camera[i].getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[5].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[5].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[5].specular[0]);

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 30);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[6];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[6].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[6].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[6].specular[0]);

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 30);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[7];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[7].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[7].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[7].specular[0]);

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 30);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[8];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[8].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[8].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[8].specular[0]);

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 30);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[9];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[9].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[9].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[9].specular[0]);

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 30);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[12];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[0].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[0].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[0].specular[0]);

	// draw lamp
	glDrawArrays(GL_TRIANGLES, 0, 30);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[13];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[1].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[1].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[1].specular[0]);

	// draw lamp
	glDrawArrays(GL_TRIANGLES, 0, 30);

	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[14];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[2].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[2].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[2].specular[0]);

	// draw lamp
	glDrawArrays(GL_TRIANGLES, 0, 30);
}

void draw_monkey(int i)
{
	mat4 MVP;
	mat4 MV;
	mat4 V;

	// set shader variables
	mat4 modelMatrix = mat4(1.0f);
	MVP = mat4(1.0f);

	glUseProgram(g_shaderProgramID);	// use the shaders associated with the shader program

	glBindVertexArray(g_VAO_mesh1);		// make VAO active

	// set uniform shader variables
	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[10];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[10].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[10].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[10].specular[0]);

	glDrawElements(GL_TRIANGLES, g_mesh[0].numberOfFaces * 3, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type
}

void draw_bull(int i)
{
	mat4 MVP;
	mat4 MV;
	mat4 V;

	// set shader variables
	mat4 modelMatrix = mat4(1.0f);
	MVP = mat4(1.0f);

	glUseProgram(g_shaderProgramID);	// use the shaders associated with the shader program

	glBindVertexArray(g_VAO_mesh2);		// make VAO active

	// set uniform shader variables
	MVP = g_camera[i].getProjectionMatrix() * g_camera[i].getViewMatrix() * g_modelMatrix[11];
	MV = g_camera[i].getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index, 1, GL_FALSE, &MV[0][0]);

	glUniform3fv(g_materialAmbientIndex, 1, &g_material[11].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex, 1, &g_material[11].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex, 1, &g_material[11].specular[0]);

	glDrawElements(GL_TRIANGLES, g_mesh[1].numberOfFaces * 3, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type
}

void draw_lines()
{
	glUseProgram(g_shaderProgramID_line);	// use the shaders associated with the shader program

	glBindVertexArray(g_VAO_line);		// make VAO for lines active

	mat4 MVP = g_projectionMatrix * g_viewMatrix;
	glUniformMatrix4fv(g_MVP_Index_line, 1, GL_FALSE, &MVP[0][0]);
	glDrawArrays(GL_LINES, 0, 12);	// display the lines
}

/////////////// V I E W ///////////////

void render_four_view()
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Top Left viewport
	glViewport(340, 452, 400, 400);

	draw_room(0, "ceiling");
	draw_objects(0);
	draw_monkey(0);
	draw_bull(0);
	draw_lights();

	// Top Right viewport
	glViewport(340, 50, 400, 400);

	draw_room(1, "front");
	draw_objects(1);
	draw_monkey(1);
	draw_bull(1);
	draw_lights();

	// Bottom Left viewport
	glViewport(760, 455, 400, 400);

	draw_room(2, "side");
	draw_objects(2);
	draw_monkey(2);
	draw_bull(2);
	draw_lights();

	// Bottom Right viewport
	glViewport(765, 80, 400, 400);

	draw_room(3, "ceiling");
	draw_objects(3);
	draw_monkey(3);
	draw_bull(3);
	draw_lights();

	// Draw lines in screen space
	glViewport(325, 50, 1200, 900);

	draw_lines();

	glFlush();	// flush the pipeline
}

void render_persp_view()
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glViewport(255, 150, 1000, 725);
	draw_room(3, "ceiling");
	draw_objects(3);
	draw_monkey(3);
	draw_bull(3);
	draw_lights();

	glFlush();	// flush the pipeline
}

/////////////// M A I N ///////////////

static void init(GLFWwindow* window)
{
	glEnable(GL_DEPTH_TEST);	// enable depth buffer test

	// create and compile our GLSL program from the shader files
	g_shaderProgramID = loadShaders("MVP_VS.vert", "ColorFS.frag");
	g_shaderProgramID_line = loadShaders("LineVS.vert", "LineColor.frag");

	// find the location of shader variables
	GLuint positionIndex = glGetAttribLocation(g_shaderProgramID, "aPosition");
	GLuint normalIndex = glGetAttribLocation(g_shaderProgramID, "aNormal");
	g_MVP_Index = glGetUniformLocation(g_shaderProgramID, "uModelViewProjectionMatrix");
	g_MV_Index = glGetUniformLocation(g_shaderProgramID, "uModelViewMatrix");
	g_V_Index = glGetUniformLocation(g_shaderProgramID, "uViewMatrix");

	GLuint positionIndex_line = glGetAttribLocation(g_shaderProgramID_line, "aPosition");
	GLuint colorIndex_line = glGetAttribLocation(g_shaderProgramID_line, "aColor");
	g_MVP_Index_line = glGetUniformLocation(g_shaderProgramID_line, "uModelViewProjectionMatrix");

	// point light
	g_PL_lightPositionIndex[0] = glGetUniformLocation(g_shaderProgramID, "uPtLight[0].position");
	g_PL_lightDirectionIndex[0] = glGetUniformLocation(g_shaderProgramID, "uPtLight[0].direction");
	g_PL_lightAmbientIndex[0] = glGetUniformLocation(g_shaderProgramID, "uPtLight[0].ambient");
	g_PL_lightDiffuseIndex[0] = glGetUniformLocation(g_shaderProgramID, "uPtLight[0].diffuse");
	g_PL_lightSpecularIndex[0] = glGetUniformLocation(g_shaderProgramID, "uPtLight[0].specular");
	g_PL_lightTypeIndex[0] = glGetUniformLocation(g_shaderProgramID, "uPtLight[0].type");
	g_PL_lightAttenuationIndex[0] = glGetUniformLocation(g_shaderProgramID, "uPtLight[0].attenuation");

	g_PL_lightPositionIndex[1] = glGetUniformLocation(g_shaderProgramID, "uPtLight[1].position");
	g_PL_lightDirectionIndex[1] = glGetUniformLocation(g_shaderProgramID, "uPtLight[1].direction");
	g_PL_lightAmbientIndex[1] = glGetUniformLocation(g_shaderProgramID, "uPtLight[1].ambient");
	g_PL_lightDiffuseIndex[1] = glGetUniformLocation(g_shaderProgramID, "uPtLight[1].diffuse");
	g_PL_lightSpecularIndex[1] = glGetUniformLocation(g_shaderProgramID, "uPtLight[1].specular");
	g_PL_lightTypeIndex[1] = glGetUniformLocation(g_shaderProgramID, "uPtLight[1].type");
	g_PL_lightAttenuationIndex[1] = glGetUniformLocation(g_shaderProgramID, "uPtLight[1].attenuation");

	// spot light
	g_SL_lightPositionIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.position");
	g_SL_lightDirectionIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.direction");
	g_SL_lightAmbientIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.ambient");
	g_SL_lightDiffuseIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.diffuse");
	g_SL_lightSpecularIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.specular");
	g_SL_lightAttenuationIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.attenuation");
	g_SL_lightCutoffAngleIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.cutoffAngle");
	g_SL_lightTypeIndex = glGetUniformLocation(g_shaderProgramID, "uSpotLight.type");

	g_materialAmbientIndex = glGetUniformLocation(g_shaderProgramID, "uMaterial.ambient");
	g_materialDiffuseIndex = glGetUniformLocation(g_shaderProgramID, "uMaterial.diffuse");
	g_materialSpecularIndex = glGetUniformLocation(g_shaderProgramID, "uMaterial.specular");

	// initialise model matrix to the identity matrix
	for (int i = 0; i < sizeof(g_modelMatrix) / sizeof(g_modelMatrix[0]); i++)
	{
		g_modelMatrix[i] = mat4(1.0f);
	}

	// line
	// initialise view matrix
	g_viewMatrix = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// initialise projection matrix
	g_projectionMatrix = glm::ortho(0.0f, 1200.0f, 0.0f, 900.0f, 0.1f, 100.0f);

	// room
	g_modelMatrix[1] = rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))
		* translate(vec3(0.0f, -2.0f, -0.5f));
	g_modelMatrix[2] = rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))
		* rotate(radians(90.0f), vec3(0.0f, 0.0f, 1.0f))
		* translate(vec3(0.0f, -2.0f, -0.5f));
	g_modelMatrix[3] = rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))
		* rotate(radians(90.0f), vec3(0.0f, 0.0f, -1.0f))
		* translate(vec3(0.0f, -2.0f, -0.5f));
	g_modelMatrix[4] = rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))
		* translate(vec3(0.0f, 2.0f, -0.5f));
	g_modelMatrix[15] = translate(vec3(0.0f, 1.0f, 0.0f));

	// objects
	g_modelMatrix[5] = translate(vec3(0.0f, 0.2f, 0.0f)) * scale(vec3(0.8f, 0.4f, 0.8f)); // table

	g_modelMatrix[6] = translate(vec3(0.0f, 0.1f, 0.8f)) * scale(vec3(0.4f, 0.2f, 0.4f)); // stools
	g_modelMatrix[7] = translate(vec3(0.8f, 0.1f, 0.0f)) * scale(vec3(0.4f, 0.2f, 0.4f)); // ...
	g_modelMatrix[8] = translate(vec3(0.0f, 0.1f, -0.8f)) * scale(vec3(0.4f, 0.2f, 0.4f)); // ...
	g_modelMatrix[9] = translate(vec3(-0.8f, 0.1f, 0.0f)) * scale(vec3(0.4f, 0.2f, 0.4f)); // ...

	g_modelMatrix[10] = translate(orna1pos) * scale(vec3(0.06f, 0.06f, 0.06f)) * rotate(radians(orna1rot), vec3(0.0f, 1.0f, 0.0f)); // ornaments
	g_modelMatrix[11] = translate(orna2pos) * scale(vec3(0.08f, 0.08f, 0.08f)) * rotate(radians(orna2rot), vec3(0.0f, 1.0f, 0.0f)); // ...

	// light source
	g_modelMatrix[12] = translate(ptLightpos1) * scale(vec3(0.1f, 0.1f, 0.1f)); // square light bulb
	g_modelMatrix[13] = translate(ptLightpos2) * scale(vec3(0.1f, 0.1f, 0.1f)); // ...
	g_modelMatrix[14] = translate(vec3(0.0f, 1.0f, 0.0f)) * scale(vec3(0.1f, 0.1f, 0.1f)); // ...

	// initialise view matrix and projection matrix
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / height;

	// set camera's view matrix
	g_camera[0].setViewMatrix(vec3(0, 6, 0.1), vec3(0, 1, 0), vec3(0, 1, 0));	// topdown
	g_camera[1].setViewMatrix(vec3(0, 0.5, 6), vec3(0, 0.5, 0), vec3(0, 1, 0));	// side
	g_camera[2].setViewMatrix(vec3(-12, 1, 0), vec3(6, 0.5, 0), vec3(0, 1, 0));	// front
	g_camera[3].setViewMatrix(vec3(0, 3, 6), vec3(0, 0, 0), vec3(0, 1, 0));		// persp

	// set camera's projection matrix
	g_camera[0].setProjection(radians(45.0f), aspectRatio, 0.1f, 100.0f);
	g_camera[0].setPitch(radians(-20.0f));

	g_camera[1].setProjection(radians(45.0f), aspectRatio, 0.1f, 100.0f);
	g_camera[1].setPitch(radians(-20.0f));

	g_camera[2].setProjection(radians(18.0f), aspectRatio, 0.1f, 100.0f);
	g_camera[2].setPitch(radians(-20.0f));

	g_camera[3].setProjection(radians(45.0f), aspectRatio, 0.1f, 100.0f);
	g_camera[3].setPitch(radians(-20.0f));

	// initialise point light properties
	g_light_point[0].position = vec3(ptLightpos1.x - 0.2f, ptLightpos1.y, ptLightpos1.z);
	g_light_point[0].ambient = vec3(0.3f, 0.3f, 0.3f);
	g_light_point[0].diffuse = vec3(0.5f, 0.5f, 0.5f);
	g_light_point[0].specular = vec3(0.5f, 0.5f, 0.5f);
	g_light_point[0].attenuation = vec3(1.0f, 0.0f, 0.0f);
	g_light_point[0].type = 0;

	g_light_point[1].position = vec3(ptLightpos2.x + 0.2f, ptLightpos2.y, ptLightpos2.z);
	g_light_point[1].ambient = vec3(0.3f, 0.3f, 0.3f);
	g_light_point[1].diffuse = vec3(0.5f, 0.5f, 0.5f);
	g_light_point[1].specular = vec3(0.5f, 0.5f, 0.5f);
	g_light_point[1].attenuation = vec3(1.0f, 0.0f, 0.0f);
	g_light_point[1].type = 0;

	// initialise spot light properties
	g_light_spot.position = vec3(0.0f, 0.9f, 0.0f);
	g_light_spot.direction = vec3(0.0f, -1.0f, 0.0f);
	g_light_spot.ambient = vec3(0.2f, 0.2f, 0.2f);
	g_light_spot.diffuse = vec3(0.3f, 0.3f, 0.3f);
	g_light_spot.specular = vec3(0.5f, 0.5f, 0.5f);
	g_light_spot.attenuation = vec3(1.0f, 0.0f, 0.0f);
	g_light_spot.cutoffAngle = 45.0f;
	g_light_spot.type = 2;
	
	srand(time(0));

	// initialise material properties
	for (int i = 3; i < sizeof(g_material)/sizeof(g_material[0]); i++) 
	{
		g_material[i].ambient = vec3rng(1, 50, "abc");
		g_material[i].diffuse = vec3rng(1, 80, "abc");
		g_material[i].specular = vec3rng(1, 20, "abc");
		cout << "Material " << i << " --\nAmbient: " << to_string(g_material[i].ambient) << "\nDiffuse: " << to_string(g_material[i].diffuse) << "\nSpecular: " << to_string(g_material[i].specular) << endl;
		cout << endl;
	}

	// lamp
	g_material[0].ambient = ptLightamb1;
	g_material[0].diffuse = ptLightdiff1;
	g_material[0].specular = ptLightspec1;

	g_material[1].ambient = ptLightamb2;
	g_material[1].diffuse = ptLightdiff2;
	g_material[1].specular = ptLightspec2;

	g_material[2].ambient = spotLightamb;
	g_material[2].diffuse = spotLightdiff;
	g_material[2].specular = spotLightspec;

	// room
	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_room);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_room);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_room), g_vertices_room, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_room);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_room);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_room);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	// cube
	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_cube), g_vertices_cube, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_cube);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_cube);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	// mesh 1
	g_mesh[0].pMeshVertices = NULL;
	g_mesh[0].pMeshIndices = NULL;
	load_mesh("models/suzanne.obj", &g_mesh[0]);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_mesh1);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_mesh1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_mesh[0].numberOfVertices, g_mesh[0].pMeshVertices, GL_STATIC_DRAW);

	// generate identifier for IBO and copy data to GPU
	glGenBuffers(1, &g_IBO_mesh1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_mesh1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * 3 * g_mesh[0].numberOfFaces, g_mesh[0].pMeshIndices, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_mesh1);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_mesh1);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_mesh1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_mesh1);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	// mesh 2
	g_mesh[1].pMeshVertices = NULL;
	g_mesh[1].pMeshIndices = NULL;
	load_mesh("models/WusonOBJ.obj", &g_mesh[1]);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_mesh2);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_mesh2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_mesh[1].numberOfVertices, g_mesh[1].pMeshVertices, GL_STATIC_DRAW);

	// generate identifier for IBO and copy data to GPU
	glGenBuffers(1, &g_IBO_mesh2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_mesh2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * 3 * g_mesh[1].numberOfFaces, g_mesh[1].pMeshIndices, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_mesh2);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_mesh2);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_mesh2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_mesh2);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	// line
	glGenBuffers(1, &g_VBO_line);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_lines), g_lines, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_line);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_line);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_line);
	glVertexAttribPointer(positionIndex_line, 3, GL_FLOAT, GL_FALSE, sizeof(Line), reinterpret_cast<void*>(offsetof(Line, position)));
	glVertexAttribPointer(colorIndex_line, 3, GL_FLOAT, GL_FALSE, sizeof(Line), reinterpret_cast<void*>(offsetof(Line, color)));

	glEnableVertexAttribArray(positionIndex_line);	// enable vertex attributes
	glEnableVertexAttribArray(colorIndex_line);
}

// function used to update the scene
static void update_scene(GLFWwindow* window, float frameTime)
{
	// variables to store forward/back and strafe movement
	float moveForward = 0;
	float strafeRight = 0;

	// update movement variables based on keyboard input
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		moveForward += 1 * MOVEMENT_SENSITIVITY * frameTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		moveForward -= 1 * MOVEMENT_SENSITIVITY * frameTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		strafeRight -= 1 * MOVEMENT_SENSITIVITY * frameTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		strafeRight += 1 * MOVEMENT_SENSITIVITY * frameTime;

	g_camera[3].update(moveForward, strafeRight);	// update camera

	if (g_mode_switch)
	{
		if (ptLightpos1.z <= 2.0f && ptLightpos1.x >= -1.95f && light1round == 1) // checks for position of the light and check to see if it is in round 1 
																				  // (as first if and last if has similar values, the round is to differentiate between them
		{
			g_modelMatrix[12] = translate(vec3(ptLightpos1.x, ptLightpos1.y, ptLightpos1.z += 0.08f)) * scale(vec3(0.1f, 0.1f, 0.1f)); // if check passes, adds movement to Z axis gradually so animation looks smooth
			g_light_point[0].position = ptLightpos1;

			g_modelMatrix[13] = translate(vec3(ptLightpos2.x, ptLightpos2.y, ptLightpos2.z -= 0.08f)) * scale(vec3(0.1f, 0.1f, 0.1f)); // does the same for light 2
			g_light_point[1].position = ptLightpos2;

			g_modelMatrix[10] = translate(vec3(orna1pos.x, orna1pos.y += 0.001, orna1pos.z)) * scale(vec3(0.06f, 0.06f, 0.06f)) * rotate(radians(orna1rot), vec3(0.0f, 1.0f, 0.0f)); // ornaments move up and down and rotates
			g_modelMatrix[11] = translate(vec3(orna2pos.x, orna2pos.y += 0.001, orna2pos.z)) * scale(vec3(0.08f, 0.08f, 0.08f)) * rotate(radians(orna2rot += 7.5f), vec3(0.0f, 1.0f, 0.0f));

			if (g_light3_switch) // if spot light is switched on
			{
				g_light_spot.ambient = vec3rng(1, 99, "abc"); // randomizes colour
				g_light_spot.diffuse = vec3rng(1, 99, "abc"); // ...colour
				g_light_spot.direction = vec3rng(-80, 80, "ac"); // ...direction

				g_material[2].ambient = g_light_spot.ambient;
				g_material[2].diffuse = g_light_spot.diffuse;
			}
		}

		else if (ptLightpos1.z >= 2.0f && ptLightpos1.x >= -1.95f && light1round == 1) // same
		{
			g_modelMatrix[12] = translate(vec3(ptLightpos1.x -= 0.08f, ptLightpos1.y, ptLightpos1.z)) * scale(vec3(0.1f, 0.1f, 0.1f));
			g_light_point[0].position = ptLightpos1;

			g_modelMatrix[13] = translate(vec3(ptLightpos2.x += 0.08f, ptLightpos2.y, ptLightpos2.z)) * scale(vec3(0.1f, 0.1f, 0.1f));
			g_light_point[1].position = ptLightpos2;

			g_modelMatrix[10] = translate(vec3(orna1pos.x, orna1pos.y -= 0.001, orna1pos.z)) * scale(vec3(0.06f, 0.06f, 0.06f)) * rotate(radians(orna1rot += 10.0f), vec3(0.0f, 1.0f, 0.0f));
			g_modelMatrix[11] = translate(vec3(orna2pos.x, orna2pos.y -= 0.001, orna2pos.z)) * scale(vec3(0.08f, 0.08f, 0.08f)) * rotate(radians(orna2rot), vec3(0.0f, 1.0f, 0.0f));

			if (g_light3_switch)
			{
				g_light_spot.ambient = vec3rng(1, 99, "abc");
				g_light_spot.diffuse = vec3rng(1, 99, "abc");
				g_light_spot.direction = vec3rng(-60, 60, "ac");

				g_material[2].ambient = g_light_spot.ambient;
				g_material[2].diffuse = g_light_spot.diffuse;
			}
		}

		else if (ptLightpos1.z >= -2.0f && ptLightpos1.x >= -2.0f && light1round == 1) // same
		{
			g_modelMatrix[12] = translate(vec3(ptLightpos1.x, ptLightpos1.y, ptLightpos1.z -= 0.08f)) * scale(vec3(0.1f, 0.1f, 0.1f));
			g_light_point[0].position = ptLightpos1;

			g_modelMatrix[13] = translate(vec3(ptLightpos2.x, ptLightpos2.y, ptLightpos2.z += 0.08f)) * scale(vec3(0.1f, 0.1f, 0.1f));
			g_light_point[1].position = ptLightpos2;

			g_modelMatrix[10] = translate(vec3(orna1pos.x, orna1pos.y += 0.001, orna1pos.z)) * scale(vec3(0.06f, 0.06f, 0.06f)) * rotate(radians(orna1rot), vec3(0.0f, 1.0f, 0.0f));
			g_modelMatrix[11] = translate(vec3(orna2pos.x, orna2pos.y += 0.001, orna2pos.z)) * scale(vec3(0.08f, 0.08f, 0.08f)) * rotate(radians(orna2rot -= 7.5f), vec3(0.0f, 1.0f, 0.0f));

			if (g_light3_switch)
			{
				g_light_spot.ambient = vec3rng(1, 99, "abc");
				g_light_spot.diffuse = vec3rng(1, 99, "abc");
				g_light_spot.direction = vec3rng(-80, 80, "ac");

				g_material[2].ambient = g_light_spot.ambient;
				g_material[2].diffuse = g_light_spot.diffuse;
			}
			
			if ((int)ptLightpos1.z == -2) // checks for position to make sure it is in its third quarter around the room and changes the round check
			{
				light1round = 2;
			}
		}

		else if (ptLightpos1.z <= 2.0f && ptLightpos1.x <= 1.95f && light1round == 2) // round check has changed, so it will not coincide with the first if values, the rest is same logic
		{
			g_modelMatrix[12] = translate(vec3(ptLightpos1.x += 0.08f, ptLightpos1.y, ptLightpos1.z)) * scale(vec3(0.1f, 0.1f, 0.1f));
			g_light_point[0].position = ptLightpos1;

			g_modelMatrix[13] = translate(vec3(ptLightpos2.x -= 0.08f, ptLightpos2.y, ptLightpos2.z)) * scale(vec3(0.1f, 0.1f, 0.1f));
			g_light_point[1].position = ptLightpos2;

			g_modelMatrix[10] = translate(vec3(orna1pos.x, orna1pos.y -= 0.001, orna1pos.z)) * scale(vec3(0.06f, 0.06f, 0.06f)) * rotate(radians(orna1rot -= 10.0f), vec3(0.0f, 1.0f, 0.0f));
			g_modelMatrix[11] = translate(vec3(orna2pos.x, orna2pos.y -= 0.001, orna2pos.z)) * scale(vec3(0.08f, 0.08f, 0.08f)) * rotate(radians(orna2rot), vec3(0.0f, 1.0f, 0.0f));

			if (g_light3_switch)
			{
				g_light_spot.ambient = vec3rng(1, 99, "abc");
				g_light_spot.diffuse = vec3rng(1, 99, "abc");
				g_light_spot.direction = vec3rng(-90, 90, "ac");
			}

			if ((int)ptLightpos1.x == 2)
			{
				light1round = 1;
			}
		}
	}

	if (reset)
	{
		// reset point light properties
		ptLightpos1 = vec3(1.95f, 0.8f, 0.0f);
		g_light_point[0].position = vec3(ptLightpos1.x - 0.2f, ptLightpos1.y, ptLightpos1.z);
		g_modelMatrix[12] = translate(ptLightpos1) * scale(vec3(0.1f, 0.1f, 0.1f));

		g_light_point[0].ambient = ptLightamb1;
		g_light_point[0].specular = ptLightspec1;
		g_light_point[0].diffuse = ptLightdiff1;
		g_light_point[0].attenuation = ptLightatten1;

		ptLightpos2 = vec3(-1.95f, 0.8f, 0.0f);
		g_light_point[1].position = vec3(ptLightpos2.x + 0.2f, ptLightpos1.y, ptLightpos1.z);
		g_modelMatrix[13] = translate(ptLightpos2) * scale(vec3(0.1f, 0.1f, 0.1f));

		g_light_point[1].ambient = ptLightamb2;
		g_light_point[1].specular = ptLightspec2;
		g_light_point[1].diffuse = ptLightdiff2;
		g_light_point[1].attenuation = ptLightatten2;

		// reset spot light properties
		g_light_spot.direction = vec3(0.0f, -1.0f, 0.0f);
		g_light_spot.ambient = spotLightamb;
		g_light_spot.specular = spotLightspec;
		g_light_spot.diffuse = spotLightdiff;
		g_light_spot.attenuation = spotLightatten;

		// reset ornament properties
		orna1pos = vec3(0.0f, 0.45f, 0.2f);
		orna2pos = vec3(0.0f, 0.4f, -0.2f);
		orna1rot = 0.0f;
		orna2rot = 180.0f;
		g_modelMatrix[10] = translate(orna1pos) * scale(vec3(0.06f, 0.06f, 0.06f)) * rotate(radians(orna1rot), vec3(0.0f, 1.0f, 0.0f));
		g_modelMatrix[11] = translate(orna2pos) * scale(vec3(0.08f, 0.08f, 0.08f)) * rotate(radians(orna2rot), vec3(0.0f, 1.0f, 0.0f));
		
		// reset lamp colour properties
		g_material[0].ambient = ptLightamb1;
		g_material[0].specular = ptLightspec1;
		g_material[0].diffuse = ptLightdiff1;

		g_material[1].ambient = ptLightamb2;
		g_material[1].specular = ptLightspec2;
		g_material[1].diffuse = ptLightdiff2;

		g_material[2].ambient = spotLightamb;
		g_material[2].specular = spotLightspec;
		g_material[2].diffuse = spotLightdiff;

		reset = false;
	}

	g_material[0].ambient = ptLightamb1curr;
	g_material[0].diffuse = ptLightdiff1curr;
	g_material[0].specular = ptLightspec1curr;

	g_material[1].ambient = ptLightamb2curr;
	g_material[1].diffuse = ptLightdiff2curr;
	g_material[1].specular = ptLightspec2curr;

	g_material[2].ambient = spotLightambcurr;
	g_material[2].diffuse = spotLightdiffcurr;
	g_material[2].specular = spotLightspeccurr;
}

// function used to render the scene
static void render_scene()
{
	if (!view)
	{
		render_four_view();
	}

	else if (view)
	{
		render_persp_view();
	}
}

// key press or release callback function
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// quit if the ESCAPE key was press
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// set flag to close the window
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		// set flag to close the window
		if (view)
		{
			view = false;
		}

		else if (!view)
		{
			view = true;
		}
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
		g_camera[3].updateRotation(delta_x * ROTATION_SENSITIVITY * g_frameTime, delta_y * ROTATION_SENSITIVITY * g_frameTime);
	}

	// update previous mouse coordinates
	previous_xpos = xpos;
	previous_ypos = ypos;

	// pass mouse data to tweak bar
	TwEventMousePosGLFW(xpos, ypos);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// pass mouse data to tweak bar
	TwEventMouseButtonGLFW(button, action);

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
	cerr << description << endl;	// output error description
}

int main(void)
{
	GLFWwindow* window = NULL;	// pointer to a GLFW window handle
	TwBar *TweakBar;			// pointer to a tweak bar

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
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Assignment 2", NULL, NULL);

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

	// use sticky mode to avoid missing state changes from polling
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// initialise AntTweakBar
	TwInit(TW_OPENGL_CORE, NULL);

	// give tweak bar the size of graphics window
	TwWindowSize(g_windowWidth, g_windowHeight);
	TwDefine(" TW_HELP visible=false ");	// disable help menu
	TwDefine(" GLOBAL fontsize=3 ");		// set large font size

	// Wireframe
	TweakBar = TwNewBar("Main");
	TwDefine(" Main position='20 20' ");
	TwDefine(" Main size='260 846' ");
	TwAddVarRW(TweakBar, "Wireframe", TW_TYPE_BOOLCPP, &g_wireFrame, " group='Controls' ");

	// Switches
	TwAddVarRW(TweakBar, "Point Light 1", TW_TYPE_BOOLCPP, &g_light1_switch, " group='Light Switches' ");
	TwAddVarRW(TweakBar, "Point Light 2", TW_TYPE_BOOLCPP, &g_light2_switch, " group='Light Switches' ");
	TwAddVarRW(TweakBar, "Spot Light", TW_TYPE_BOOLCPP, &g_light3_switch, " group='Light Switches' ");
	TwAddVarRW(TweakBar, "Disco Mode", TW_TYPE_BOOLCPP, &g_mode_switch, " group='Mode Switches' ");
	TwAddVarRW(TweakBar, "Reset", TW_TYPE_BOOLCPP, &reset, " group='Reset Switch' ");

	// Light 1 Editor
	//TweakBar = TwNewBar("Pt Light 1");
	TwAddVarRW(TweakBar, "PL1 Ambient: x", TW_TYPE_FLOAT, &g_light_point[0].ambient[0], " group='Point Light 1 Ambient' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL1 Ambient: y", TW_TYPE_FLOAT, &g_light_point[0].ambient[1], " group='Point Light 1 Ambient' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL1 Ambient: z", TW_TYPE_FLOAT, &g_light_point[0].ambient[2], " group='Point Light 1 Ambient' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "PL1 Specular: x", TW_TYPE_FLOAT, &g_light_point[0].specular[0], " group='Point Light 1 Specular' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL1 Specular: y", TW_TYPE_FLOAT, &g_light_point[0].specular[1], " group='Point Light 1 Specular' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL1 Specular: z", TW_TYPE_FLOAT, &g_light_point[0].specular[2], " group='Point Light 1 Specular' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "PL1 Diffuse: x", TW_TYPE_FLOAT, &g_light_point[0].diffuse[0], " group='Point Light 1 Diffuse' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL1 Diffuse: y", TW_TYPE_FLOAT, &g_light_point[0].diffuse[1], " group='Point Light 1 Diffuse' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL1 Diffuse: z", TW_TYPE_FLOAT, &g_light_point[0].diffuse[2], " group='Point Light 1 Diffuse' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "PL1 Constant", TW_TYPE_FLOAT, &g_light_point[0].attenuation[0], " group='Point Light 1 Attenuation' min=0.0 max=1.0 step=0.01 ");
	TwAddVarRW(TweakBar, "PL1 Linear", TW_TYPE_FLOAT, &g_light_point[0].attenuation[1], " group='Point Light 1 Attenuation' min=0.0 max=1.0 step=0.001 ");
	TwAddVarRW(TweakBar, "PL1 Quadratic", TW_TYPE_FLOAT, &g_light_point[0].attenuation[2], " group='Point Light 1 Attenuation' min=0.0 max=1.0 step=0.001 ");

	// Light 2 Editor
	//TweakBar = TwNewBar("Pt Light 2");
	TwAddVarRW(TweakBar, "PL2 Ambient: x", TW_TYPE_FLOAT, &g_light_point[1].ambient[0], " group='Point Light 2 Ambient' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL2 Ambient: y", TW_TYPE_FLOAT, &g_light_point[1].ambient[1], " group='Point Light 2 Ambient' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL2 Ambient: z", TW_TYPE_FLOAT, &g_light_point[1].ambient[2], " group='Point Light 2 Ambient' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "PL2 Specular: x", TW_TYPE_FLOAT, &g_light_point[1].specular[0], " group='Point Light 2 Specular' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL2 Specular: y", TW_TYPE_FLOAT, &g_light_point[1].specular[1], " group='Point Light 2 Specular' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL2 Specular: z", TW_TYPE_FLOAT, &g_light_point[1].specular[2], " group='Point Light 2 Specular' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "PL2 Diffuse: x", TW_TYPE_FLOAT, &g_light_point[1].diffuse[0], " group='Point Light 2 Diffuse' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL2 Diffuse: y", TW_TYPE_FLOAT, &g_light_point[1].diffuse[1], " group='Point Light 2 Diffuse' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "PL2 Diffuse: z", TW_TYPE_FLOAT, &g_light_point[1].diffuse[2], " group='Point Light 2 Diffuse' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "PL2 Constant", TW_TYPE_FLOAT, &g_light_point[1].attenuation[0], " group='Point Light 2 Attenuation' min=0.0 max=1.0 step=0.01 ");
	TwAddVarRW(TweakBar, "PL2 Linear", TW_TYPE_FLOAT, &g_light_point[1].attenuation[1], " group='Point Light 2 Attenuation' min=0.0 max=1.0 step=0.001 ");
	TwAddVarRW(TweakBar, "PL2 Quadratic", TW_TYPE_FLOAT, &g_light_point[1].attenuation[2], " group='Point Light 2 Attenuation' min=0.0 max=1.0 step=0.001 ");

	// Light 3 Editor
	//TweakBar = TwNewBar("Spot Light");
	TwAddVarRW(TweakBar, "SL Ambient: x", TW_TYPE_FLOAT, &g_light_spot.ambient[0], " group='Spot Light Ambient' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "SL Ambient: y", TW_TYPE_FLOAT, &g_light_spot.ambient[1], " group='Spot Light Ambient' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "SL Ambient: z", TW_TYPE_FLOAT, &g_light_spot.ambient[2], " group='Spot Light Ambient' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "SL Specular: x", TW_TYPE_FLOAT, &g_light_spot.specular[0], " group='Spot Light Specular' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "SL Specular: y", TW_TYPE_FLOAT, &g_light_spot.specular[1], " group='Spot Light Specular' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "SL Specular: z", TW_TYPE_FLOAT, &g_light_spot.specular[2], " group='Spot Light Specular' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "SL Diffuse: x", TW_TYPE_FLOAT, &g_light_spot.diffuse[0], " group='Spot Light Diffuse' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "SL Diffuse: y", TW_TYPE_FLOAT, &g_light_spot.diffuse[1], " group='Spot Light Diffuse' min=0.0 max=1.0 step=0.01");
	TwAddVarRW(TweakBar, "SL Diffuse: z", TW_TYPE_FLOAT, &g_light_spot.diffuse[2], " group='Spot Light Diffuse' min=0.0 max=1.0 step=0.01");

	TwAddVarRW(TweakBar, "SL Constant", TW_TYPE_FLOAT, &g_light_spot.attenuation[0], " group='Spot Light Attenuation' min=0.0 max=1.0 step=0.01 ");
	TwAddVarRW(TweakBar, "SL Linear", TW_TYPE_FLOAT, &g_light_spot.attenuation[1], " group='Spot Light Attenuation' min=0.0 max=1.0 step=0.001 ");
	TwAddVarRW(TweakBar, "SL Quadratic", TW_TYPE_FLOAT, &g_light_spot.attenuation[2], " group='Spot Light Attenuation' min=0.0 max=1.0 step=0.001 ");

	// initialise rendering states
	init(window);

	double lastUpdateTime = glfwGetTime();	// last update time
	double elapsedTime = lastUpdateTime;	// time elapsed since last update
	int frameCount = 0;						// number of frames since last update

	g_moveCamera = false;

	// the rendering loop
	while (!glfwWindowShouldClose(window))
	{
		if (g_wireFrame)
		{
		
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (!g_light1_switch)
		{
			g_light_point[0].ambient = vec3(0.0f, 0.0f, 0.0f);
			g_light_point[0].diffuse = vec3(0.0f, 0.0f, 0.0f);
			g_light_point[0].specular = vec3(0.0f, 0.0f, 0.0f);
		}

		if (!g_light2_switch)
		{
			g_light_point[1].ambient = vec3(0.0f, 0.0f, 0.0f);
			g_light_point[1].diffuse = vec3(0.0f, 0.0f, 0.0f);
			g_light_point[1].specular = vec3(0.0f, 0.0f, 0.0f);
		}

		if (!g_light3_switch)
		{
			g_light_spot.ambient = vec3(0.0f, 0.0f, 0.0f);
			g_light_spot.diffuse = vec3(0.0f, 0.0f, 0.0f);
			g_light_spot.specular = vec3(0.0f, 0.0f, 0.0f);
		}

		update_scene(window, g_frameTime);		// update the scene
		render_scene();							// render the scene

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (g_light1_switch)
		{
			ptLightamb1curr = g_light_point[0].ambient;
			ptLightspec1curr = g_light_point[0].specular;
			ptLightdiff1curr = g_light_point[0].diffuse;
			ptLightatten1curr = g_light_point[0].attenuation;
		}

		g_light_point[0].ambient = ptLightamb1curr;
		g_light_point[0].diffuse = ptLightdiff1curr;
		g_light_point[0].specular = ptLightspec1curr;
		g_light_point[0].attenuation = ptLightatten1curr;


		if (g_light2_switch)
		{
			ptLightamb2curr = g_light_point[1].ambient;
			ptLightspec2curr = g_light_point[1].specular;
			ptLightdiff2curr = g_light_point[1].diffuse;
			ptLightatten2curr = g_light_point[1].attenuation;
		}

		g_light_point[1].ambient = ptLightamb2curr;
		g_light_point[1].diffuse = ptLightdiff2curr;
		g_light_point[1].specular = ptLightspec2curr;
		g_light_point[1].attenuation = ptLightatten2curr;

		if (g_light3_switch)
		{
			spotLightambcurr = g_light_spot.ambient;
			spotLightspeccurr = g_light_spot.specular;
			spotLightdiffcurr = g_light_spot.diffuse;
			spotLightattencurr = g_light_spot.attenuation;
		}

		g_light_spot.ambient = spotLightambcurr;
		g_light_spot.diffuse = spotLightdiffcurr;
		g_light_spot.specular = spotLightspeccurr;
		g_light_spot.attenuation = spotLightattencurr;

		TwDraw();					// draw tweak bar(s)

		glfwSwapBuffers(window);	// swap buffers
		glfwPollEvents();			// poll for events

		frameCount++;
		elapsedTime = glfwGetTime() - lastUpdateTime;	// current time - last update time

		if (elapsedTime >= 1.0f)	// if time since last update >= to 1 second
		{
			g_frameTime = 1.0f / frameCount;	// calculate frame time

			string str = "FPS = " + to_string(frameCount) + "; FT = " + to_string(g_frameTime);

			glfwSetWindowTitle(window, str.c_str());	// update window title

			frameCount = 0;					// reset frame count
			lastUpdateTime += elapsedTime;	// update last update time
		}
	}

	// clean up
	for (int i = 0; i < sizeof(g_mesh) / sizeof(g_mesh[0]); i++)
	{
		if (g_mesh[i].pMeshVertices)
			delete[] g_mesh[i].pMeshVertices;
		if (g_mesh[i].pMeshIndices)
			delete[] g_mesh[i].pMeshIndices;
	}

	glDeleteProgram(g_shaderProgramID);
	glDeleteProgram(g_shaderProgramID_line);

	glDeleteBuffers(1, &g_VBO_line);
	glDeleteVertexArrays(1, &g_VAO_line);

	glDeleteBuffers(1, &g_VBO_room);
	glDeleteVertexArrays(1, &g_VAO_room);

	glDeleteBuffers(1, &g_VBO_cube);
	glDeleteVertexArrays(1, &g_VAO_cube);

	glDeleteBuffers(1, &g_VBO_mesh1);
	glDeleteVertexArrays(1, &g_VAO_mesh1);
	glDeleteBuffers(1, &g_IBO_mesh1);

	glDeleteBuffers(1, &g_VBO_mesh2);
	glDeleteVertexArrays(1, &g_VAO_mesh2);
	glDeleteBuffers(1, &g_IBO_mesh2);

	// uninitialise tweak bar
	TwTerminate();

	// close the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}