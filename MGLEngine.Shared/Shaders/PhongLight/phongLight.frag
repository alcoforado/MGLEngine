#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 fragColor;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 8, std140) uniform Light {
     vec4 pos;
     vec4 direction;
     vec4 lcolor;
     vec4 parameters;
};


void main() {
    float ambientLight= parameters.x;
    vec3 ambient=ambientLight*lcolor.rgb;
    outColor =vec4(ambient*fragColor.rgb,1.0);
}