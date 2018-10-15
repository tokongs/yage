#include "GuiElement.h"

namespace yage
{
DEFINE_LOGGERS(GuiElement);
GuiElement::GuiElement(std::function<void()> action)
    : m_action(action)
{
    INIT_LOGGERS(GuiElement);
    m_open = std::make_unique<bool>(false);

}

GuiElement::~GuiElement()
{
    FLUSH_LOGGERS(GuiElement);

}

void GuiElement::constructFrame(bool independent)
{
    LOG(GuiElement, info, "Trying to construct gui element with base class. Which has not gui implemented. See GuiElement::constructFrame");
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