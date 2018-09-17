#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" //support for stdout logging
#include "spdlog/sinks/basic_file_sink.h"    //support for basic file logging
#include <config.h>
#include <memory>
#include <iostream>
#include <glm/vec4.hpp>

namespace yage
{

static void GLAPIENTRY
gl_debug_message_callback(GLenum source,
                          GLenum type,
                          GLuint id,
                          GLenum severity,
                          GLsizei length,
                          const GLchar *message,
                          const void *userParam);

/**
 * @brief Graphics Device using OpenGL.
 * 
 */
class GLDevice
{
  public:
    /**
     * @brief Loads the OpenGL extensions and setup what is needed to get GL to work. Should only be used by the Window class
     * 
     */
    GLDevice();
    ~GLDevice();

    /**
     * @brief Clears the Color and Depth bufers
     * 
     */
    void clearBuffers();

    /**
     * @brief Set the color to clear the color buffer with
     * 
     * @param color
     */
    void setClearColor(glm::vec4 color);

  private:

    //Loggers
    static std::shared_ptr<spdlog::logger> console_logger;
    static std::shared_ptr<spdlog::logger> file_logger;


  private:
    friend void GLAPIENTRY
    gl_debug_message_callback(GLenum source,
                              GLenum type,
                              GLuint id,
                              GLenum severity,
                              GLsizei length,
                              const GLchar *message,
                              const void *userParam);
};

} // namespace yage