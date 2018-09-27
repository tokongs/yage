#include <Renderer.h>

namespace yage
{
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::render(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<Shader> shader)
{
    std::shared_ptr<IndexBuffer> ib = vb->getIndexBuffer();
    vb->bind();
    shader->activate();
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
