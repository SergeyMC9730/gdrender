#include "GameLayerPreload.h"

GameLayerPreload::GameLayerPreload() {
    auto res = font.loadFromFile("arial.ttf");
    (void)res;
}