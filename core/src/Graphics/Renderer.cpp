#include <Renderer.h>

namespace yage
{
Renderer::Renderer()
    : mCamera(Camera())
{
}

Renderer::~Renderer()
{
}

void Renderer::setCamera(Camera camera){
    mCamera = camera;
}

void Renderer::render(VertexBuffer* vb, Program* program)
{
    IndexBuffer* ib = vb->getIndexBuffer();
    vb->bind();
    program->activate();
    program->setMat4("projection_matrix", mCamera.getProjectionMatrix());
    program->setMat4("view_matrix", mCamera.getViewMatrix());
    program->setMat4("model_matrix", glm::mat4(1));
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
