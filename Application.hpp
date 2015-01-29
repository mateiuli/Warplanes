#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"
#include "StateStack.hpp"
#include "Player.hpp"

class Application {
public:
			Application();
	void 	run();

private:
	void	processInput();
	void	update(sf::Time dt);
	void 	render();
	
	void	registerStates();
	void	updateStatistics(sf::Time dt);

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow 	mWindow;
	TextureHolder		mTextures;
	FontHolder			mFonts;
	Player				mPlayer;
	StateStack			mStateStack;

	sf::Text	mStatisticsText;
	sf::Time 	mStatisticsUpdateTime;
	int 		mStatisticsNumFrames;
};

#endif
