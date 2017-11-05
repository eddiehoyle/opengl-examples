#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 out_Color;

uniform sampler2D textureSampler;

uniform vec3 lightColour;

void main() {
//    out_Color = vec4( 1, 1, 1, 1 );

    vec3 unitNormal = normalize( surfaceNormal );
    vec3 unitLightVector = normalize( toLightVector );

    float nDot1 = dot( unitNormal, unitLightVector );
    float brightness = max( nDot1, 0.0 );

//    vec3 diffuse = brightness * lightColour;
    vec3 diffuse = brightness * vec3( 1, 1, 1 );

    /// Fix
    out_Color = vec4( diffuse, 1.0 ) * texture( textureSampler, pass_textureCoords );
}


