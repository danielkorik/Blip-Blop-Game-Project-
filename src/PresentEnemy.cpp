#include "PresentEnemy.h"

std::optional<Direction> toDiirection(sf::Keyboard::Key key, Direction headingTowards)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        return Direction::Left;
    case sf::Keyboard::Right:
        return Direction::Right;
    case sf::Keyboard::Space:
        return Direction::Stay;
    default:
        return {};
    }
}
//====================================
//~ctor
PresentEnemy::PresentEnemy()
    : m_animation(Resources::instance().animationData(Resources::PRESENTENEMY), Direction::Left, m_sprite, 0)
{
    m_sprite.setScale(MAPSCALE, MAPSCALE);

}
//==========================================
//move function
void PresentEnemy::move(const sf::Vector2f v)
{
    m_sprite.move(v);
}
//==========================================
//die function
bool PresentEnemy::Die()
{
    if (m_hp <= 0)
        return true;

    return false;
}
//==========================================
//draw function
void PresentEnemy::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

//==========================================
void PresentEnemy::setIsJumping(const bool isit)
{
    isJumping = isit;
}
//==========================================
sf::Sprite PresentEnemy::getSprite()
{
    return m_sprite;
}
//==========================================
sf::Vector2f PresentEnemy::getVelocity() const
{
    return velocity;
}
//==========================================
void PresentEnemy::setVelocity(const sf::Vector2f v)
{
    velocity = v;
}
//==========================================
void PresentEnemy::setPosition(sf::Vector2f v)
{
    m_sprite.setPosition(v);
}
//==========================================
float PresentEnemy::GetSpeed()
{
    return movementSpeed;
}
//==========================================
//update function
void PresentEnemy::update(sf::Time deltaTime, sf::RenderWindow& window, const bool Gcollis, const sf::Vector2f whereTo)
{
    //handle the inputs
    HandleInput(window, whereTo);
    //check if there is ground collision
    if (Gcollis)
        velocity.y = 0;
    else
        velocity.y = m_dy + (m_Gravity * deltaTime.asSeconds());  //physics rule for gravity
    m_dy = velocity.y;
    if (velocity.y > 0)     //this means it was jumping and now it will falls
        m_isGoingDown = true;
    else
        m_isGoingDown = false;
    velocity.x *= deltaTime.asSeconds();

    //timer for the texture updates
    sf::Time t = sf::Time();
    t = sf::seconds(0.01f); // Use sf::seconds to set the time in seconds
    m_animation.update(t);

    m_diePosVEc = sf::Vector2f(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y);

    //looping on the die format textures 
    if (Die()) {

        setPosition(sf::Vector2f(m_diePosVEc.x - m_sprite.getGlobalBounds().width / 2, m_diePosVEc.y));
        if (c.getElapsedTime().asSeconds() > 0.3f) {
            m_dieSpriteCounter++;
            c.restart();
        }
    }
    //move
    m_sprite.move(velocity);
}
//==========================================
//handle the inputs function and the directions
void PresentEnemy::HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo)
{
    velocity.x = 0.f;
    velocity.y = 0.f;
    if (m_dir != Direction::Stay) {


        if (m_sprite.getPosition().x > whereTo.x) {
            velocity.x = -movementSpeed;
            m_headingLeftOrRight = Direction::Left;
            m_animation.direction(Direction::Left);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
            m_dir = Direction::Left;
            }
        if (m_sprite.getPosition().x < whereTo.x) {
            velocity.x = movementSpeed;
            m_headingLeftOrRight = Direction::Right;
            m_animation.direction(Direction::Right);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
            m_dir = Direction::Right;
        }
        /*if (m_sprite.getPosition().y > whereTo.y && !isJumping) {
            if (m_sprite.getPosition().x > whereTo.x) {
                isJumping = true;
                m_dy = -3;
                jumpStartedFrom = m_sprite.getPosition().y;
                m_dir = Direction::UpHeadLeft;
                m_animation.direction(Direction::UpHeadLeft);
                m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
            }
            else {
                isJumping = true;
                m_dy = -3;
                jumpStartedFrom = m_sprite.getPosition().y;
                m_dir = Direction::UpHeadRight;
                m_animation.direction(Direction::UpHeadRight);
                m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
            }
        }*/
    }
    else {
        setAnimationByDirection(Direction::Stay);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    m_sprite.setScale(MAPSCALE, MAPSCALE);
}
//==========================================
//check collision with the ground
bool PresentEnemy::CheckGroundCollision()
{
    if (m_sprite.getPosition().y >= GroundLimit - m_sprite.getGlobalBounds().height)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, GroundLimit - m_sprite.getGlobalBounds().height);
        isJumping = false;
        return true;
    }
    isJumping = true;
    return false;
}
//==========================================
bool PresentEnemy::getIfGoingDown()
{
    return m_isGoingDown;
}
//==========================================
void PresentEnemy::direction(sf::Keyboard::Key key)
{
    if (auto dir = toDiirection(key, m_headingLeftOrRight))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//==========================================
Direction PresentEnemy::getDir()
{
    return m_dir;
}
//==========================================
void PresentEnemy::setAnimationByDirection(Direction dir)
{
    m_dir = dir;
    m_animation.direction(dir);
    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
}
//==========================================
void PresentEnemy::setHp()
{
    m_hp = 1;
}
//==========================================
void PresentEnemy::LostHp(int GunDamage)
{
    m_hp -= GunDamage;
}
//==========================================
int PresentEnemy::GetHp()
{
    return m_hp;
}
//==========================================
void PresentEnemy::LostLife()
{
    m_lives--;
}
//==========================================
int PresentEnemy::GetLives()
{
    return m_lives;
}
//==========================================
void PresentEnemy::DieTimerReset()
{
    m_timer.restart();
}
//==========================================
int PresentEnemy::getDamage() const
{
    return m_damage;
}
//==========================================
void PresentEnemy::setDamage(int dmg)
{
    m_damage = dmg;
}
//==========================================
void PresentEnemy::setDied()
{
    m_died = true;
}
//==========================================
bool PresentEnemy::getDied() const
{
    return m_died;
}
//==========================================
int PresentEnemy::getDieSpriteCount() const
{
    return m_dieSpriteCounter;
}
