#pragma once

#include "Platform.h"
#include <mutex>
#include <memory>

class Tree
{
public:
    static const std::string treeType();
    const std::string type() const { return this->treeType(); }
private:
    static std::unique_ptr<const std::string> sTreeTypeName;
};

std::unique_ptr<const std::string> Tree::sTreeTypeName;

inline const std::string
Tree::treeType()
{
    static std::once_flag once;
    std::call_once(once, []()
    {
    });
    return *sTreeTypeName;
}
