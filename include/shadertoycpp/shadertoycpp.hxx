#pragma once

#include <cstdlib>
#include <cstdio>
#include <memory>

#define GLAD_GL_IMPLEMENTATION
#include <3rdparty/glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <3rdparty/backends/imgui_impl_glfw.h>
#include <3rdparty/backends/imgui_impl_opengl3.h>

struct shadertoy_uniforms_t {};

struct shader_program_t {};

struct program_base_t {};

class app_t {
public:
  app_t(int w, int h);

  void run();

private:
  GLFWwindow* _window = nullptr;
  GLuint _vao = 0;
  GLuint _array_buffer = 0;
  GLuint _uniform_buffer = 0;

  shader_program_t _active_shader = {};

  shadertoy_uniforms_t _uniforms;
  
  std::unique_ptr<program_base_t> _program;

  float _spd = 1;
  double _t_elapsed = 0;
  bool _debug_on_click = false;
  bool _async = true;
  
  void framebuffer_callback(int width, int height);
  static void _framebuffer_callback(GLFWwindow* win, int width, int height);
  void button_callback(int button, int action, int mods);
  static void _button_callback(GLFWwindow* win, int button, int action, int mods);

  static void _debug_callback(GLenum src, GLenum type, GLuint id, 
                              GLenum severity, GLsizei length,
                              const GLchar* message, const void* user_param);
};

void app_t::framebuffer_callback(int width, int height) {
  glViewport(0, 0, width, height);
}

void app_t::_framebuffer_callback(GLFWwindow* win, int width, int height) {
  app_t* app = static_cast<app_t*>(glfwGetWindowUserPointer(win));
  app->framebuffer_callback(width, height);
}

void app_t::_debug_callback(GLenum src, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar* message, const void* user_param) {
  if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) {
    fprintf(stderr, "OpenGL: %s", message);
  }

  if (severity == GL_DEBUG_SEVERITY_HIGH) exit(EXIT_FAILURE); // error 
}

app_t::app_t(int w, int h) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

  _window = glfwCreateWindow(w, h, "Shadertoy App", NULL, NULL);

  
  glfwSetWindowUserPointer(_window, this);
  glfwSetFramebufferSizeCallback(_window, _framebuffer_callback);
  //glfwSetMouseButtonCallback(_window, _button_callback);
  glfwMakeContextCurrent(_window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    fprintf(stderr, "Failed to initialise GL context\n");
    exit(EXIT_FAILURE);
  }

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(_debug_callback, this);

  glfwSwapInterval(1);
  
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(_window, true);
  ImGui_ImplOpenGL3_Init("#version 460");
}

void app_t::run() {
  while(!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    glViewport(0, 0, width, height);
    //glfwSwapBuffers(_window);
  }
}
