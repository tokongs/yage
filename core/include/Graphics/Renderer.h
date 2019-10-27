#pragma once
#include <GL/glew.h>
#include <memory>
#include <Scene/Scene.h>
#include "VertexBuffer.h"
#include "Program.h"
#include "Camera.h"
#include "Reference.h"
#include "Mesh.h"
#include "Material.h"

namespace yage
{
/**
 * @brief Basic OpenGL renderer class
 * 
 */
class Renderer
{
    public:
    static void Init();
    static void Shutdown();

    /**
     * @brief Render a vertex buffer with the specified shader
     * 
     * @param vb 
     * @param shader 
     */
    static void Render(VertexBuffer* vb, Program* program);
    static void Render(Ref<Mesh> mesh, Ref<Material> material);
    static void SetCamera(Camera camera);

    private:
    static Camera mCamera;

};

} // namespace yage