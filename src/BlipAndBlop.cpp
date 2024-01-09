#include"BlipAndBlop.h"
#include <optional>
#include<Cmath>

namespace
{
    //getting the key pressed Direction
    std::optional<Direction> toDirection(sf::Keyboard::Key key, Direction headingTowards)
    {
        switch (key)
        {
        case sf::Keyboard::Left:
            return Direction::Left;
        case sf::Keyboard::Right:
            return Direction::Right;
        case sf::Keyboard::Up: {
            if(headingTowards == Direction::Left)
                return Direction::UpHeadLeft;
            else
                return Direction::UpHeadRight;
        }
        case sf::Keyboard::Down: {
            if(headingTowards == Direction::Right)
                return Direction::DownHeadLeft;
            else
                return Direction::DownHeadRight;
        }
        case sf::Keyboard::Space:
            return Direction::Stay;
        default:
            return {};
        }
    }
}
//constructor !
BlipAndBlop::BlipAndBlop(Resources::Objects obj, Resources::Objects weap)
    :m_bOrb(obj), m_WeapT(weap), m_animation(Resources::instance().animationData(m_bOrb), Direction::DownRight, m_sprite,0)

{
    m_sprite.setPosition(sf::Vector2f(WINDOW_HEIGHT/ 2.0f, WINDOW_HEIGHT / 2.0f));
    m_sprite.setScale(MAPSCALE, MAPSCALE);


    //getting the inner bounds of the characters texturres we need them to the collisions to b more realistic
    //------------------------------blip----------------------------
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::UpHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (33 * MAPSCALE), 43 * MAPSCALE, 26 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::DownHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (6 * MAPSCALE), 42 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::UpHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y + (31 * MAPSCALE), 42 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::DownHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (3 * MAPSCALE), m_sprite.getPosition().y + (7 * MAPSCALE), 43 * MAPSCALE, 26 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::Left)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (17 * MAPSCALE), m_sprite.getPosition().y, 42 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::Right)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (9 * MAPSCALE), m_sprite.getPosition().y, 40 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::DownLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (7 * MAPSCALE), m_sprite.getPosition().y + (3 * MAPSCALE), 43 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::DownRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y + (3 * MAPSCALE), 43 * MAPSCALE, 29 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::UpRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (5 * MAPSCALE), m_sprite.getPosition().y + (19 * MAPSCALE), 42 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[m_WeapT][Resources::BLIP][static_cast<int>(Direction::UpLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (9 * MAPSCALE), m_sprite.getPosition().y + (19 * MAPSCALE), 42 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    
    
    ////shotgun char
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::UpHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (37 * MAPSCALE), 43 * MAPSCALE, 25 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::DownHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (3 * MAPSCALE), 41 * MAPSCALE, 26 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::UpHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y + (37 * MAPSCALE), 43 * MAPSCALE, 25 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::DownHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y + (3 * MAPSCALE), 41 * MAPSCALE, 26 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::Left)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (15 * MAPSCALE), m_sprite.getPosition().y, 49 * MAPSCALE, 27 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::Right)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y, 50 * MAPSCALE, 27 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::DownLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (7 * MAPSCALE), m_sprite.getPosition().y + (2 * MAPSCALE), 44 * MAPSCALE, 29 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::DownRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y + (2 * MAPSCALE), 44 * MAPSCALE, 29 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::UpRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y + (19 * MAPSCALE), 43 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHAR][static_cast<int>(Direction::UpLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (12 * MAPSCALE), m_sprite.getPosition().y + (18 * MAPSCALE), 43 * MAPSCALE, 27 * MAPSCALE), m_sprite.getGlobalBounds());

    //
    ////rifle char
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::UpHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (27 * MAPSCALE), 39 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::DownHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 43 * MAPSCALE, 26 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::UpHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (5 * MAPSCALE), m_sprite.getPosition().y + (27 * MAPSCALE), 39 * MAPSCALE, 28 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::DownHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y, 43 * MAPSCALE, 25 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::Left)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (12 * MAPSCALE), m_sprite.getPosition().y, 45 * MAPSCALE, 27 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::Right)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 44 * MAPSCALE, 29 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::DownLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x , m_sprite.getPosition().y , 45 * MAPSCALE, 27 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::DownRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (3 * MAPSCALE), m_sprite.getPosition().y , 45 * MAPSCALE, 27 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::UpRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x , m_sprite.getPosition().y + (14 * MAPSCALE), 42 * MAPSCALE, 30 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHAR][static_cast<int>(Direction::UpLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (5 * MAPSCALE), m_sprite.getPosition().y + (14 * MAPSCALE), 41 * MAPSCALE, 30 * MAPSCALE), m_sprite.getGlobalBounds());


    //
    ////~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ blop ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~  ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~~ ~ 

    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::UpHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (7 * MAPSCALE), 44 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::DownHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 42 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::UpHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (7 * MAPSCALE), 45 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::DownHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 46 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::Left)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (20 * MAPSCALE), m_sprite.getPosition().y, 37 * MAPSCALE, 35 * MAPSCALE), m_sprite.getGlobalBounds());    
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::Right)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (7 * MAPSCALE), m_sprite.getPosition().y, 38 * MAPSCALE, 36 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::DownLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (11 * MAPSCALE), m_sprite.getPosition().y, 40 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::DownRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (4 * MAPSCALE), m_sprite.getPosition().y, 41 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::UpRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x , m_sprite.getPosition().y + (9 * MAPSCALE), 41 * MAPSCALE, 37 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::STANDARDBULLET][Resources::BLOP][static_cast<int>(Direction::UpLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (8 * MAPSCALE), m_sprite.getPosition().y + (10 * MAPSCALE), 42 * MAPSCALE, 37 * MAPSCALE), m_sprite.getGlobalBounds());

    ////shotgun char blop
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::UpHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (7 * MAPSCALE), 46 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::DownHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 44 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::UpHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (27 * MAPSCALE), 46 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::DownHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 43 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::Left)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (30 * MAPSCALE), m_sprite.getPosition().y, 39 * MAPSCALE, 37 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::Right)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 40 * MAPSCALE, 37 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::DownLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (8 * MAPSCALE), m_sprite.getPosition().y, 42 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::DownRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (3 * MAPSCALE), m_sprite.getPosition().y , 42 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::UpRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (12 * MAPSCALE), 42 * MAPSCALE, 34 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::SHOTGUNBULLET][Resources::SHOTGUNCHARBLOP][static_cast<int>(Direction::UpLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (13 * MAPSCALE), m_sprite.getPosition().y + (12 * MAPSCALE), 42 * MAPSCALE, 34 * MAPSCALE), m_sprite.getGlobalBounds());


    ////rifle char blop
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::UpHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (22 * MAPSCALE), 41 * MAPSCALE, 37 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::DownHeadLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 44 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::UpHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (21 * MAPSCALE), 42 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::DownHeadRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 44 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::Left)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (13 * MAPSCALE), m_sprite.getPosition().y, 40 * MAPSCALE, 39 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::Right)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (2 * MAPSCALE), m_sprite.getPosition().y, 40 * MAPSCALE, 37 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::DownLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (6 * MAPSCALE), m_sprite.getPosition().y, 42 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::DownRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, 42 * MAPSCALE, 38 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::UpRight)] = std::pair(sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y + (6 * MAPSCALE), 42 * MAPSCALE, 35 * MAPSCALE), m_sprite.getGlobalBounds());
    m_InnerBoundsRectArr[Resources::RIFLEGUNBULLET][Resources::RIFLEGUNCHARBLOP][static_cast<int>(Direction::UpLeft)] = std::pair(sf::FloatRect(m_sprite.getPosition().x + (7 * MAPSCALE), m_sprite.getPosition().y + (6 * MAPSCALE), 42 * MAPSCALE, 35 * MAPSCALE), m_sprite.getGlobalBounds());
   
}
//setting the position of the character
void BlipAndBlop::setPosition(sf::Vector2f v)
{
    m_sprite.setPosition(v);
}
//move functtion
void BlipAndBlop::move(sf::Vector2f vec)
{
    m_sprite.move(vec);
}
//Die function that returns if the character is out of lifes 
bool BlipAndBlop::Die()
{
    if (m_lives == 0)
        return true;

    return false;
}
//function to get the sprite
sf::Sprite BlipAndBlop::getSprite() 
{
    return m_sprite;
}
//function to set the color
void BlipAndBlop::setColor(sf::Color c)
{
    m_sprite.setColor(c);

}
//function that returns if the characcter is fallin from the jump
bool BlipAndBlop::getIfGoingDown()
{
    return m_isGoingDown;
}
//setting that the character is falling
void BlipAndBlop::setIsGoingDown(const bool is)
{
    m_isGoingDown = is;
}
//update function
void BlipAndBlop::update(sf::Time deltaTime, sf::RenderWindow& window,const bool Gcollis, const sf::Vector2f whereTo) {
   

    HandleInput(window, m_sprite.getPosition());
   
    if (Gcollis && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        velocity.y = 0;
    else
        velocity.y = m_dy + (Gravity * deltaTime.asSeconds());  //physics rule for gravity
    m_dy = velocity.y;
    if (velocity.y > 0)
        m_isGoingDown = true;
    else
        m_isGoingDown = false;

    velocity.x *= deltaTime.asSeconds();
    
    //make sure the character isnt going throught the map limits
    if (m_sprite.getPosition().x <= 1 * MAPSCALE)
        m_sprite.setPosition(sf::Vector2f(1 * MAPSCALE, m_sprite.getPosition().y));
    if (m_sprite.getPosition().x >= 14216 * MAPSCALE)
        m_sprite.setPosition(sf::Vector2f(14216 * MAPSCALE, m_sprite.getPosition().y));


    m_sprite.move(velocity);



    //transperent when died
    if (m_timer.asSeconds() > 0)
    {
        isCharacterVisible = !isCharacterVisible;

        if (isCharacterVisible) {
            setColor(normalColor);
        }
        else {
           setColor(transparentColor);
        }
    }
    else
        setColor(normalColor);
}
//===================================================
//handle the key pressed by the user and get us the velocity we need of the pressed button
//and set the sprite texture the new one that determines the side of the movement
void BlipAndBlop::HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo)
{

    velocity.x = 0.f;
    velocity.y = 0.f;

    m_LastDir = m_dir;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -movementSpeed;
        m_headingLeftOrRight = Direction::Left;
        m_animation.direction(Direction::Left);
        m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
        m_dir = Direction::Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = movementSpeed;
        m_headingLeftOrRight = Direction::Right;
        m_animation.direction(Direction::Right);
        m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
        m_dir = Direction::Right;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (m_headingLeftOrRight == Direction::Left) {
            m_dir = Direction::UpHeadLeft;
            m_animation.direction(Direction::UpHeadLeft);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
        }
        else {
            m_dir = Direction::UpHeadRight;
            m_animation.direction(Direction::UpHeadRight);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        isJumping = true;
        m_dy = -4.5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (m_headingLeftOrRight == Direction::Left)
        {
            m_dir = Direction::DownHeadLeft;
            m_animation.direction(Direction::DownHeadLeft);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
        }
        else {
            m_dir = Direction::DownHeadRight;
            m_animation.direction(Direction::DownHeadRight);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_dir = Direction::DownLeft;
        m_headingLeftOrRight = Direction::Left;
        m_animation.direction(Direction::DownLeft);
        m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_dir = Direction::DownRight;
        m_headingLeftOrRight = Direction::Right;
        m_animation.direction(Direction::DownRight);
        m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_dir = Direction::UpRight;
        m_headingLeftOrRight = Direction::Right;
        m_animation.direction(Direction::UpRight);
        m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_headingLeftOrRight = Direction::Left;
        m_dir = Direction::UpLeft;
        m_animation.direction(Direction::UpLeft);
        m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    m_sprite.setScale(MAPSCALE, MAPSCALE);
}
//==================================
//just to get the speed if needed
float BlipAndBlop::GetSpeed()
{
    return movementSpeed;
}
//==================================
//set the direction of the character
void BlipAndBlop::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key, m_headingLeftOrRight))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//==================================
//set is jumping 
void BlipAndBlop::setIsJumping(const bool isit)
{
    isJumping = isit;
}
//==================================
//get the velocity of the character
sf::Vector2f BlipAndBlop::getVelocity() const
{
    return velocity;
}
//===================================
//set teh velocity of the character
void BlipAndBlop::setVelocity(const sf::Vector2f v)
{
    velocity = v;
}
//=======================================
//checking the ground collision with the character
bool BlipAndBlop::CheckGroundCollision()
{
    auto inn = getInnerBoundsForCollision();
    auto glb = getGlobalBoundsForCollision();

    if (m_sprite.getPosition().y >= GroundLimit - inn.height - (inn.top - glb.top))
    {
        m_sprite.setPosition(m_sprite.getPosition().x, GroundLimit - inn.height - (inn.top - glb.top));
        isJumping = false;
        return true;
    }
    isJumping = true;
    return false;
}
//=======================================================
//getting the inner bounds to check the collision with them
sf::FloatRect BlipAndBlop::getInnerBoundsForCollision()
{
    return m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)].first;
}
//==================================================
//getting the global bounds for the collision
sf::FloatRect BlipAndBlop::getGlobalBoundsForCollision()
{
    return m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)].second;
}
//===============================
//setting the animation texture 
void BlipAndBlop::setAnimationByDirection(Direction dir)
{
    m_dir = dir;
    m_animation.direction(dir);
    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
}
//===========================
//getting the direction if needed
Direction BlipAndBlop::getDir()
{
    return m_animation.Getdirection();
}
/// ======================================
//inner 3d array update
void BlipAndBlop::innerUpdater()
{
    auto currFullBound = m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)].second;
    auto currInnerBound = m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)].first;
    /*auto lastFullBound = m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_LastDir)].second;*/
    auto currStdev = sf::Vector2f(m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)].first.left - currFullBound.left, 
        m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)].first.top - currFullBound.top);
    /*auto lastStdev = sf::Vector2f(m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_LastDir)].first.left - lastFullBound.left,
        m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_LastDir)].first.top - lastFullBound.top);*/

    m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)] =
        std::pair(sf::FloatRect((m_sprite.getPosition().x + currStdev.x) , m_sprite.getPosition().y + currStdev.y,currInnerBound.width,currInnerBound.height)
            , m_sprite.getGlobalBounds());
}
/// =============================
//getting the inner bounds cells to draw them on the screen we needed it to check that its working correctly
sf::RectangleShape BlipAndBlop::getCurrInnerBoundToDrawOnly() const
{
    sf::FloatRect fr = m_InnerBoundsRectArr[m_WeapT][m_bOrb][static_cast<int>(m_dir)].first;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fr.width, fr.height));
    rectangle.setPosition(sf::Vector2f(fr.left, fr.top));
    rectangle.setFillColor(sf::Color::Red);
    return rectangle;
}
//=========================
//set hp
void BlipAndBlop::setHp()
{
    m_hp = 5;
}
//==========================
//to give the new character the old character hp 
void BlipAndBlop::SaveHp(int hp)
{
    m_hp = hp;
}
//==========================
//if there where a collison then hp -- 
void BlipAndBlop::LostHp(int GunDamage)
{
    m_hp -= GunDamage;
}
//=====================
//getting the character hp
int BlipAndBlop::GetHp()
{
    return m_hp;
}
/// ==========================
//if all the hp is gone then lifes-- 
void BlipAndBlop::LostLife()
{
    m_lives--;
}
//==============================
//get the character lives
int BlipAndBlop::GetLives()
{
    return m_lives;
}
//=================================
//set lives
void BlipAndBlop::setLivers()
{
    m_lives = 6;
}
//============================
//to give the new character the old character lives 
void BlipAndBlop::SaveLives(int live)
{
    m_lives = live;
}
//====================================
//set timer for the collision so that no one can make collision with it for 3 sec
void BlipAndBlop::setAfterCollisionTimer()
{
    m_timer = sf::seconds(3);
}

sf::Time BlipAndBlop::CheckAfterCollisionTimer()
{
    return m_timer;
}

void BlipAndBlop::minusTimer(sf::Time delta)
{

    m_timer -= delta;
}



