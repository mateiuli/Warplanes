#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class SpriteNode : public SceneNode {
public:
	explicit	SpriteNode(const sf::Texture&);
				SpriteNode(const sf::Texture&, const sf::IntRect&);

private:
	virtual void	drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
	sf::Sprite 		mSprite;
};

#endif
