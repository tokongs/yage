#include "GuiElement.h"

namespace yage
{
DEFINE_LOGGERS(GuiElement);
GuiElement::GuiElement()
{
    INIT_LOGGERS(GuiElement);
    m_open = new bool();
    *m_open = true;
}

GuiElement::~GuiElement()
{
    FLUSH_LOGGERS(GuiElement);
    delete m_open;
}

void GuiElement::constructFrame(bool independent)
{
    LOG(GuiElement, info, "Trying to construct gui element with base class. Which has not gui implemented. See GuiElement::constructFrame");
}

bool GuiElement::isOpen(){
    return *m_open;
}
} // namespace yage