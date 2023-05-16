#pragma once
#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "GameTile.h"
#include "Player.h"


class Map {
private:
    void SetUpTiles();

public:
    std::vector<std::vector<GameTile*>> tiles;
    Map();
    void update(sf::Time deltaTime, float speed, Player& player);
    void draw(RenderWindow& window);
    ~Map();


};
#endif