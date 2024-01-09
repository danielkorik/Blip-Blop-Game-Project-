#include"Game.h"
#include <algorithm>
#include<string>
float findYOnEdge(const sf::ConvexShape& shape, float x);
//==================================
// ~constructor
Game::Game()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Blip And Blop Game")
{
    //random algorithm
    std::srand(static_cast<unsigned>(std::time(nullptr)));


}
//==================================
//function that checks the button that have been pressed on the menu 
void Game::checkBottunPressed(const sf::Vector2f mousePosF)
{
    for (int i = 0; i < m_menu.getMenuOptions().size(); i++)
    {
        if (m_menu.getMenuOptions()[i].getGlobalBounds().contains(mousePosF)) {
            if (i == _STARTGAME)
                m_startGame = true;
            else if (i == _HELP) {
                m_menu.openHelpOption();
            }
            else if( i == _EXIT)
                exit(EXIT_SUCCESS);
        }
    }
}
//==================================
//run function that runs the game 
void Game::run()
{
    m_menu.setMenu();   //set menu
    m_menu.drawMenu();  //draw menu
    m_window.display(); //diplay them
    MenuMusic.play();

    while (m_window.isOpen())   //open window
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            if (sf::Event::MouseMoved) //if there is a movement in the mouse from the user gets the coordinates
                ///and checks if the user is on an option
            {
                auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                m_menu.ifMouseOn(location);
            }//check which character selected blip or blop
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                    sf::Vector2f mousePosF = m_window.mapPixelToCoords(mousePos);
                    if (m_menu.isMenuRunning()) {
                        checkBottunPressed(mousePosF);

                        if (m_startGame && m_menu.isMenuRunning()) {
                            m_menu.CharachterSelect(CHARACTER_SELECTED);//it returns for me the enum name of which character selected
                            m_menu.changeMenuRunning();
                            m_window.clear();
                        }
                        if (m_startGame && !m_menu.isMenuRunning()) {
                            MenuMusic.stop();
                            play(); //play function(all the game is in here :) )
                        }
                    }
                }
            }//draw the menu
            if (m_menu.isMenuRunning())
                m_menu.drawMenu();

            m_window.display();
        }
    }

}
//=========================================
//function that sets all the game needs to start playing 
void Game::play()
{
    m_window.clear();
    
    GameMusic.play();
    //if blip or blop character that the user choose
     if(CHARACTER_SELECTED)
            m_p1 = new BlipAndBlop(Resources::BLOP, Resources::STANDARDBULLET);
        else
            m_p1 = new BlipAndBlop(Resources::BLIP, Resources::STANDARDBULLET);


    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("map.png")) {
        // Failed to load the map texture
        exit(EXIT_FAILURE);
    }
    //creating the enemies
    createEnemies();
    //setting the map texture and scale
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(MAPSCALE, MAPSCALE);
    
    // Create view to match the window size
    sf::View view(m_window.getDefaultView());

    //creating the platforms
    m_board.createPlatforms();
    // Set the map sprite's position 
    mapSprite.setPosition(view.getCenter() - sf::Vector2f(view.getSize().x / 2.0f, (view.getSize().y / 2.0f)));

    //setting the shotgun sprites to draw them
    m_shotgunWeap.setSpritesOfGun();

    //setting the riffle sprites to draw them
    m_RifleGunWeap.setSpritesOfGun();

   while (m_window.isOpen() && !m_menu.isMenuRunning())
   {
       sf::Event event;
       if (m_p1->GetLives() > 0 && !m_WinGame) {
           while (m_window.pollEvent(event))
           {
               if (event.type == sf::Event::Closed)
                   m_window.close();
               if (event.type == sf::Event::KeyPressed)
               {
                   if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                       
                       if (m_BulletsTimer <= sf::seconds(0)) {
                           BulletsFiring();
                           if (m_ShotGun)
                               m_BulletsTimer = sf::seconds(0.6);
                           else if (m_rifle)
                               m_BulletsTimer = sf::seconds(0.1);
                           else
                               m_BulletsTimer = sf::seconds(0.3);
                       }
                   
                   }
               }//controlling the pressing that the character can look upleft and upright and downleft and downright 
               if (event.type == sf::Event::KeyReleased) {
                   if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                   {
                       if (m_p1->getDir() == Direction::UpLeft || m_p1->getDir() == Direction::DownLeft ||
                           m_p1->getDir() == Direction::UpHeadLeft || m_p1->getDir() == Direction::DownHeadLeft)
                       {
                           m_p1->setAnimationByDirection(Direction::Left);
                       }
                       else if (m_p1->getDir() == Direction::UpRight || m_p1->getDir() == Direction::DownRight ||
                           m_p1->getDir() == Direction::UpHeadRight || m_p1->getDir() == Direction::DownHeadRight) {
                           m_p1->setAnimationByDirection(Direction::Right);
                       }
                   }
               }
           }
           update();    //update all the needed updates
           draw();  //drawing all the needed things on the view
           m_window.display();  
           platformsToCheckCollision.clear();   //clearing the platform vector of the past view bounds
       }
       else if (m_p1->GetLives() > 0 && m_WinGame)
       {
           m_deltaTime += clock.restart();

            m_status.DrawWinText(m_window);

            if (m_deltaTime >= sf::seconds(4)) {
                clearVectors();
                m_window.close();
                GameMusic.stop();
                auto game = Game();
                game.run();
            }


       }
       else {   //clearing vetors and running the menu again 
           m_deltaTime += clock.restart();

           m_status.DrawLoseText(m_window);

           if (m_deltaTime >= sf::seconds(4)) {
               clearVectors();
               m_window.close();
               GameMusic.stop();
               auto game = Game();
               game.run();
           }

       }
   }
}

