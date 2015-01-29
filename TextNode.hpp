#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP

#include "SceneNode.hpp"
#include "ResourceIdentifiers.hpp"

#include <string>

class TextNode : public SceneNode {
public:
	explicit	TextNode(const FontHolder& fonts, const std::string& text);
	void		setString(const std::string& text);

private:
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
	sf::Text mText;
};

#endif
