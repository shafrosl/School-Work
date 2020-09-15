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
#include "bmpfuncs.h"
#include "shader.h"
#include "Camera.h"

#define MOVEMENT_SENSITIVITY 3.0f		// camera movement sensitivity
#define ROTATION_SENSITIVITY 0.3f		// camera rotation sensitivity

// struct for vertex attributes
typedef struct VTex
{
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat texCoord[2];
	GLfloat colour[3];
} VTex;

typedef struct VMap
{
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat tangent[3];
	GLfloat texCoord[2];
}; VMap;

typedef struct Vertex
{
	GLfloat position[3];
	GLfloat normal[3];
} Vertex;

// light and material structs
typedef struct Light
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
} Light;

typedef struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
} Material;

// struct for mesh properties
typedef struct Mesh
{
	Vertex* pMeshVertices;		// pointer to mesh vertices
	GLint numberOfVertices;		// number of vertices in the mesh
	GLint* pMeshIndices;		// pointer to mesh indices
	GLint numberOfFaces;		// number of faces in the mesh
} Mesh;

// Global variables
VTex g_vertices_floor[] = {
	// floor
	-2.0f, 0.0f, 2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 4.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	2.0f, 0.0f, 2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	-2.0f, 0.0f, -2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	4.0f, 4.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	-2.0f, 0.0f, -2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	4.0f, 4.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour
	2.0f, 0.0f, 2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	2.0f, 0.0f, -2.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	4.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
};

VTex g_vertices_plane[] = {
	// plane
	-2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
};

VTex g_vertices_paint[] = {
	// paint

	-2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
};

VTex g_vertices_cube[] = {
	// Front: triangle 1
	// vertex 1
	-0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// triangle 2
	// vertex 1
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour

	// Right: triangle 3
	// vertex 1
	0.5f, 0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 2
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	0.5f, 0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// triangle 4
	// vertex 1
	0.5f, 0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// vertex 2
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	0.5f, -0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour

	// Back: triangle 5
	// vertex 1
	0.5f, -0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 2
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// triangle 6
	// vertex 1
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// vertex 2
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour

	// Left: triangle 7
	// vertex 1
	-0.5f, -0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 2
	-0.5f, 0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	-0.5f, -0.5f, -0.5f,// position
	-1.0f, 0.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// triangle 8
	// vertex 1
	-0.5f, -0.5f, -0.5f,// position
	-1.0f, 0.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// vertex 2
	-0.5f, 0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	-0.5f, 0.5f, -0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour

	// Top: triangle 9
	// vertex 1
	-0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 2
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// triangle 10
	// vertex 1
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// vertex 2
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour

	// Bottom: triangle 11
	// vertex 1
	0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 1.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	0.5f, -0.5f, -0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// triangle 12
	// vertex 1
	0.5f, -0.5f, -0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f,			// texture coordinate
	0.0f, 0.0f, 1.0f,	// colour

	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	0.0f, 1.0f,			// texture coordinate
	0.0f, 1.0f, 0.0f,	// colour
	// vertex 3
	-0.5f, -0.5f, -0.5f,// position
	0.0f, -1.0f, 0.0f,	// normal
	0.0f, 0.0f,			// texture coordinate
	1.0f, 0.0f, 0.0f,	// colour
};

VMap g_vertices_wall[] = {
	// wall
	-2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 4.0f,			// texture coordinate
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	4.0f, 4.0f,			// texture coordinate

	-2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	4.0f, 4.0f,			// texture coordinate
	2.0f, 0.0f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	2.0f, 0.0f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	4.0f, 0.0f,			// texture coordinate
};

GLuint g_VBO_room[2];				// vertex buffer object identifier
GLuint g_VAO_room[2];				// vertex array object identifier

GLuint g_VBO_cube = 0;				// vertex buffer object identifier
GLuint g_VAO_cube = 0;				// vertex array object identifier

GLuint g_IBO_mesh = 0;				// index buffer object identifier
GLuint g_VBO_mesh = 0;				// vertex buffer object identifier
GLuint g_VAO_mesh = 0;				// vertex array object identifier

GLuint g_VBO_paint[2];				// vertex buffer object identifier
GLuint g_VAO_paint[2];				// vertex array object identifier

GLuint g_VBO_plane = 0;				// vertex buffer object identifier
GLuint g_VAO_plane = 0;				// vertex array object identifier

GLuint g_shaderProgramID_tex = 0;		// shader program identifier
GLuint g_shaderProgramID_map = 0;		// shader program identifier
GLuint g_shaderProgramID_envmap = 0;	// shader program identifier

// locations in shader for texture
GLuint g_MVP_Index_tex;
GLuint g_MV_Index_tex;
GLuint g_V_Index_tex;
GLuint g_texSamplerIndex_tex;
GLuint g_lightPositionIndex_tex;
GLuint g_lightAmbientIndex_tex;
GLuint g_lightDiffuseIndex_tex;
GLuint g_lightSpecularIndex_tex;
GLuint g_materialAmbientIndex_tex;
GLuint g_materialDiffuseIndex_tex;
GLuint g_materialSpecularIndex_tex;
GLuint g_materialShininessIndex_tex;

