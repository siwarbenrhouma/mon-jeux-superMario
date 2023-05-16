#include "GameTile.h"
GameTile::GameTile(String textureName, float x, float y){
	if (!setUpSprite(textureName))
	{std::cout << "fichier non reconu" << endl;
		return;}
	pos = Vector2f(x, y);
	sprite.setPosition(pos);
	previousPosition = pos;
}


bool GameTile::setUpSprite(String textureName) {
	if (!texture.loadFromFile(textureName)) {
		return false;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	return true;
}

void GameTile::update(float t, float speed)
{
		sprite.move(-speed *t, 0.f);
}
sf::Vector2f GameTile::getPosition()
{
	return sprite.getPosition();
}


