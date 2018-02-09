
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
#include "bunny.hh"
#include "player.hh"
#include "mousePicker.hh"
#include "buffer.hh"

#include <common/display.hh>
#include <common/resources.hh>
#include <common/math.hh>
#include <common/input/input.hh>
#include <common/controllers/controller.hh>
#include <common/controllers/fpsController.hh>
#include <common/components/transformComponent.hh>
#include <common/controllers/tankController.hh>


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
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );

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

    // Collections
    std::vector< Entity > entities;
    std::vector< Terrain > terrains;
    std::vector< Light > lights;
    std::vector< WaterTile > waters;
    std::vector< GuiTexture > guiTextures;

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

    const std::string heightMapPath = common::getResource( "heightmapPond.png", result );
    Terrain terrain( 0, 0, loader, texturePack, blendMap, heightMapPath );
    terrains.push_back( terrain );

    // ---------------------------------------------------------------

    // Fern
    const std::string treeModelPath = common::getResource( "tree.obj", result );
    assert( result );
    const std::string treeTexturePath = common::getResource( "tree.png", result );
    assert( result );

    // Model and texture
    RawModel treeModel = OBJLoader::loadObjModel( treeModelPath, loader );
    ModelTexture treeTexture( loader.loadTexture( treeTexturePath ) );
    treeTexture.setNumberOfRows( 2 );
    treeTexture.setShineDamper( 10.0f );
    treeTexture.setReflectivity( 1.0f );
    treeTexture.setHasTransparency( true );
    treeTexture.setUseFakeLighting( false );
    TexturedModel treeTexturedModel( treeModel, treeTexture );


    // Corners
    entities.push_back( Entity( treeTexturedModel, glm::vec3( 98, 0, 98 ), glm::vec3( 0, 0, 0 ), 1, glm::vec2( 0, 0 ) ) );
    entities.push_back( Entity( treeTexturedModel, glm::vec3( 0, 0, 98 ), glm::vec3( 0, 0, 0 ), 1, glm::vec2( 0, 0 ) ) );
    entities.push_back( Entity( treeTexturedModel, glm::vec3( 98, 0, 0 ), glm::vec3( 0, 0, 0 ), 1, glm::vec2( 0, 0 ) ) );

    // Detail
    entities.push_back( Entity( treeTexturedModel, glm::vec3( 84, 0, 98 ), glm::vec3( 0, 0, 0 ), 1.3, glm::vec2( 0, 0 ) ) );
    entities.push_back( Entity( treeTexturedModel, glm::vec3( 96, 0, 74 ), glm::vec3( 0, 0, 0 ), 1.7, glm::vec2( 0, 0 ) ) );


    entities.push_back( Entity( treeTexturedModel, glm::vec3( 2, 0, 78 ), glm::vec3( 0, 0, 0 ), 0.7, glm::vec2( 0, 0 ) ) );

//    std::random_device rd;  // Will be used to obtain a seed for the random number engine
//    std::mt19937 gen( rd() ); // Standard mersenne_twister_engine seeded with rd()
//
//    for ( int i = 0; i < numEntities; ++i ) {
//
//        std::uniform_real_distribution<> dis( 0.0, terrainSize );
//
//        std::uniform_real_distribution<> textureIndexGen( 0, 2 );
//        glm::vec2 textureGrid( ( int )textureIndexGen( gen ),
//                               ( int )textureIndexGen( gen ) );
//
//        double posX = dis( gen );
//        double posZ = dis( gen );
//        double posY = terrain.getHeightOfTerrain( posX, posZ );
//
//        Entity fernEntity( fernTexturedModel,
//                           glm::vec3( posX, posY, posZ ),
//                           glm::vec3( 0, 0, 0 ),
//                           1,
//                           textureGrid );
//
//        entities.push_back( fernEntity );
//    }

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

    // Remember! Limited to only four lights at the moment
    // Sun
    lights.push_back( Light( glm::vec3( 200.0f, 1000.0f, 500.0f ), glm::vec3( 0.8, 0.8, 1 ) ) );

    // ---------------------------------------------------------------

//    double lampHeight = 14.0;
//    lights.push_back( Light( glm::vec3( 370.0f, 0.2 + lampHeight, 300.0f ), glm::vec3( 0, 1, 1 ), glm::vec3( 0.4, 0.01f, 0.001f ) ) );
//    lights.push_back( Light( glm::vec3( 293.0f, -4.4 + lampHeight, 305.0f ), glm::vec3( 1, 1, 0 ), glm::vec3( 0.4, 0.01f, 0.001f ) ) );
//    lights.push_back( Light( glm::vec3( 185.0f, -9.7 + lampHeight, 293.0f ), glm::vec3( 1, 0, 0 ), glm::vec3( 0.4, 0.01f, 0.001f ) ) );
//
//    const std::string lampModelPath = common::getResource( "lamp.obj", result );
//    assert( result );
//    const std::string lampMtlPath = common::getResource( "lamp.mtl", result );
//    assert( result );
//    const std::string lampTexturePath = common::getResource( "lamp.png", result );
//    assert( result );
//
//    // Model and texture
//    RawModel lampModel = OBJLoader::loadObjModel( lampModelPath, lampMtlPath, loader );
//    ModelTexture lampTexture( loader.loadTexture( lampTexturePath ) );
//    lampTexture.setShineDamper( 10.0f );
//    lampTexture.setReflectivity( 1.0f );
//    lampTexture.setHasTransparency( false );
//    lampTexture.setUseFakeLighting( false );
//    TexturedModel lampTexturedModel( lampModel, lampTexture );
//
//    entities.push_back( Entity( lampTexturedModel, glm::vec3( 370.0f, 0.2f, 300.0f ), glm::vec3( 0, 0, 0 ), 1 ) );
//    entities.push_back( Entity( lampTexturedModel, glm::vec3( 293.0f, -4.4f, 305.0f ), glm::vec3( 0, 0, 0 ), 1 ) );
//    entities.push_back( Entity( lampTexturedModel, glm::vec3( 185.0f, -9.7f, 293.0f ), glm::vec3( 0, 0, 0 ), 1 ) );

    // ---------------------------------------------------------------

