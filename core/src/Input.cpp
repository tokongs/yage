#include <Events/InputEvent.h>
#include "Input.h"

namespace yage
{
std::unordered_map<int, KEY_ACTION> Input::m_keys = std::unordered_map<int, KEY_ACTION>();
MouseState Input::m_mouse_state = MouseState();
std::unordered_map<std::string, std::vector<std::function<void()>>> Input::m_on_press_callbacks = std::unordered_map<std::string, std::vector<std::function<void()>>>();
std::unordered_map<std::string, std::vector<std::function<void()>>> Input::m_on_release_callbacks = std::unordered_map<std::string, std::vector<std::function<void()>>>();
std::unordered_map<std::string, std::vector<std::function<void()>>> Input::m_on_repeat_callbacks = std::unordered_map<std::string, std::vector<std::function<void()>>>();

std::vector<std::vector<std::function<void()>>> Input::m_on_mouse_down_callbacks = std::vector<std::vector<std::function<void()>>>();
std::vector<std::vector<std::function<void()>>> Input::m_on_mouse_up_callbacks = std::vector<std::vector<std::function<void()>>>();
std::vector<std::vector<std::function<void()>>> Input::m_on_mouse_repeat_callbacks = std::vector<std::vector<std::function<void()>>>();

std::vector<std::function<void()>> Input::m_on_mouse_leave_callbacks = std::vector<std::function<void()>>();
std::vector<std::function<void()>> Input::m_on_mouse_enter_callbacks = std::vector<std::function<void()>>();
std::vector<std::function<void(float, float)>> Input::m_on_mouse_move_callbacks = std::vector<std::function<void(float, float)>>();
std::vector<std::function<void(double, double)>> Input::m_on_mouse_scroll_callbacks = std::vector<std::function<void(double, double)>>();


std::unordered_map<int, std::vector<std::string>> Input::m_mappings = std::unordered_map<int, std::vector<std::string>>();
std::unordered_map<std::string, unsigned int> Input::m_reverse_mappings = std::unordered_map<std::string, unsigned int>();

EventBus Input::eventBus = EventBus();

void Input::Init() {
    for (int i = GLFW_MOUSE_BUTTON_1; i < GLFW_MOUSE_BUTTON_8; i++)
    {
        m_keys[i] = KEY_ACTION::NONE;
    }
    for (int i = 32; i <= GLFW_KEY_LAST; i++)
    {
        m_keys[i] = KEY_ACTION::NONE;
    }

    //GLFW_MOUSE_BUTTON_1
    m_on_mouse_down_callbacks.push_back(std::vector<std::function<void()>>());
    m_on_mouse_up_callbacks.push_back(std::vector<std::function<void()>>());
    m_on_mouse_repeat_callbacks.push_back(std::vector<std::function<void()>>());
    //GLFW_MOUSE_BUTTON_2
    m_on_mouse_down_callbacks.push_back(std::vector<std::function<void()>>());
    m_on_mouse_up_callbacks.push_back(std::vector<std::function<void()>>());
    m_on_mouse_repeat_callbacks.push_back(std::vector<std::function<void()>>());
    //GLFW_MOUSE_BUTTON_3
    m_on_mouse_down_callbacks.push_back(std::vector<std::function<void()>>());
    m_on_mouse_up_callbacks.push_back(std::vector<std::function<void()>>());
    m_on_mouse_repeat_callbacks.push_back(std::vector<std::function<void()>>());
}

void Input::mapKey(int key, std::string action)
{
    //If a mapping already exists just insert a new one,
    //else create a new vector first
    auto it = m_mappings.find(key);
    if (it != m_mappings.end())
    {
        it->second.push_back(action);
    }
    else
    {
        m_mappings[key] = std::vector<std::string>();
        m_mappings[key].push_back(action);
    }
    m_reverse_mappings[action] = key;
}

MouseState Input::GetMouseState(){
   return m_mouse_state;
}

void Input::registerKeyCallBack(KEY_ACTION action, std::string mapping, std::function<void()> callback)
{
    switch (action)
    {
    case KEY_ACTION::PRESS:
    {
        auto it = m_on_press_callbacks.find(mapping);

        if (it != m_on_press_callbacks.end())
        {
            it->second.push_back(callback);
        }
        else
        {
            m_on_press_callbacks[mapping] = std::vector<std::function<void()>>();
            m_on_press_callbacks[mapping].push_back(callback);
        }
        break;
    }
    case KEY_ACTION::REPEAT:
    {
        auto it = m_on_repeat_callbacks.find(mapping);

        if (it != m_on_repeat_callbacks.end())
        {
            it->second.push_back(callback);
        }
        else
        {
            m_on_repeat_callbacks[mapping] = std::vector<std::function<void()>>();
            m_on_repeat_callbacks[mapping].push_back(callback);
        }
        break;
    }
    case KEY_ACTION::RELEASE:
    {
        auto it = m_on_release_callbacks.find(mapping);

        if (it != m_on_release_callbacks.end())
        {
            it->second.push_back(callback);
        }
        else
        {
            m_on_release_callbacks[mapping] = std::vector<std::function<void()>>();
            m_on_release_callbacks[mapping].push_back(callback);
        }
        break;
    }
    }
}

void Input::registerMouseButtonCallBack(KEY_ACTION action, int button, std::function<void()> callback)
{
    switch (action)
    {
    case KEY_ACTION::PRESS:
        m_on_mouse_down_callbacks[button].push_back(callback);
        break;
    case KEY_ACTION::RELEASE:
        m_on_mouse_up_callbacks[button].push_back(callback);
        break;
    case KEY_ACTION::REPEAT:
        m_on_mouse_repeat_callbacks[button].push_back(callback);
        break;
    }
}

void Input::registerMouseMoveCallBack(std::function<void(float x, float y)> callback)
{
    m_on_mouse_move_callbacks.push_back(callback);
}

void Input::registerMouseEnterCallBack(std::function<void()> callback)
{
    m_on_mouse_enter_callbacks.push_back(callback);
}

void Input::registerMouseScrollCallback(std::function<void(double, double)> callback){
    m_on_mouse_scroll_callbacks.push_back(callback);
}
void Input::registerMouseLeaveCallBack(std::function<void()> callback)
{
    m_on_mouse_leave_callbacks.push_back(callback);
}

int Input::GetKeyState(int key)
{
    return m_keys[key];
}

void Input::handleInputs() {
    eventBus.handleEvents();
}

void Input::handleKey(int key_code, KEY_ACTION action)
{
    m_keys[key_code] = action;

    std::vector<std::string> mappings = m_mappings[key_code];
    if (mappings.empty())
    {
        return;
    }

    std::vector<std::function<void()>> callbacks;

    for (int i = 0; i < mappings.size(); i++)
    {
        switch (action)
        {
        case KEY_ACTION::PRESS:
            callbacks = m_on_press_callbacks[mappings[i]];
            for (int j = 0; j < callbacks.size(); j++)
            {
                callbacks[j]();
            }
            break;
        case KEY_ACTION::REPEAT:
            callbacks = m_on_repeat_callbacks[mappings[i]];
            for (int j = 0; j < callbacks.size(); j++)
            {
                callbacks[j]();
            }
            break;
        case KEY_ACTION::RELEASE:
            callbacks = m_on_release_callbacks[mappings[i]];
            for (int j = 0; j < callbacks.size(); j++)
            {
                callbacks[j]();
            }
            break;
        }
    }
}

void Input::handleMouseMove(float x, float y)
{
    m_mouse_state.x = x;
    m_mouse_state.y = y;

    for (int i = 0; i < m_on_mouse_move_callbacks.size(); i++)
    {
        m_on_mouse_move_callbacks[i](x, y);
    }
}

void Input::handleMouseEnter()
{
    for (int i = 0; i < m_on_mouse_enter_callbacks.size(); i++)
    {
        m_on_mouse_enter_callbacks[i]();
    }
}

void Input::handleMouseLeave()
{
    for (int i = 0; i < m_on_mouse_move_callbacks.size(); i++)
    {
        m_on_mouse_leave_callbacks[i]();
    }
}

void Input::handleMouseAction(int key_code, KEY_ACTION action)
{

    if(key_code == GLFW_MOUSE_BUTTON_1){
        m_mouse_state.mouse_button_1 = action;
    }
    if(key_code == GLFW_MOUSE_BUTTON_2){
        m_mouse_state.mouse_button_2 = action;
    }
    if(key_code == GLFW_MOUSE_BUTTON_3){
        m_mouse_state.mouse_button_3 = action;
    }

}

void Input::handleMouseScrollAction(double x_offset, double y_offset){
    Input::eventBus.publish(new MouseScrollEvent(glm::vec2(x_offset, y_offset)));
}

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    Input::handleKey(key, (KEY_ACTION)action);
    switch(action){
        case GLFW_PRESS:
            Input::eventBus.publish(new KeyPressEvent(key));
        case GLFW_RELEASE:
            Input::eventBus.publish(new KeyReleaseEvent(key));
        case GLFW_REPEAT:
            Input::eventBus.publish(new KeyRepeatEvent(key));
    }
}

void glfw_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Input::handleMouseMove(xpos, ypos);
}

void glfw_cursor_enter_callback(GLFWwindow *window, int entered)
{
    if (entered)
    {
        Input::handleMouseEnter();
    }
    else
    {
        Input::handleMouseLeave();
    }
}

void glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    Input::handleMouseAction(button, (KEY_ACTION)action);
}

void glfw_scroll_callback(GLFWwindow *window, double x_offset, double y_offset){
    Input::handleMouseScrollAction(x_offset, y_offset);
}

} // namespace yage