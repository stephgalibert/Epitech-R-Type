#pragma once

#include <functional>

enum class ApplicationState : short
{
	AS_MainMenu = 0,
	AS_Game = 1
};

struct ApplicationStateHash
{
  template <typename T>
  std::size_t operator()(T t) const
  {
    return static_cast<std::size_t>(t);
  }
};
