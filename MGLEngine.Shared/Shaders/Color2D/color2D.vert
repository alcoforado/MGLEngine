#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 position2d;
layout(location = 1) in vec4 color;

layout(location = 0) out vec4 fragColor;


layout(set = 0, binding = 6, std140) uniform TransformBlock {
    mat2 uTransformMatrix;
};

void main() {
	
	gl_Position = vec4(uTransformMatrix * position2d, 0.0, 1.0);
    fragColor = color;
}

