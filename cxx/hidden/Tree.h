#pragma once

#include <memory>
#include <mutex>

class Tree {
public:
  static const std::string treeType() {
    static std::once_flag once;
    std::call_once(once, []() {
      std::printf("%p\n", &sTreeTypeName);
      sTreeTypeName.reset(new std::string());
    });
    std::printf("%p\n", &sTreeTypeName);
    if (!sTreeTypeName)
      throw "uhoh";
    return *sTreeTypeName;
  }

private:
  static std::unique_ptr<const std::string> sTreeTypeName;
};

std::unique_ptr<const std::string> Tree::sTreeTypeName;
