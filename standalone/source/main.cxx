#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "A program to visualise c++ fragment shaders");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("w,width", "width of render viewport", cxxopts::value(width)->default_value(800))
    ("h,height", "height of render viewport", cxxopts::value(height)->default_value(600))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  return 0;
}
