#pragma once
#include <GL/glew.h>
#include <memory>
#include "VertexBuffer.h"
#include "Program.h"
#include "Camera.h"

namespace yage
{
/**
 * @brief Basic OpenGL renderer class
 * 
 */
class Renderer
{
    public:
    /**
     * @brief Construct a new Renderer object
     * 
     * @param device An OpenGL Rendering Device
     */
    Renderer();
    ~Renderer();

    /**
     * @brief Render a vertex buffer with the specified shader
     * 
     * @param vb 
     * @param shader 
     */
    void render(VertexBuffer* vb, Program* program);
    void setCamera(Camera camera);

    private:
    Camera mCamera;

};

} // namespace yage