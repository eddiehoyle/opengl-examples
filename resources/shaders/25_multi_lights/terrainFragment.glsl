#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in float visibility;

out vec4 out_Color;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMapTexture;

uniform vec3 lightColour[4];
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColour;

const float tileMultiplier = 20.0;

void main() {

    // Texture blending
    vec4 blendMapColour = texture( blendMapTexture, pass_textureCoords );
    float backTextureAmount = 1 - ( blendMapColour.r + blendMapColour.g + blendMapColour.b );
    vec2 tiledCoords = pass_textureCoords * tileMultiplier;
    vec4 backgroundTextureColour = texture( backgroundTexture, tiledCoords ) * backTextureAmount;
    vec4 rTextureColour = texture( rTexture, tiledCoords ) * blendMapColour.r;
    vec4 gTextureColour = texture( gTexture, tiledCoords ) * blendMapColour.g;
    vec4 bTextureColour = texture( bTexture, tiledCoords ) * blendMapColour.b;
    vec4 textureColour = backgroundTextureColour + rTextureColour + gTextureColour + bTextureColour;

    vec3 unitNormal = normalize( surfaceNormal );
    vec3 unitVectorToCamera = normalize( toCameraVector );

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for ( int i=0;i<4;++i) {
        vec3 unitLightVector = normalize( toLightVector[i] );
        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max( nDot1, 0.0 );
        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect( lightDirection, unitNormal );
        float specularFactor = dot( reflectedLightDirection, unitVectorToCamera );
        specularFactor = max( specularFactor, 0.0 );
        float dampedFactor = pow( specularFactor, shineDamper );
        totalDiffuse = totalDiffuse + brightness * lightColour[i];
        totalSpecular = totalSpecular + dampedFactor * reflectivity * lightColour[i];
    }

    totalDiffuse = max(totalDiffuse, 0.2);

    // Specular removed atm
    out_Color = vec4( totalDiffuse, 1.0 ) * textureColour;// * vec4( totalSpecular, 1.0 );
    out_Color = mix( vec4( skyColour, 1.0 ), out_Color, visibility );

/*    vec3 actualLightVector = toLightVector;

    vec3 unitNormal = normalize( surfaceNormal );
    vec3 unitLightVector = normalize( actualLightVector );
    float brightness = max( dot( unitNormal, unitLightVector ), 0.2 );
    vec3 diffuse = brightness * lightColour;

    vec3 unitVectorToCamera = normalize( toCameraVector );
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect( lightDirection, unitNormal );

    float specularFactor = dot( reflectedLightDirection, unitVectorToCamera );
    specularFactor = max( specularFactor, 0.0 );
    float dampedFactor = pow( specularFactor, shineDamper );
    vec3 finalSpecular = dampedFactor * reflectivity * lightColour;

    // Specular removed atm
    out_Color = vec4( diffuse, 1.0 ) * totalColour;// * vec4( finalSpecular, 1.0 );

    // Mix in with fog
    out_Color = mix( vec4( skyColour, 1.0 ), out_Color, visibility );*/
}


