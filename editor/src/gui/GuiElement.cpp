#include "GuiElement.h"

namespace yage
{
GuiElement::GuiElement(std::function<void()> action)
    : m_action(action)
{
    m_open = std::make_unique<bool>(false);

}

GuiElement::~GuiElement()
{

}

void GuiElement::constructFrame(bool independent)
{
    YAGE_INFO("Trying to construct gui element with base class. Which has not gui implemented. See GuiElement::constructFrame");
}

void GuiElement::setAction(std::function<void()> action)
{
    m_action = action;
}

bool GuiElement::isOpen()
{
    return *m_open;
}

void GuiElement::open()
{
    *m_open = true;
}
void GuiElement::close()
{
    *m_open = false;
}
} // namespace yage