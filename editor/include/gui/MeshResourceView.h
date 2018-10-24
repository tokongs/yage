#pragma once
#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "ResourceView.h"
#include "Mesh.h"

namespace yage
{
/**
 * @brief Constructs a gui from a MeshPtr.
 * 
 */
class MeshResourceView : public ResourceView
{
    public:
    MeshResourceView();
    ~MeshResourceView();

    void constructFrame(bool independent) override;

};
} // namespace yage