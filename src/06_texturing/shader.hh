//
// Created by Eddie Hoyle on 23/10/17.
//

#ifndef LEARNING_OPENGL_06_TEXTURING_SHADER_HH
#define LEARNING_OPENGL_06_TEXTURING_SHADER_HH

#include <GL/glew.h>
#include <string>

class AbstractShader {

public:

    explicit AbstractShader( const std::string& vertex_path, const std::string& fragment_path );

    void start();
    void stop();
    void cleanup();
    virtual void bindAttributes() {};

protected:
    virtual void bindAttribute( GLint attribute, const std::string& name );

private:
    GLint m_programID;
    GLint m_vertexShaderID;
    GLint m_fragmentShaderID;

};

class StaticShader : public AbstractShader {

public:
    StaticShader();
    virtual void bindAttributes();

};


#endif //LEARNING_OPENGL_06_TEXTURING_SHADER_HH