float findYOnEdge(const sf::ConvexShape& shape, float x) {
    sf::Vector2f prevPoint = shape.getPoint(0);

    // Iterate over the edges of the shape
    for (int i = 1; i < shape.getPointCount(); ++i) {
        sf::Vector2f currentPoint = shape.getPoint(i);

        // Check if the x coordinate is within the range of the current edge
        if ((prevPoint.x <= x && currentPoint.x >= x)|| (prevPoint.x >= x && currentPoint.x <= x)) {
            // Perform linear interpolation to find the y coordinate on the edge
            float t = (x - prevPoint.x) / (currentPoint.x - prevPoint.x);
            float y = prevPoint.y + t * (currentPoint.y - prevPoint.y);
            return y;
        }

        prevPoint = currentPoint;
    }

    // Return a default value if the x coordinate is outside the convex shape
       return 0.0f;
}
//==================================
//function to draw the platforms for us we made it for us to check if its correct
void Game::drawPlatforms()
{
    const std::vector<Platform>& platformsToDraw = m_board.getPlatformsToDraw();

    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());

    for (const Platform& platform : platformsToDraw) {
        const sf::FloatRect& platformBounds = platform.getPlatform().getGlobalBounds();
        const bool isVisible = viewBounds.intersects(platformBounds);

        if (isVisible) {
            //delete this from a note to see the convex shape itself as a platforms
            //m_window.draw(platform.getPlatform());
            platformsToCheckCollision.push_back(platform);
        }
    }
}
//==================================
//updating the bullets vecttors and checking the collisions with them and the enemes and view bounds
void Game::updateAndCheckIfBulletsInTheField(const sf::FloatRect& view)
{

    bool collied = false;
    //if its a default weapon
    if (!m_ShotGun && !m_rifle && !m_defWeapp.empty()) {
        m_ShotGun = false;
        m_rifle = false;
        m_ShotWeap.clear(); //clearing the vecor of the shotgun 
        m_RifleWeap.clear();        //clearing the vector of the rifle
        //updates the default weapon
        for (auto& weap : m_defWeapp) {
            weap->update(m_deltaTime2);
        }
        //check the collision of the standard enemies with the default weapon bullets 
        int sizew = m_defWeapp.size();
        for (int i = 0; i < sizew; i++)
        {
            if (!m_standardEnemies.empty()) {
                for (auto& enm : m_standardEnemies) {   //if there is a collision then:
                    if (m_board.checkCollisionBetweenTwoSprites(enm->getSprite(), m_defWeapp[i]->GetBulletSprite())) {
                        enm->LostHp(m_defWeapp[i]->getDamage());
                        m_defWeapp.erase(m_defWeapp.begin() + i);   //clearing the currr bullet from the vector
                        collied = true; //there were a collision
                        break;
                    }
                }
                if (collied)
                    break;
            }
            if (!m_presentEnemies.empty()) {
                for (auto& Penm : m_presentEnemies) {   //if there is a collision then:
                    if (m_board.checkCollisionBetweenTwoSprites(Penm->getSprite(), m_defWeapp[i]->GetBulletSprite())) {
                        Penm->LostHp(m_defWeapp[i]->getDamage());
                        m_defWeapp.erase(m_defWeapp.begin() + i);   //clearing the currr bullet from the vector
                        collied = true; //there were a collision
                        break;
                    }
                }
                if (collied)
                    break;
            }
            if (!m_forkEnemies.empty()) {   //checking the collision between the default weapon and the form enemies vector
                for (auto& fork : m_forkEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(fork->getSprite(), m_defWeapp[i]->GetBulletSprite()) && !fork->Die()) {
                        fork->LostHp(m_defWeapp[i]->getDamage());
                        m_defWeapp.erase(m_defWeapp.begin() + i);   //cleari the current bullet from the vector
                        collied = true;
                        break;
                    }
                }
                if (collied)
                    break;
            }
            if (!m_BossEnemies.empty()) {   //checking the collision between the boss vector and the default weapon bullets
                for (auto& boss : m_BossEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(boss->getSprite(), m_defWeapp[i]->GetBulletSprite()) && !boss->Die()) {
                        boss->LostHp(m_defWeapp[i]->getDamage());
                        m_defWeapp.erase(m_defWeapp.begin() + i);   //clearing the current bullet from the vector 
                        collied = true;
                        break;
                    }
                }
                if (collied)
                    break;
            }   //checking if the bullet get out of the view bounds if yes to delet it
            const sf::FloatRect& bulletBounds = m_defWeapp[i]->GetBulletSprite().getGlobalBounds();
            const bool isVisible = view.intersects(bulletBounds);
            if (!isVisible) {
                delete m_defWeapp[i];
                m_defWeapp.erase(m_defWeapp.begin() + i);
                sizew--;
            }
        }
    }   //check the collisions between the shotgun bullets and the enemies and update the vector of the bullets 
    if (m_ShotGun && !m_ShotWeap.empty()) {
        m_rifle = false;
        m_defWeapp.clear(); //clearing the def vec
        m_RifleWeap.clear();    //clearing the rifle weap vec
        for (auto& weap : m_ShotWeap) {
            weap->update(m_deltaTime2);
        }

        int sizew = m_ShotWeap.size();
        for (int i = 0; i < sizew; i++)
        {
            //checking collision between standar eneemies vec and the bullet vec
            if (!m_standardEnemies.empty()) {
                for (auto& enm : m_standardEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(enm->getSprite(), m_ShotWeap[i]->GetBulletSprite())) {
                        enm->LostHp(m_ShotWeap[i]->getDamage());

                        m_ShotWeap.erase(m_ShotWeap.begin() + i);   //clearing the current bbullet if there is collision
                        collied = true;
                        break;
                    }

                }
                if (collied)
                    break;
            }
            if (!m_presentEnemies.empty()) {
                for (auto& Penm : m_presentEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(Penm->getSprite(), m_ShotWeap[i]->GetBulletSprite())) {
                        Penm->LostHp(m_ShotWeap[i]->getDamage());

                        m_ShotWeap.erase(m_ShotWeap.begin() + i);   //clearing the current bbullet if there is collision
                        collied = true;
                        break;
                    }

                }
                if (collied)
                    break;
            }
            //checking the collision between the fork vec and the shotgun bull vec
            if (!m_forkEnemies.empty()) {
                for (auto& fork : m_forkEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(fork->getSprite(), m_ShotWeap[i]->GetBulletSprite()) && !fork->Die()) {
                        fork->LostHp(m_ShotWeap[i]->getDamage());

                        m_ShotWeap.erase(m_ShotWeap.begin() + i);   //clearing the current bullet
                        collied = true;
                        break;
                    }

                }
                if (collied)
                    break;
            }//checking the collision betweeen the boss vec and the shotgun vec 
            if (!m_BossEnemies.empty()) {
                for (auto& boss : m_BossEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(boss->getSprite(), m_ShotWeap[i]->GetBulletSprite()) && !boss->Die()) {
                        boss->LostHp(m_ShotWeap[i]->getDamage());

                        m_ShotWeap.erase(m_ShotWeap.begin() + i); //clearing the current bullet
                        collied = true;
                        break;
                    }

                }
                if (collied)
                    break;
            }//checking the bullets if its out the view bounds to delete them
            const sf::FloatRect& bulletBounds = m_ShotWeap[i]->GetBulletSprite().getGlobalBounds();
            const bool isVisible = view.intersects(bulletBounds);
            if (!isVisible) {
                delete m_ShotWeap[i];
                m_ShotWeap.erase(m_ShotWeap.begin() + i);
                sizew--;
                m_shotgunWeap.fireAmmo();

            }
        }
    }//check the collision between tthe rifle bull vec and the enemies vec
    if (m_rifle && !m_RifleWeap.empty())
    {
        m_ShotGun = false;
        m_defWeapp.clear();
        m_ShotWeap.clear();
        //update the rifle bullet vec
        for (auto& weap : m_RifleWeap) {
            weap->update(m_deltaTime2);
        }
        int sizew = m_RifleWeap.size();
        for (int i = 0; i < sizew; i++)
        {
            //check the collision between the standard enemies and the rifle weapon bullets vec
            if (!m_standardEnemies.empty()) {
                for (auto& enm : m_standardEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(enm->getSprite(), m_RifleWeap[i]->GetBulletSprite())) {
                        enm->LostHp(m_RifleWeap[i]->getDamage());

                        m_RifleWeap.erase(m_RifleWeap.begin() + i);  //clearing the current bullet
                        collied = true;
                        break;
                    }
                }
                if (collied)
                    break;
            }
            if (!m_presentEnemies.empty()) {
                for (auto& Penm : m_presentEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(Penm->getSprite(), m_RifleWeap[i]->GetBulletSprite())) {
                        Penm->LostHp(m_RifleWeap[i]->getDamage());

                        m_RifleWeap.erase(m_RifleWeap.begin() + i);  //clearing the current bullet
                        collied = true;
                        break;
                    }
                }
                if (collied)
                    break;
            }
            //checking the collision between the fork vec and the rilfe bullet vec
            if (!m_forkEnemies.empty()) {
                for (auto& fork : m_forkEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(fork->getSprite(), m_RifleWeap[i]->GetBulletSprite())&& !fork->Die()) {
                        fork->LostHp(m_RifleWeap[i]->getDamage());

                        m_RifleWeap.erase(m_RifleWeap.begin() + i); //clearing the current bullet
                        collied = true;
                        break;
                    }
                }
                if (collied)
                    break;
            }//checking the boss collision with the bullets vec
            if (!m_BossEnemies.empty()) {
                for (auto& boss : m_BossEnemies) {
                    if (m_board.checkCollisionBetweenTwoSprites(boss->getSprite(), m_RifleWeap[i]->GetBulletSprite()) && !boss->Die()) {
                        boss->LostHp(m_RifleWeap[i]->getDamage());

                        m_RifleWeap.erase(m_RifleWeap.begin() + i);  //clearing the current bullet
                        collied = true;
                        break;
                    }
                }
                if (collied)
                    break;
            }//checking the bullets if its out the view bounds to delete them
            const sf::FloatRect& bulletBounds = m_RifleWeap[i]->GetBulletSprite().getGlobalBounds();
            const bool isVisible = view.intersects(bulletBounds);
            if (!isVisible) {
                delete m_RifleWeap[i];
                m_RifleWeap.erase(m_RifleWeap.begin() + i);
                sizew--;
                m_RifleGunWeap.fireAmmo();

            }
        }
    }
    collied = false;    //if there were a collision between the standard enmis and one of the bullets 
    //we do the die format of the exact standard enemy
    if (!m_standardEnemies.empty()) {
        for (int i = 0; i < m_standardEnemies.size(); i++)
        {
            if (m_standardEnemies[i]->Die()) {

                m_standardEnemies[i]->setAnimationByDirection(Direction::Stay);
                if (m_standardEnemies[i]->getDieSpriteCount() > 6) {
                    m_score += 20;
                    m_standardEnemies.erase(m_standardEnemies.begin() + i);

                    break;
                }
               // m_standardEnemies[i]->DieFormat();
                break;

            }

        }
    }
    if (!m_presentEnemies.empty()) {
        for (int i = 0; i < m_presentEnemies.size(); i++)
        {
            if (m_presentEnemies[i]->Die()) {

                m_presentEnemies[i]->setAnimationByDirection(Direction::Stay);
                if (m_presentEnemies[i]->getDieSpriteCount() >= 3) {
                    m_score += 25;
                    m_presentEnemies.erase(m_presentEnemies.begin() + i);

                    break;
                }
                break;
            }
        }
    }
    //die format of the fork enemies that had a collision with a bullets
    if (!m_forkEnemies.empty()) {
        for (int i = 0; i < m_forkEnemies.size(); i++)
        {
            if (m_forkEnemies[i]->Die() && !m_forkEnemies[i]->getDied()) {

                m_score += 30;
                m_forkEnemies[i]->setDamage(0);
                m_forkEnemies[i]->DieFormat();
                m_forkEnemies[i]->setDied();
                break;

            }
           
        }
    }//die format of the boss that have a collision with a bullet
    if (!m_BossEnemies.empty()) {
        for (int i = 0; i < m_BossEnemies.size(); i++)
        {
            if (m_BossEnemies[i]->Die()) {
                if (m_BossEnemies[i]->getDir() == Direction::Right)
                    m_BossEnemies[i]->setAnimationByDirection(Direction::DownHeadRight);
                else
                    m_BossEnemies[i]->setAnimationByDirection(Direction::DownHeadLeft);

                m_BossEnemies[i]->setDamage(0);


                if (m_BossEnemies[i]->getDieSpriteCount() >= 7) {
                    m_score += 50;
                    m_BossEnemies.erase(m_BossEnemies.begin() + i);
                }
                break;

            }
        }
    }
    //doing the update of the boss vec
    if (!m_BossBull.empty())
    {
        for (auto& bul : m_BossBull)
        {
            bul->update(m_deltaTime);
        }
    }


    if (m_fEnemPos.empty() && m_sEnemPos.empty() && m_pEnemPos.empty() && m_BossPos.empty() &&
        m_standardEnemies.empty() && m_forkEnemies.empty() && m_presentEnemies.empty() && m_BossEnemies.empty())
        m_WinGame = true;
}
//================================================
//function used to lock the screen view for us the begging and the end 
void Game::CheckForLockScreens()
{

    // Get the current position of m_p1 character
    sf::Vector2f characterPos = m_p1->getSprite().getPosition();

    // Get the half size of the view
    sf::Vector2f viewHalfSize = view.getSize() / 2.0f;

    // Calculate the minimum and maximum
    sf::Vector2f minViewCenter = viewHalfSize;
    sf::Vector2f maxViewCenter = sf::Vector2f(14222 * MAPSCALE,WINDOW_HEIGHT/2)- viewHalfSize;

    // Calculate the character position for x-coordinate
    float cx = std::max(minViewCenter.x, std::min(maxViewCenter.x, characterPos.x));

    // Calculate the character position for y-coordinate
    float cy = std::max(minViewCenter.y, std::min(maxViewCenter.y, characterPos.y));

    // Set the clamped character position as the view center
    view.setCenter(cx, cy);  
}

