#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition[4];

uniform float numberOfRows;
uniform vec2 offset;

uniform float useFakeLighting;

const float density = 0.003;
const float gradient = 2.5;

void main( void ) {

    vec4 worldPosition = ( transformationMatrix * vec4( position, 1.0 ) );
    vec4 positionRelativeToCam = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * positionRelativeToCam;
    pass_textureCoords = (textureCoords/numberOfRows) + offset;

    vec3 actualNormal = normal;
    if ( useFakeLighting > 0.5 ) {
        actualNormal = vec3( 0.0, 1.0, 0.0 );
    }

    mat4 normalMatrix = transpose( inverse( transformationMatrix ) );
    surfaceNormal = ( normalMatrix * vec4( actualNormal, 0.0 ) ).xyz;
    toCameraVector = ( inverse( viewMatrix ) * vec4( 0.0, 0.0, 0.0, 1.0 ) ).xyz - worldPosition.xyz;

    // TODO
    // Does the light need to be a vector from vertex to light?
    // Removing the worldPosition actually makes this work
    // toLightVector = lightPosition;// - worldPosition.xyz; // Does not work if this is uncommented
    for ( int i = 0; i < 4; ++i ) {
        toLightVector[i] = lightPosition[i] - worldPosition.xyz;
    }
    float distance = length( positionRelativeToCam.xyz );
    visibility = exp( -pow( ( distance * density ), gradient ) );
    visibility = clamp( visibility, 0.0, 1.0 );
}