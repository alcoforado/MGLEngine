#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 position2d;
layout(location = 1) in vec2 texCoord;

layout(location = 0) out vec2 fragTexCoord;




void main() {
	
	gl_Position = vec4(position2d,0.0, 1.0);
    fragTexCoord = texCoord;
}

