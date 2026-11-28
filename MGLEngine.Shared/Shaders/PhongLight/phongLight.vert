#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position3d;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec3 fragPos;


layout(set = 0, binding = 7, std140) uniform CameraNdc {
    mat4 WorldToNdc;
};






void main() {
	
	gl_Position = WorldToNdc * vec4(position3d, 1.0);
    fragColor = color;
    fragNormal=normal;
    fragPos=position3d;


}


