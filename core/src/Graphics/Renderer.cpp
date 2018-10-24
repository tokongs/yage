#include <Renderer.h>

namespace yage
{
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
float x = 0;
void Renderer::render(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<Program> program)
{
    std::shared_ptr<IndexBuffer> ib = vb->getIndexBuffer();
    vb->bind();
    program->activate();
    if (ib)
    {
        glDrawElements(GL_TRIANGLES, ib->getSize(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, vb->getSize());
    }


    x += 0.001;
    x > 1 ? x = 0: x=x;
}

} // namespace yage
