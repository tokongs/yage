#pragma once
#include <GLDevice.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <memory>
#include "config.h"
#include "Input.h"
#include "Logger.h"

namespace yage
{

/**
 * @brief Window creation description
 * 
 */
struct WindowDesc
{
  int width = 1024;        ///< Width of the window. 1024 by default.
  int height = 768;        ///< Height of the window. 768 by default.
  std::string title = "";  ///<Title of the window. No default title
  bool decorated = true;   ///< Is window decorated. True by default.
  bool resizable = false;  ///< Is window resizable. False by default.
  bool floating = false;   ///< Is window floating. False by default.
  bool fullscreen = false; ///< Is window fullscreen. False by default.  If this is set, width and height no longer matters
  bool visible = true;     ///< Is window visible. True by default.
};

static void glfw_error_callback(int error, const char *description);
/**
 * @brief Wrapper around a GLFW window
 *  
 */
class Window
{

public:
  /**
    * @brief Initializes glfw and creates a new window
    * 
    * @param desc A description of the window 
    */
  Window(WindowDesc desc);

  /**
    * @brief Terminate glfw
    */
  ~Window();

  /**
    * @brief Poll glfw for input and swap buffers
    */
  void update();

  /**
    * @brief Check if the glfw close flag is set
    * 
    * @return true if window is supposed to close
    */
  bool shouldClose();

  /**
    * @brief Manually resize the window
    * 
    * @param width the new width of the window
    * @param height the new height of the window
    */
  void resize(int width, int height);

  /**
     * @brief Get this window's graphics device
     * 
     * @return GLDevice* 
     */
  GLDevice* getGraphicsDevice();

  /**
     * @brief Get a pointer to the glfw window internal window handle
     * 
     * @return GLFWwindow* 
     */
  GLFWwindow *getWindowHandle();

private:
  //Window properties
  WindowDesc mWindowDesc;

  //pointer to the internal glfw window
  GLFWwindow *mWindowHandle;

  //Graphics Device
  GLDevice* mDevice;

private:
  /**
     * @brief Create this windows graphics device
     * 
     */
  void createGraphicsDevice();

  //Window should be non-copyable
  Window(const Window &);
  Window &operator=(const Window &);

  /**
 * @brief 
 * 
 * @param error GLFW error code
 * @param description Human readable description of the error
 */
  friend void glfw_error_callback(int error, const char *description);
};

} // namespace yage
