
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
#include "player.hh"
#include "../common/input/input.hh"

#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#endif

#ifndef GLFW_FALSE
#define GLFW_FALSE 0
#endif

const unsigned int kWindowWidth = 640;
const unsigned int kWindowHeight = 480;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
common::CameraLOGL cameraOgl(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
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

    cameraOgl.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cameraOgl.ProcessMouseScroll(yoffset);
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
    GLFWwindow *window = glfwCreateWindow( kWindowWidth, kWindowHeight, "18_player", nullptr, nullptr );
    if ( window == nullptr ) {
        printf( "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Setup defaults
    glfwSwapInterval( 1 );
    glfwSetTime( 0.0 );

    // Setup callbacks
    glfwSetKeyCallback( window, common::glfw3KeyPressCallback );
//    glfwSetWindowSizeCallback( window, windowResizeCallback );

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
    common::DisplayManager::instance()->camera()->setPitch( 15.0f );

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
    Model bladesModel = OBJLoader::loadObjModel( bladesModelPath, loader );
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

        std::uniform_real_distribution<> dis(-0, -500.0 );
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

    Terrain terrain( -1, -1, loader, texturePack, blendMap );

    // ---------------------------------------------------------------

    Light light( glm::vec3( 0, 100, 0 ), glm::vec3( 1, 1, 1 ) );

    // ---------------------------------------------------------------

    StaticShader shader;
    TerrainShader terrainShader;
    shader.init();
    terrainShader.init();
    MasterRenderer render( shader, terrainShader );

    // ---------------------------------------------------------------

    // Player model and texture
    const std::string cubeModelPath = common::getResource( "cube.obj", result );
    assert( result );
    const std::string cubeTexturePath = common::getResource( "white.png", result );
    assert( result );

    Model cubeModel = OBJLoader::loadObjModel( cubeModelPath, loader );
    ModelTexture cubeTexture( loader.loadTexture( cubeTexturePath ) );
    cubeTexture.setShineDamper( 10.0f );
    cubeTexture.setReflectivity( 1.0f );
    cubeTexture.setHasTransparency( true );
    cubeTexture.setUseFakeLighting( true );
    TexturedModel cubeTexturedModel( cubeModel, cubeTexture );

    Player player( cubeTexturedModel,
                   glm::vec3( 0, 0, 0 ),
                   glm::vec3( 0, 0, 0 ),
                   1 );

    // ---------------------------------------------------------------

    // Watching
    // https://youtu.be/d-kuzyCkjoQ?t=383

    // ---------------------------------------------------------------

    common::ObserverGame* observerGame = new common::ObserverGame;
    common::InputManager::instance()->addObserver( observerGame );

    double speed = 2.0;

    while ( glfwWindowShouldClose( window ) == 0 ) {

        if ( observerGame->isQuit() ) {
            glfwSetWindowShouldClose( window, GLFW_TRUE );
        }

        camera->update();
        player.checkInputs( window );

        for ( auto entity : entities ) {
            render.processEntity( entity );
        }
        render.processTerrain( terrain );
        render.render( light, camera );

        // Update display
        common::DisplayManager::instance()->updateDisplay();

        // Swap buffers
        glfwSwapBuffers( window );
        glfwPollEvents();
    }


    // Cleanup
    render.cleanup();
    loader.cleanup();
    common::InputManager::instance()->removeObserver( observerGame );

    // Tidy up camera
    delete camera;

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
