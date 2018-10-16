#include "Input.h"

namespace yage
{
Input::Input()
{
    for (int i = 32; i <= GLFW_KEY_LAST; i++)
    {
        m_keys[i] = KEY_ACTION::NONE;
    }
}

Input::~Input()
{
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

void Input::registerCallback(KEY_ACTION action, std::string mapping, std::function<void()> callback)
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

KEY_ACTION Input::getKeyStatus(std::string mapping)
{
    return m_keys[m_reverse_mappings[mapping]];
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

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    Input::getInstance().handleKey(key, (KEY_ACTION)action);
}

} // namespace yage