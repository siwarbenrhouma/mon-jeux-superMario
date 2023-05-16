#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <fstream>
class Player {
private:
    //la declaration des variables privées
        sf::Texture texture;
        // nos variable pour le son du saut
        sf::SoundBuffer m_jumpBuffer;
        sf::Sound m_jumpSound;

public:
    //la declaration des variables publics
        float m_jumpSpeed;//vitesse du saut
        float groundLevel;
        bool m_facingLeft;// pour detecter la direction du sprite pour le modifier
        sf::Sprite m_sprite;//le sprite du mario
        bool m_onGround;// pour detecter s'il est sur le sol
        float m_gravity;//la gravité
    Player(float jumpSpeed, float gravity) :
        m_jumpSpeed(0),
        m_gravity(gravity),
        m_onGround(true), // set m_onGround to true
        m_facingLeft(false),
        m_jumpBuffer(),
        m_jumpSound()
    {
        //telechargement du notre sprite du début
        texture.loadFromFile("images/super_mario1.png");
        m_sprite.setTexture(texture);
        m_sprite.setScale(0.02f, 0.02f);
        m_sprite.setPosition(400.f, 380.f);//changer sa position
        groundLevel = 580.f;
        //telechargementdu son du saut
        m_jumpBuffer.loadFromFile("audio/mario-jump.ogg");
        m_jumpSound.setBuffer(m_jumpBuffer);
        m_jumpSound.setVolume(50.f);
    }

    void update(sf::Time deltaTime) {
       
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (m_onGround) {
                    texture.loadFromFile("images/mario-marcheLeft.png");
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.025f);
                }
                else {
                    texture.loadFromFile("images/super_mario2Left.png");
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.02f);
                 
                   
                }

               
                m_facingLeft = true;
                
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (m_onGround) {
                    texture.loadFromFile("images/mario-marche.png");
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.025f);
                }
                else {
                    texture.loadFromFile("images/super_mario2.png");
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.02f);
                  
                }

                
                m_facingLeft = false;
            }
            else {
                if (m_onGround) {
                    if (m_facingLeft) {
                        texture.loadFromFile("images/super_mario1Left.png");
                    }
                    else {
                        texture.loadFromFile("images/super_mario1.png");
                    }
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.02f);
                }
            }

            // sauter
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_onGround) {
                m_onGround = false;
                m_jumpSound.play();// commancer à jouer le son
                groundLevel += 200;
                if (m_facingLeft) {
                    texture.loadFromFile("images/super_mario2Left.png");
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.02f);
                }
                else {
                    texture.loadFromFile("images/super_mario2.png");
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.02f);
                }

                m_jumpSpeed = std::sqrt(2.f * m_gravity * (580.f - m_sprite.getPosition().y));
            }
            if (!m_onGround) {
                m_sprite.move(0.f, -m_jumpSpeed * deltaTime.asSeconds());
                m_jumpSpeed -= m_gravity * deltaTime.asSeconds();
                 if (m_sprite.getPosition().y >= groundLevel - 200) {
                    groundLevel -= 200;
                    m_onGround = true;
                    if (m_facingLeft) {
                        texture.loadFromFile("images/super_mario1Left.png");
                    }
                    else {
                        texture.loadFromFile("images/super_mario1.png");
                    }
                    m_sprite.setTexture(texture);
                    m_sprite.setScale(0.02f, 0.02f);
                 }
            }
            

        
    }
 

    void draw(sf::RenderWindow& window) {
        window.draw(m_sprite);
    }

  
    sf::Vector2f position() {
        return m_sprite.getPosition();
    }
};

#endif
