#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);	

Game::Game()
:	mWindow(sf::VideoMode(800, 600), "SFML Application", sf::Style::Close, sf::ContextSettings(32, 8, 4)), 
	mWorld(mWindow),
	mIsPaused(false)
{
	mWindow.setKeyRepeatEnabled(false);
}

/**
* Fixed Time Steps
*/
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while(mWindow.isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while(timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			
			if(!mIsPaused)
				update(TimePerFrame);
		}

		render();
	}
}

void Game::processEvents()
{
	CommandQueue& commands = mWorld.getCommandQueue();
	sf::Event event;

	while(mWindow.pollEvent(event)) {
		// Let the player handle some events
		mPlayer.handleEvent(event, commands);

		if(event.type == sf::Event::Closed)
				mWindow.close();
	}

	// Real Time Input
	mPlayer.handleRealTimeInput(commands);
}

void Game::update(sf::Time dt)
{
	mWorld.update(dt);
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();
	mWindow.display();
}
