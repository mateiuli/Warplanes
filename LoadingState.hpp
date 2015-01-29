#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "State.hpp"
#include "ParallelTask.hpp"

class StateStack;

class LoadingState : public State {
public:
					LoadingState(StateStack& stack, Context context);
	virtual void	draw();
	virtual bool	update(sf::Time dt);
	virtual bool	handleEvent(const sf::Event& event);

private:
	/* Change progress bar completion percent */
	void setCompletion(float percent);

private:
	sf::Text			mLoadingText;
	sf::RectangleShape	mProgressBarBackground;
	sf::RectangleShape	mProgressBar;
	ParallelTask		mLoadingTask;
};


#endif
