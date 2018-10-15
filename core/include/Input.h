#pragma once
#include <vector>
#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include "config.h"
#include "Singleton.h"

namespace yage
{
enum KEY_ACTION
{
    PRESS = GLFW_PRESS,
    RELEASE = GLFW_RELEASE,
    REPEAT = GLFW_REPEAT,
    NONE = 0
};
/**
 * @brief Some of the input is handled in the Window class because GLFW :/
 * 
 */
class Input : public Singleton<Input>
{
  public:
    Input();
    ~Input();

    void mapKey(int key, std::string action);
    void registerCallback(KEY_ACTION action, std::string mapping, std::function<void()>);

    KEY_ACTION getKeyStatus(std::string mapping);
    KEY_ACTION getKeyStatus(int key);

    void handleKey(int key_code, KEY_ACTION action);

  private:
    std::unordered_map<int, KEY_ACTION> m_keys;
    std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_press_callbacks;
    std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_release_callbacks;
    std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_repeat_callbacks;

    std::unordered_map<int, std::vector<std::string>> m_mappings;
    std::unordered_map<std::string, unsigned int> m_reverse_mappings;

}; // namespace yage
void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
} // namespace yage