#version 430

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;
out vec3 varyingNormal;
out vec3 varyingLightDir;
out vec3 varyingVertPos;
out vec3 varyingHalfVector;

struct PositionalLight
{	vec4 ambient;
        vec4 diffuse;
        vec4 specular;
        vec3 position;
};
struct Material
{	vec4 ambient;
        vec4 diffuse;
        vec4 specular;
        float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;
uniform mat4 model;
uniform mat4 position;

void main(void)
{	varyingVertPos = vec3(mv_matrix * vec4(vertPos,1.0));
        varyingLightDir = light.position - varyingVertPos;
        varyingNormal = vec3(norm_matrix * position * vec4(vertNormal,1.0));

        varyingHalfVector =
                normalize(normalize(varyingLightDir)
                + normalize(-varyingVertPos)).xyz;

        gl_Position =model* position* vec4(0.2*vertPos.x,0.2*vertPos.y,0.2*vertPos.z,1.0);
}
