#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragPos;

layout(location = 0) out vec4 outColor;


layout(set = 0, binding = 8, std140) uniform Light {
     vec4 lightPos;
     vec4 direction;
     vec4 lcolor;
     vec4 parameters;
};


void main() {
    float ambientLight= parameters.x;
    vec3 ambient=ambientLight*lcolor.rgb;

    vec3 lightDir = normalize(lightPos.xyz-fragPos);
    float diff = max(dot(fragNormal,lightDir),0.0); 
    vec3 diffuse=diff*lcolor.rgb;

    outColor =vec4((diffuse+ambient)*fragColor.rgb,1.0);
}