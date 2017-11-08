
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
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, "13_optimising", nullptr, nullptr );
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
    common::Camera* camera = new common::Camera();
    common::DisplayManager::instance()->setCamera( camera );
    common::DisplayManager::instance()->update( kWindowWidth, kWindowHeight );
    common::DisplayManager::instance()->camera()->setPosition( glm::vec3( 0.0f, 0.0f, -3.0f ) );

    Loader loader = Loader();

    bool result;
    const std::string modelPath = common::getResource( "cube3.obj", result );
    assert( result );

    Model model = OBJLoader::loadObjModel( modelPath, loader );

    // Texture
    const std::string modelTexture = common::getResource( "cat.png", result );
    assert( result );

    GLuint textureID = loader.loadTexture( modelTexture );
    ModelTexture texture( textureID );
    texture.setShineDamper( 10.0f );
    texture.setReflectivity( 1.0f );

    // Textured model
    TexturedModel texturedModel( model, texture );

    // Create entities
    std::vector< Entity > entities;

    std::size_t numEntities = 1000;
    for ( std::size_t i = 0; i < numEntities; ++i ) {

        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(-10.0, 10.0);
        double posX = dis(gen);
        double posY = dis(gen);
        double posZ = dis(gen);

        // Entity position
        glm::vec3 translate( posX, posY, posZ );
        glm::vec3 rotate( 0.0f, 0.0f, 0.0f );
        GLfloat scale = 1.0f;
        Entity entity( texturedModel,
                       translate,
                       rotate,
                       scale );
        entities.push_back( entity );
    }

    Light light( glm::vec3( 0, 0, -20 ), glm::vec3( 1, 1, 1 ) );

    double speed = 0.4;

    StaticShader shader;
    MasterRender render( shader );

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

        common::DisplayManager::instance()->camera()->move( cameraPosition );

        for ( std::size_t i = 0; i < entities.size(); ++i ) {

            // Create some variation
            if ( i % 2 == 0 ) {
                entities[ i ].increaseRotation( 1, 1, 0 );
            } else if ( i % 3 == 0 ) {
                entities[ i ].increaseRotation( -1, 0, -1 );
            } else {
                entities[ i ].increaseRotation( 0, 1, -1 );
            }
            render.processEntity( entities[ i ] );
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

