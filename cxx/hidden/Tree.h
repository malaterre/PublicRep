#pragma once

#include <mutex>
#include <memory>

class Tree
{
public:
    static const std::string treeType() {
      static std::once_flag once;
      std::call_once(once, []() {
        sTreeTypeName.reset(new std::string());
		      });
      return *sTreeTypeName;
    }
private:
    static std::unique_ptr<const std::string> sTreeTypeName;
};

std::unique_ptr<const std::string> Tree::sTreeTypeName;
