#version 400 core

in vec2 pass_textureCoords;

out vec4 out_Color;

uniform sampler2D textureSampler;

void main() {
    out_Color = vec4( 1, 1, 1, 1 );

    // https://youtu.be/SPt-aogu72A
    // 13.10

    /// Fix
    vec4 asd = texture( textureSampler, pass_textureCoords );
}