//=========================================
//adding the type of the bullet that have been fired to the vector of the same type
void Game::BulletsFiring()
{
    //if shotgun bullet
    if (m_ShotGun && !m_rifle) {

        auto m_Weap = new ShotgunWeap();
        m_direction = m_p1->getDir();
        m_Weap->setTexture(m_direction);
        m_Weap->setVelocity(toVector(m_p1->getDir()));
        m_Weap->setDirection(m_direction);
        m_Weap->SetPosition(m_p1->getSprite());

        m_ShotWeap.push_back(m_Weap);
        m_sound.setBuffer(*m_resource.getBuffer(SHOTGUN_SHOT));
        m_sound.play();

    }//if deafult bullet been fired
    else if (!m_ShotGun && !m_rifle) {

        auto m_defWeap = new DefaultWeap();

        m_direction = m_p1->getDir();
        m_defWeap->setTexture(m_direction);
        m_defWeap->setVelocity(toVector(m_p1->getDir()));
        m_defWeap->setDirection(m_direction);
        m_defWeap->SetPosition(m_p1->getSprite());

        m_defWeapp.push_back(m_defWeap);
        m_sound.setBuffer(*m_resource.getBuffer(DEFAULT_SHOT));
        m_sound.play();
    }
    else if ( m_rifle && !m_ShotGun) {  //if rifle bullet been fired

        auto m_rifWeap = new RifleWeap();

        m_direction = m_p1->getDir();
        m_rifWeap->setTexture(m_direction);
        m_rifWeap->setVelocity(toVector(m_p1->getDir()));
        m_rifWeap->setDirection(m_direction);
        m_rifWeap->SetPosition(m_p1->getSprite());

        m_RifleWeap.push_back(m_rifWeap);
        m_sound.setBuffer(*m_resource.getBuffer(RIFLE_SHOT));
        m_sound.play();
    }
}
//=========================================
//creating the enemies vectors and positions
void Game::createEnemies()
{
    createStandardEnemiesPos();
    createForkEnemiesPos();
    createPresentEnemiesPos();
    createBossPos();
}
//=========================================
//function to create the standrad enemies vector positions 
void Game::createStandardEnemiesPos()
{
    int lowerLimitX = 2500 * MAPSCALE,
        upperLimitX = 8356 * MAPSCALE,
        lowerLimitY = 0,
        upperLimitY = 800;

    for (int i = 0; i < 35; ++i)
        m_sEnemPos.emplace_back(sf::Vector2f(float(lowerLimitX + rand() % (upperLimitX - lowerLimitX + 1)), float(lowerLimitY + rand() % (upperLimitY - lowerLimitY + 1))));


    lowerLimitX = 9145 * MAPSCALE;
    upperLimitX = 13461 * MAPSCALE;

    for (int i = 0; i < 35; ++i)
        m_sEnemPos.emplace_back(sf::Vector2f(float(lowerLimitX + rand() % (upperLimitX - lowerLimitX + 1)), float(lowerLimitY + rand() % (upperLimitY - lowerLimitY + 1))));

}
//=========================================
//create the fork enemies positions 
void Game::createForkEnemiesPos()
{
    int lowerLimitX = 8356 * MAPSCALE,
        upperLimitX = 9145 * MAPSCALE,
        lowerLimitY = 700,
        upperLimitY = 850;

    for (int i = 0; i < 20; ++i)
        m_fEnemPos.emplace_back(sf::Vector2f(float(lowerLimitX + rand() % (upperLimitX - lowerLimitX + 1)), float(lowerLimitY + rand() % (upperLimitY - lowerLimitY + 1))));
    lowerLimitX = 10262 * MAPSCALE;
    upperLimitX = 13461 * MAPSCALE;
    for (int i = 0; i < 20; ++i)
        m_fEnemPos.emplace_back(sf::Vector2f(float(lowerLimitX + rand() % (upperLimitX - lowerLimitX + 1)), float(lowerLimitY + rand() % (upperLimitY - lowerLimitY + 1))));
}
void Game::createPresentEnemiesPos()
{
    int lowerLimitX = 2500 * MAPSCALE,
        upperLimitX = 8356 * MAPSCALE,
        lowerLimitY = 0,
        upperLimitY = 800;

    for (int i = 0; i < 15; ++i)
        m_pEnemPos.emplace_back(sf::Vector2f(float(lowerLimitX + rand() % (upperLimitX - lowerLimitX + 1)), float(lowerLimitY + rand() % (upperLimitY - lowerLimitY + 1))));


    lowerLimitX = 9145 * MAPSCALE;
    upperLimitX = 13461 * MAPSCALE;

    for (int i = 0; i < 20; ++i)
        m_pEnemPos.emplace_back(sf::Vector2f(float(lowerLimitX + rand() % (upperLimitX - lowerLimitX + 1)), float(lowerLimitY + rand() % (upperLimitY - lowerLimitY + 1))));

}
//=========================================
//create the boss enemies positions
void Game::createBossPos()
{
    int lowerLimitX = 14000 * MAPSCALE,
        upperLimitX = 14000*MAPSCALE,
        lowerLimitY = 600,
        upperLimitY = 800;

    for (int i = 0; i < BOSSSIZE; ++i)
        m_BossPos.emplace_back(sf::Vector2f(float(lowerLimitX + rand() % (upperLimitX - lowerLimitX + 1)), float(lowerLimitY + rand() % (upperLimitY - lowerLimitY + 1))));

}
//=========================================
//create the vector of the boss enemies 
void Game::createBossEnemy()
{
    std::vector<sf::Vector2f> toRemove;
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    if (!m_BossPos.empty()) {
        for (auto& boss : m_BossPos) {
            if (viewBounds.contains(boss)) {    //if the view contains the postion of the curr boss then we add it to the vec
                Boss* b = new Boss();
                auto side = rand() % 2;
                if (!side) {    //giving it a random position to be in the left or right view side
                    b->setAnimationByDirection(Direction::Right);
                    b->setPosition(sf::Vector2f(viewBounds.left + 1, boss.y));

                }
                else
                {
                    //adding it to the vector
                }
                    b->setPosition(boss);
                m_BossEnemies.emplace_back(b);
                toRemove.emplace_back(boss);
            }
        }
    }   //to delete the pos of the boss that have been added to the boss enemies vector from the positions vectors
    int posSize = m_BossPos.size(),
        rem = toRemove.size();
    for (int i = 0; i < posSize; i++) {
        for (int j = 0; j < toRemove.size(); j++) {
            if (m_BossPos[i] == toRemove[j]) {
                m_BossPos.erase(m_BossPos.begin() + i);
                posSize--;
                break;
            }

        }
    }
    toRemove.clear();
}
//=========================================
//function that clears the vectors of the class
void Game::clearVectors()
{
    m_board.clearVec();
    m_defWeapp.clear();
    m_ShotWeap.clear();
    m_RifleWeap.clear();
    m_standardEnemies.clear();
    m_presentEnemies.clear();
    m_forkEnemies.clear();
    m_sEnemPos.clear();
    m_fEnemPos.clear();
    m_pEnemPos.clear();
    platformsToCheckCollision.clear();
    m_shotgunWeap.clearVec();
    m_RifleGunWeap.clearVec();
}
//=========================================
//function to create the enemies vectors 
void Game::drawAndCreateEnemies()
{
    createStandardEnemy();
    createForkEnemy();
    createPresentEnemy();
    createBossEnemy();
}
//=========================================
//function to create the standard enemy vec by the positions vec it creates
void Game::createStandardEnemy()
{
    std::vector<sf::Vector2f> toRemove;
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    if (!m_sEnemPos.empty()) {
        for (auto& standard : m_sEnemPos) {
            if (viewBounds.contains(standard)) {    //if the pos of the enemies in the view then it will add them to the vector
                StandardEnemy* s = new StandardEnemy();
                auto side = rand() % 2;
                if (!side)
                    s->setPosition(sf::Vector2f(viewBounds.left + 1, standard.y));
                else
                    s->setPosition(standard);
                m_standardEnemies.emplace_back(s);
                toRemove.emplace_back(standard);
            }
        }
    }   //deleting the pos from the pos vec of the enemy that have been added to the enemies vec 
    int posSize = m_sEnemPos.size(),
        rem = toRemove.size();
    for (int i = 0; i < posSize; i++) {
        for (int j = 0; j < rem; j++) {
            if (m_sEnemPos[i] == toRemove[j]) {
                m_sEnemPos.erase(m_sEnemPos.begin() + i);
                posSize--;
                break;
            }

        }

    }
    toRemove.clear();
    viewBounds.left = viewBounds.left - 3000;
    viewBounds.width = viewBounds.width + 6000;

    //if the enemies is out of the view bounds left and width that is up here writeen then it gets deleted
    for (int i = 0; i < m_standardEnemies.size(); i++)
    {
        if (!viewBounds.contains(m_standardEnemies[i]->getSprite().getPosition())) {
            delete m_standardEnemies[i];
            m_standardEnemies.erase(m_standardEnemies.begin() + i);
            break;
        }
    }
}
void Game::createPresentEnemy()
{
     std::vector<sf::Vector2f> toRemove;
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    if (!m_pEnemPos.empty()) {
        for (auto& present : m_pEnemPos) {
            if (viewBounds.contains(present)) {    //if the pos of the enemies in the view then it will add them to the vector
               PresentEnemy* p = new PresentEnemy();
                auto side = rand() % 2;
                if (!side)
                    p->setPosition(sf::Vector2f(viewBounds.left + 1, present.y));
                else
                    p->setPosition(present);
                m_presentEnemies.emplace_back(p);
                toRemove.emplace_back(present);
            }
        }
    }   //deleting the pos from the pos vec of the enemy that have been added to the enemies vec 
    int posSize = m_pEnemPos.size(),
        rem = toRemove.size();
    for (int i = 0; i < posSize; i++) {
        for (int j = 0; j < rem; j++) {
            if (m_pEnemPos[i] == toRemove[j]) {
                m_pEnemPos.erase(m_pEnemPos.begin() + i);
                posSize--;
                break;
            }

        }

    }
    toRemove.clear();
    viewBounds.left = viewBounds.left - 2500;
    viewBounds.width = viewBounds.width + 5000;

    //if the enemies is out of the view bounds left and width that is up here writeen then it gets deleted
    for (int i = 0; i < m_presentEnemies.size(); i++)
    {
        if (!viewBounds.contains(m_presentEnemies[i]->getSprite().getPosition())) {
            delete m_presentEnemies[i];
            m_presentEnemies.erase(m_presentEnemies.begin() + i);
            break;
        }
    }
}
//=========================================
//function to create the fork enemies vector 
void Game::createForkEnemy()
{
    std::vector<sf::Vector2f> toRemove;
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    if (!m_fEnemPos.empty()) {
        for (auto& fork : m_fEnemPos) {
            if (viewBounds.contains(fork)) {    //iif the curr pos is in the view then it creates an enemie in this pos and add to the vec
                 ForkEnemy *f = new ForkEnemy();
                auto side = rand() % 2;
                if (!side) {
                    f->setAnimationByDirection(Direction::Right);
                    f->setPosition(sf::Vector2f(viewBounds.left + 1, fork.y));

                }
                else
                    f->setPosition(fork);
                m_forkEnemies.emplace_back(f);
                toRemove.emplace_back(fork);
            }
        }
    }   //erasing the pos that the view contained and used to create the fork enemy up there
    int posSize = m_fEnemPos.size(),    
    rem = toRemove.size();
    for (int i = 0; i < posSize; i++) {
        for (int j = 0; j < rem; j++) {
            if (m_fEnemPos[i] == toRemove[j]) {
                m_fEnemPos.erase(m_fEnemPos.begin() + i);
                posSize--;
                break;
                //rem--;
            }
        }
    }
    toRemove.clear();
    //if the fork enemy gets out of the view bounds then it gets deleted
    for (int i = 0; i < m_forkEnemies.size(); i++)
    {
        if (!viewBounds.contains(m_forkEnemies[i]->getSprite().getPosition())) {
            delete m_forkEnemies[i];
            m_forkEnemies.erase(m_forkEnemies.begin() + i);
            break;
        }

    }
}
//=========================================
//update function 
void Game::update()
{
    m_deltaTime = clock.restart();
    m_deltaTime2 = clock2.restart();
    m_BulletsTimer -= m_deltaTime;

    m_lastPositionOfBlip = m_p1->getSprite().getGlobalBounds();


    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.0f, view.getSize());
    updateAndCheckIfBulletsInTheField(viewBounds);  //update the bullets 
    CheckForLockScreens();  //check the lock screen update

    m_window.clear();
    
    //setting the view
    m_window.setView(view);
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    // Calculate the top left corner coordinates
    sf::Vector2f viewTopLeft = viewCenter - (viewSize / 2.f);
    
    //setting the status postion
    m_status.setPostion(viewTopLeft);

    //to loose the life
    if (m_p1->GetHp() <= 0 && m_p1->GetLives() > 0) {
        m_p1->setHp();
        m_p1->LostLife();
        m_p1->setPosition(sf::Vector2f(m_p1->getSprite().getPosition().x, 0));
    }
    sf::Vector2f pos = sf::Vector2f(m_status.getSprite(m_p1->GetHp()).getTexture()->getSize().x, m_status.getSprite(m_p1->GetHp()).getTexture()->getSize().y);

    //set the lives text on the view
    m_status.setText(m_p1->GetLives(), sf::Vector2f(viewTopLeft.x + pos.x/2 , viewTopLeft.y + pos.y/2));
    m_status.setScore(m_score, sf::Vector2f(viewTopLeft.x + WINDOW_WIDTH/2,viewTopLeft.y +10*MAPSCALE));
    m_status.setWinText(m_score, sf::Vector2f(viewTopLeft.x + WINDOW_WIDTH /9, viewTopLeft.y + WINDOW_HEIGHT/3));
    m_status.setLoseText(m_score, sf::Vector2f(viewTopLeft.x + WINDOW_WIDTH / 9, viewTopLeft.y + WINDOW_HEIGHT / 3));
    m_status.GarGamelSetText(sf::Vector2f(viewTopLeft.x + WINDOW_WIDTH / 4, viewTopLeft.y + WINDOW_HEIGHT / 3));

    if (viewBounds.contains(sf::Vector2f(1300 * MAPSCALE, WINDOW_HEIGHT / 2)) && !m_TextIsOn)
    {
        m_TextOnScreenTimer = sf::seconds(5);
        m_TextIsOn = true;
    }
    if (m_TextIsOn)
    {
        m_TextOnScreenTimer -= sf::seconds(0.1f); // Subtract the elapsed frame time

        if (m_TextOnScreenTimer <= sf::Time::Zero)
        {
            m_TextIsOn = false;
        }
    }
}
//=========================================
//function that holds all the draw things 
void Game::draw()
{
    m_window.draw(mapSprite);
    m_status.DrawStatusBar(m_window, m_p1->GetHp());    //draw the status bar

    if (m_TextIsOn)
        m_status.DrawGarGamelText(m_window);


    drawPlatforms();    //draw the platform forr us !!
    drawAndCreateEnemies(); //draw the enemies 
    checkCollision();   //check the collision
    //return to the default weapon
    if (m_ShotGun && m_shotgunWeap.isOutOFAmmo() || (m_rifle && m_RifleGunWeap.isOutOFAmmo()))
    {
        m_ShotWeap.clear();
        m_RifleWeap.clear();
        sf::Sprite sp;
        sp = m_p1->getSprite();
        int hp = m_p1->GetHp();
        int live = m_p1->GetLives();
        if(CHARACTER_SELECTED)
            m_p1 = new BlipAndBlop(Resources::BLOP, Resources::STANDARDBULLET);
        else
        m_p1 = new BlipAndBlop(Resources::BLIP, Resources::STANDARDBULLET);


        m_p1->SaveHp(hp);
        m_p1->SaveLives(live);
        m_p1->setPosition(sf::Vector2f(sp.getPosition().x,GroundLimit));
        m_shotgunWeap.setAmmo(SHOTGUNAMMOCAPACITY);
        m_RifleGunWeap.setAmmo(RIFLEGUNAMMOCAPACITY);
        m_ShotGun = false;
        m_rifle = false;
    }

    m_window.draw(m_p1->getSprite());

    //draw the standard enemies 
    if (!m_standardEnemies.empty()) {
        for (auto& s : m_standardEnemies) {
            m_window.draw(s->getSprite());
        }
    }   
    //draw the present enemies 
    if (!m_presentEnemies.empty()) {
        for (auto& p : m_presentEnemies) {
            m_window.draw(p->getSprite());
        }
    }
    //draw the fork enemies
    if (!m_forkEnemies.empty()) {
        for (auto& fork : m_forkEnemies) {

            m_window.draw(fork->getSprite());
        }
    }//draw the boss enemies
    if (!m_BossEnemies.empty()) {
        for (auto& boss : m_BossEnemies) {

            m_window.draw(boss->getSprite());
        }
    }//draw the default bulls
    if (!m_defWeapp.empty() ) {
        for (auto& weap : m_defWeapp) {

            m_window.draw(weap->GetBulletSprite());
        }
    }//draw the shotgun bullets
    else if (!m_ShotWeap.empty()) {
        for (auto& weap : m_ShotWeap) {

            m_window.draw(weap->GetBulletSprite());
            
        }
    }//draw the rifle bullets
    else if (!m_RifleWeap.empty()) {
        for (auto& weap : m_RifleWeap) {

            m_window.draw(weap->GetBulletSprite());
           
        }
    }
    //draw the boss 
    if (!m_BossBull.empty())
    {
        for (auto& bul : m_BossBull)
        {
            m_window.draw(bul->GetBulletSprite());
        }
    }
    m_p1->innerUpdater();   //update the inner bounds 

    m_shotgunWeap.Draw(m_window);   //draw the shotgun on the ground 
    m_RifleGunWeap.Draw(m_window);  //draw the rifle on the ground

    //m_window.draw(m_p1->getCurrInnerBoundToDrawOnly()); //for us to draw the bounds!!!

}
//=========================================
//function to check the collisions
void Game::checkCollision()
{

    bool colPlat = false;
    float colY = 0.0f;
    //check cllision with the platforms 
    for (auto plat : platformsToCheckCollision)
    {
        {
            if (!m_p1->getIfGoingDown())
                break;
            auto inn = m_p1->getInnerBoundsForCollision();
            auto glb = m_p1->getGlobalBoundsForCollision();

            auto innerBotRight = sf::Vector2f(inn.left + inn.width, inn.top + inn.height);
            auto innerBotLeft = sf::Vector2f(inn.left, inn.top + inn.height);
            float rightCon = 0, leftCon = 0;
            rightCon = findYOnEdge(plat.getPlatform(), innerBotRight.x);
            leftCon = findYOnEdge(plat.getPlatform(), innerBotLeft.x);

            if (rightCon == 0.0f)
                rightCon = innerBotLeft.y;
            if (leftCon == 0.0f)
                leftCon = innerBotRight.y;
            if (rightCon == innerBotLeft.y && leftCon == innerBotRight.y) {
                colPlat = false;
                continue;
            }
            if (rightCon > innerBotRight.y || leftCon > innerBotLeft.y ||
                rightCon < inn.top || leftCon < inn.top) {
                colPlat = false;
                continue;

            }
            if (rightCon >= inn.top && innerBotRight.y > rightCon)
                colY = rightCon;
            if (leftCon >= inn.top && innerBotLeft.y > leftCon)
                colY = leftCon;
            if (leftCon >= inn.top && innerBotLeft.y > leftCon && rightCon >= inn.top && innerBotRight.y > rightCon)
            {
                colY = std::min(leftCon, rightCon);
            }
            auto v = sf::Vector2f(m_p1->getSprite().getPosition().x, colY - inn.height - (inn.top - glb.top));
            m_p1->setPosition(v);
            m_p1->setIsJumping(false);
            m_p1->setIsGoingDown(false);
            colPlat = true;
            break;
        }
    }
    if (colPlat) {
        m_p1->setIsJumping(false);
        m_p1->update(m_deltaTime, m_window, true, sf::Vector2f());
    }
    else if (m_p1->CheckGroundCollision()) {
        m_p1->update(m_deltaTime, m_window,  true, sf::Vector2f());
    }
    else {
        m_p1->update(m_deltaTime, m_window,  false, sf::Vector2f());
    }
    if (!m_standardEnemies.empty()) {

        for (auto& s : m_standardEnemies) {
            if (s->CheckGroundCollision()) {
                s->update(m_deltaTime, m_window,  true, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
            else {
                s->update(m_deltaTime, m_window,false, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
        }
    }
    if (!m_presentEnemies.empty()) {

        for (auto& p : m_presentEnemies) {
            if (p->CheckGroundCollision()) {
                p->update(m_deltaTime, m_window, true, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
            else {
                p->update(m_deltaTime, m_window, false, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
        }
    }
    if (!m_BossEnemies.empty()) {

        for (auto& b : m_BossEnemies) {
            if (b->CheckGroundCollision()) {
                b->update(m_deltaTime, m_window,  true, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
            else {
                b->update(m_deltaTime, m_window,  false, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
        }
        //check collision between the character and the boss enemies 
        m_timer = clock3.restart();

        m_p1->minusTimer(m_timer);
        for (int i = 0; i < m_BossEnemies.size(); i++) {

            if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), m_BossEnemies[i]->getSprite()) && !m_BossEnemies[i]->getDied()) {

                if (m_p1->CheckAfterCollisionTimer() <= sf::seconds(0)) {
                    m_p1->LostHp(m_BossEnemies[i]->getDamage());
                    m_p1->setAfterCollisionTimer();
                    clock3.restart();
                }
                break;
            }
        }//adding the bullets firing from the boss to the vector when its ready to fire 
        for (int i = 0; i < m_BossEnemies.size(); i++)
        {
            if (m_BossEnemies[i]->getCDIsReadyToFire())
            {
                BossBullet* bul = new BossBullet();

                m_direction = m_BossEnemies[i]->HeadTo();
                bul->setTexture(m_direction);
                bul->setVelocity(toVector(m_direction));
                bul->setDirection(m_direction);
                bul->SetPosition(m_BossEnemies[i]->getSprite());
                m_BossBull.emplace_back(bul);
            }

        }
        
    }//check collision between the shotgun pic and the character
    if (!m_shotgunWeap.getShotGunSpriteVec().empty()) {
        for (int i = 0; i < m_shotgunWeap.getShotGunSpriteVec().size(); i++)
        {
            auto spr = m_shotgunWeap.getShotGunSpriteVec()[i];
            if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), spr[0]) && !m_ShotGun)
            {
                sf::Sprite sp;
                sp = m_p1->getSprite();
                int hp = m_p1->GetHp();
                int live = m_p1->GetLives();
                if (CHARACTER_SELECTED)
                    m_p1 = new BlipAndBlop(Resources::SHOTGUNCHARBLOP, Resources::SHOTGUNBULLET);
                else
                    m_p1 = new BlipAndBlop(Resources::SHOTGUNCHAR, Resources::SHOTGUNBULLET);

                m_p1->SaveHp(hp);
                m_p1->SaveLives(live);

                m_shotgunWeap.setAmmo(SHOTGUNAMMOCAPACITY);
                m_p1->setPosition(sf::Vector2f(sp.getPosition().x, sp.getPosition().y));
                m_shotgunWeap.getShotGunSpriteVec().erase(m_shotgunWeap.getShotGunSpriteVec().begin() + i);
                m_ShotGun = true;
                m_rifle = false;
                m_RifleWeap.clear();
                m_defWeapp.clear();
                m_sound.setBuffer(*m_resource.getBuffer(SHOTGUN_WORD_VOICE));
                m_sound.play();
                break;
            }
            else if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), spr[0]) && m_ShotGun && !m_rifle)
            {
                m_shotgunWeap.AddAmmo(SHOTGUNAMMOCAPACITY);
                m_shotgunWeap.getShotGunSpriteVec().erase(m_shotgunWeap.getShotGunSpriteVec().begin() + i);
                m_sound.setBuffer(*m_resource.getBuffer(SHOTGUN_WORD_VOICE));
                m_sound.play();
                break;
            }


        }
    }//rifle collision and set ============================
    if (!m_RifleGunWeap.getGunSpriteVec().empty()) {
        for (int i = 0; i < m_RifleGunWeap.getGunSpriteVec().size(); i++)
        {
            auto spr = m_RifleGunWeap.getGunSpriteVec()[i];
            if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), spr[0]) && !m_rifle)
            {
                sf::Sprite sp;
                sp = m_p1->getSprite();
                int hp = m_p1->GetHp();
                int live = m_p1->GetLives();

                if (CHARACTER_SELECTED)
                    m_p1 = new BlipAndBlop(Resources::RIFLEGUNCHARBLOP, Resources::RIFLEGUNBULLET);
                else
                    m_p1 = new BlipAndBlop(Resources::RIFLEGUNCHAR, Resources::RIFLEGUNBULLET);

                m_p1->SaveHp(hp);
                m_p1->SaveLives(live);
                m_RifleGunWeap.setAmmo(RIFLEGUNAMMOCAPACITY);
                m_p1->setPosition(sp.getPosition());
                m_RifleGunWeap.getGunSpriteVec().erase(m_RifleGunWeap.getGunSpriteVec().begin() + i);
                m_rifle = true;
                m_ShotGun = false;
                m_ShotWeap.clear();
                m_defWeapp.clear();
                m_sound.setBuffer(*m_resource.getBuffer(RIFLE_WORD_VOICE));
                m_sound.play();
                break;
            }
            else if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), spr[0]) && m_rifle && !m_ShotGun)
            {
                m_RifleGunWeap.AddAmmo(RIFLEGUNAMMOCAPACITY);
                m_RifleGunWeap.getGunSpriteVec().erase(m_RifleGunWeap.getGunSpriteVec().begin() + i);
                m_sound.setBuffer(*m_resource.getBuffer(RIFLE_WORD_VOICE));
                m_sound.play();
                break;
            }

        }
    }
    //cehck the collision between the eneimes and the character 

    m_timer = clock3.restart();

    m_p1->minusTimer(m_timer);
    if (!m_standardEnemies.empty()) {
        for (int i = 0; i < m_standardEnemies.size(); i++) {

            if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), m_standardEnemies[i]->getSprite())) {
                
                if (m_p1->CheckAfterCollisionTimer() <= sf::seconds(0)) {
                    m_p1->LostHp(m_standardEnemies[i]->getDamage());
                    m_p1->setAfterCollisionTimer();
                    clock3.restart();
                }
           
                break;
            }
        }
    }
    //check the collision between the present enemies and the character
    m_timer = clock3.restart();
    m_p1->minusTimer(m_timer);
    if (!m_presentEnemies.empty()) {
        for (int i = 0; i < m_presentEnemies.size(); i++) {

            if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), m_presentEnemies[i]->getSprite())) {
                if (m_p1->CheckAfterCollisionTimer() <= sf::seconds(0)) {
                    m_p1->LostHp(m_presentEnemies[i]->getDamage());
                    m_p1->setAfterCollisionTimer();
                    clock3.restart();
                }
                m_presentEnemies[i]->LostHp(1); //kills it
                break;
            }
        }
    }
    //check the collision between the fork enemies and the character
    m_timer = clock3.restart();

    m_p1->minusTimer(m_timer);

    if (!m_forkEnemies.empty()) {

        for (int i = 0; i < m_forkEnemies.size(); i++) {

            if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), m_forkEnemies[i]->getSprite()) && !m_forkEnemies[i]->Die()) {

                if (m_p1->CheckAfterCollisionTimer() <= sf::seconds(0)) {
                    m_p1->LostHp(m_forkEnemies[i]->getDamage());
                    m_p1->setAfterCollisionTimer();
                    clock3.restart();
                }
                break;
            }
        }
    }
    //updates the fork enemies
    if (!m_forkEnemies.empty()) {

        for (auto& fork : m_forkEnemies) {
            if (fork->CheckGroundCollision()) {
                fork->update(m_deltaTime, m_window, true, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
            else {
                fork->update(m_deltaTime, m_window,false, sf::Vector2f(m_p1->getInnerBoundsForCollision().left + (m_p1->getInnerBoundsForCollision().width / 2)
                    , m_p1->getInnerBoundsForCollision().top + (m_p1->getInnerBoundsForCollision().height / 2)));
            }
        }
  
    }//check collisin between the bosses and the character
    if (!m_BossBull.empty() && !m_BossEnemies.empty()) {
        for (int i = 0; i < m_BossBull.size(); i++) {

            if (m_board.checkCollisionBetweenTwoSprites(m_p1->getSprite(), m_BossBull[i]->GetBulletSprite())) {

                if (m_p1->CheckAfterCollisionTimer() <= sf::seconds(0)) {
                    m_p1->LostHp(m_BossBull[i]->getDamage());
                    m_p1->setAfterCollisionTimer();
                    clock3.restart();
                }
                break;
            }
        }
    }
}