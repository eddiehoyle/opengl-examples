
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
#include "../common/resources.hh"
#include "../common/math.hh"

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
    GLFWwindow* window = glfwCreateWindow( 640, 480, "07_uniforms", nullptr, nullptr );
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
    glfwSetWindowTitle( window, "07_uniforms" );

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

    std::vector< GLfloat > textureCoods = {
            0.0f, 0.0f, // V0
            0.0f, 1.0f, // V1
            1.0f, 1.0f, // V2
            1.0f, 0.0f, // V3
    };


//    glm::vec3 translate( 1.0f, 2.0f, 3.0f );
//    glm::vec3 rotate( 40.0f, 120.0f, 12.0f );
//    GLfloat scale = 1.4f;
//    glm::mat4 matrix = common::createTransformationMatrix( translate, rotate, scale );

    // Model
    RawModel model = loader.loadToVao( vertices, textureCoods, indices );

    // Texture
    bool result;
    const std::string cat = common::getResource( "cat.png", result );
    GLuint textureID = loader.loadTexture( cat );
    ModelTexture texture( textureID );

    // Create a transform matrix
    glm::vec3 translate( 0.0f, 0.0f, 0.0f );
    glm::vec3 rotate( 0.0f, 0.0f, 30.0f );
    GLfloat scale = 1.0f;
    glm::mat4 matrix = common::createTransformationMatrix( translate, rotate, scale );

    // Textured model
    TexturedModel texturedModel( model, texture );

    while ( glfwWindowShouldClose( window ) == 0 ) {

        // Prepare
        render.prepare();
        shader.start();

        // Apply matrix
        shader.loadTransformationMatrix( matrix );

        // Render
        render.render( texturedModel );
        shader.stop();

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

