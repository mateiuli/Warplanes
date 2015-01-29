#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Aircraft.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"

namespace sf {
	class Time;
}

class Player {
public:
	enum class Action : int {
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		Count,
	};

public:
	Player();

	/* These methods ar invoked from the Game class - processInput() */
	void	handleEvent(const sf::Event& event, CommandQueue& commands);
	void 	handleRealTimeInput(CommandQueue& commands);

	/* Customizing key-layout */
	void				assignKey(Action action, sf::Keyboard::Key);
	sf::Keyboard::Key 	getAssignedKey(Action action) const;

private:
	void		initializeActions();
	static bool isRealTimeAction(Action action);

private:
	/* Bind keys to actions */
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	/* Bind actions to commands */
	std::map<Action, Command>			mActionBinding;
};

#endif
