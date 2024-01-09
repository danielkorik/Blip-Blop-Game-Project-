#include"DefaultWeap.h"
#include<iostream>

//==================================
// ~constructor
DefaultWeap::DefaultWeap(/*sf::Vector2f pos, sf::Vector2f vel*/)
    :m_animation(Resources::instance().animationData(Resources::STANDARDBULLET), Direction::Right, m_bulletsSprite,0)

{
    m_bulletsSprite.setScale(1.5, 1.5);
}
//==================================
//draw function
void DefaultWeap::Draw(sf::RenderWindow& window)
{
    window.draw(m_bulletsSprite);
}
//==================================
//set the damage
void DefaultWeap::setDamage()
{
    m_damage = 2;
}
//==================================
//get the damage 
int DefaultWeap::getDamage()
{
    return m_damage;
}
//==================================
//check if out of ammo its unlimited here
bool DefaultWeap::isOutOFAmmo()
{
    return false;
}
//==================================
//update function
void DefaultWeap::update(sf::Time deltaTime)
{
    float gunForce = 1000;
    
    m_bulletsSprite.move(m_velocity * deltaTime.asSeconds() * gunForce );
}
//==================================
//get the sprite
sf::Sprite& DefaultWeap::GetBulletSprite()
{
    return m_bulletsSprite;
}
//==================================
//set the postion of the bullet to look exiting right from the sprite texture
void DefaultWeap::SetPosition(sf::Sprite p)
{

    if (m_dir == Direction::Right) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width) * p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y + (float(p.getLocalBounds().height / 2) * p.getScale().y)));
    }
    else if (m_dir == Direction::Left)
    {
        m_bulletsSprite.setPosition(p.getPosition().x - m_bulletsSprite.getGlobalBounds().width,
            (p.getPosition().y + (float(p.getLocalBounds().height / 2) * p.getScale().y)));
    }
    else if (m_dir == Direction::UpRight) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width) * p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y - m_bulletsSprite.getGlobalBounds().height));
    }
    else if (m_dir == Direction::UpLeft) {
        m_bulletsSprite.setPosition((p.getPosition().x + (p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y + (p.getScale().y * toVector(m_dir).y)));
    }
    else if (m_dir == Direction::DownLeft) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(m_bulletsSprite.getLocalBounds().width) * p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y + (float(p.getLocalBounds().height) * p.getScale().y * toVector(m_dir).y)));
    }
    else if (m_dir == Direction::DownRight) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width) * p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y + float(p.getGlobalBounds().height)));
    }
    else if (m_dir == Direction::DownHeadRight) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width / 2) * p.getScale().x - 7)),
            (p.getPosition().y + float(p.getGlobalBounds().height)));
    }
    else if (m_dir == Direction::DownHeadLeft) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width / 2) * p.getScale().x - 7)),
            (p.getPosition().y + float(p.getGlobalBounds().height)));
    }
    else if (m_dir == Direction::UpHeadRight) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width / 2) * p.getScale().x - 7)),
            (p.getPosition().y));
    }
    else if (m_dir == Direction::UpHeadLeft) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width / 2) * p.getScale().x - 7)),
            (p.getPosition().y));
    }
}
//==================================
//set the texture
void DefaultWeap::setTexture(Direction dir)
{
    m_animation.direction(dir);
    m_bulletsSprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
    
}
//==================================
//set the velocity
void DefaultWeap::setVelocity(sf::Vector2f vec)
{
    m_velocity = vec;
}
//==================================
//set the direction
void DefaultWeap::setDirection(Direction dir)
{
    m_dir = dir;
}
