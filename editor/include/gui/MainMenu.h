#pragma once
#include <map>
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GuiElement.h"
#include "MenuElement.h"
#include "vector"

namespace yage
{
/**
 * @brief Main menu for the editor window
 * 
 */
class MainMenu : public GuiElement
{
  public:
    MainMenu();
    ~MainMenu();

    void constructFrame(bool independent = false) override;

    void addMenuItem(std::string menu, MenuElement element);

  private:
    std::map<std::string, std::vector<MenuElement > > mElements;
};
} // namespace yage