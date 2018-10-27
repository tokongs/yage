#include <Renderer.h>
#include <Texture.h>
#include <ResourceManager.h>

namespace yage
{
    int texture1 = 0;
Renderer::Renderer()
    : m_camera(Camera())
{
    texture1 = yage::ResourceManager::getInstance().getHandle<Texture>("test");
}

Renderer::~Renderer()
{
}

void Renderer::setCamera(Camera camera){
    m_camera = camera;
}

void Renderer::render(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<Program> program)
{
    std::shared_ptr<IndexBuffer> ib = vb->getIndexBuffer();
    vb->bind();
    program->activate();
    program->setMat4("projection_matrix", m_camera.getProjectionMatrix());
    program->setMat4("view_matrix", m_camera.getViewMatrix());
    program->setMat4("model_matrix", glm::mat4(1));
    TexturePtr tex = yage::ResourceManager::getInstance().getResource<Texture>(texture1);
    tex->bind();
    program->setInt("texture1", tex->getTextureUnit());
    if (ib)
    {
        glDrawElements(GL_TRIANGLES, ib->getSize(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, vb->getSize());
    }
}

} // namespace yage
