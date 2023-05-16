#include"Map.h"

Map::Map() {
    SetUpTiles();
}
//remplir notre tableau tiles
void Map::SetUpTiles() {
	tiles.clear();
    std::vector<GameTile*> firstRow;
    firstRow.push_back(new GameTile("images/le sol.png", 0.f, 450.f));
    firstRow.push_back(new GameTile("images/le sol.png", 285.f, 450.f));
    firstRow.push_back(new GameTile("images/le sol.png", 1370.f, 450.f));
    firstRow.push_back(new GameTile("images/le sol.png", 1755.f, 450.f));
    firstRow.push_back(new GameTile("images/le sol.png", 2400, 450.f));
    tiles.push_back(firstRow);
    std::vector<GameTile*> secondRow;
    secondRow.push_back(new GameTile("images/egg.png", 1420.f, 430.f));
    secondRow.push_back(new GameTile("images/egg.png", 1470.f, 430.f));
    secondRow.push_back(new GameTile("images/egg.png", 1800.f, 430.f));
    secondRow.push_back(new GameTile("images/egg.png", 1850.f, 430.f));
    tiles.push_back(secondRow);
    std::vector<GameTile*> forthRow;
    forthRow.push_back(new GameTile("images/lhjar.png", 730.f, 300.f));
    forthRow.push_back(new GameTile("images/lhjar.png", 1100.f, 220.f));
    forthRow.push_back(new GameTile("images/lhjar.png", 2130.f, 300.f));
    forthRow.push_back(new GameTile("images/le sol.png", 2680.f, 450.f));
    forthRow.push_back(new GameTile("images/le sol.png", 2870.f, 450.f));
    forthRow.push_back(new GameTile("images/fin.png", 2600.f, 250.f));
    tiles.push_back(forthRow);
}

void Map::update(sf::Time deltaTime, float speed, Player& player)
{
    bool onGround = false; 

    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            if (player.m_sprite.getGlobalBounds().intersects(tiles[i][j]->sprite.getGlobalBounds()) &&
                (player.position().x - 1 <= tiles[i][j]->sprite.getLocalBounds().width + tiles[i][j]->getPosition().x)) {

                onGround = true; // player is on ground

                player.m_onGround = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                tiles[i][j]->update(deltaTime.asSeconds(), -speed);
                if (!onGround) { 
                    player.groundLevel = 1000.f;
                    player.m_onGround = false; 
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                tiles[i][j]->update(deltaTime.asSeconds(), speed);
                if (!onGround) { // player is not on ground
                    player.groundLevel = 1000.f;
                    player.m_onGround = false; // update m_onGround flag
                }
            }
        }
    }

   
}



void Map::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            window.draw(tiles[i][j]->sprite);
        }
    }
}



Map::~Map()
{
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            delete tiles[i][j];
        }
    }
}
