
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
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, "21_terrain_height_map", nullptr, nullptr );
    if ( window == nullptr ) {
        printf( "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Setup defaults
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );

    // Setup callbacks
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback( window, common::glfw3KeyPressCallback );
    glfwSetScrollCallback( window, common::glfw3MouseScrollCallback );
    glfwSetMouseButtonCallback( window, common::glfw3MouseButtonCallback );
    glfwSetWindowFocusCallback( window, common::glfw3WindowFocusCallback );

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if ( glewInit() != GLEW_OK ) {
        printf( "Failed to initialize GLEW\n" );
        glfwTerminate();
        return 1;
    }


    // Set width/height
//    common::DisplayManager::instance()->setCamera( camera );
    common::DisplayManager::instance()->update( kWindowWidth, kWindowHeight );

    // ---------------------------------------------------------------

    bool result;
    Loader loader = Loader();

    // ---------------------------------------------------------------

    // Grass
    const std::string bladesModelPath = common::getResource( "grass.obj", result );
    assert( result );
    const std::string bladesTexturePath = common::getResource( "grassBlades.png", result );
    assert( result );

    // Model and texture
    RawModel bladesModel = OBJLoader::loadObjModel( bladesModelPath, loader );
    ModelTexture bladesTexture( loader.loadTexture( bladesTexturePath ) );
    bladesTexture.setShineDamper( 10.0f );
    bladesTexture.setReflectivity( 1.0f );
    bladesTexture.setHasTransparency( true );
    bladesTexture.setUseFakeLighting( true );
    TexturedModel bladesTexturedModel( bladesModel, bladesTexture );

    // Create entities
    std::vector< Entity > entities;

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen( rd() ); // Standard mersenne_twister_engine seeded with rd()

    std::size_t numGrass = 100;
    for ( std::size_t i = 0; i < numGrass; ++i ) {

        std::uniform_real_distribution<> dis(0.0, 500.0 );
        std::uniform_real_distribution<> scaleDis( 3.0, 5.0 );

        double posX = dis( gen );
        double posZ = dis( gen );
        double scaleXYZ = scaleDis( gen );

        Entity grassEntity( bladesTexturedModel,
                           glm::vec3( 0, 0, 0 ),
                           glm::vec3( 0, 0, 0 ),
                           1 );
        grassEntity.setPosition( glm::vec3( posX, 0.0, posZ ) );
        grassEntity.setScale( scaleXYZ );
        entities.push_back( grassEntity );
    }

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

    // Light pointing straight down
    Light light( glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec3( 1, 1, 1 ) );

    // ---------------------------------------------------------------

    StaticShader shader;
    TerrainShader terrainShader;
    shader.init();
    terrainShader.init();
    MasterRenderer render( shader, terrainShader );

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

    float value = 0;

    while ( glfwWindowShouldClose( window ) == 0 ) {

        common::glfw3ProcessMouse( window );

        player.move();
        camera.move();

        render.processEntity( player );
        render.processTerrain( terrain );

        // Update entities
        for ( auto entity : entities ) {
            render.processEntity( entity );
        }

        render.render( light, camera );

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

    // Tidy up camera
//    delete camera;
//    delete bunny;

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

