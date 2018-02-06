//
// Created by Eddie Hoyle on 6/02/18.
//

#ifndef OPENGL_EXAMPLES_BUFFER_HH
#define OPENGL_EXAMPLES_BUFFER_HH


class WaterFrameBuffers {

public:

    WaterFrameBuffers();
    ~WaterFrameBuffers() = default;

    void cleanup();

    /// Call before rendering to this FBO
    void bindReflectionFrameBuffer();

    /// Call before rendering to this FBO
    void bindRefractionFrameBuffer();

    /// Call to switch to default frame buffer
    void unbindCurrentFrameBuffer();

    /// Get the resulting texture
    GLuint getReflectionTexture();

    /// Get the resulting texture
    GLuint getRefractionTexture();

    /// Get the resulting depth texture
    GLuint getRefractionDepthTexture();

private:

    void initialiseReflectionFrameBuffer();
    void initialiseRefractionFrameBuffer();
    void bindFrameBuffer(int frameBuffer, int width, int height);

    GLuint createFrameBuffer();
    GLuint createTextureAttachment(int width, int height);
    GLuint createDepthTextureAttachment(int width, int height);
    GLuint createDepthBufferAttachment(int width, int height);

    GLuint m_reflectionFrameBuffer;
    GLuint m_reflectionTexture;
    GLuint m_reflectionDepthBuffer;

    GLuint m_refractionFrameBuffer;
    GLuint m_refractionTexture;
    GLuint m_refractionDepthTexture;
};


#endif //OPENGL_EXAMPLES_BUFFER_HH
