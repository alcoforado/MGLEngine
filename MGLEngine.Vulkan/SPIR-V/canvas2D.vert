#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;


layout(binding = 0) uniform UniformBufferObject {
    mat4 mGT;
} ubo;


out gl_PerVertex {
    vec4 gl_Position;
};


void main() {


	vec3 v=mat3(ubo.mGT)*vec3(inPosition,1.0);
	gl_Position = vec4(v[0],v[1],0.0, 1.0);
    fragColor = vec3(ubo.mGT[2][0],ubo.mGT[2][1],ubo.mGT[2][2]);
}

