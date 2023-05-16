// jeux app.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include"jeux.h"


//coin structure
struct Coin {
    sf::Sprite sprite;
    bool isCollected;
};

int main()
{
//************************************premiére partie************************************
    //for window
    sf::RenderWindow window(sf::VideoMode(800, 500), "Super Mario");

    //for background
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/sky.png");
    backgroundTexture.setSmooth(true);
    sf::Sprite background(backgroundTexture);
    background.setPosition(0.f, 0.f);
    background.setScale(4.f, 4.f);
    perso.loadFromFile("images/map.png");
    Sprite map_sprite(perso);
    map_sprite.setScale(0.8f, 0.8f);
    map_sprite.setPosition(0.f, 20.f);
    //super mario music
    Music music;
    music.openFromFile("audio/supermario.ogg");
    music.setVolume(50);
    music.setLoop(true);
    music.play();


   // for game over
    bool mariodead = false;
    int i = 0;
    sf::SoundBuffer gameOver;
    sf::Sound dead;
    gameOver.loadFromFile("audio/mario_gameover.ogg");
    dead.setBuffer(gameOver);
    dead.setVolume(50.f);
    loadFont();

    // for winning
    bool winner = false;
    sf::SoundBuffer winning;
    sf::Sound win;
    winning.loadFromFile("audio/mario_start.ogg");
    win.setBuffer(winning);
    win.setVolume(50.f);
    perso2.loadFromFile("images/mario_peace.png");
    Sprite peace(perso2);
    peace.setScale(0.1f, 0.1f);
    peace.setPosition(350.f, 300.f);

    
   


    //for collecting coins
    std::srand(std::time(nullptr));
    int score = 0;
    sf::Texture coinTexture;
    coinTexture.loadFromFile("images/coin.gif");
    coinTexture.setSmooth(true);
    sf::Texture poseTexture;
    sf::SoundBuffer c;
    sf::Sound cn;
    c.loadFromFile("audio/coin.ogg");
    cn.setBuffer(c);
    cn.setVolume(50.f);


    //setting position of the coins
    std::vector<Coin> coins;
    srand(static_cast<unsigned int>(time(NULL)));
    const int numCoins = 10;
    for (int i = 0; i < numCoins; ++i)
    {
        sf::Sprite coinSprite(coinTexture);
        // set coin position randomly on the ground
        coinSprite.setScale(0.5, 0.5);
        coinSprite.setPosition(static_cast<float>(rand() % 200) + 320, 380.f);
        Coin coin = { coinSprite, false };
        coins.push_back(coin);
    }


    //for pose game
    bool gamepose = false;
    poseTexture.loadFromFile("images/pose.png");
    poseTexture.setSmooth(true);
    sf::Sprite posesprite(poseTexture);
    posesprite.setPosition(300.f, 200.f);
    posesprite.setScale(2.f, 2.f);

   

    float speed = 200.f;
   
    sf::Clock clock;
//***********************deuxième partie******************************************************
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
             if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    gamepose = true;
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    gamepose = false;
                }
             }
        }

        sf::Time deltaTime = clock.restart();

        
        if (!mariodead&&!gamepose) {
            p.update(deltaTime);
            mymap.update(deltaTime, speed, p);
            for (auto& coin : coins)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    coin.sprite.move(-200.f * deltaTime.asSeconds(), 0.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    coin.sprite.move(200.f * deltaTime.asSeconds(), 0.f);
                }
                // check for collision between player and coin
                if (!coin.isCollected && coin.sprite.getGlobalBounds().intersects(p.m_sprite.getGlobalBounds()))
                {
                    cn.play();
                    coin.isCollected = true;
                    score += 10;
                }
                if (coin.isCollected) {
                    coin.isCollected = false;
                    coin.sprite.setPosition(static_cast<float>(rand() % 200)+1400, 380.f);
                }
            }
            if (mymap.tiles[2][5]->sprite.getPosition().x +120 <= p.m_sprite.getPosition().x) { winner = true; 
            setText(txt, "winner", 300.f, 200.f);
            }
        }
       
        if(p.position().y > 580.f) {
           
            setText(txt, "Game over",245.f,200.f);
            mariodead = true;
        }
       
       
       setText( scoreText,"Score: " + std::to_string(score),250.f,100.f);
       //changer le son
       if (mariodead && i == 0)
       {
           sf::sleep(sf::seconds(0.5));
           music.stop();
           dead.play();
           i++;
       }
       if (winner && i == 0) {
           sf::sleep(sf::seconds(0.5));
           music.stop();
           win.play();
           i++;
       }
        window.clear();
        
        window.draw(background);
        window.draw(map_sprite);
       // window.draw(g.sprite);
        mymap.draw(window);

        for (auto const& coin : coins)
        {
            if (!coin.isCollected)
            {
                window.draw(coin.sprite);
            }
        }
        p.draw(window);
       
        if (mariodead ) {
            window.draw(background);
            window.draw(scoreText);
        }
        if (winner) {
            window.draw(background);
            window.draw(peace);
            window.draw(scoreText);
        }
        window.draw(txt);
        if (gamepose) {
            window.draw(posesprite);
        }
        window.display();
        
    }



    return 0;
}

//for writing
void loadFont()
{
    if (! font.loadFromFile("res/poppins.ttf"))
    {
        cout << "erreur chargement font" << endl; 
    }
}
void setText(Text& txt,String s,float x,float y ) {
    txt.setFont(font);
    txt.setString(s);
    txt.setPosition(x, y);
    txt.setCharacterSize(50);
    txt.setFillColor(Color::White);
}





// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
