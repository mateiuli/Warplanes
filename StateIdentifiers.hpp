#ifndef STATE_IDENTIFIERS_HPP
#define STATE_IDENTIFIERS_HPP

/* Unique Identifiers for each state */
enum class StateID {
	Title,
	Menu,
	Settings,
	Loading,
	Game,
	Pause,

	/* Transition States */
	TransitionFadeIn,
	TransitionFadeOut,
};


#endif
