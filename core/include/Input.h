#pragma once
#include <vector>
#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <Events/EventBus.h>
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

struct MouseState
{
  float x, y;
  KEY_ACTION mouse_button_1;
  KEY_ACTION mouse_button_2;
  KEY_ACTION mouse_button_3;
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
  void registerKeyCallBack(KEY_ACTION action, std::string mapping, std::function<void()>);

  void registerMouseButtonCallBack(KEY_ACTION action, int button, std::function<void()>);
  void registerMouseMoveCallBack(std::function<void(float, float)>);
  void registerMouseLeaveCallBack(std::function<void()>);
  void registerMouseEnterCallBack(std::function<void()>);
  void registerMouseScrollCallback(std::function<void(double, double)>);

  void handleInputs();
  KEY_ACTION getKeyStatus(std::string mapping);
  KEY_ACTION getKeyStatus(int key);

  MouseState getMouseState();

  static EventBus eventBus;
private:
  static void handleKey(int key_code, KEY_ACTION action);
  static void handleMouseMove(float x, float y);
  static void handleMouseAction(int key_code, KEY_ACTION action);
  static void handleMouseLeave();
  static void handleMouseEnter();
  static void handleMouseScrollAction(double x_offset, double y_offset);

  //Input data. m_keys stores keyboard keys and mouse buttons
  static std::unordered_map<int, KEY_ACTION> m_keys;
  static float m_mouse_x, m_mouse_y, m_mouse_delta_x, m_mouse_delta_y;

  //Key callbacks
  static std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_press_callbacks;
  static std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_release_callbacks;
  static std::unordered_map<std::string, std::vector<std::function<void()>>> m_on_repeat_callbacks;
  //Mouse callbacks
  //One vector for each mouse button indexed 0-2
  static std::vector<std::vector<std::function<void()>>> m_on_mouse_down_callbacks;
  static std::vector<std::vector<std::function<void()>>> m_on_mouse_up_callbacks;
  static std::vector<std::vector<std::function<void()>>> m_on_mouse_repeat_callbacks;
  static std::vector<std::function<void()>> m_on_mouse_enter_callbacks;
  static std::vector<std::function<void()>> m_on_mouse_leave_callbacks;
  static std::vector<std::function<void(float, float)>> m_on_mouse_move_callbacks;
  static std::vector<std::function<void(double, double)>> m_on_mouse_scroll_callbacks;

  //Key mappings
  static std::unordered_map<int, std::vector<std::string>> m_mappings;
  static std::unordered_map<std::string, unsigned int> m_reverse_mappings;

  friend void glfw_cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
  friend void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
  friend void glfw_cursor_enter_callback(GLFWwindow *window, int entered);
  friend void glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
  friend void glfw_scroll_callback(GLFWwindow *window, double x_offset, double y_offset);
};
void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void glfw_cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void glfw_cursor_enter_callback(GLFWwindow *window, int entered);
void glfw_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void glfw_scroll_callback(GLFWwindow *window, double x_offset, double y_offset);
} // namespace yage