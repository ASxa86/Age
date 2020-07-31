#include <azule/graphics/ProgressBarComponent.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <azule/graphics/Utilities.h>

using namespace azule;

void ProgressBarComponent::ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->fill, states);
	target.draw(this->outline, states);
}

double ProgressBarComponent::getPercentage() const
{
	return static_cast<double>(this->Value) / static_cast<double>(this->ValueMax);
}

const sf::Drawable* ProgressBarComponent::getDrawable()
{
	this->progressBar.fill.setSize(FromVector(this->Size));
	this->progressBar.fill.setFillColor(FromColor(this->Color));
	this->progressBar.fill.setPosition(FromVector(this->Position));

	this->progressBar.outline.setPosition(FromVector(this->Position));
	this->progressBar.outline.setSize(FromVector(this->Size));
	this->progressBar.outline.setFillColor(sf::Color::Transparent);
	this->progressBar.outline.setOutlineColor(sf::Color::Black);
	this->progressBar.outline.setOutlineThickness(1.0f);

	auto size = this->progressBar.fill.getSize();
	size.x *= static_cast<float>(this->getPercentage());
	this->progressBar.fill.setSize(size);

	return &this->progressBar;
}
