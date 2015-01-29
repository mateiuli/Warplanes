#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <functional>
#include <cassert>

#include <SFML/System/Time.hpp>

// forward declaration
class SceneNode;

namespace Category {
	enum Type {
		None						= 0,
		Scene						= 1 << 0,
		PlayerAircraft	= 1 << 1,
		AlliedAircraft	= 1 << 2,
		EnemyAircraft		= 1 << 3,
		EnemyProjectile = 1 << 4,
		AlliedProjectile = 1 << 5,
	};
}

struct Command {
	Command() : category(0) {};

	std::function<void(SceneNode&, sf::Time)>	action;
	unsigned int category;
};

/*
* In order to avoid multiple and annoying downcasting from
* Aircraft to SceneNode (actions are executed on SceneNodes)
* this function downcast it for us, yet it is more cleaner.
*/

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt) {	
		// check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif
