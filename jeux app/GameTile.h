#pragma once
#ifndef GAMETILE_H
#define GAMETILE_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class GameTile
{
public:
	sf::Vector2f previousPosition;
	Vector2f pos;
	Texture texture;
	Sprite sprite;
	GameTile(String,float,float);
	bool setUpSprite(String);
	sf::Clock clock;
	void update(float t, float speed);
	sf::Vector2f getPosition();
};


#endif