// locations in shader for map
GLuint g_MVP_Index_map = 0;
GLuint g_MV_Index_map = 0;
GLuint g_V_Index_map = 0;
GLuint g_texSamplerIndex_map;
GLuint g_normalSamplerIndex_map;
GLuint g_lightPositionIndex_map = 0;
GLuint g_lightDirectionIndex_map = 0;
GLuint g_lightAmbientIndex_map = 0;
GLuint g_lightDiffuseIndex_map = 0;
GLuint g_lightSpecularIndex_map = 0;
GLuint g_lightTypeIndex_map = 0;
GLuint g_materialAmbientIndex_map = 0;
GLuint g_materialDiffuseIndex_map = 0;
GLuint g_materialSpecularIndex_map = 0;
GLuint g_materialShininessIndex_map = 0;

// locations in shader for env map
GLuint g_MVP_Index_envmap = 0;
GLuint g_MV_Index_envmap = 0;
GLuint g_V_Index_envmap = 0;
GLuint g_envMapSamplerIndex_envmap;
GLuint g_lightPositionIndex_envmap = 0;
GLuint g_lightAmbientIndex_envmap = 0;
GLuint g_lightDiffuseIndex_envmap = 0;
GLuint g_lightSpecularIndex_envmap = 0;
GLuint g_materialAmbientIndex_envmap = 0;
GLuint g_materialDiffuseIndex_envmap = 0;
GLuint g_materialSpecularIndex_envmap = 0;
GLuint g_materialShininessIndex_envmap = 0;

Light g_light;					// light properties
Material g_material[6];			// material properties
mat4 g_modelMatrix[10];			// object's model matrix
Mesh g_mesh;
GLuint g_alphaIndex_tex;

unsigned char* g_texImage_tex[2];		//image data
GLuint g_textureID_tex[2];				//texture id

unsigned char* g_texImage_wall[2];		//image data
GLuint g_textureID_wall[2];				//texture id

unsigned char* g_texImage_paint[2];		//image data
GLuint g_textureID_paint[2];			//texture id

unsigned char* g_texImage_plane;		//image data
GLuint g_textureID_plane;				//texture id

enum CUBE_FACE { FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM };
unsigned char* g_texImage_envmap[6];	//image data
GLuint g_textureID_envmap;				//texture id

GLuint g_windowWidth = 800;				// window dimensions
GLuint g_windowHeight = 600;

float g_frameTime = 0.0f;
float g_alpha = 0.7f;
float g_alpha_floor = 0.75f;
float g_alpha_cube = 1.0f;
Camera g_camera;
bool g_moveCamera = false;

// texture
GLuint positionIndex_tex;
GLuint normalIndex_tex;
GLuint texCoordIndex_tex;
GLuint colourIndex_tex;

// normal mapping
GLuint positionIndex_map;
GLuint normalIndex_map;
GLuint tangentIndex_map;
GLuint texCoordIndex_map;

// enviro mapping
GLuint positionIndex_envmap;
GLuint normalIndex_envmap;
GLuint texCoordIndex_envmap;

/////////////// E T C - ///////////////

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

/////////////// I N I T ///////////////

void textInit()
{
	// floor
	// read the image data
	GLint imageWidth_floor;				//image width info
	GLint imageHeight_floor;			//image height info
	g_texImage_tex[0] = readBitmapRGBImage("images/check.bmp", &imageWidth_floor, &imageHeight_floor);

	// generate identifier for texture object and set texture properties
	glGenTextures(1, &g_textureID_tex[0]);
	glBindTexture(GL_TEXTURE_2D, g_textureID_tex[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_floor, imageHeight_floor, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_tex[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_room[0]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_room[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_floor), g_vertices_floor, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_room[0]);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_room[0]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_room[0]);
	glVertexAttribPointer(positionIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, position)));
	glVertexAttribPointer(normalIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, normal)));
	glVertexAttribPointer(texCoordIndex_tex, 2, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, texCoord)));

	glEnableVertexAttribArray(positionIndex_tex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex_tex);
	glEnableVertexAttribArray(texCoordIndex_tex);

	// cube
	// read the image data
	GLint imageWidth_cube;			//image width info
	GLint imageHeight_cube;			//image height info
	g_texImage_tex[1] = readBitmapRGBImage("images/smile.bmp", &imageWidth_cube, &imageHeight_cube);

	// generate identifier for texture object and set texture properties
	glGenTextures(1, &g_textureID_tex[1]);
	glBindTexture(GL_TEXTURE_2D, g_textureID_tex[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_cube, imageHeight_cube, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_tex[1]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_cube), g_vertices_cube, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_cube);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_cube);
	glVertexAttribPointer(positionIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, position)));
	glVertexAttribPointer(normalIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, normal)));
	glVertexAttribPointer(texCoordIndex_tex, 2, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, texCoord)));

	glEnableVertexAttribArray(positionIndex_tex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex_tex);
	glEnableVertexAttribArray(texCoordIndex_tex);
}

