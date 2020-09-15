#version 330 core

// interpolated values from the vertex shaders
in vec3 vPos;
in vec3 vN;

// light and material structs
#define MAX_LIGHTS 2

struct ptLight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 attenuation;
	int type;
};

struct spotLight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 attenuation;
	float cutoffAngle;
	int type;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

// uniform input data
uniform mat4 uViewMatrix;
uniform ptLight uPtLight[MAX_LIGHTS];
uniform spotLight uSpotLight;
uniform Material uMaterial;

// output data
out vec3 fColor;

vec3 calculatePtLight(int lightIndex)
{
    vec3 N = normalize(vN);
    vec3 L;
	float attenuation = 1.0;

	// calculate the attenuation based on distance if it's a point light source
	L = (uViewMatrix * vec4(uPtLight[lightIndex].position, 1.0f)).xyz - vPos;
	float distance = length(L);
	L = normalize(L);

	attenuation = 1/(uPtLight[lightIndex].attenuation.x 
		+ uPtLight[lightIndex].attenuation.y * distance 
		+ uPtLight[lightIndex].attenuation.z * distance * distance);

    vec3 E = normalize(-vPos);
    vec3 H = normalize(L + E);

	// calculate the ambient, diffuse and specular components
	vec3 ambient  = uPtLight[lightIndex].ambient * uMaterial.ambient;
    vec3 diffuse  = uPtLight[lightIndex].diffuse * uMaterial.diffuse * max(dot(L, N), 0.0);
	vec3 specular = vec3(0.0f, 0.0f, 0.0f);

	if(dot(L, N) > 0.0f)
	    specular = uPtLight[lightIndex].specular * uMaterial.specular * pow(max(dot(N, H), 0.0), uMaterial.shininess);

	// return color
	return (attenuation * (diffuse + specular)) + ambient;
}

vec3 calculateSpotLight()
{
    vec3 N = normalize(vN);
    vec3 L;
	float attenuation = 1.0;

	// direction to light in eye space
	L = (uViewMatrix * vec4(uSpotLight.position, 1.0f)).xyz - vPos;
	float distance = length(L);
	L = normalize(L);

	// calculate the attenuation based on distance
	attenuation = 1/(uSpotLight.attenuation.x 
		+ uSpotLight.attenuation.y * distance 
		+ uSpotLight.attenuation.z * distance * distance);

    vec3 E = normalize(-vPos);
    vec3 H = normalize(L + E);

	// the direction of the spotlight in eye space
	vec3 direction = (normalize(uViewMatrix * vec4(uSpotLight.direction, 0.0f))).xyz;

	// the angle between the vector from the light to the fragment’s position and the spotlight’s direction
	float angle = degrees(acos(dot(-L, direction)));

	vec3 colour = vec3(0.0f, 0.0f, 0.0f);

	// only compute if angle is less than the cutoff angle
	if(angle <= uSpotLight.cutoffAngle)
	{
		// calculate the ambient, diffuse and specular components
		vec3 ambient  = uSpotLight.ambient * uMaterial.ambient;
		vec3 diffuse  = uSpotLight.diffuse * uMaterial.diffuse * max(dot(L, N), 0.0);
		vec3 specular = vec3(0.0f, 0.0f, 0.0f);

		if(dot(L, N) > 0.0f)
			specular = uSpotLight.specular * uMaterial.specular * pow(max(dot(N, H), 0.0), uMaterial.shininess);

		colour = (attenuation * (diffuse + specular)) + ambient;

		// fade the spotlight's intensity linearly with angle
		colour *= 1.0f - angle/uSpotLight.cutoffAngle;
	}

	// return color
	return colour;
}

void main()
{
    vec3 N = normalize(vN);
    vec3 colour = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < MAX_LIGHTS; i++)
	//for(int i = 0; i < 1; i++)
	//for(int i = 1; i < MAX_LIGHTS; i++)
	{
		colour += calculatePtLight(i);
	}

	colour += calculateSpotLight();

	// set output color
	fColor = colour;
}