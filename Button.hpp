#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{

class Button : public Component {
public:
	using Ptr = std::shared_ptr<Button>;
	using Callback = std::function<void()>;

public:
			Button(const FontHolder& fonts, const TextureHolder& textures);
	void	setCallback(Callback callback);
	void	setText(const std::string& text);
	void	setToggle(bool flag);

	virtual bool	isSelectable() const;
	virtual void	select();
	virtual void	deselect();
	virtual void	activate();
	virtual void	deactivate();
	virtual void	handleEvent(const sf::Event& event);

private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	/* Action to do when pressed */
	Callback			mCallback;

	/* Different types of textures */
	const sf::Texture&	mNormalTexture;
	const sf::Texture&	mSelectedTexture;
	const sf::Texture&	mPressedTexture;

	/* The button */
	sf::Sprite	mSprite;
	sf::Text	mText;
	bool		mIsToggle;
};

}
#endif
