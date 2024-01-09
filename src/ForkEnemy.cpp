#include"ForkEnemy.h"

//==================================
// ~constructor
ForkEnemy::ForkEnemy()
	: m_animation(Resources::instance().animationData(Resources::FORKENEMY), Direction::Left, m_sprite,0)
{
    m_sprite.setScale(MAPSCALE, MAPSCALE);

}
//==================================
//die functtion that checks if its died 
bool ForkEnemy::Die()
{
    if (m_hp <= 0)
        return true;

    return false;
}
//==================================
//move function
void ForkEnemy::move(sf::Vector2f vec)
{
    m_sprite.move(vec);
}
//==================================
//die format function to set the direction that been used for the die texturres
void ForkEnemy::DieFormat()
{
    if (m_dir == Direction::Left)
        m_dir = Direction::DownLeft;
    else
        m_dir = Direction::DownRight;
    //sets the speed more faster because thats how in the real game
    movementSpeed = 600.f;
}
//==================================
//get sprite
sf::Sprite ForkEnemy::getSprite()
{
    return m_sprite;
}
//==================================
//get the velocity
sf::Vector2f ForkEnemy::getVelocity() const
{
    return velocity;
}
//==================================
//set the velocity
void ForkEnemy::setVelocity(const sf::Vector2f v)
{
    velocity = v;
}
//==================================
//set the postion
void ForkEnemy::setPosition(sf::Vector2f v)
{
    m_sprite.setPosition(v);
}
//==================================
//get the speed
float ForkEnemy::GetSpeed()
{
    return movementSpeed;
}
//==================================
//update function
void ForkEnemy::update(sf::Time deltaTime, sf::RenderWindow& window,/* sf::Clock clock,*/ const bool Gcollis, const sf::Vector2f whereTo)
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
    //move
    m_sprite.move(velocity);
}
//==================================
//handle the inputs function
void ForkEnemy::HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo)
{
    velocity.x = 0.f;
    velocity.y = 0.f;
    if(m_dir == Direction::Right || m_dir == Direction::DownRight)
        velocity.x = movementSpeed;
    else
        velocity.x = -movementSpeed;
    m_animation.direction(m_dir);
    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
            
       
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    m_sprite.setScale(MAPSCALE, MAPSCALE);
}
//==================================
//check collision with the ground function
bool ForkEnemy::CheckGroundCollision()
{
    if (m_sprite.getPosition().y >= GroundLimit - m_sprite.getGlobalBounds().height)
    {
        m_sprite.setPosition(m_sprite.getPosition().x, GroundLimit - m_sprite.getGlobalBounds().height);
        return true;
    }
    return false;
}
//==================================
//get if its going dows
bool ForkEnemy::getIfGoingDown()
{
    return m_isGoingDown;
}
//==================================
//set direction
void ForkEnemy::direction(sf::Keyboard::Key key)
{
    m_animation.direction(m_dir);
}
//==================================
//get the direction
Direction ForkEnemy::getDir()
{
    return m_dir;
}
//==================================
//set the texture of it 
void ForkEnemy::setAnimationByDirection(Direction dir)
{
    m_dir = dir;
    m_animation.direction(dir);
    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
}
//==================================
//set the hp
void ForkEnemy::setHp()
{
    m_hp = 1;
}
//==================================
//lost hp 
void ForkEnemy::LostHp(int GunDamage)
{
    m_hp -= GunDamage;
}
//==================================
///get the hp
int ForkEnemy::GetHp()
{
    return m_hp;
}
//==================================
//lost life 
void ForkEnemy::LostLife()
{
    m_lives--;
}
//==================================
//get the lives
int ForkEnemy::GetLives()
{
    return m_lives;
}
//==================================
//set the damage 
void ForkEnemy::setDamage(int dmg)
{
    m_damage = dmg;
}
//==================================
//get the damage
int ForkEnemy::getDamage() const
{
    return m_damage;
}
//==================================
//set died after all the textures of the die format
void ForkEnemy::setDied()
{
    m_died = true;
}
//==================================
//get died condition
bool ForkEnemy::getDied() const
{
    return m_died;
}
