
// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// C++
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <thread>

#include "render.hh"
#include "loader.hh"
#include "shader.hh"
#include "OBJLoader.hh"
#include "../common/display.hh"
#include "../common/resources.hh"
#include "../common/math.hh"
#include "../common/controllers/controller.hh"
#include "../common/input/input.hh"

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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

common::Camera* camera = new common::Camera();

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float totalTime = 0.0f;


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
            switch( key ) {
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
            switch( key ) {
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


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->look( xoffset, yoffset );
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
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, "10_models", nullptr, nullptr );
    if ( window == nullptr ) {
        printf( "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Setup defaults
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );

    // Setup callbacks
    glfwSetKeyCallback(window, common::glfw3KeyPressCallback );
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowSizeCallback( window, windowResizeCallback );

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    camera->setSpeed( 10.0 );
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

    bool result;
    const std::string modelPath = common::getResource( "stall.obj", result );
    Model model = OBJLoader::loadObjModel( modelPath, loader );

    // Texture
    const std::string modelTexture = common::getResource( "stall.jpg", result );
    GLuint textureID = loader.loadTexture( modelTexture );
    ModelTexture texture( textureID );

    // Textured model
    TexturedModel texturedModel( model, texture );

    glm::vec3 translate( 0.0f, -4.0f, 1.0f );
    glm::vec3 rotate( 0.0f, 0.0f, 0.0f );
    GLfloat scale = 1.0f;
    Entity entity( texturedModel,
                   translate,
                   rotate,
                   scale );

    // Move away from screen
    entity.setPosition( glm::vec3( 0.0f, 0.0f, 0.0f ) );

    const double FRAMES_PER_SECOND = 60.0;
    const double MS_PER_FRAME = 1000.0 / FRAMES_PER_SECOND;

    double previous = glfwGetTime();
    double last_second_time = 0.0;
    unsigned int frame_count;

    float value = 0.0;
    double speed = 0.4;

    common::InputController cameraController( camera );

    while ( glfwWindowShouldClose( window ) == 0 ) {

        double current = glfwGetTime();
        double elapsed = current - previous;
        previous = current;

        // Update camera
        cameraController.update( elapsed );

        float xPosition = sin( value ) * 1.5;
        value += 0.04;

        // Move away from screen
        entity.setPosition( glm::vec3( xPosition, -2.0f, 0.0f ) );
        entity.increaseRotation( 0.0f, 1.0f, 0.0f );

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


        // Prepare
        render.prepare();
        shader.start();
        shader.loadViewMatrix( camera->view() );

        // Render
        render.render( entity, shader );
        shader.stop();


        // Clear inputs
        common::InputManager::instance()->clear();

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();

        // Cap FPS
        double sleep_time = std::max( 0.0, MS_PER_FRAME - elapsed );
        std::this_thread::sleep_for( std::chrono::milliseconds( ( unsigned int )sleep_time ) );
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

