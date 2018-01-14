
// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "camera.hh"
#include "render.hh"
#include "loader.hh"
#include "shader.hh"
#include "OBJLoader.hh"


#include "../common/display.hh"
#include "../common/resources.hh"
#include "../common/math.hh"
//#include "../common/scene/camera.hh"
#include "../common/input/input.hh"
#include "../common/controllers/controller.hh"
#include "../common/controllers/fpsController.hh"
#include "../common/components/transformComponent.hh"
#include "bunny.hh"
#include "../common/controllers/tankController.hh"
#include "player.hh"

#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#endif

#ifndef GLFW_FALSE
#define GLFW_FALSE 0
#endif

const unsigned int kWindowWidth = 640;
const unsigned int kWindowHeight = 480;


int main( int argc, char **argv ) {

    // Initialise GLFW
    if ( glfwInit() == GLFW_FALSE ) {
        printf( "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // To make MacOS happy; should not be needed
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );

    // Open a window and create its OpenGL context
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, EXERCISE_NAME, nullptr, nullptr );
    if ( window == nullptr ) {
        printf( "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Setup defaults
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );

    // Setup callbacks
    glfwMakeContextCurrent( window );
    glfwSetKeyCallback( window, common::glfw3KeyPressCallback );
    glfwSetScrollCallback( window, common::glfw3MouseScrollCallback );
    glfwSetMouseButtonCallback( window, common::glfw3MouseButtonCallback );
    glfwSetWindowFocusCallback( window, common::glfw3WindowFocusCallback );

    // tell GLFW to capture our mouse
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if ( glewInit() != GLEW_OK ) {
        printf( "Failed to initialize GLEW\n" );
        glfwTerminate();
        return 1;
    }

    // Set width/height
    common::DisplayManager::instance()->update( kWindowWidth, kWindowHeight );

    // ---------------------------------------------------------------

    bool result;
    Loader loader = Loader();

    // ---------------------------------------------------------------

    const std::string grassyTexturePath = common::getResource( "grass1.jpg", result );
    assert( result );
    const std::string dirtTexturePath = common::getResource( "dirt.png", result );
    assert( result );
    const std::string pinkFlowersTexturePath = common::getResource( "flowers.png", result );
    assert( result );
    const std::string pathTexturePath = common::getResource( "path.png", result );
    assert( result );
    const std::string blendMapTexturePath = common::getResource( "blendMap.png", result );
    assert( result );

    TerrainTexture backgroundTexture = TerrainTexture( loader.loadTexture( grassyTexturePath ) );
    TerrainTexture rTexture = TerrainTexture( loader.loadTexture( dirtTexturePath ) );
    TerrainTexture gTexture = TerrainTexture( loader.loadTexture( pinkFlowersTexturePath ) );
    TerrainTexture bTexture = TerrainTexture( loader.loadTexture( pathTexturePath ) );
    TerrainTexture blendMapTexture = TerrainTexture( loader.loadTexture( blendMapTexturePath ) );

    TerrainTexturePack texturePack( backgroundTexture,
                                    rTexture,
                                    gTexture,
                                    bTexture );
    TerrainTexture blendMap = TerrainTexture( blendMapTexture );

    const std::string heightMapPath = common::getResource( "heightmap.png", result );
    Terrain terrain( 0, 0, loader, texturePack, blendMap, heightMapPath );

    // ---------------------------------------------------------------

    // Fern
    const std::string fernModelPath = common::getResource( "fern.obj", result );
    assert( result );
    const std::string fernTexturePath = common::getResource( "fern_atlas.png", result );
    assert( result );

    // Model and texture
    RawModel fernModel = OBJLoader::loadObjModel( fernModelPath, loader );
    ModelTexture fernTexture( loader.loadTexture( fernTexturePath ) );
    fernTexture.setNumberOfRows( 2 );
    fernTexture.setShineDamper( 10.0f );
    fernTexture.setReflectivity( 1.0f );
    fernTexture.setHasTransparency( true );
    fernTexture.setUseFakeLighting( false );
    TexturedModel fernTexturedModel( fernModel, fernTexture );

    // Create entities
    std::vector< Entity > entities;

    int terrainSize = 500;
    int numEntities = 1000;

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen( rd() ); // Standard mersenne_twister_engine seeded with rd()

    for ( int i = 0; i < numEntities; ++i ) {

        std::uniform_real_distribution<> dis( 0.0, terrainSize );

        std::uniform_real_distribution<> textureIndexGen( 0, 2 );
        glm::vec2 textureGrid( ( int )textureIndexGen( gen ),
                               ( int )textureIndexGen( gen ) );

        double posX = dis( gen );
        double posZ = dis( gen );
        double posY = terrain.getHeightOfTerrain( posX, posZ );

        Entity fernEntity( fernTexturedModel,
                           glm::vec3( posX, posY, posZ ),
                           glm::vec3( 0, 0, 0 ),
                           1,
                           textureGrid );

        entities.push_back( fernEntity );
    }

    // ---------------------------------------------------------------

    const std::string bunnyModelPath = common::getResource( "bunny.obj", result );
    assert( result );
    const std::string bunnyTexturePath = common::getResource( "white.png", result );
    assert( result );

    // Model and texture
    RawModel bunnyModel = OBJLoader::loadObjModel( bunnyModelPath, loader );
    ModelTexture bunnyTexture( loader.loadTexture( bunnyTexturePath ) );
    bunnyTexture.setShineDamper( 10.0f );
    bunnyTexture.setReflectivity( 1.0f );
    bunnyTexture.setHasTransparency( false );
    bunnyTexture.setUseFakeLighting( false );
    TexturedModel bunnyTexturedModel( bunnyModel, bunnyTexture );

    Player player( bunnyTexturedModel,
                   glm::vec3( 0, 0, 0 ),
                   glm::vec3( 0, 0, 0 ),
                   1 );

    // Camera
    Camera camera = Camera( &player );

    // ---------------------------------------------------------------

    // Light pointing straight down
    std::vector< Light > lights;
    lights.push_back( Light( glm::vec3( 0.0f, 10.0f, -70.0f ), glm::vec3( 1, 1, 1 ) ) );
    lights.push_back( Light( glm::vec3( -200.0f, 10.0f, -200.0f ), glm::vec3( 5, 0, 0 ) ) );
    lights.push_back( Light( glm::vec3( 200.0f, 10.0f, 200.0f ), glm::vec3( 0, 0, 5 ) ) );

    // ---------------------------------------------------------------

    const std::string gui1Path = common::getResource( "gui1.png", result );
    assert( result );
    const std::string gui2Path = common::getResource( "gui2.png", result );
    assert( result );

    // Health bar
    GuiTexture gui1Texture = GuiTexture( loader.loadTexture( gui1Path ),
                                         glm::vec2( -0.75f, 0.85f ),
                                         glm::vec2( 0.2f, 0.05f ) );

    // Runes
    GuiTexture gui2Texture = GuiTexture( loader.loadTexture( gui2Path ),
                                         glm::vec2( -0.8f, 0.73f ),
                                         glm::vec2( 0.12f, 0.05f ) );

    std::vector< GuiTexture > guis;
    guis.push_back( gui1Texture );
    guis.push_back( gui2Texture );

    std::vector< GLfloat > guiPositions = {
            -1.0f, 1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f, -1.0f
    };
    RawModel guiModel = loader.loadToVao( guiPositions );


    // ---------------------------------------------------------------

    StaticShader staticShader;
    TerrainShader terrainShader;
    GuiShader guiShader;

    staticShader.init();
    terrainShader.init();
    guiShader.init();

    MasterRenderer render( staticShader, terrainShader );
    GuiRenderer guiRenderer( guiShader, guiModel );

    float value = 0;

    while ( glfwWindowShouldClose( window ) == 0 ) {

        common::glfw3ProcessMouse( window );

        player.move( terrain );
        camera.move();

        render.processEntity( player );
        render.processTerrain( terrain );

        // Update entities
        for ( auto entity : entities ) {
            render.processEntity( entity );
        }

        render.render( lights, camera );

        // Render guis last
        guiRenderer.render( guis );

        common::DisplayManager::instance()->updateDisplay();

        // Clear inputs
        common::InputManager::instance()->clear();

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();

        value += 0.02f;
    }

    // Cleanup
    render.cleanup();
    loader.cleanup();
    guiRenderer.cleanup();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

