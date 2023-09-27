#include "HSV.h"

#include <cmath>
#include <algorithm>

HSV HSV::fromRGB(sf::Color& color)
{
	float colR = (float)color.r / 255.f;
	float colG = (float)color.g / 255.f;
	float colB = (float)color.b / 255.f;

	// fmax

	float hsvM = std::max({colR, colG, colB});
	float hsvm = std::min({colR, colG, colB});
	float hsvC = hsvM - hsvm; // Chroma

	float hsvH = 0.f; // Hue
	float hsvS = 0.f; // Saturation
	float hsvV = 0.f; // Value

	if (hsvC != 0.f)
	{
		if (hsvM == colR)
			hsvH = std::fmod(((colG - colB) / hsvC), 6.f);
		else if (hsvM == colG)
			hsvH = ((colB - colR) / hsvC) + 2;
		else if (hsvM == colB)
			hsvH = ((colR - colG) / hsvC) + 4;

		hsvH *= 60;
	}

	if (hsvH < 0.f)
		hsvH += 360;

	hsvV = hsvM;

	if (hsvV != 0.f)
		hsvS = hsvC / hsvV;

	return { hsvH, hsvS, hsvV, false, false };
}

sf::Color HSV::toRGB()
{
	if (std::isnan(h)) {
		return { (uint8_t)(v * 255.0f), (uint8_t)(v * 255.0f), (uint8_t)(v * 255.0f) };
	}

	h = std::fmod((360.0f + std::fmod(h, 360)), 360.0f);
	s = std::clamp(s, 0.0f, 1.0f);
	v = std::clamp(v, 0.0f, 1.0f);

	h /= 60.0;
	float p = v * (1.0f - s);
	float q = v * (1.0f - (s * std::fmod(h, 1.0f)));
	float t = v * (1.0f - (s * (1.0f - std::fmod(h, 1.0f))));

	switch (static_cast<int>(std::floor(h)) % 6) {
	case 0:
		return { (uint8_t)(v * 255.0f), (uint8_t)(t * 255.0f), (uint8_t)(p * 255.0f) };
	case 1:
		return { (uint8_t)(q * 255.0f), (uint8_t)(v * 255.0f), (uint8_t)(p * 255.0f) };
	case 2:
		return { (uint8_t)(p * 255.0f), (uint8_t)(v * 255.0f), (uint8_t)(t * 255.0f) };
	case 3:
		return { (uint8_t)(p * 255.0f), (uint8_t)(q * 255.0f), (uint8_t)(v * 255.0f) };
	case 4:
		return { (uint8_t)(t * 255.0f), (uint8_t)(p * 255.0f), (uint8_t)(v * 255.0f) };
	case 5:
		return { (uint8_t)(v * 255.0f), (uint8_t)(p * 255.0f), (uint8_t)(q * 255.0f) };
	default:
		throw std::logic_error("Unreachable!");
	}
}

sf::Color HSV::combine(sf::Color color, HSV hsv)
{
	if (hsv.h == 0 && hsv.s == 0 && hsv.v == 0)
		return color;

	HSV colorHSV = fromRGB(color);
	hsv.h += colorHSV.h;
	if (hsv.sChecked)
		hsv.s += colorHSV.s;
	else
		hsv.s *= colorHSV.s;
	if (hsv.vChecked)
		hsv.v += colorHSV.v;
	else
		hsv.v *= colorHSV.v;

	return hsv.toRGB();
}