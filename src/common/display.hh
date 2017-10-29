//
// Created by Eddie Hoyle on 29/10/17.
//

#ifndef OPENGL_EXAMPLES_DISPLAY_HH
#define OPENGL_EXAMPLES_DISPLAY_HH

namespace common {

class Camera;

class DisplayManager {

public:
    static DisplayManager* instance();

public:
    DisplayManager( const DisplayManager& ) = delete;
    DisplayManager& operator=( const DisplayManager& ) = delete;
    ~DisplayManager();

    void setCamera( Camera* camera );
    Camera* camera() const;

    unsigned int width() const;
    unsigned int height() const;
    void setWidth( unsigned int width );
    void setHeight( unsigned int height );
    void update( unsigned int width, unsigned int height );

private:
    DisplayManager();
    static DisplayManager* s_instance;

    unsigned int m_width;
    unsigned int m_height;

    Camera* m_camera;
};

} // namespace common

#endif //OPENGL_EXAMPLES_DISPLAY_HH
