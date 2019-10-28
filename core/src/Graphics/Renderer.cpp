#include <Renderer.h>

namespace yage {
    Camera Renderer::mCamera;
    void Renderer::Init() {
    }

    void Renderer::SetCamera(Camera camera) {
        mCamera = camera;
    }

    void Renderer::Render(VertexBuffer *vb, Shader* shader) {
        IndexBuffer *ib = vb->getIndexBuffer();
        vb->bind();
        shader->setMat4("projection_matrix", mCamera.getProjectionMatrix());
        shader->setMat4("view_matrix", mCamera.getViewMatrix());
        shader->setMat4("model_matrix", glm::mat4(1));
        shader->activate();
        if (ib) {
            glDrawElements(GL_TRIANGLES, ib->getSize(), GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, vb->getSize());
        }
    }

    void Renderer::Render(yage::Ref<yage::Mesh> mesh, yage::Ref<yage::Material> material) {
        Render(mesh->getVertexBuffer(), material->getShader().get());
    }

} // namespace yage
