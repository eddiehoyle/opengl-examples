
// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++
#include <cstdlib>
#include <cstdio>
#include <iostream>

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
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, "11_diffuse_lighting", nullptr, nullptr );
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
    common::DisplayManager::instance()->camera()->setPosition( glm::vec3( 0.0f, 0.0f, -5.0f ) );

    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Render render = Render( shader );

    bool result;
    const std::string modelPath = common::getResource( "dragon.obj", result );
    RawModel model = OBJLoader::loadObjModel( modelPath, loader );

    // Texture
    const std::string modelTexture = common::getResource( "white.png", result );
    GLuint textureID = loader.loadTexture( modelTexture );
    ModelTexture texture( textureID );

    // Textured model
    TexturedModel texturedModel( model, texture );

    // Entity position
    glm::vec3 translate( 0.0f, -2.0f, 0.0f );
    glm::vec3 rotate( 0.0f, 0.0f, 0.0f );
    GLfloat scale = 1.0f;
    Entity entity( texturedModel,
                   translate,
                   rotate,
                   scale );

    Light light( glm::vec3( 0, 0, -20 ), glm::vec3( 1, 1, 1 ) );

    float value = 0.0;
    double speed = 0.4;

    while ( glfwWindowShouldClose( window ) == 0 ) {

        float sinx = sin( value );
        float cosx = cos( value );
        value += 0.04;

        // Update
        entity.setPosition( glm::vec3( sinx, -2.0f, 0.0f ) );
//        entity.setRotation( glm::vec3( 0.0f, sinx * cosx * 10, 0.0f ) );
        entity.increaseRotation( 0, 1, 0 );

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

        // Prepare
        render.prepare();
        shader.start();
        shader.loadViewMatrix( common::Camera::createViewMatrix( camera ) );
        shader.loadLight( light );

        // Render
        render.render( entity, shader );
        shader.stop();

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // Cleanup
    shader.cleanup();
    loader.cleanup();

    // Tidy up camera
    delete camera;

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

