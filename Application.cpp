#include "Application.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "SettingsState.hpp"
#include "PauseState.hpp"
#include "LoadingState.hpp"
#include "FadeInState.hpp"
#include "FadeOutState.hpp"
#include "Utility.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);	

Application::Application()
:	mWindow(sf::VideoMode(1024, 768), "SFML Application", sf::Style::Close, sf::ContextSettings(32, 8, 4)),
	mTextures(),
	mFonts(),
	mPlayer(),
	mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer)),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	/* Load fonts and textures */
	mFonts.load(FontID::Main,			"Media/Fonts/Sansation.ttf");
	mFonts.load(FontID::Armalite, "Media/Fonts/armalite.ttf");
	mFonts.load(FontID::Destroy,	"Media/Fonts/destroy.ttf");

	/* Title screens */
	mTextures.load(TextureID::TitleScreen1,		"Media/Textures/Titlescreen/aircraft_1.png");
	mTextures.load(TextureID::TitleScreen2,		"Media/Textures/Titlescreen/aircraft_2.png");
	mTextures.load(TextureID::TitleScreen3,		"Media/Textures/Titlescreen/aircraft_3.png");

	/* GUI Buttons */
	mTextures.load(TextureID::ButtonNormal,		"Media/Textures/GUI/ButtonNormal.png");
	mTextures.load(TextureID::ButtonSelected, "Media/Textures/GUI/ButtonSelected.png");
	mTextures.load(TextureID::ButtonPressed,	"Media/Textures/GUI/ButtonPressed.png");

	/* FPS Counter */
	mStatisticsText.setFont(mFonts.get(FontID::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(13);

	/* Register all the states and start with the title screen */
	this->registerStates();
	mStateStack.pushState(StateID::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timSinceLastUpdate = sf::Time::Zero;

	// Fixed time steps
	while(mWindow.isOpen()) {
		sf::Time dt = clock.restart();
		timSinceLastUpdate += dt;
		
		while(timSinceLastUpdate > TimePerFrame) {
			timSinceLastUpdate -= TimePerFrame;

			this->processInput();
			this->update(TimePerFrame);

			// stack might be empty before update()
			if(mStateStack.isEmpty())
				mWindow.close();
		}

		this->updateStatistics(dt);
		this->render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while(mWindow.pollEvent(event)) {
		mStateStack.handleEvent(event);

		if(event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt) 
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;

	if(mStatisticsUpdateTime >= sf::seconds(1.0f)) {
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(StateID::Title);
	mStateStack.registerState<MenuState>(StateID::Menu);
	mStateStack.registerState<SettingsState>(StateID::Settings);
	mStateStack.registerState<GameState>(StateID::Game);
	mStateStack.registerState<PauseState>(StateID::Pause);
	mStateStack.registerState<LoadingState>(StateID::Loading);

	// Transitions
	mStateStack.registerState<FadeInState>(StateID::TransitionFadeIn);
	mStateStack.registerState<FadeOutState>(StateID::TransitionFadeOut);
}
