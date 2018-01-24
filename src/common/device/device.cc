//
// Created by Eddie Hoyle on 25/11/17.
//

#include "device.hh"

namespace common {

DeviceType Device::type() const {
    return m_type;
}

Device::Device( DeviceType type )
    : m_type( type ) {}

MouseDevice::MouseDevice()
        : m_x( 0 ),
          m_y( 0 ),
          m_prevX( 0 ),
          m_prevY( 0 ),
          m_windowX( 0 ),
          m_windowY( 0 ),
          Device( DeviceType::Mouse ){
}

void MouseDevice::init( int x, int y ) {
    m_initX = x;
    m_initY = y;
    m_prevX = x;
    m_prevY = y;
    set( x, y );
}

void MouseDevice::set( int x, int y ) {
    setX( x );
    setY( y );
}

void MouseDevice::setX( int x ) {
    m_windowX = x;
    m_prevX = m_x;
    m_x = x - m_initX;
}

void MouseDevice::setY( int y ) {
    m_windowY = y;
    m_prevY = m_y;
    m_y = y - m_initY;
}

int MouseDevice::windowX() const {
    return m_windowX;
}

int MouseDevice::windowY() const {
    return m_windowY;
}

int MouseDevice::deltaX() const {
    return m_x;
}

int MouseDevice::deltaY() const {
    return m_y;
}

int MouseDevice::prevX() const {
    return m_prevX;
}

int MouseDevice::prevY() const {
    return m_prevY;
}

}