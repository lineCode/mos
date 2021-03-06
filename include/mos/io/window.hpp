#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <string>

namespace mos {
namespace io {

class Window {
public:
  enum class CursorMode : int {
    NORMAL = GLFW_CURSOR_NORMAL,
    HIDDDEN = GLFW_CURSOR_HIDDEN,
    DISABLED = GLFW_CURSOR_DISABLED
  };

  enum class Cursor {
    HAND, ARROW, CROSSHAIR
  };

  Window(const std::string &title = "Window", const glm::ivec2 &resolution = {1920, 1080}, const int swap_interval = 0);
  ~Window();

  using ErrorFunc =
  std::function<void(const int error, const std::string &description)>;
  using PosFunc = std::function<void(const glm::vec2 &position)>;
  using SizeFunc = std::function<void(const glm::vec2 &size)>;
  using ClickFunc =
  std::function<void(const int button, const int action, const int mods)>;
  using MouseFunc = std::function<void(const glm::dvec2 &position)>;
  using ScrollFunc = std::function<void(const glm::dvec2 &offset)>;
  using KeyFunc = std::function<void(const int key, const int scancode,
                                     const int action, const int mods)>;

  static ErrorFunc error_func;
  static PosFunc pos_func;
  static SizeFunc size_func;
  static ClickFunc click_func;
  static MouseFunc mouse_func;
  static ScrollFunc scroll_func;
  static KeyFunc key_func;

  glm::ivec2 framebuffer_size() const;
  void poll_events();
  void swap_buffers();
  bool close() const;
  void close(const bool);
  void cursor_mode(const CursorMode &mode);
  void cursor(const Cursor &cursor);
  glm::dvec2 cursor_position() const;
  float dpi() const;

private:
  GLFWwindow *window_;
  GLFWcursor *hand_cursor_;
  GLFWcursor *arrow_cursor_;
  GLFWcursor *crosshair_cursor_;

  static void error_callback(int error, const char *description);
  static void position_callback(GLFWwindow *window, int x, int y);
  static void size_callback(GLFWwindow *window, int width, int height);
  static void click_callback(GLFWwindow *window, int button, int action,
                             int mods);
  static void mouse_callback(GLFWwindow *window, double x, double y);
  static void scroll_callback(GLFWwindow *window, double xoffset,
                              double yoffset);
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);

  bool pause_ = false;
  float pause_time_ = 0.0f;
  const float max_pause_ = 0.2f;
};
}
}

