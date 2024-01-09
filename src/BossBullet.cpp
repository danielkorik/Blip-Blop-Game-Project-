#include"BossBullet.h"
#include<iostream>

//==================================
// ~constructor
BossBullet::BossBullet()
    :m_animation(Resources::instance().animationData(Resources::BOSSBULL), Direction::Left, m_bulletsSprite,1)

{
    m_bulletsSprite.setScale(1.87, 1.87);
}
//==================================
//set damage
void BossBullet::setDamage()
{
    m_damage = 2;
}
//==================================
//get damage
int BossBullet::getDamage()
{
    return m_damage;
}
//==================================
//check if its out of emmo
bool BossBullet::isOutOFAmmo()
{
    if (m_ammo > 0)
        return false;

    return true;
}
//==================================
//update function
void BossBullet::update(sf::Time deltaTime)
{
    float gunForce = 1000;
    m_bulletsSprite.move(m_velocity * deltaTime.asSeconds() * gunForce);
}
//==================================
//get the sprite 
sf::Sprite& BossBullet::GetBulletSprite()
{
    return m_bulletsSprite;
}
//==================================
//set the position of the bullet
void BossBullet::SetPosition(sf::Sprite p)
{
    if (m_dir == Direction::Right) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width) * p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y + (float(p.getLocalBounds().height / 3) * p.getScale().y)));
    }
    else
    {
        m_bulletsSprite.setPosition(p.getPosition().x - m_bulletsSprite.getGlobalBounds().width,
            (p.getPosition().y + (float(p.getLocalBounds().height / 3) * p.getScale().y /** toVector(m_dir).y*/)));
    }
}
//==================================
//set the texturre 
void BossBullet::setTexture(Direction dir)
{
    m_animation.direction(dir);
    m_bulletsSprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
}
//==================================
//set the velocity
void BossBullet::setVelocity(sf::Vector2f vec)
{
    m_velocity = vec;
}
//==================================
//set Direction
void BossBullet::setDirection(Direction dir)
{
    m_dir = dir;
}