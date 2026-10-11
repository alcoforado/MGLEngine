#version 450


layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D fontSampler;


void main() {
    outColor = texture(fontSampler, fragTexCoord);
}