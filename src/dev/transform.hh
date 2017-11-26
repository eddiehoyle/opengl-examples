//
// Created by Eddie Hoyle on 26/11/17.
//

#ifndef OPENGL_EXAMPLES_TRANSFORM_HH
#define OPENGL_EXAMPLES_TRANSFORM_HH

//#include "../common/components/component.hh"


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>



class Transform
{
public:
    Transform();
    Transform(const glm::vec3 &t, const glm::quat &o, const glm::vec3 &s);
    Transform(const glm::mat4 &matrix);

    void setTranslation(const glm::vec3 &translation) { m_translation = translation; }
    void setOrientation(const glm::quat &orientation) { m_orientation = orientation; }
    void setScale(const glm::vec3 &scale) { m_scale = scale; }

    void setMat4(const glm::mat4 &matrix);

    const glm::vec3 & getTranslation() const { return m_translation; }
    const glm::quat & getOrientation() const { return m_orientation; }
    const glm::vec3 & getScale() const { return m_scale; }

    glm::mat4 getMat4() const;
    glm::mat4 getInvMat4() const;

    static Transform interpolate(const Transform & t0, const Transform & t1, float k);

    Transform operator + (const Transform &rhs) const;
    Transform operator - (const Transform &rhs) const;
    Transform operator * (const Transform &rhs) const;
    Transform operator * (float rhs) const;

private:
    glm::vec3 m_translation;
    glm::quat m_orientation;
    glm::vec3 m_scale;
};


Transform::Transform() :
        m_scale(glm::vec3(1))
{

}

Transform::Transform(const glm::vec3 &t, const glm::quat &o, const glm::vec3 &s) :
        m_translation(t),
        m_orientation(o),
        m_scale(s)
{

}

Transform::Transform(const glm::mat4 &matrix) :
        m_scale(glm::vec3(1))
{
    setMat4(matrix);
}

void Transform::setMat4(const glm::mat4 &matrix)
{
    glm::vec3 c[] = {
            glm::vec3(glm::column(matrix, 0)),
            glm::vec3(glm::column(matrix, 1)),
            glm::vec3(glm::column(matrix, 2)),
            glm::vec3(glm::column(matrix, 3)) };

    glm::vec3 scale = glm::vec3(glm::length(c[0]), glm::length(c[1]), glm::length(c[2]));
    glm::quat orientation = glm::quat_cast(matrix);
    glm::vec3 translation = c[3];

    /*printf("Result: S: %.2f %.2f %.2f, R: %.2f %.2f %.2f %.2f, T: %.2f %.2f %.2f\n",
        scale.x, scale.y, scale.z,
        orientation.w, orientation.x, orientation.y, orientation.z,
        translation.x, translation.y, translation.z);*/

    setScale(scale);
    setOrientation(orientation);
    setTranslation(translation);
}

glm::mat4 Transform::getMat4() const
{
    glm::mat4 T = glm::translate(glm::mat4(), m_translation);
    glm::mat4 R = glm::mat4_cast(m_orientation);
    glm::mat4 S = glm::scale(glm::mat4(), m_scale);

    return T * R * S;
}

glm::mat4 Transform::getInvMat4() const
{
    glm::mat4 T = glm::translate(glm::mat4(), -m_translation);
    glm::mat4 R = glm::mat4_cast(glm::conjugate(m_orientation));
    glm::mat4 S = glm::scale(glm::mat4(), 1.0f/m_scale);

    return S * R * T;
}

Transform Transform::interpolate(const Transform & t0, const Transform & t1, float k)
{
    Transform T;
    k = glm::clamp(k, 0.0f, 1.0f);

    T.setTranslation(glm::mix(t0.getTranslation(), t1.getTranslation(), k));
    T.setOrientation(glm::slerp(t0.getOrientation(), t1.getOrientation(), k));
    T.setScale(glm::mix(t0.getScale(), t1.getScale(), k));

    return T;
}

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "../common/components/component.hh"


class Entity
{
public:
    // Spatial functionality
    void setPosition(const glm::vec3 & position);
    void setOrientation(const glm::quat & orientation);
    void setScale(const glm::vec3 & scale);

    void translate(const glm::vec3 & translation);
    void move(const glm::vec3 & move);

    void rotate(const glm::quat & quaternion);
    void rotate(const glm::vec3 & eulerAngles);

    Transform getTransform() { return m_transform; }
protected:
    Transform m_transform;
};

void Entity::setPosition(const glm::vec3 & position)
{
    m_transform.setTranslation(position);
}

void Entity::setOrientation(const glm::quat & orientation)
{
    m_transform.setOrientation(orientation);
}

void Entity::setScale(const glm::vec3 & scale)
{
    m_transform.setScale(scale);
}

void Entity::translate(const glm::vec3 & translation)
{
    glm::vec3 position = m_transform.getTranslation();
    m_transform.setTranslation(position + translation);
}

void Entity::move(const glm::vec3 & move)
{
    // Maybe R-1 should be used
    glm::mat3 R = glm::mat3_cast(m_transform.getOrientation());
    translate(R * move);
}

void Entity::rotate(const glm::quat & quaternion)
{
    glm::quat orientation = m_transform.getOrientation();
    m_transform.setOrientation(orientation * quaternion);
}

void Entity::rotate(const glm::vec3 & eulerAngles)
{
    glm::vec3 xyz(eulerAngles.y, eulerAngles.x, eulerAngles.z);
    glm::mat3 R = glm::orientate3(xyz);
    rotate(glm::quat_cast(R));
}

void runTransform() {

//    Entity e;
//    e.rotate( glm::radians( glm::vec3( 90.0f, 0.0f, 0.0f ) ) );
//    e.rotate( glm::radians( glm::vec3( 0.0f, 90.0f, 0.0f ) ) );
//    e.rotate( glm::radians( glm::vec3( 0.0f, 0.0f, 90.0f ) ) );
//
//    Transform t = e.getTransform();
//
//    glm::mat4 matrix = t.getMat4();
//    float x, y, z;
//    glm::extractEulerAngleXYZ( matrix, x, y, z );
//    glm::vec3 degreesExternal = glm::degrees( glm::vec3( x, y, z ) );
//    std::cerr << glm::to_string( degreesExternal ) << std::endl;

    common::TransformComponent transform;
//    transform.rotate( glm::radians( glm::vec3( 90.0f, 0.0f, 0.0f ) ) );
//    transform.rotate( glm::radians( glm::vec3( 0.0f, 90.0f, 0.0f ) ) );
//    transform.rotate( glm::radians( glm::vec3( 0.0f, 0.0f, 90.0f ) ) );


    while ( true ) {
        transform.rotate( glm::radians( glm::vec3( 0.00f, 0.0f, 0.01f ) ) );
        glm::vec3 degreesInternal = transform.rotation();
        std::cerr << glm::to_string( degreesInternal ) << std::endl;
    }




}

#endif //OPENGL_EXAMPLES_TRANSFORM_HH
