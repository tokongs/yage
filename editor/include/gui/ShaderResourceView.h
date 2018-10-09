#pragma once
#include <memory>
#include "imgui.h"
#include "ResourceView.h"
#include "Shader.h"

namespace yage
{
/**
 * @brief Constructs a gui detail view for a Shader
 * 
 */
class ShaderResourceView : public ResourceView
{
    public:
    ShaderResourceView();
    ~ShaderResourceView();

    void constructFrame(bool independent) override;

};
} // namespace yage