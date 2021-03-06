
// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++
#include <cstdlib>
#include <cstdio>

#include "render.hh"
#include "loader.hh"
#include "shader.hh"
#include "../common/display.hh"

#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#endif

#ifndef GLFW_FALSE
#define GLFW_FALSE 0
#endif

void keyPressEvent( GLFWwindow* window, int key, int scancode, int action, int mods ) {
    if ( action != GLFW_PRESS )
        return;
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
    GLFWwindow* window = glfwCreateWindow( 640, 480, "05_colouring", nullptr, nullptr );
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

    // Activate this context
    glfwMakeContextCurrent( window );

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if ( glewInit() != GLEW_OK ) {
        printf( "Failed to initialize GLEW\n" );
        glfwTerminate();
        return 1;
    }

    Loader loader = Loader();
    Render render = Render();
    StaticShader shader = StaticShader();

    std::vector< GLfloat > vertices = {
            -0.5f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
    };

    std::vector< GLuint > indices = {
            0, 1, 3,
            3, 1, 2
    };

    RawModel model = loader.loadToVao( vertices, indices );

    while ( glfwWindowShouldClose( window ) == 0 ) {

        // Prepare
        render.prepare();
        shader.start();

        // TODO
        // Fix the quad

        // Render
        render.render( model );
        shader.stop();

        // NOTE:
        // This won't render at the moment as we need a shader.
        // Add this in later.

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // Cleanup
    shader.cleanup();
    loader.cleanup();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

