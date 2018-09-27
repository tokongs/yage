#include <GL/glew.h>
#include <VertexBuffer.h>
#include <Shader.h>
#include <memory>

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
    void render(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<Shader> shader);

};

} // namespace yage