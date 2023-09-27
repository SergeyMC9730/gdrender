#include "ColorChannel.h"
#include <deque>

#include "GameLayer.h"

std::shared_ptr<ColorChannel> ColorChannel::create(sf::Color color, int id)
{
	std::shared_ptr<ColorChannel> ptr(new ColorChannel);
	ptr->id = id;
	ptr->setColor(color);
	return ptr;
}

void ColorChannel::setColor(sf::Color color, bool pulse)
{
	this->color = color;
	if(!pulse)
		nonPulsedColor = color;
}

void ColorChannel::setR(uint8_t r, bool pulse)
{
	this->color.r = r;
	if (!pulse)
		nonPulsedColor = color;
}
void ColorChannel::setG(uint8_t g, bool pulse)
{
	this->color.g = g;
	if (!pulse)
		nonPulsedColor = color;
}
void ColorChannel::setB(uint8_t b, bool pulse)
{
	this->color.b = b;
	if (!pulse)
		nonPulsedColor = color;
}
void ColorChannel::setA(uint8_t a, bool pulse)
{
	this->color.a = a;
	if (!pulse)
		nonPulsedColor = color;
}

sf::Color ColorChannel::getColor()
{
	if(!copyColor)
		return color;
	else
	{
		return HSV::combine(copyColor->getColor(), hsvModifier);
	}
}
sf::Color ColorChannel::getNonPulseColor()
{
	return nonPulsedColor;
}

void ColorChannel::setDirtyRecusively()
{
	auto dirty = &GameLayer::instance->dirtyChannels;
	if (std::find(dirty->begin(), dirty->end(), id) == dirty->end())
		dirty->push_back(id);

	for (auto ptr : copiers)
		ptr->setDirtyRecusively();
}