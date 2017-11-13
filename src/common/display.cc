//
// Created by Eddie Hoyle on 29/10/17.
//

#include "display.hh"
#include "camera.hh"

#include <chrono>
#include <ctime>

namespace common {

DisplayManager *DisplayManager::s_instance = nullptr;

DisplayManager *DisplayManager::instance() {
    if ( s_instance == nullptr ) {
        s_instance = new DisplayManager();
    }
    return s_instance;
}

DisplayManager::DisplayManager()
        : m_width( 0 ),
          m_height( 0 ) {
    m_lastFrameTime = getCurrentTime();
}

DisplayManager::~DisplayManager() {
    delete s_instance;
}

void DisplayManager::setCamera( Camera* camera ) {
    m_camera = camera;
}

Camera* DisplayManager::camera() const {
    return m_camera;
}

unsigned int DisplayManager::width() const {
    return m_width;
}

unsigned int DisplayManager::height() const {
    return m_height;
}

void DisplayManager::setWidth( unsigned int width ) {
    m_width = width;
}

void DisplayManager::setHeight( unsigned int height ) {
    m_height = height;
}

void DisplayManager::update( unsigned int width, unsigned int height ) {
    m_width = width;
    m_height = height;
}

void DisplayManager::updateDisplay() {
    long currentTime = getCurrentTime();
    m_delta = ( currentTime - m_lastFrameTime ) / 1000.0f;
    m_lastFrameTime = currentTime;
}

float DisplayManager::getFrameTimeSeconds() const {
    return m_delta;
}

long DisplayManager::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    return value.count();
}

} // namespace common
