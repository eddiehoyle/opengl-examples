#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

uniform float numberOfRows;
uniform vec2 offset;

uniform float useFakeLighting;

const float density = 0.0015;
const float gradient = 4.5;
const float visibilityClamp = 1.0;

void main( void ) {

    vec4 worldPosition = ( transformationMatrix * vec4( position, 1.0 ) );
    vec4 positionRelativeToCam = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * positionRelativeToCam;

//    pass_textureCoords = textureCoords;
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
    toLightVector = lightPosition;// - worldPosition.xyz; // Does not work if this is uncommented, should I be dpi

    float distance = length( positionRelativeToCam.xyz );
    visibility = exp( -pow( ( distance * density ), gradient ) );
    visibility = clamp( visibility, visibilityClamp, visibilityClamp );
}