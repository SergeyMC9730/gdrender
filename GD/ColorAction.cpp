#include "ColorAction.h"
#include "GameLayer.h"

std::shared_ptr<ColorAction> ColorAction::create(float duration, int colorChannel, sf::Color from, sf::Color to)
{
	std::shared_ptr<ColorAction> ptr(new ColorAction);

	if (ptr->init(duration, colorChannel, from, to))
		return ptr;

	return nullptr;
}

bool ColorAction::init(float duration, int colorChannel, sf::Color from, sf::Color to)
{
	ActionInterval::init(duration);

	this->colorChannel = colorChannel;
	this->from = from;
	this->to = to;

	deltar = static_cast<float>(to.r - from.r);
	deltag = static_cast<float>(to.g - from.g);
	deltab = static_cast<float>(to.b - from.b);
	deltaa = static_cast<float>(to.a - from.a);
	return true;
}

void ColorAction::update(float time)
{
	auto channel = GameLayer::instance->colorChannels[colorChannel];
	uint8_t r = static_cast<uint8_t>(to.r - deltar * (1 - time));
	uint8_t g = static_cast<uint8_t>(to.g - deltag * (1 - time));
	uint8_t b = static_cast<uint8_t>(to.b - deltab * (1 - time));
	uint8_t a = static_cast<uint8_t>(to.a - deltaa * (1 - time));
	channel->setColor({ r, g, b, a });
	
	channel->setDirtyRecusively();
}