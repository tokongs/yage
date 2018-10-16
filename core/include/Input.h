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
 * 
 * @brief This is where input is handled. A callback is registered with glfw
 * for getting key_events from the os. All key_actions are stored in an
 * unordered map. It is possible to resigster a mapping from a keycode to 
 * a string to make it easier to change keymapping later on. You can also
 * register callbacks to certain events e.g. a key being pressed.
 * 
 * This class needs some work
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
  //Input data
  std::unordered_map<int, KEY_ACTION> m_keys;
  float m_mouse_x, m_mouse_y;

  //Key callbacks
  std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_press_callbacks;
  std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_release_callbacks;
  std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_repeat_callbacks;
  //Mouse callbacks
  std::vector<std::vector<std::function<void(float x, float y)>>> m_on_mouse_down_callback;
  std::vector<std::vector<std::function<void(float x, float y)>>> m_on_mouse_up_callback;
  std::vector<std::vector<std::function<void(float x, float y)>>> m_on_mouse_repeat_callback;
  std::vector<std::vector<std::function<void(float x, float y)>>> m_on_mouse_enter_callback;
  std::vector<std::vector<std::function<void(float x, float y)>>> m_on_mouse_leave_callback;
  std::vector<std::vector<std::function<void(float x, float y)>>> m_on_mouse_move_callback;

  
  //Key mappings
  std::unordered_map<int, std::vector<std::string>> m_mappings;
  std::unordered_map<std::string, unsigned int> m_reverse_mappings;

}; // namespace yage
void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void glfw_cursor_enter_callback(GLFWwindow* window, int entered);
void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
} // namespace yage