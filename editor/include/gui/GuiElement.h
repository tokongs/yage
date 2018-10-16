#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "config.h"
#include "functional"
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
  GuiElement(std::function<void()> action = NULL);
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

  void setAction(std::function<void()> action);

  bool isOpen();

  void open();
  void close();

protected:
  std::unique_ptr<bool> m_open;
  std::function<void()> m_action;

private:
  DECLARE_LOGGERS;
};
} // namespace yage