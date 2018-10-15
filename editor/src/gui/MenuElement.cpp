#include "MenuElement.h"

namespace yage
{
MenuElement::MenuElement(std::string name, std::function<void()> action)
    : GuiElement(action), m_name(name)
{
    m_selected = std::make_unique<bool>(false);
}

MenuElement::~MenuElement()
{
}

void MenuElement::constructFrame(bool independent)
{
    ImGui::MenuItem(m_name.c_str(), nullptr, m_selected.get());

    if (*m_selected)
    {
        if (m_action)
        {
            m_action();
        }
        *m_selected = false;
    }
}

} // namespace yage