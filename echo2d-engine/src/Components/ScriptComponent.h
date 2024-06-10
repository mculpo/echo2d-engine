#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "../Core/Core.h"

struct ScriptComponent {
	sol::function func;
	ScriptComponent(sol::function pFunction = sol::lua_nil) {
		this->func = pFunction;
	}
};

#endif // !SCRIPTCOMPONENT_H
