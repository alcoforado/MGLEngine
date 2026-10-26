#version 450

layout(push_constant, std430) uniform MyPushConstants {
    vec4 fontColor;
};

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 2) uniform sampler2D fontSampler;



void main() {
    outColor = texture(fontSampler, fragTexCoord);
    outColor = fontColor*outColor.r;
}