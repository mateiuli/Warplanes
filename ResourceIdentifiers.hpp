#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include "ResourceHolder.hpp"

namespace sf {
	class Texture;
	class Font;
}

/* Textures identifiers */
enum class TextureID {
	/* Default texture */
	NoTexture,

	/* Aircrafts */
	Eagle,
	Raptor,
	Avenger,
	Desert,

	/* Backgrounds */
	TitleScreen1,
	TitleScreen2,
	TitleScreen3,

	/* GUI */
	ButtonNormal,
	ButtonSelected,
	ButtonPressed,

	/* Projectiles */
	Bullet,
	Missile,
};

/* Fonts identifiers */
enum class FontID {
	Main,
	Armalite,
	Destroy,
};

using TextureHolder = ResourceHolder<sf::Texture, TextureID>;
using FontHolder		= ResourceHolder<sf::Font, FontID>;

#endif
