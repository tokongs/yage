#pragma once
#include "GuiElement.h"
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

    void constructFrame(bool independent) override;

    private:
    std::vector<std::unique_ptr<MenuElement> > m_elements;
};
} // namespace yage