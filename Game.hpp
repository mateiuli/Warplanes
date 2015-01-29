#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "CommandQueue.hpp"

class Game {
public:
	Game();
	void	run();

private:
	void	processEvents();
	void	update(sf::Time);
	void	render();
	void	handlePlayerInput(sf::Keyboard::Key, bool);

private:
	sf::RenderWindow		mWindow;
	World					mWorld;
	Player					mPlayer;
	bool					mIsPaused;
	static const sf::Time	TimePerFrame;
};

#endif
