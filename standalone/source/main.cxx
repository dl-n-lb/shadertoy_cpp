// stl includes
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

// 3rd party includes
#include <cxxopts.hpp>

// gl includes
#define GLAD_GL_IMPLEMENTATION
#include <3rdparty/glad/gl.h>
#include <GLFW/glfw3.h>

// shadertoycpp includes

auto main(int argc, char** argv) -> int { 
  // Parse command line inputs

  cxxopts::Options options(*argv, "A program to visualise c++ fragment shaders");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("s,size", "size (pixels) of render viewport", cxxopts::value<std::string>()->default_value("800,600"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  auto dims = result["size"].as<std::string>();
  auto w = std::stoi(dims.substr(0, dims.find(',')));
  auto h = std::stoi(dims.substr(dims.find(',')+1, dims.size()-1));

  // Init GLFW, glad
  glfwInit();

  GLFWwindow* window = glfwCreateWindow(w, h, "Test Window", NULL, NULL);
  glfwMakeContextCurrent(window);
  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    fprintf(stderr, "Failed to initialise GL context\n");
    return 1;
  }

  // Create App, render
  for(;;) {

  }

  return 0;
}
