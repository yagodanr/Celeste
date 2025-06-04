#version 430 core


// input
layout (location = 0) in vec2 textureCordsIn;

// output
layout (location = 0) out vec4 fragColor;

// binds
layout (location = 0) uniform sampler2D textureAtlas;

void main() {
    vec4 textureColor = texelFetch(textureAtlas, ivec2(textureCordsIn), 0);
    if(textureColor.a == 0.0) {
        discard;
    }
    //White
    fragColor = textureColor;
}

