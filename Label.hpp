#ifndef LABEL_HPP
#define LABEL_HPP

#include "Component.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include <SFML/Graphics/Text.hpp>

namespace GUI
{

class Label : public Component {
public:
	enum class Align {
		Left,
		Right,
		Center,
	};

public:
	using Ptr = std::shared_ptr<Label>;

public:
					Label(const std::string& text, const FontHolder& fonts);
	virtual bool	isSelectable() const;
	virtual void 	handleEvent(const sf::Event& event);

	void	setText(const std::string& text);
	void	alignText(const Align pos);

private:
	void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Text mText;
};

}

#endif
