#include "Label.hpp"

namespace GUI
{

Label::Label(const std::string& text, const FontHolder& fonts)
:	mText(text, fonts.get(FontID::Main), 16)
{
	mText.setColor(sf::Color::Red);
}

bool Label::isSelectable() const
{
	return false;
}

void Label::handleEvent(const sf::Event& event)
{
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	target.draw(mText, states);
}

void Label::setText(const std::string& text)
{
	mText.setString(text);
}

void Label::alignText(const Align pos)
{
	sf::FloatRect bounds = mText.getLocalBounds();
	// Center text by default
	sf::Vector2f origin(bounds.width / 2.f, mText.getOrigin().y);

	switch(pos) {
	case Label::Align::Left:
		origin.x = 0;
		break;

	case Label::Align::Right:
		origin.x = bounds.width;
		break;

	default:
		break;
	}

	mText.setOrigin(origin);
}

}
