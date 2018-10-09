#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "config.h"

namespace yage
{
/**
     * @brief Base class for gui elements
     * 
     */
class GuiElement
{
  public:
    /**
         * @brief Construct a new gui element.
         */
    GuiElement();
    ~GuiElement();

    /**
         * @brief Constructs the gui using ImGUi. If independent is true this gui will be constructed as an independent window.
         * else it's gonna be imbeded in the "current gui". the window that had its "begin" called last and "end" not yet called.
         * These are called in construct frame.
         * 
         * @param bool independent
         */
    virtual void constructFrame(bool independent = false);
    /**
     * @brief A pointer to the open status of the element. Do not use this unless you know what you are doing
     * 
     * @return true 
     * @return false 
     */

    bool isOpen();
    protected:
      bool *m_open;
  private:
    DECLARE_LOGGERS;
};
} // namespace yage