//    const std::string gui1Path = common::getResource( "gui1.png", result );
//    assert( result );
//    const std::string gui2Path = common::getResource( "gui2.png", result );
//    assert( result );
//
//    // Health bar
//    GuiTexture gui1Texture = GuiTexture( loader.loadTexture( gui1Path ),
//                                         glm::vec2( -0.75f, 0.85f ),
//                                         glm::vec2( 0.2f, 0.05f ) );
//
//    // Runes
//    GuiTexture gui2Texture = GuiTexture( loader.loadTexture( gui2Path ),
//                                         glm::vec2( -0.8f, 0.73f ),
//                                         glm::vec2( 0.12f, 0.05f ) );

//    guis.push_back( gui1Texture );
//    guis.push_back( gui2Texture );
//
    std::vector< GLfloat > guiPositions = {
            -1.0f, 1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f, -1.0f
    };
    int guiDimensions = 2;
    RawModel guiModel = loader.loadToVao( guiPositions, guiDimensions );

    // ---------------------------------------------------------------

    std::vector< GLfloat > waterPositions = {
            -1, -1, -1, 1, 1, -1,
            1, -1, -1, 1, 1, 1
    };

    int waterDimensions = 2;
    RawModel waterModel = loader.loadToVao( waterPositions, waterDimensions );

    WaterTile waterTile( 50, 50, -1 );
    waters.push_back( waterTile );

    // ---------------------------------------------------------------

    WaterFrameBuffers fbos = WaterFrameBuffers();
//    GuiTexture refraction = GuiTexture( fbos.getRefractionTexture(),
//                                        glm::vec2( 0.5f, 0.5f ),
//                                        glm::vec2( 0.25f, 0.25f ) );
//    GuiTexture reflection = GuiTexture( fbos.getReflectionTexture(),
//                                        glm::vec2( -0.5f, 0.5f ),
//                                        glm::vec2( 0.25f, 0.25f ) );
//    guiTextures.push_back( refraction );
//    guiTextures.push_back( reflection );

    // ---------------------------------------------------------------

    StaticShader staticShader;
    TerrainShader terrainShader;
    GuiShader guiShader;
    SkyboxShader skyboxShader;
    WaterShader waterShader;

    staticShader.init();
    terrainShader.init();
    guiShader.init();
    skyboxShader.init();
    waterShader.init();

    MasterRenderer renderer( staticShader, terrainShader, skyboxShader );
    WaterRenderer waterRenderer( waterShader, waterModel, renderer.getProjectionMatrix(), fbos );
    GuiRenderer guiRenderer( guiShader, guiModel );

    // ---------------------------------------------------------------

    MousePicker picker = MousePicker( &camera, renderer.getProjectionMatrix(), terrain );

    // ---------------------------------------------------------------

    // ---------------------------------------------------------------

    while ( glfwWindowShouldClose( window ) == 0 ) {

        common::glfw3ProcessMouse( window );

        player.move( terrain );
        camera.move();

        glEnable( GL_CLIP_DISTANCE0 );

        // Render reflection texture
        fbos.bindReflectionFrameBuffer();

        glm::vec3 cameraPosition = camera.position();
        float distance = 2 * ( cameraPosition.y - waterTile.getHeight() );
        cameraPosition.y -= distance;
        camera.setPosition( cameraPosition );
        camera.invertPitch();
        renderer.renderScene( player, entities, terrains, lights, camera, glm::vec4( 0, 1, 0, -waterTile.getHeight() ) );
        cameraPosition.y += distance;
        camera.setPosition( cameraPosition );
        camera.invertPitch();

        // Render refraction texture
        fbos.bindRefractionFrameBuffer();
        renderer.renderScene( player, entities, terrains, lights, camera, glm::vec4( 0, -1, 0, waterTile.getHeight() ) );

        // Render
        fbos.unbindCurrentFrameBuffer();
        renderer.renderScene( player, entities, terrains, lights, camera, glm::vec4( 0, 0, 0, 0 ) );
        waterRenderer.render( waters, camera );
        guiRenderer.render( guiTextures );

        common::DisplayManager::instance()->updateDisplay();

        // Clear inputs
        common::InputManager::instance()->clear();

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // Cleanup
    fbos.cleanup();
    waterShader.cleanup();
    renderer.cleanup();
    loader.cleanup();
    guiRenderer.cleanup();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

