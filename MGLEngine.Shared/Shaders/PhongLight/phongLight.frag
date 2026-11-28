#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragPos;

layout(location = 0) out vec4 outColor;


// 2. Storage Buffer (SSBO) - Variable-length array
struct Light {
    vec4 position;
    vec4 color;
    float ambientLight;
    float reserved1;
    float reserved3;
    float reserved4;
};

layout(std430, set = 0, binding = 8) readonly buffer LightSSBO {
     Light lights[];
     uint lightCount;
};


void main() {
    for (uint i=0;i<lightCount; ++i)
    {
        vec3 ambient = lights[i].ambientLight*lights[i].color.rgb;
        vec3 lightDir = normalize(lightPos.xyz-fragPos);

    }
    
    

    float diff = max(dot(fragNormal,lightDir),0.0); 
    vec3 diffuse=diff*lcolor.rgb;

    outColor =vec4((diffuse+ambient)*fragColor.rgb,1.0);
}