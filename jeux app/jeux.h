#pragma once
#ifndef JEUX_H
#define JEUX_H
//importation
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include"GameTile.h"
#include"Map.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib> // for rand() and srand()
#include <ctime>
using namespace sf;
using namespace std;
// les variables utilisées
Font font;
Text txt,txt1, scoreText;
RenderWindow window;
void loadFont();
void setText(Text& txt, String s,float,float);

Texture perso;
Texture perso2;
Sprite sprite_perso;
//instaciation
Player p(800.f, 1000.f);
Map mymap = Map();

#endif // !JEUX_H
