#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GuiElement.h>
namespace yage
{
class MenuElement : public GuiElement
{
public:
  MenuElement(std::string name, std::function<void()> action = NULL);
  ~MenuElement();

  void constructFrame(bool independent = false) override;

private:
  std::string mName;
  bool  mSelected = false;
};
} // namespace yage