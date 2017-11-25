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
          Device( DeviceType::Mouse ){
}

void MouseDevice::set( int x, int y ) {
    setX( x );
    setY( y );
}

void MouseDevice::setX( int x ) {
    m_prevX = m_x;
    m_x = x;
}

void MouseDevice::setY( int y ) {
    m_prevY = m_y;
    m_y = y;
}

int MouseDevice::x() const {
    return m_x;
}

int MouseDevice::y() const {
    return m_y;
}

int MouseDevice::prevX() const {
    return m_prevX;
}

int MouseDevice::prevY() const {
    return m_prevY;
}

}