#include "Button.hpp"

namespace GUI
{

Button::Button(const FontHolder &fonts, const TextureHolder &textures)
:	mCallback(),
	mNormalTexture(textures.get(TextureID::ButtonNormal)),
	mSelectedTexture(textures.get(TextureID::ButtonSelected)),
	mPressedTexture(textures.get(TextureID::ButtonPressed)),
	mSprite(),
	mText("", fonts.get(FontID::Main), 16),
	mIsToggle(false)
{
	mSprite.setTexture(mNormalTexture);

	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(15.f, bounds.height / 2.f - 10.f);
}

void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	mText.setString(text);
	//centerOrigin(mText);
}

void Button::setToggle(bool flag)
{
	mIsToggle = flag;
}

bool Button::isSelectable() const
{
	return true;
}

void Button::select()
{
	Component::select();
	mSprite.setTexture(mSelectedTexture);
	mText.setColor(sf::Color::Yellow);
	mText.setPosition(37.f, mText.getPosition().y);
}

void Button::deselect()
{
	Component::deselect();
	mSprite.setTexture(mNormalTexture);
	mText.setColor(sf::Color::White);
	mText.setPosition(15.f, mText.getPosition().y);
}

void Button::activate()
{
	Component::activate();

	// if we are toggle then we should show that the button is toggled
	if(mIsToggle)
		mSprite.setTexture(mPressedTexture);

	// Do some action
	if(mCallback)
		mCallback();

	// untoggle
	if(!mIsToggle)
		this->deactivate();
}

void Button::deactivate()
{
	Component::deactivate();

	if(mIsToggle) {
		// reset to the right texture depeding on if the button is selected
		mSprite.setTexture(this->isSelected() ? mSelectedTexture : mNormalTexture);
	}
}

void Button::handleEvent(const sf::Event& event)
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

}
