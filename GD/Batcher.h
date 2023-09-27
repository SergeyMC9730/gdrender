#pragma once

#include "Sprite.h"

#include <iostream>

#include <map>

class Batcher : public sf::Drawable, public sf::Transformable
{
private:
    static std::map<std::string, std::shared_ptr<sf::Texture>> images;
    
    sf::Texture* texture;

    std::vector<Sprite*> sprites;

    sf::BlendMode blendMode;
public:
    std::vector<sf::Vertex> vertices;
protected:
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
public:
    void addSprite(Sprite* sp);

    void removeSprite(Sprite* sp);

    static std::shared_ptr<Batcher> create(std::string texture, sf::BlendMode blendMode = sf::BlendAlpha);

    bool init(std::string texture, sf::BlendMode blendMode);
};