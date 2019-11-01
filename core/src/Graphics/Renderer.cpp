#include <Renderer.h>

namespace yage {
    Camera Renderer::mCamera;
    void Renderer::Init() {
    }

    void Renderer::SetCamera(Camera camera) {
        mCamera = camera;
    }

    void Renderer::Render(VertexBuffer *vb, Shader* shader) {

        if(!vb){
            YAGE_ERROR("Trying to render with a nullptr vertex buffer. Skipping.");
            return;
        }
        if(!shader){
            YAGE_ERROR("Trying to render with a nullptr shader. Skipping.");
            return;
        }
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
        VertexBuffer *vb = mesh->getVertexBuffer();
        Shader *shader = material->getShader().get();
        if(!vb){
            YAGE_ERROR("Trying to render with a nullptr vertex buffer. Skipping.");
            return;
        }
        if(!shader){
            YAGE_ERROR("Trying to render with a nullptr shader. Skipping.");
            return;
        }
        IndexBuffer *ib = vb->getIndexBuffer();
        vb->bind();
        shader->setMat4("projection_matrix", mCamera.getProjectionMatrix());
        shader->setMat4("view_matrix", mCamera.getViewMatrix());
        shader->setMat4("model_matrix", glm::mat4(1));
        material->activate();
        if (ib) {
            glDrawElements(GL_TRIANGLES, ib->getSize(), GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, vb->getSize());
        }
    }

} // namespace yage