void wallInit()
{
	// walls
	GLint imageWidth_wall[2];			//image width info
	GLint imageHeight_wall[2];			//image height info
	g_texImage_wall[0] = readBitmapRGBImage("images/Fieldstone.bmp", &imageWidth_wall[0], &imageHeight_wall[0]);
	g_texImage_wall[1] = readBitmapRGBImage("images/FieldstoneBumpDOT3.bmp", &imageWidth_wall[1], &imageHeight_wall[1]);

	// generate identifier for texture object and set texture properties
	glGenTextures(2, g_textureID_wall);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_wall[0], imageHeight_wall[0], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_wall[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_wall[1], imageHeight_wall[1], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_wall[1]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_room[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_room[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_wall), g_vertices_wall, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_room[1]);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_room[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_room[1]);
	glVertexAttribPointer(positionIndex_map, 3, GL_FLOAT, GL_FALSE, sizeof(VMap), reinterpret_cast<void*>(offsetof(VMap, position)));
	glVertexAttribPointer(normalIndex_map, 3, GL_FLOAT, GL_FALSE, sizeof(VMap), reinterpret_cast<void*>(offsetof(VMap, normal)));
	glVertexAttribPointer(tangentIndex_map, 3, GL_FLOAT, GL_FALSE, sizeof(VMap), reinterpret_cast<void*>(offsetof(VMap, tangent)));
	glVertexAttribPointer(texCoordIndex_map, 2, GL_FLOAT, GL_FALSE, sizeof(VMap), reinterpret_cast<void*>(offsetof(VMap, texCoord)));

	glEnableVertexAttribArray(positionIndex_map);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex_map);
	glEnableVertexAttribArray(tangentIndex_map);
	glEnableVertexAttribArray(texCoordIndex_map);
}

void paintInit()
{
	// painting 1
	// read the image data
	GLint imageWidth_paint;				//image width info
	GLint imageHeight_paint;			//image height info
	g_texImage_paint[0] = readBitmapRGBImage("images/cm_back.bmp", &imageWidth_paint, &imageHeight_paint);

	// generate identifier for texture object and set texture properties
	glGenTextures(1, &g_textureID_paint[0]);
	glBindTexture(GL_TEXTURE_2D, g_textureID_paint[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_paint, imageHeight_paint, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_paint[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_paint[0]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_paint[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_paint), g_vertices_paint, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_paint[0]);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_paint[0]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_paint[0]);
	glVertexAttribPointer(positionIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, position)));
	glVertexAttribPointer(normalIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, normal)));
	glVertexAttribPointer(texCoordIndex_tex, 2, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, texCoord)));

	glEnableVertexAttribArray(positionIndex_tex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex_tex);
	glEnableVertexAttribArray(texCoordIndex_tex);

	// painting 2
	// read the image data
	g_texImage_paint[1] = readBitmapRGBImage("images/screenshot.bmp", &imageWidth_paint, &imageHeight_paint);

	// generate identifier for texture object and set texture properties
	glGenTextures(1, &g_textureID_paint[1]);
	glBindTexture(GL_TEXTURE_2D, g_textureID_paint[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_paint, imageHeight_paint, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_paint[1]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_paint[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_paint[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_paint), g_vertices_paint, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_paint[1]);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_paint[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_paint[1]);
	glVertexAttribPointer(positionIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, position)));
	glVertexAttribPointer(normalIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, normal)));
	glVertexAttribPointer(texCoordIndex_tex, 2, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, texCoord)));

	glEnableVertexAttribArray(positionIndex_tex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex_tex);
	glEnableVertexAttribArray(texCoordIndex_tex);
}

void planeInit()
{
	// plane
	// read the image data
	GLint imageWidth_plane;				//image width info
	GLint imageHeight_plane;			//image height info
	g_texImage_plane = readBitmapRGBImage("images/mf.bmp", &imageWidth_plane, &imageHeight_plane);

	// generate identifier for texture object and set texture properties
	glGenTextures(1, &g_textureID_plane);
	glBindTexture(GL_TEXTURE_2D, g_textureID_plane);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_plane, imageHeight_plane, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_plane);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_plane);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_plane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices_plane), g_vertices_plane, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_plane);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_plane);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_plane);
	glVertexAttribPointer(positionIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, position)));
	glVertexAttribPointer(normalIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, normal)));
	glVertexAttribPointer(texCoordIndex_tex, 2, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, texCoord)));
	glVertexAttribPointer(colourIndex_tex, 3, GL_FLOAT, GL_FALSE, sizeof(VTex), reinterpret_cast<void*>(offsetof(VTex, colour)));

	glEnableVertexAttribArray(positionIndex_tex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex_tex);
	glEnableVertexAttribArray(texCoordIndex_tex);
	glEnableVertexAttribArray(colourIndex_tex);
}

void meshInit()
{
	// mesh
	GLint imageWidth_envmap;			//image width info
	GLint imageHeight_envmap;			//image height info

	g_texImage_envmap[FRONT] = readBitmapRGBImage("images/cm_front.bmp", &imageWidth_envmap, &imageHeight_envmap);
	g_texImage_envmap[BACK] = readBitmapRGBImage("images/cm_back.bmp", &imageWidth_envmap, &imageHeight_envmap);
	g_texImage_envmap[LEFT] = readBitmapRGBImage("images/cm_left.bmp", &imageWidth_envmap, &imageHeight_envmap);
	g_texImage_envmap[RIGHT] = readBitmapRGBImage("images/cm_right.bmp", &imageWidth_envmap, &imageHeight_envmap);
	g_texImage_envmap[TOP] = readBitmapRGBImage("images/cm_top.bmp", &imageWidth_envmap, &imageHeight_envmap);
	g_texImage_envmap[BOTTOM] = readBitmapRGBImage("images/cm_bottom.bmp", &imageWidth_envmap, &imageHeight_envmap);

	glGenTextures(1, &g_textureID_envmap);                  // generate texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_textureID_envmap);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, imageWidth_envmap, imageHeight_envmap, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_envmap[RIGHT]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, imageWidth_envmap, imageHeight_envmap, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_envmap[LEFT]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, imageWidth_envmap, imageHeight_envmap, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_envmap[TOP]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, imageWidth_envmap, imageHeight_envmap, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_envmap[BOTTOM]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, imageWidth_envmap, imageHeight_envmap, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_envmap[BACK]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, imageWidth_envmap, imageHeight_envmap, 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage_envmap[FRONT]);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	g_mesh.pMeshVertices = NULL;
	g_mesh.pMeshIndices = NULL;
	load_mesh("models/torus.obj", &g_mesh);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(1, &g_VBO_mesh);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_mesh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_mesh.numberOfVertices, g_mesh.pMeshVertices, GL_STATIC_DRAW);

	// generate identifier for IBO and copy data to GPU
	glGenBuffers(1, &g_IBO_mesh);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_mesh);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * 3 * g_mesh.numberOfFaces, g_mesh.pMeshIndices, GL_STATIC_DRAW);

	// generate identifiers for VAO
	glGenVertexArrays(1, &g_VAO_mesh);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO_mesh);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO_mesh);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO_mesh);
	glVertexAttribPointer(positionIndex_envmap, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex_envmap, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex_envmap);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex_envmap);
}

