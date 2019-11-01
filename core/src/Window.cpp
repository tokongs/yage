#include <Window.h>
namespace yage
{
Window::Window(WindowDesc desc)
{
    mWindowDesc = desc;


    //Initialize GLFW
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        YAGE_CRITICAL("Failed to initialize GLFW");
        return;
    }

    //create GLFW window and OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, mWindowDesc.resizable);
    glfwWindowHint(GLFW_VISIBLE, mWindowDesc.visible);
    glfwWindowHint(GLFW_DECORATED, mWindowDesc.decorated);
    glfwWindowHint(GLFW_FLOATING, mWindowDesc.floating);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    if (mWindowDesc.fullscreen)
        mWindowHandle = glfwCreateWindow(mWindowDesc.width, mWindowDesc.height, mWindowDesc.title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        mWindowHandle = glfwCreateWindow(mWindowDesc.width, mWindowDesc.height, mWindowDesc.title.c_str(), NULL, NULL);

    if (!mWindowHandle)
    {
        glfwTerminate();
        YAGE_CRITICAL("Failed to create GLFW window");
        return;
    }

    glfwSetKeyCallback(mWindowHandle, glfw_key_callback);
    glfwSetCursorPosCallback(mWindowHandle, glfw_cursor_position_callback);
    glfwSetCursorEnterCallback(mWindowHandle, glfw_cursor_enter_callback);
    glfwSetMouseButtonCallback(mWindowHandle, glfw_mouse_button_callback);
    glfwSetScrollCallback(mWindowHandle, glfw_scroll_callback);
    glfwSetWindowSizeCallback(mWindowHandle, window_size_callback);

    //Make the created OpenGL context the current context
    glfwMakeContextCurrent(mWindowHandle);

    mDevice = new GLDevice();
}

Window::~Window()
{
    if(mDevice){
        delete mDevice;
    }
    glfwTerminate();
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(mWindowHandle);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(mWindowHandle);
}

void Window::resize(int width, int height)
{
    mWindowDesc.width = width;
    mWindowDesc.height = height;
    glfwSetWindowSize(mWindowHandle, width, height);
}

GLDevice* Window::getGraphicsDevice()
{
    return mDevice;
}

GLFWwindow *Window::getWindowHandle()
{
    return mWindowHandle;
}

void Window::window_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void glfw_error_callback(int error, const char *description)
{
    YAGE_ERROR("GLFW ERROR: " + std::to_string(error) + description);
}
 
} // namespace yage
