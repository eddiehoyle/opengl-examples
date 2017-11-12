
// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <random>

#include "render.hh"
#include "loader.hh"
#include "shader.hh"

#include "../common/display.hh"
#include "../common/resources.hh"
#include "../common/math.hh"
#include "OBJLoader.hh"

#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#endif

#ifndef GLFW_FALSE
#define GLFW_FALSE 0
#endif


const unsigned int kWindowWidth = 640;
const unsigned int kWindowHeight = 480;

// Simple key press states
static bool kKeyPressedW = false;
static bool kKeyPressedA = false;
static bool kKeyPressedS = false;
static bool kKeyPressedD = false;
static bool kKeyPressedQ = false;
static bool kKeyPressedE = false;

void windowResizeCallback( GLFWwindow *window, int width, int height ) {
    common::DisplayManager::instance()->update(
            static_cast< unsigned int >( std::max( width, 0 ) ),
            static_cast< unsigned int >( std::max( height, 0 ) ) );
    std::cerr << __func__ << " : " << width << ", " << height << std::endl;
}

void keyPressEvent( GLFWwindow *window, int key, int scancode, int action, int mods ) {

    if ( key == GLFW_KEY_ESCAPE && mods == 0 )
        glfwSetWindowShouldClose( window, GLFW_TRUE );

    switch ( action ) {
        case GLFW_PRESS:
            switch ( key ) {
                case GLFW_KEY_W:
                    kKeyPressedW = true;
                    break;
                case GLFW_KEY_A:
                    kKeyPressedA = true;
                    break;
                case GLFW_KEY_S:
                    kKeyPressedS = true;
                    break;
                case GLFW_KEY_D:
                    kKeyPressedD = true;
                    break;
                case GLFW_KEY_Q:
                    kKeyPressedQ = true;
                    break;
                case GLFW_KEY_E:
                    kKeyPressedE = true;
                    break;
            }
            break;
        case GLFW_RELEASE:
            switch ( key ) {
                case GLFW_KEY_W:
                    kKeyPressedW = false;
                    break;
                case GLFW_KEY_A:
                    kKeyPressedA = false;
                    break;
                case GLFW_KEY_S:
                    kKeyPressedS = false;
                    break;
                case GLFW_KEY_D:
                    kKeyPressedD = false;
                    break;
                case GLFW_KEY_Q:
                    kKeyPressedQ = false;
                    break;
                case GLFW_KEY_E:
                    kKeyPressedE = false;
                    break;
            }
            break;
    }
}

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
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, "17_multi_texturing", nullptr, nullptr );
    if ( window == nullptr ) {
        printf( "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Setup defaults
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );

    // Setup callbacks
    glfwSetKeyCallback( window, keyPressEvent );
    glfwSetWindowSizeCallback( window, windowResizeCallback );

    // Activate this context
    glfwMakeContextCurrent( window );

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if ( glewInit() != GLEW_OK ) {
        printf( "Failed to initialize GLEW\n" );
        glfwTerminate();
        return 1;
    }

    // Set width/height
    common::Camera *camera = new common::Camera();
    common::DisplayManager::instance()->setCamera( camera );
    common::DisplayManager::instance()->update( kWindowWidth, kWindowHeight );
    common::DisplayManager::instance()->camera()->setPosition( glm::vec3( 0.0f, -5.0f, 0.0f ) );


    bool result;
    Loader loader = Loader();

    // Grass
    const std::string grassModelPath = common::getResource( "grass.obj", result );
    assert( result );
    const std::string grassTexturePath = common::getResource( "grassBlades.png", result );
    assert( result );
    Model grassModel = OBJLoader::loadObjModel( grassModelPath, loader );
    ModelTexture grassTexture( loader.loadTexture( grassTexturePath ) );
    grassTexture.setShineDamper( 10.0f );
    grassTexture.setReflectivity( 1.0f );
    grassTexture.setHasTransparency( true );
    grassTexture.setUseFakeLighting( true );
    TexturedModel grassTexturedModel( grassModel, grassTexture );

    // Fern
    const std::string fernModelPath = common::getResource( "fern.obj", result );
    assert( result );
    const std::string fernTexturePath = common::getResource( "fern2.png", result );
    assert( result );
    Model fernModel = OBJLoader::loadObjModel( fernModelPath, loader );
    ModelTexture fernTexture( loader.loadTexture( fernTexturePath ) );
    fernTexture.setShineDamper( 10.0f );
    fernTexture.setReflectivity( 1.0f );
    fernTexture.setHasTransparency( true );
    fernTexture.setUseFakeLighting( false );
    TexturedModel fernTexturedModel( fernModel, fernTexture );

    // Create entities
    std::vector< Entity > entities;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen( rd() ); //Standard mersenne_twister_engine seeded with rd()

    std::size_t numGrass = 500;
    for ( std::size_t i = 0; i < numGrass; ++i ) {

        std::uniform_real_distribution<> dis(-0, -500.0 );
        std::uniform_real_distribution<> scaleDis( 3.0, 5.0 );

        double posX = dis( gen );
        double posZ = dis( gen );
        double scaleXYZ = scaleDis( gen );

        Entity grassEntity( grassTexturedModel,
                           glm::vec3( 0, 0, 0 ),
                           glm::vec3( 0, 0, 0 ),
                           1 );
        grassEntity.setPosition( glm::vec3( posX, 0.0, posZ ) );
        grassEntity.setScale( scaleXYZ );
        entities.push_back( grassEntity );

    }

//    std::size_t numFerns = 100;
//    for ( std::size_t i = 0; i < numFerns; ++i ) {
//
//        std::uniform_real_distribution<> dis( -200, 100.0 );
//        std::uniform_real_distribution<> scaleDis( 1.0, 2.2 );
//
//        double posX = dis( gen );
//        double posZ = dis( gen );
//        double scaleXYZ = scaleDis( gen );
//
//        Entity fernEntity( fernTexturedModel,
//                       glm::vec3( 0, 0, 0 ),
//                       glm::vec3( 0, 0, 0 ),
//                       1 );
//        fernEntity.setPosition( glm::vec3( posX, 0.0, posZ ) );
//        fernEntity.setScale( scaleXYZ );
//        entities.push_back( fernEntity );
//    }

    Light light( glm::vec3( 0, 100, 0 ), glm::vec3( 1, 1, 1 ) );


    // Grass texture 0
    const std::string grass0 = common::getResource( "grass0.jpg", result );
    GLuint grassTextureID0 = loader.loadTexture( grass0 );
    ModelTexture grassTexture0( grassTextureID0 );
    grassTexture0.setShineDamper( 1.0f );
    grassTexture0.setReflectivity( 0.0f );
    assert( result );

    std::vector< Terrain > terrains;
    Terrain terrain( -1, -1, loader, grassTexture0 );
    terrains.push_back( terrain );

    double speed = 2.0;

    StaticShader shader;
    TerrainShader terrainShader;
    shader.init();
    terrainShader.init();
    MasterRenderer render( shader, terrainShader );

    while ( glfwWindowShouldClose( window ) == 0 ) {

        glm::vec3 cameraPosition;
        if ( kKeyPressedW ) {
            cameraPosition.z += speed;
        }
        if ( kKeyPressedA ) {
            cameraPosition.x += speed;
        }
        if ( kKeyPressedS ) {
            cameraPosition.z -= speed;
        }
        if ( kKeyPressedD ) {
            cameraPosition.x -= speed;
        }
        if ( kKeyPressedQ ) {
            cameraPosition.y -= speed;
        }
        if ( kKeyPressedE ) {
            cameraPosition.y += speed;
        }

        common::DisplayManager::instance()->camera()->move( cameraPosition );

        for ( auto entity : entities ) {
            render.processEntity( entity );
        }

        for ( auto terrain : terrains ) {
            render.processTerrain( terrain );
        }

        render.render( light, camera );

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // Cleanup
    render.cleanup();
    loader.cleanup();

    // Tidy up camera
    delete camera;

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

