#include "GuiElement.h"

namespace yage
{
DEFINE_LOGGERS(GuiElement);
GuiElement::GuiElement()
{
    INIT_LOGGERS(GuiElement);
}

GuiElement::~GuiElement()
{
    FLUSH_LOGGERS(GuiElement);
}

void GuiElement::constructFrame(bool independent)
{
    LOG(GuiElement, info, "Trying to construct gui element with base class. Which has not gui implemented. See GuiElement::constructFrame");
}
} // namespace yage