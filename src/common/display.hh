//
// Created by Eddie Hoyle on 29/10/17.
//

#ifndef OPENGL_EXAMPLES_DISPLAY_HH
#define OPENGL_EXAMPLES_DISPLAY_HH

class GLFWwindow;

namespace common {

class Camera;

void glfw3WindowFocusCallback(GLFWwindow* window, int state );

class DisplayManager {

public:
    static DisplayManager* instance();

public:
    DisplayManager( const DisplayManager& ) = delete;
    DisplayManager& operator=( const DisplayManager& ) = delete;
    ~DisplayManager();

    void setFocused( bool state ) { m_focused = state; }
    bool isFocused() { return m_focused; }

    unsigned int width() const;
    unsigned int height() const;
    void setWidth( unsigned int width );
    void setHeight( unsigned int height );
    void update( unsigned int width, unsigned int height );
    long getCurrentTime() const;

    /// Not sure yet...
    void updateDisplay();

    float getFrameTimeSeconds() const;

private:
    DisplayManager();
    static DisplayManager* s_instance;

private:

    unsigned int m_width;
    unsigned int m_height;

    bool m_focused;

    Camera* m_camera;

    // Frames
    long m_lastFrameTime;
    float m_delta;
};

} // namespace common

#endif //OPENGL_EXAMPLES_DISPLAY_HH
