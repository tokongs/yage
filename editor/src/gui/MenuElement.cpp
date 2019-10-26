#include "MenuElement.h"

namespace yage
{
MenuElement::MenuElement(std::string name, std::function<void()> action)
    : GuiElement(action), mName(name)
{
    mSelected = false;
}

MenuElement::~MenuElement()
{
}

void MenuElement::constructFrame(bool independent)
{
    ImGui::MenuItem(mName.c_str(), nullptr, mSelected);

    if (mSelected)
    {
        if (mAction)
        {
            mAction();
        }
        mSelected = false;
    }
}

} // namespace yage