static void init(GLFWwindow* window)
{
	// Texture
	// create and compile our GLSL program from the shader files
	g_shaderProgramID_tex = loadShaders("LightAndTextureVS.vert", "LightAndTextureFS.frag");

	// find the location of shader variables
	positionIndex_tex = glGetAttribLocation(g_shaderProgramID_tex, "aPosition");
	normalIndex_tex = glGetAttribLocation(g_shaderProgramID_tex, "aNormal");
	texCoordIndex_tex = glGetAttribLocation(g_shaderProgramID_tex, "aTexCoord");
	colourIndex_tex = glGetAttribLocation(g_shaderProgramID_tex, "aColour");

	g_MVP_Index_tex = glGetUniformLocation(g_shaderProgramID_tex, "uModelViewProjectionMatrix");
	g_MV_Index_tex = glGetUniformLocation(g_shaderProgramID_tex, "uModelViewMatrix");
	g_V_Index_tex = glGetUniformLocation(g_shaderProgramID_tex, "uViewMatrix");

	g_texSamplerIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uTextureSampler");
	g_alphaIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uAlpha");

	g_lightPositionIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uLight.position");
	g_lightAmbientIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uLight.ambient");
	g_lightDiffuseIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uLight.diffuse");
	g_lightSpecularIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uLight.specular");

	g_materialAmbientIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uMaterial.ambient");
	g_materialDiffuseIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uMaterial.diffuse");
	g_materialSpecularIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uMaterial.specular");
	g_materialShininessIndex_tex = glGetUniformLocation(g_shaderProgramID_tex, "uMaterial.shininess");

	// Mapping
	// create and compile our GLSL program from the shader files
	g_shaderProgramID_map = loadShaders("NormalMapVS.vert", "NormalMapFS.frag");

	// find the location of shader variables
	positionIndex_map = glGetAttribLocation(g_shaderProgramID_map, "aPosition");
	normalIndex_map = glGetAttribLocation(g_shaderProgramID_map, "aNormal");
	tangentIndex_map = glGetAttribLocation(g_shaderProgramID_map, "aTangent");
	texCoordIndex_map = glGetAttribLocation(g_shaderProgramID_map, "aTexCoord");

	g_MVP_Index_map = glGetUniformLocation(g_shaderProgramID_map, "uModelViewProjectionMatrix");
	g_MV_Index_map = glGetUniformLocation(g_shaderProgramID_map, "uModelViewMatrix");
	g_V_Index_map = glGetUniformLocation(g_shaderProgramID_map, "uViewMatrix");

	g_texSamplerIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uTextureSampler");
	g_normalSamplerIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uNormalSampler");

	g_lightPositionIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uLight.position");
	g_lightDirectionIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uLight.direction");
	g_lightAmbientIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uLight.ambient");
	g_lightDiffuseIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uLight.diffuse");
	g_lightSpecularIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uLight.specular");
	g_lightTypeIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uLight.type");

	g_materialAmbientIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uMaterial.ambient");
	g_materialDiffuseIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uMaterial.diffuse");
	g_materialSpecularIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uMaterial.specular");
	g_materialShininessIndex_map = glGetUniformLocation(g_shaderProgramID_map, "uMaterial.shininess");

	// Environment Mapping
	// create and compile our GLSL program from the shader files
	g_shaderProgramID_envmap = loadShaders("CubeEnvMapVS.vert", "CubeEnvMapFS.frag");

	// find the location of shader variables
	positionIndex_envmap = glGetAttribLocation(g_shaderProgramID_envmap, "aPosition");
	normalIndex_envmap = glGetAttribLocation(g_shaderProgramID_envmap, "aNormal");
	texCoordIndex_envmap = glGetAttribLocation(g_shaderProgramID_envmap, "aTexCoord");

	g_MVP_Index_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uModelViewProjectionMatrix");
	g_MV_Index_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uModelViewMatrix");
	g_V_Index_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uViewMatrix");
	g_envMapSamplerIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uEnvironmentMap");

	g_lightPositionIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uLight.position");
	g_lightAmbientIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uLight.ambient");
	g_lightDiffuseIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uLight.diffuse");
	g_lightSpecularIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uLight.specular");

	g_materialAmbientIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uMaterial.ambient");
	g_materialDiffuseIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uMaterial.diffuse");
	g_materialSpecularIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uMaterial.specular");
	g_materialShininessIndex_envmap = glGetUniformLocation(g_shaderProgramID_envmap, "uMaterial.shininess");

	// initialise model matrix to the identity matrix
	for (int i = 0; i < sizeof(g_modelMatrix) / sizeof(g_modelMatrix[0]); i++)
	{
		g_modelMatrix[i] = mat4(1.0f);
	}

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

	// objects
	g_modelMatrix[5] = rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))	// painting
		* translate(vec3(0.0f, -1.99f, -0.5f))
		* scale(vec3(0.3f, 0.6f, 0.6f));
	g_modelMatrix[6] = rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))	// ...
		* rotate(radians(90.0f), vec3(0.0f, 0.0f, 1.0f))
		* translate(vec3(0.0f, -1.99f, -0.5f))
		* scale(vec3(0.3f, 0.6f, 0.6f));

	g_modelMatrix[7] = translate(vec3(0.8f, 0.3f, 0.0f))				// table
		* scale(vec3(0.4f, 0.6f, 0.4f));

	g_modelMatrix[8] = translate(vec3(0.8f, 0.73f, 0.0f))				// mesh
		* rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))
		* scale(vec3(0.1f, 0.1f, 0.1f));

	g_modelMatrix[9] = rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f))	// plane
		* translate(vec3(0.0f, 1.0f, -0.5f))
		* scale(vec3(0.4f, 1.0f, 1.0f));

	// initialise view matrix and projection matrix
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / height;

	// set camera's view matrix
	g_camera.setViewMatrix(glm::vec3(0, 3, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// set camera's projection matrix
	g_camera.setProjection(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	g_camera.setPitch(glm::radians(-20.0f));

	// initialise light and material properties
	g_light.position = vec3(3.0f, 7.0f, 0.0f);
	g_light.ambient = vec3(1.0f, 1.0f, 1.0f);
	g_light.diffuse = vec3(1.0f, 1.0f, 1.0f);
	g_light.specular = vec3(1.0f, 1.0f, 1.0f);

	g_material[0].ambient = vec3(0.6f, 0.6f, 0.3f);		// floor
	g_material[0].diffuse = vec3(0.5f, 0.5f, 0.5f);
	g_material[0].specular = vec3(0.5f, 0.5f, 0.5f);
	g_material[0].shininess = 40.0f;

	g_material[1].ambient = vec3(0.5f, 0.5f, 0.5f);		// walls
	g_material[1].diffuse = vec3(0.3f, 0.3f, 0.3f);
	g_material[1].specular = vec3(0.3f, 0.3f, 0.3f);
	g_material[1].shininess = 40.0f;

	g_material[2].ambient = vec3(0.8f, 0.8f, 0.8f);		// cube
	g_material[2].diffuse = vec3(0.5f, 0.5f, 0.5f);
	g_material[2].specular = vec3(0.8f, 0.8f, 0.8f);
	g_material[2].shininess = 40.0f;

	g_material[3].ambient = vec3(0.8f, 0.8f, 0.8f);		// ornament
	g_material[3].diffuse = vec3(0.8f, 0.8f, 0.8f);
	g_material[3].specular = vec3(0.8f, 0.8f, 0.8f);
	g_material[3].shininess = 40.0f;

	g_material[4].ambient = vec3(0.8f, 0.2f, 0.2f);		// plane
	g_material[4].diffuse = vec3(0.8f, 0.8f, 0.8f);
	g_material[4].specular = vec3(0.8f, 0.8f, 0.8f);
	g_material[4].shininess = 40.0f;

	g_material[5].ambient = vec3(0.8f, 0.8f, 0.8f);		// cube
	g_material[5].diffuse = vec3(0.5f, 0.5f, 0.5f);
	g_material[5].specular = vec3(0.8f, 0.8f, 0.8f);
	g_material[5].shininess = 40.0f;


	// initialize objects
	textInit();
	wallInit();
	paintInit();
	planeInit();
	meshInit();
}

/////////////// D R A W ///////////////

void draw_floor()
{
	glUseProgram(g_shaderProgramID_tex);	// use the shaders associated with the shader program
	glBindVertexArray(g_VAO_room[0]);		// make VAO active

	mat4 MVP;
	mat4 MV;
	mat4 V;

	// floor
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[0];
	MV = g_camera.getViewMatrix() * g_modelMatrix[0];
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_tex, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_tex, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_tex, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_tex, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_tex, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_tex, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_tex, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_tex, 1, &g_material[0].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_tex, 1, &g_material[0].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_tex, 1, &g_material[0].specular[0]);
	glUniform1fv(g_materialShininessIndex_tex, 1, &g_material[0].shininess);

	glUniform1i(g_texSamplerIndex_tex, 0);
	glUniform1fv(g_alphaIndex_tex, 1, &g_alpha_floor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_tex[0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_walls(bool bReflect)
{
	// walls
	glUseProgram(g_shaderProgramID_map);	// use the shaders associated with the shader program
	glBindVertexArray(g_VAO_room[1]);		// make VAO active

	// set shader variables
	mat4 reflectMatrix = mat4(1.0f);
	mat4 modelMatrix = mat4(1.0f);
	mat4 MVP = mat4(1.0f);
	mat4 MV;
	mat4 V;

	vec3 lightPosition = g_light.position;

	if (bReflect)
	{
		reflectMatrix = scale(vec3(1.0f, -1.0f, 1.0f));
		lightPosition = vec3(reflectMatrix * vec4(lightPosition, 1.0f));
	}
	else
	{
		reflectMatrix = mat4(1.0f);
	}

	modelMatrix = reflectMatrix * g_modelMatrix[1];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * g_modelMatrix[1];
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_map, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_map, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_map, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_map, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_map, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_map, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_map, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_map, 1, &g_material[1].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_map, 1, &g_material[1].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_map, 1, &g_material[1].specular[0]);
	glUniform1fv(g_materialShininessIndex_map, 1, &g_material[1].shininess);

	glUniform1i(g_texSamplerIndex_map, 0);
	glUniform1i(g_normalSamplerIndex_map, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[1]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	modelMatrix = reflectMatrix * g_modelMatrix[2];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * g_modelMatrix[2];
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_map, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_map, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_map, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_map, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_map, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_map, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_map, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_map, 1, &g_material[1].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_map, 1, &g_material[1].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_map, 1, &g_material[1].specular[0]);
	glUniform1fv(g_materialShininessIndex_map, 1, &g_material[1].shininess);

	glUniform1i(g_texSamplerIndex_map, 0);
	glUniform1i(g_normalSamplerIndex_map, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[1]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	modelMatrix = reflectMatrix * g_modelMatrix[3];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * g_modelMatrix[3];
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_map, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_map, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_map, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_map, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_map, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_map, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_map, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_map, 1, &g_material[1].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_map, 1, &g_material[1].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_map, 1, &g_material[1].specular[0]);
	glUniform1fv(g_materialShininessIndex_map, 1, &g_material[1].shininess);

	glUniform1i(g_texSamplerIndex_map, 0);
	glUniform1i(g_normalSamplerIndex_map, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[1]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	modelMatrix = reflectMatrix * g_modelMatrix[4];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * g_modelMatrix[4];
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_map, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_map, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_map, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_map, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_map, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_map, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_map, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_map, 1, &g_material[1].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_map, 1, &g_material[1].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_map, 1, &g_material[1].specular[0]);
	glUniform1fv(g_materialShininessIndex_map, 1, &g_material[1].shininess);

	glUniform1i(g_texSamplerIndex_map, 0);
	glUniform1i(g_normalSamplerIndex_map, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID_wall[1]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_cube(bool bReflect)
{
	glUseProgram(g_shaderProgramID_tex);	// use the shaders associated with the shader program
	glBindVertexArray(g_VAO_cube);		// make VAO active

	// set shader variables
	mat4 reflectMatrix = mat4(1.0f);
	mat4 modelMatrix = mat4(1.0f);
	mat4 MVP = mat4(1.0f);
	mat4 MV;
	mat4 V;

	vec3 lightPosition = g_light.position;

	if (bReflect)
	{
		reflectMatrix = glm::scale(vec3(1.0f, -1.0f, 1.0f));
		lightPosition = vec3(reflectMatrix * vec4(lightPosition, 1.0f));
	}
	else
	{
		reflectMatrix = mat4(1.0f);
	}

	// cube
	modelMatrix = reflectMatrix * g_modelMatrix[7];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * modelMatrix;
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_tex, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_tex, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_tex, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_materialAmbientIndex_tex, 1, &g_material[2].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_tex, 1, &g_material[2].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_tex, 1, &g_material[2].specular[0]);
	glUniform1f(g_materialShininessIndex_tex, g_material[2].shininess);

	glUniform1fv(g_alphaIndex_tex, 1, &g_alpha_cube);
	glUniform1i(g_texSamplerIndex_tex, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_tex[1]);

	glDrawArrays(GL_TRIANGLES, 0, 30);
}

void draw_orna(bool bReflect)
{
	glUseProgram(g_shaderProgramID_envmap);	// use the shaders associated with the shader program
	glBindVertexArray(g_VAO_mesh);			// make VAO active

	// set shader variables
	mat4 reflectMatrix = mat4(1.0f);
	mat4 modelMatrix = mat4(1.0f);
	mat4 MVP = mat4(1.0f);
	mat4 MV;
	mat4 V;

	vec3 lightPosition = g_light.position;

	if (bReflect)
	{
		reflectMatrix = glm::scale(vec3(1.0f, -1.0f, 1.0f));
		lightPosition = vec3(reflectMatrix * vec4(lightPosition, 1.0f));
	}
	else
	{
		reflectMatrix = mat4(1.0f);
	}

	// mesh
	// set uniform shader variables
	modelMatrix = reflectMatrix * g_modelMatrix[8];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * modelMatrix;
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_envmap, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_envmap, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_envmap, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_envmap, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_envmap, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_envmap, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_envmap, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_envmap, 1, &g_material[3].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_envmap, 1, &g_material[3].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_envmap, 1, &g_material[3].specular[0]);
	glUniform1f(g_materialShininessIndex_envmap, g_material[3].shininess);

	glUniform1i(g_envMapSamplerIndex_envmap, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_textureID_envmap);

	glDrawElements(GL_TRIANGLES, g_mesh.numberOfFaces * 3, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type
}

void draw_painting(bool bReflect)
{
	glUseProgram(g_shaderProgramID_tex);	// use the shaders associated with the shader program
	glBindVertexArray(g_VAO_paint[0]);		// make VAO active

	// set shader variables
	mat4 reflectMatrix = mat4(1.0f);
	mat4 modelMatrix = mat4(1.0f);
	mat4 MVP = mat4(1.0f);
	mat4 MV;
	mat4 V;

	vec3 lightPosition = g_light.position;

	if (bReflect)
	{
		reflectMatrix = glm::scale(vec3(1.0f, -1.0f, 1.0f));
		lightPosition = vec3(reflectMatrix * vec4(lightPosition, 1.0f));
	}
	else
	{
		reflectMatrix = mat4(1.0f);
	}

	// painting 1
	modelMatrix = reflectMatrix * g_modelMatrix[5];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * modelMatrix;
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_tex, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_tex, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_tex, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_tex, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_tex, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_tex, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_tex, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_tex, 1, &g_material[5].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_tex, 1, &g_material[5].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_tex, 1, &g_material[5].specular[0]);
	glUniform1fv(g_materialShininessIndex_tex, 1, &g_material[5].shininess);

	glUniform1f(g_alphaIndex_tex, 1.0);
	glUniform1i(g_texSamplerIndex_tex, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_paint[0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(g_VAO_paint[1]);		// make VAO active

	// painting 2
	modelMatrix = reflectMatrix * g_modelMatrix[6];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * modelMatrix;
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_tex, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_tex, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_tex, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_tex, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_tex, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_tex, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_tex, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_tex, 1, &g_material[5].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_tex, 1, &g_material[5].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_tex, 1, &g_material[5].specular[0]);
	glUniform1fv(g_materialShininessIndex_tex, 1, &g_material[5].shininess);

	glUniform1f(g_alphaIndex_tex, 1.0);
	glUniform1i(g_texSamplerIndex_tex, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_paint[1]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_plane(bool bReflect)
{
	glUseProgram(g_shaderProgramID_tex);	// use the shaders associated with the shader program
	glBindVertexArray(g_VAO_plane);			// make VAO active

	// set shader variables
	mat4 reflectMatrix = mat4(1.0f);
	mat4 modelMatrix = mat4(1.0f);
	mat4 MVP = mat4(1.0f);
	mat4 MV;
	mat4 V;

	vec3 lightPosition = g_light.position;

	if (bReflect)
	{
		reflectMatrix = glm::scale(vec3(1.0f, -1.0f, 1.0f));
		lightPosition = vec3(reflectMatrix * vec4(lightPosition, 1.0f));
	}
	else
	{
		reflectMatrix = mat4(1.0f);
	}

	// plane
	modelMatrix = reflectMatrix * g_modelMatrix[9];
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	MV = g_camera.getViewMatrix() * modelMatrix;
	V = g_camera.getViewMatrix();
	glUniformMatrix4fv(g_MVP_Index_tex, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_MV_Index_tex, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(g_V_Index_tex, 1, GL_FALSE, &V[0][0]);

	glUniform3fv(g_lightPositionIndex_tex, 1, &g_light.position[0]);
	glUniform3fv(g_lightAmbientIndex_tex, 1, &g_light.ambient[0]);
	glUniform3fv(g_lightDiffuseIndex_tex, 1, &g_light.diffuse[0]);
	glUniform3fv(g_lightSpecularIndex_tex, 1, &g_light.specular[0]);

	glUniform3fv(g_materialAmbientIndex_tex, 1, &g_material[4].ambient[0]);
	glUniform3fv(g_materialDiffuseIndex_tex, 1, &g_material[4].diffuse[0]);
	glUniform3fv(g_materialSpecularIndex_tex, 1, &g_material[4].specular[0]);
	glUniform1fv(g_materialShininessIndex_tex, 1, &g_material[4].shininess);

	glUniform1fv(g_alphaIndex_tex, 1, &g_alpha);
	glUniform1i(g_texSamplerIndex_tex, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID_plane);

	glDrawArrays(GL_TRIANGLES, 0, 6);
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

	g_camera.update(moveForward, strafeRight);	// update camera


}

// function used to render the scene
static void render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	// clear colour buffer and depth buffer

	// disable depth buffer and draw mirror surface to stencil buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);  //disable any modification of all color components
	glDepthMask(GL_FALSE);                                //disable any modification to depth buffer
	glEnable(GL_STENCIL_TEST);                            //enable stencil testing

	//setup the stencil buffer for a function reference value
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 1);

	draw_floor();

	//enable depth buffer, draw reflected geometry where stencil buffer passes

	//render where the stencil buffer equal to 1
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);   //allow all color components to be modified 
	glDepthMask(GL_TRUE);                              //allow depth buffer contents to be modified

	draw_walls(true);
	draw_cube(true);
	draw_orna(true);
	draw_painting(true);
	draw_plane(true);

	glDisable(GL_STENCIL_TEST);		//disable stencil testing

	//blend in reflection
	glEnable(GL_BLEND);		//enable blending            
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	draw_floor();

	glDisable(GL_BLEND);	//disable blending

	draw_walls(false);
	draw_cube(false);
	draw_orna(false);
	draw_painting(false);


	glFlush();	// flush the pipeline
}

static void render_plane()
{
	glEnable(GL_BLEND);		//enable blending            
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	draw_plane(false);
}

/////////////// P R E S ///////////////

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

	// if the 0 key is pressed that a screen capture
	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		// compute size of the image
		int size = g_windowWidth * g_windowHeight * 3;

		// allocate memory to store the image
		unsigned char* outBuffer = new unsigned char[size];

		// read pixels from the colour buffer
		glReadPixels(0, 0, g_windowWidth, g_windowHeight, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)outBuffer);

		// write the image to a file
		writeBitmapRGBImage("images/screenshot.bmp", (char*)outBuffer, g_windowWidth, g_windowHeight);

		// deallocate memory
		delete[] outBuffer;
	}

	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		paintInit();
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
		g_camera.updateRotation(delta_x * ROTATION_SENSITIVITY * g_frameTime, delta_y * ROTATION_SENSITIVITY * g_frameTime);
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

/////////////// M A I N ///////////////

int main(void)
{
	GLFWwindow* window = NULL;				// pointer to a GLFW window handle
	TwBar *TweakBar;						// pointer to a tweak bar
	double lastUpdateTime = glfwGetTime();	// last update time
	double elapsedTime = lastUpdateTime;	// time elapsed since last update
	int frameCount = 0;						// number of frames since last update
	int FPS = 0;							// frames per second

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
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Assignment 3", NULL, NULL);

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

	// initialise AntTweakBar
	TwInit(TW_OPENGL_CORE, NULL);

	// give tweak bar the size of graphics window
	TwWindowSize(g_windowWidth, g_windowHeight);
	TwDefine(" TW_HELP visible=false ");	// disable help menu
	TwDefine(" GLOBAL fontsize=3 ");		// set large font size

	// create a tweak bar
	TweakBar = TwNewBar("Main");
	TwDefine(" Main label='Controls' refresh=0.02 text=light size='220 300' ");

	// create light position
	TwAddVarRW(TweakBar, "Light: x", TW_TYPE_FLOAT, &g_light.position[0], " group='Light Position' min=-10.0 max=10.0 step=0.1");
	TwAddVarRW(TweakBar, "Light: y", TW_TYPE_FLOAT, &g_light.position[1], " group='Light Position' min=-10.0 max=10.0 step=0.1");
	TwAddVarRW(TweakBar, "Light: z", TW_TYPE_FLOAT, &g_light.position[2], " group='Light Position' min=0.0 max=10.0 step=0.1");

	// create material properties entries
	TwAddVarRW(TweakBar, "Cubemap", TW_TYPE_COLOR3F, &g_material[2].ambient[0], " group='Cube Map' ");
	TwAddVarRW(TweakBar, "Translucency", TW_TYPE_FLOAT, &g_alpha_cube, " group='Cube Map' min=0.1 max=1.0 step=0.01");

	// create alpha property entry
	TwAddVarRW(TweakBar, "Colour", TW_TYPE_COLOR3F, &g_material[4].ambient[0], " group='Glass Partition' ");
	TwAddVarRW(TweakBar, "Translucency", TW_TYPE_FLOAT, &g_alpha, " group='Glass Partition' min=0.0 max=1.0 step=0.01");

	// floor reflection
	TwAddVarRW(TweakBar, "Reflection", TW_TYPE_FLOAT, &g_alpha_floor, " group='Floor' min=0.35 max=1.0 step=0.01");

	// initialise rendering states
	init(window);

	// the rendering loop
	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		update_scene(window, g_frameTime);		// update the scene

		render_scene();							// render the scene
		render_plane();

		TwDraw();								// draw tweak bar(s)

		glfwSwapBuffers(window);				// swap buffers
		glfwPollEvents();						// poll for events

		frameCount++;
		elapsedTime = glfwGetTime() - lastUpdateTime;	// current time - last update time

		if (elapsedTime >= 1.0f)	// if time since last update >= to 1 second
		{
			g_frameTime = 1.0f / frameCount;	// calculate frame time

			string str = "FPS = " + to_string(frameCount) + "; FT = " + to_string(g_frameTime);

			glfwSetWindowTitle(window, str.c_str());	// update window title

			FPS = frameCount;
			frameCount = 0;					// reset frame count
			lastUpdateTime += elapsedTime;	// update last update time
		}
	}

	// clean up
	glDeleteProgram(g_shaderProgramID_tex);
	glDeleteProgram(g_shaderProgramID_map);
	glDeleteProgram(g_shaderProgramID_envmap);

	for (int i = 0; i < 2; i++)
	{
		glDeleteBuffers(1, &g_VBO_room[i]);
		glDeleteVertexArrays(1, &g_VAO_room[i]);

		glDeleteBuffers(1, &g_VBO_paint[i]);
		glDeleteVertexArrays(1, &g_VAO_paint[i]);

		glDeleteTextures(1, &g_textureID_tex[i]);
		glDeleteTextures(1, &g_textureID_wall[i]);

		if (g_texImage_tex[i])
			delete[] g_texImage_tex[i];

		if (g_texImage_wall[i])
			delete[] g_texImage_wall[i];

		if (g_texImage_paint[i])
			delete[] g_texImage_paint[i];
	}

	for (int i = 0; i < 6; i++)
		if (g_texImage_envmap[i])
			delete[] g_texImage_envmap[i];

	glDeleteBuffers(1, &g_VBO_cube);
	glDeleteVertexArrays(1, &g_VAO_cube);

	glDeleteBuffers(1, &g_VBO_mesh);
	glDeleteVertexArrays(1, &g_VAO_mesh);
	glDeleteBuffers(1, &g_IBO_mesh);

	// uninitialise tweak bar
	TwTerminate();

	// close the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

