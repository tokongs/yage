#pragma once
#include <GLDevice.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" //support for stdout logging
#include "spdlog/sinks/basic_file_sink.h"    //support for basic file logging
#include <config.h>
#include <memory>



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
    std::string title = ""; ///<Title of the window. No default title
    bool decorated = true;   ///< Is window decorated. True by default.
    bool resizable = false;  ///< Is window resizable. False by default.
    bool floating = false;   ///< Is window floating. False by default.
    bool fullscreen = false; ///< Is window fullscreen. False by default.  If this is set, width and height no longer matters
    bool visible = true; ///< Is window visible. True by default.
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
    std::shared_ptr<GLDevice> getGraphicsDevice();

    

  private:
    //Window properties
    WindowDesc m_window_desc;

    //pointer to the internal glfw window
    GLFWwindow *m_window_handle;

    //Loggers
    static std::shared_ptr<spdlog::logger> console_logger;
    static std::shared_ptr<spdlog::logger> file_logger;

    //Graphics Device
    std::shared_ptr<GLDevice> m_device;
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