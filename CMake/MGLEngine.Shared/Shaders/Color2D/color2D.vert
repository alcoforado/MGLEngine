#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 position2d;
layout(location = 1) in vec4 color;

layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform UniformBufferObject {
    mat4 mGT;
} ubo;


out gl_PerVertex {
    vec4 gl_Position;
};


void main() {
	
	gl_Position = vec4(position2d[0],position2d[1],0.0, 1.0);
    fragColor = color;
}

