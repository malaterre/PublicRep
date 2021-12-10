#pragma once

#include <mutex>
#include <memory>

class Tree
{
public:
    static const std::string treeType() {
      static std::once_flag once;
      std::call_once(once, []()
      {
      });
      return *sTreeTypeName;
    }
    const std::string type() const { return this->treeType(); }
private:
    static std::unique_ptr<const std::string> sTreeTypeName;
};

std::unique_ptr<const std::string> Tree::sTreeTypeName;
