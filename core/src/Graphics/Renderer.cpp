#include <Renderer.h>

namespace yage {
    Camera Renderer::mCamera;
    void Renderer::Init() {
    }

    void Renderer::SetCamera(Camera camera) {
        mCamera = camera;
    }

    void Renderer::Render(VertexBuffer *vb, Program *program) {
        IndexBuffer *ib = vb->getIndexBuffer();
        vb->bind();
        program->setMat4("projection_matrix", mCamera.getProjectionMatrix());
        program->setMat4("view_matrix", mCamera.getViewMatrix());
        program->setMat4("model_matrix", glm::mat4(1));
        program->activate();
        if (ib) {
            glDrawElements(GL_TRIANGLES, ib->getSize(), GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, vb->getSize());
        }
    }

    void Renderer::Render(yage::Ref<yage::Mesh> mesh, yage::Ref<yage::Material> material) {
        Render(mesh->getVertexBuffer(), material->getShaderProgram().get());
    }

} // namespace yage
