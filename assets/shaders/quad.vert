#version 430 core

struct Transform {
    ivec2 atlasOffset;
    ivec2 spriteSize;
    vec2 pos;
    vec2 size;
};

layout(std430, binding = 0) buffer TransformSBO {
    Transform transforms[];
};

layout (location = 0) out vec2 textureCoordsOut;

uniform vec2 screenSize;
uniform mat4 orthoProj;

void main() {

    Transform inst = transforms[gl_InstanceID];

    vec2 vertices[6] = {
        inst.pos,                                        // Top Left
        vec2(inst.pos + vec2(0.0, inst.size.y)),    // Bottom Left
        vec2(inst.pos + vec2(inst.size.x, 0.0)),    // Top Right
        vec2(inst.pos + vec2(inst.size.x, 0.0)),    // Top Right
        vec2(inst.pos + vec2(0.0, inst.size.y)),    // Bottom Left
        inst.pos + inst.size                        // Bottom Right
    };
    vec2 vertex = vertices[gl_VertexID];
    // //normalize it
    // vertex.y = -vertex.y + screenSize.y;
    // vertex = 2*(vertex / screenSize) - 1.0;

    float left = inst.atlasOffset.x;
    float right = inst.atlasOffset.x + inst.spriteSize.x;
    float top = inst.atlasOffset.y;
    float bottom = inst.atlasOffset.y + inst.spriteSize.y;

    vec2 textureCoords[6] = {
        vec2(left, top),
        vec2(left, bottom),
        vec2(right, top),
        vec2(right, top),
        vec2(left, bottom),
        vec2(right, bottom),
    };


    gl_Position = orthoProj * vec4(vertex, 0.0, 1.0);
    textureCoordsOut = textureCoords[gl_VertexID];
}