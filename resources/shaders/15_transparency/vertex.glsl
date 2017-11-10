#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;

void main( void ) {

    // World position of vertex
    vec4 worldPosition = ( transformationMatrix * vec4( position, 1.0 ) );

    // UVs
    pass_textureCoords = textureCoords;

    // Normals
    mat4 normalMatrix = transpose( inverse( transformationMatrix ) );
    surfaceNormal = ( normalMatrix * vec4( normal, 0.0 ) ).xyz;

    // Vertex
    gl_Position = projectionMatrix * viewMatrix * worldPosition;

    // Direction of light
    toLightVector = lightPosition - worldPosition.xyz;

    // Direction of camera
    toCameraVector = ( inverse( viewMatrix ) * vec4( 0.0, 0.0, 0.0, 1.0 ) ).xyz - worldPosition.xyz;
}