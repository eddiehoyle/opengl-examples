//
// Created by Eddie Hoyle on 25/11/17.
//

#ifndef OPENGL_EXAMPLES_DEVICE_HH
#define OPENGL_EXAMPLES_DEVICE_HH


#include <glm/vec2.hpp>

namespace common {

enum class DeviceType {
    None,
    Mouse
};

class Device {
public:
    virtual ~Device() {}

    DeviceType type() const;

    template< class CommandT >
    CommandT* asType() {
        return dynamic_cast< CommandT * >( this );
    }

protected:
    explicit Device( DeviceType type );
    DeviceType m_type;
};

class MouseDevice : public Device {

public:
    MouseDevice();
    void init( int x, int y );
    void set( int x, int y );
    void setX( int x );
    void setY( int y );

    int windowX() const;
    int windowY() const;
    int deltaX() const;
    int deltaY() const;
    int prevX() const;
    int prevY() const;

private:
    int m_initX;
    int m_initY;
    int m_x;
    int m_y;
    int m_prevX;
    int m_prevY;
    int m_windowX;
    int m_windowY;
};



}

#endif //OPENGL_EXAMPLES_DEVICE_HH
