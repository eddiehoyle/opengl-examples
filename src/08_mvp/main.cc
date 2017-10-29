
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

#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#endif

#ifndef GLFW_FALSE
#define GLFW_FALSE 0
#endif

const unsigned int kWindowWidth = 640;
const unsigned int kWindowHeight = 480;

void windowResizeCallback( GLFWwindow *window, int width, int height ) {
    common::DisplayManager::instance()->update(
            static_cast< unsigned int >( std::max( width, 0 ) ),
            static_cast< unsigned int >( std::max( height, 0 ) ) );
    std::cerr << __func__ << " : " << width << ", " << height << std::endl;
}


void keyPressEvent( GLFWwindow *window, int key, int scancode, int action, int mods ) {

    if ( key == GLFW_KEY_ESCAPE && mods == 0 )
        glfwSetWindowShouldClose( window, GLFW_TRUE );
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
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, "08_mvp", nullptr, nullptr );
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

    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Render render = Render( shader );

    std::vector< GLfloat > vertices = {
            -0.5f,0.5f,-0.5f,
            -0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,0.5f,-0.5f,

            -0.5f,0.5f,0.5f,
            -0.5f,-0.5f,0.5f,
            0.5f,-0.5f,0.5f,
            0.5f,0.5f,0.5f,

            0.5f,0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,0.5f,
            0.5f,0.5f,0.5f,

            -0.5f,0.5f,-0.5f,
            -0.5f,-0.5f,-0.5f,
            -0.5f,-0.5f,0.5f,
            -0.5f,0.5f,0.5f,

            -0.5f,0.5f,0.5f,
            -0.5f,0.5f,-0.5f,
            0.5f,0.5f,-0.5f,
            0.5f,0.5f,0.5f,

            -0.5f,-0.5f,0.5f,
            -0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,-0.5f,
            0.5f,-0.5f,0.5f

    };

    std::vector< GLfloat > textureCoods = {

            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0


    };

    std::vector< GLuint > indices = {
            0,1,3,
            3,1,2,
            4,5,7,
            7,5,6,
            8,9,11,
            11,9,10,
            12,13,15,
            15,13,14,
            16,17,19,
            19,17,18,
            20,21,23,
            23,21,22

    };

//    std::vector< GLfloat > vertices = {
//            -0.5f, 0.5f, 0.0f,
//            -0.5f, -0.5f, 0.0f,
//            0.5f, -0.5f, 0.0f,
//            0.5f, 0.5f, 0.0f
//    };
//
//    std::vector< GLuint > indices = {
//            0, 1, 3,
//            3, 1, 2
//    };
//
//    std::vector< GLfloat > textureCoods = {
//            0.0f, 0.0f, // V0
//            0.0f, 1.0f, // V1
//            1.0f, 1.0f, // V2
//            1.0f, 0.0f, // V3
//    };

    // Model
    Model model = loader.loadToVao( vertices, textureCoods, indices );

    // Texture
    bool result;
    const std::string cat = common::getResource( "cat.png", result );
    GLuint textureID = loader.loadTexture( cat );
    ModelTexture texture( textureID );

    // Textured model
    TexturedModel texturedModel( model, texture );

    glm::vec3 translate( 0.0f, 0.0f, 5.0f );
    glm::vec3 rotate( 0.0f, 0.0f, 0.0f );
    GLfloat scale = 1.0f;
    Entity entity( texturedModel,
                   translate,
                   rotate,
                   scale );

    while ( glfwWindowShouldClose( window ) == 0 ) {

        // Move away from screen
//        entity.increasePosition( 0.0f, 0.0f, -0.01f );

        glm::vec3 cameraPosition;

        int wState = glfwGetKey( window, GLFW_KEY_W );
        if ( wState == GLFW_PRESS || wState == GLFW_REPEAT ) {
            cameraPosition.z += 0.05f;
        }
        int aState = glfwGetKey( window, GLFW_KEY_A );
        if ( aState == GLFW_PRESS || aState == GLFW_REPEAT ) {
            cameraPosition.x += 0.05f;
        }

        int sState = glfwGetKey( window, GLFW_KEY_S );
        if ( sState == GLFW_PRESS || sState == GLFW_REPEAT ) {
            cameraPosition.z -= 0.05f;
        }

        int dState = glfwGetKey( window, GLFW_KEY_D );
        if ( dState == GLFW_PRESS || dState == GLFW_REPEAT ) {
            cameraPosition.x -= 0.05f;
        }

        common::DisplayManager::instance()->camera()->move( cameraPosition );

        // Prepare
        render.prepare();
        shader.start();
        shader.loadViewMatrix( common::Camera::createViewMatrix( camera ) );

        entity.increaseRotation( 1.0f, 1.0f, 0.0f );

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

