#include "GuiElement.h"

namespace yage
{
GuiElement::GuiElement(std::function<void()> action)
    : mAction(action)
{
    mOpen = true;

}

GuiElement::~GuiElement()
{

}

void GuiElement::setAction(std::function<void()> action)
{
    mAction = action;
}

bool GuiElement::isOpen()
{
    return mOpen;
}

void GuiElement::open()
{
    mOpen = true;
}
void GuiElement::close()
{
    mOpen = false;
}
} // namespace yage