#pragma once
#include <memory>
#include "imgui.h"
#include "ResourceView.h"
#include "Mesh.h"

namespace yage
{
class MeshResourceView : public ResourceView
{
    public:
    MeshResourceView();
    ~MeshResourceView();

    void constructFrame(bool independent) override;

};
} // namespace yage