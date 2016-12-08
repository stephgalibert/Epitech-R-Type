#pragma once

#include <functional>

enum class ApplicationState : short
{
	AS_MainMenu = 0,
	AS_Game = 1
};

namespace std
{
	template<>
	class less<ApplicationState>
	{
	public:
		bool operator()(ApplicationState lhs, ApplicationState  rhs) const
		{
			return (lhs < rhs);
		}
	};
}