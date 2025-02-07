#pragma once

#include "ActionInterval.h"
#include "ColorChannel.h"

class CopyColorAction : public ActionInterval
{
private:

	int colorChannelID;
	sf::Color from;
	ColorChannel* targetChannel, *copyColor;
	HSV hsvModifier;
public:
	static std::shared_ptr<CopyColorAction> create(float duration, ColorChannel* target, ColorChannel* copy, HSV hsvModifier, int colorChannelID);
	bool init(float duration, ColorChannel* target, ColorChannel* copy, HSV hsvModifier, int colorChannelID);

	virtual void update(float time) override;
	virtual void step(float dt) override;
};