#include <Events/InputEvent.h>
#include "Input.h"

namespace yage
{
std::unordered_map<int, KEY_ACTION> Input::mKeys = std::unordered_map<int, KEY_ACTION>();
MouseState Input::mMouseState = MouseState();
std::unordered_map<std::string, std::vector<std::function<void()>>> Input::mOnPressCallbacks = std::unordered_map<std::string, std::vector<std::function<void()>>>();
std::unordered_map<std::string, std::vector<std::function<void()>>> Input::mOnReleaseCallbacks = std::unordered_map<std::string, std::vector<std::function<void()>>>();
std::unordered_map<std::string, std::vector<std::function<void()>>> Input::mOnRepeatCallbacks = std::unordered_map<std::string, std::vector<std::function<void()>>>();

std::vector<std::vector<std::function<void()>>> Input::mOnMouseDownCallbacks = std::vector<std::vector<std::function<void()>>>();
std::vector<std::vector<std::function<void()>>> Input::mOnMouseUpCallbacks = std::vector<std::vector<std::function<void()>>>();
std::vector<std::vector<std::function<void()>>> Input::mOnMouseRepeatCallbacks = std::vector<std::vector<std::function<void()>>>();

std::vector<std::function<void()>> Input::mOnMouseLeaveCallbacks = std::vector<std::function<void()>>();
std::vector<std::function<void()>> Input::mOnMouseEnterCallbacks = std::vector<std::function<void()>>();
std::vector<std::function<void(float, float)>> Input::mOnMouseMoveCallbacks = std::vector<std::function<void(float, float)>>();
std::vector<std::function<void(double, double)>> Input::mOnMouseScrollCallbacks = std::vector<std::function<void(double, double)>>();


std::unordered_map<int, std::vector<std::string>> Input::mMappings = std::unordered_map<int, std::vector<std::string>>();
std::unordered_map<std::string, unsigned int> Input::mReverseMappings = std::unordered_map<std::string, unsigned int>();

EventBus Input::eventBus = EventBus();

void Input::Init() {
    for (int i = GLFW_MOUSE_BUTTON_1; i < GLFW_MOUSE_BUTTON_8; i++)
    {
        mKeys[i] = KEY_ACTION::NONE;
    }
    for (int i = 32; i <= GLFW_KEY_LAST; i++)
    {
        mKeys[i] = KEY_ACTION::NONE;
    }

    //GLFW_MOUSE_BUTTON_1
    mOnMouseDownCallbacks.push_back(std::vector<std::function<void()>>());
    mOnMouseUpCallbacks.push_back(std::vector<std::function<void()>>());
    mOnMouseRepeatCallbacks.push_back(std::vector<std::function<void()>>());
    //GLFW_MOUSE_BUTTON_2
    mOnMouseDownCallbacks.push_back(std::vector<std::function<void()>>());
    mOnMouseUpCallbacks.push_back(std::vector<std::function<void()>>());
    mOnMouseRepeatCallbacks.push_back(std::vector<std::function<void()>>());
    //GLFW_MOUSE_BUTTON_3
    mOnMouseDownCallbacks.push_back(std::vector<std::function<void()>>());
    mOnMouseUpCallbacks.push_back(std::vector<std::function<void()>>());
    mOnMouseRepeatCallbacks.push_back(std::vector<std::function<void()>>());
}

void Input::mapKey(int key, std::string action)
{
    //If a mapping already exists just insert a new one,
    //else create a new vector first
    auto it = mMappings.find(key);
    if (it != mMappings.end())
    {
        it->second.push_back(action);
    }
    else
    {
        mMappings[key] = std::vector<std::string>();
        mMappings[key].push_back(action);
    }
    mReverseMappings[action] = key;
}

MouseState Input::GetMouseState(){
   return mMouseState;
}

void Input::registerKeyCallBack(KEY_ACTION action, std::string mapping, std::function<void()> callback)
{
    switch (action)
    {
    case KEY_ACTION::PRESS:
    {
        auto it = mOnPressCallbacks.find(mapping);

        if (it != mOnPressCallbacks.end())
        {
            it->second.push_back(callback);
        }
        else
        {
            mOnPressCallbacks[mapping] = std::vector<std::function<void()>>();
            mOnPressCallbacks[mapping].push_back(callback);
        }
        break;
    }
    case KEY_ACTION::REPEAT:
    {
        auto it = mOnRepeatCallbacks.find(mapping);

        if (it != mOnRepeatCallbacks.end())
        {
            it->second.push_back(callback);
        }
        else
        {
            mOnRepeatCallbacks[mapping] = std::vector<std::function<void()>>();
            mOnRepeatCallbacks[mapping].push_back(callback);
        }
        break;
    }
    case KEY_ACTION::RELEASE:
    {
        auto it = mOnReleaseCallbacks.find(mapping);

        if (it != mOnReleaseCallbacks.end())
        {
            it->second.push_back(callback);
        }
        else
        {
            mOnReleaseCallbacks[mapping] = std::vector<std::function<void()>>();
            mOnReleaseCallbacks[mapping].push_back(callback);
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
        mOnMouseDownCallbacks[button].push_back(callback);
        break;
    case KEY_ACTION::RELEASE:
        mOnMouseUpCallbacks[button].push_back(callback);
        break;
    case KEY_ACTION::REPEAT:
        mOnMouseRepeatCallbacks[button].push_back(callback);
        break;
    }
}

void Input::registerMouseMoveCallBack(std::function<void(float x, float y)> callback)
{
    mOnMouseMoveCallbacks.push_back(callback);
}

void Input::registerMouseEnterCallBack(std::function<void()> callback)
{
    mOnMouseEnterCallbacks.push_back(callback);
}

void Input::registerMouseScrollCallback(std::function<void(double, double)> callback){
    mOnMouseScrollCallbacks.push_back(callback);
}
void Input::registerMouseLeaveCallBack(std::function<void()> callback)
{
    mOnMouseLeaveCallbacks.push_back(callback);
}

int Input::GetKeyState(int key)
{
    return mKeys[key];
}

void Input::handleInputs() {
    eventBus.handleEvents();
}

void Input::handleKey(int key_code, KEY_ACTION action)
{
    mKeys[key_code] = action;

    std::vector<std::string> mappings = mMappings[key_code];
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
            callbacks = mOnPressCallbacks[mappings[i]];
            for (int j = 0; j < callbacks.size(); j++)
            {
                callbacks[j]();
            }
            break;
        case KEY_ACTION::REPEAT:
            callbacks = mOnRepeatCallbacks[mappings[i]];
            for (int j = 0; j < callbacks.size(); j++)
            {
                callbacks[j]();
            }
            break;
        case KEY_ACTION::RELEASE:
            callbacks = mOnReleaseCallbacks[mappings[i]];
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
    mMouseState.x = x;
    mMouseState.y = y;

    for (int i = 0; i < mOnMouseMoveCallbacks.size(); i++)
    {
        mOnMouseMoveCallbacks[i](x, y);
    }
}

void Input::handleMouseEnter()
{
    for (int i = 0; i < mOnMouseEnterCallbacks.size(); i++)
    {
        mOnMouseEnterCallbacks[i]();
    }
}

void Input::handleMouseLeave()
{
    for (int i = 0; i < mOnMouseMoveCallbacks.size(); i++)
    {
        mOnMouseLeaveCallbacks[i]();
    }
}

void Input::handleMouseAction(int key_code, KEY_ACTION action)
{

    if(key_code == GLFW_MOUSE_BUTTON_1){
        mMouseState.mouse_button_1 = action;
    }
    if(key_code == GLFW_MOUSE_BUTTON_2){
        mMouseState.mouse_button_2 = action;
    }
    if(key_code == GLFW_MOUSE_BUTTON_3){
        mMouseState.mouse_button_3 = action;
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