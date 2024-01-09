#include"ShotgunWeap.h"
#include<iostream>

//====================================
///~c-torr
ShotgunWeap::ShotgunWeap(/*sf::Vector2f pos, sf::Vector2f vel*/)
    :m_animation(Resources::instance().animationData(Resources::SHOTGUNBULLET), Direction::Right, m_bulletsSprite,0)

{
    m_bulletsSprite.setScale(1.87, 1.87);

}
//====================================
///draw function
void ShotgunWeap::Draw(sf::RenderWindow& window)
{
    static int index = 0;
    static float frame = 0.0f, frameSpeed = 0.2f;
    const int changeCount = 5;

    frame += frameSpeed;
    if (frame > changeCount)
    {
        frame -= changeCount;
        ++index;
        if (index >= 2) { index %= 2; }
    }
    for (auto shotGun : m_ShotGunSpriteVector) {

        window.draw(shotGun[index]);
    }
}
//====================================

//set damage
void ShotgunWeap::setDamage()
{
    m_damage = 5;
}
//====================================
//get damage
int ShotgunWeap::getDamage()
{
    return m_damage;
}
//====================================
//check if its out of ammo
bool ShotgunWeap::isOutOFAmmo()
{
    if (m_ammo > 0)
        return false;

    return true;
}
//====================================
//update
void ShotgunWeap::update(sf::Time deltaTime)
{

    float gunForce = 1000;
    m_bulletsSprite.move(m_velocity * deltaTime.asSeconds() * gunForce);

}
//====================================
//get bullet sprite
sf::Sprite& ShotgunWeap::GetBulletSprite()
{
    return m_bulletsSprite;
}
//====================================
//set postion
void ShotgunWeap::SetPosition(sf::Sprite p)
{

    if (m_dir == Direction::Right) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width) * p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y + (float(p.getLocalBounds().height / 3) * p.getScale().y)));
    }
    else if (m_dir == Direction::Left)
    {
        m_bulletsSprite.setPosition(p.getPosition().x - m_bulletsSprite.getGlobalBounds().width,
            (p.getPosition().y + (float(p.getLocalBounds().height / 3) * p.getScale().y)));
    }
    else if (m_dir == Direction::UpRight) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width) * p.getScale().x * toVector(m_dir).x)),
            (p.getPosition().y - m_bulletsSprite.getGlobalBounds().height));
    }
    else if (m_dir == Direction::UpLeft) {
        m_bulletsSprite.setPosition((p.getPosition().x + ( p.getScale().x * toVector(m_dir).x)),
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
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width / 3) * p.getScale().x - 7)),
            (p.getPosition().y + float(p.getGlobalBounds().height)));
    }
    else if (m_dir == Direction::DownHeadLeft) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width / 3) * p.getScale().x - 7)),
            (p.getPosition().y + float(p.getGlobalBounds().height)));
    }
    else if (m_dir == Direction::UpHeadRight) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width / 3) * p.getScale().x - 7)),
            (p.getPosition().y ));
    }
    else if (m_dir == Direction::UpHeadLeft) {
        m_bulletsSprite.setPosition((p.getPosition().x + (float(p.getLocalBounds().width /3) * p.getScale().x - 7)),
            (p.getPosition().y ));
    }
}
//====================================
//set texture of the bullet
void ShotgunWeap::setTexture(Direction dir)
{
    m_animation.direction(dir);
    m_bulletsSprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());

}

void ShotgunWeap::setVelocity(sf::Vector2f vec)
{
    m_velocity = vec;
}

void ShotgunWeap::setDirection(Direction dir)
{
    m_dir = dir;
}
//====================================
//set the sprite pos on the map
void ShotgunWeap::SetSpritesPos()
{

        sprites[0].setPosition(2500 * MAPSCALE , 163 * MAPSCALE);
        sprites[1].setPosition(2500 * MAPSCALE, 163 * MAPSCALE);
        sprites[0].setScale(1.87, 1.87);
        sprites[1].setScale(1.57, 1.57);
        std::array<sf::Sprite, 2> vSprite = { sprites[0], sprites[1] };

        m_ShotGunSpriteVector.push_back(vSprite);



        m_ShotGunSpriteVector.push_back(vSprite);
        sprites[0].setPosition(9714 * MAPSCALE, 182 * MAPSCALE);
        sprites[1].setPosition(9714 * MAPSCALE, 182 * MAPSCALE);
        sprites[0].setScale(1.87, 1.87);
        sprites[1].setScale(1.57, 1.57);
        vSprite = { sprites[0], sprites[1] };

        m_ShotGunSpriteVector.push_back(vSprite);
        sprites[0].setPosition(14059 * MAPSCALE, 310 * MAPSCALE);
        sprites[1].setPosition(14059 * MAPSCALE, 310 * MAPSCALE);
        sprites[0].setScale(1.87, 1.87);
        sprites[1].setScale(1.57, 1.57);
        vSprite = { sprites[0], sprites[1] };

        m_ShotGunSpriteVector.push_back(vSprite);

}

void ShotgunWeap::AddAmmo(int num)
{
    m_ammo += num;
}
//====================================
//set the sprite gun pic texture
void ShotgunWeap::setSpritesOfGun()
{
    sf::IntRect rec = sf::IntRect(sf::Vector2i(100, 592), sf::Vector2i(65, 12));

    if (!m_SHotGuntexture.loadFromFile("characterSprite.png", rec))
    {
        throw std::runtime_error("Can't load ShoutGun Texture\n");

    }
    sprites[0].setTexture(m_SHotGuntexture);

    rec = sf::IntRect(sf::Vector2i(100, 686), sf::Vector2i(53, 12));

    if (!m_SHotGuntexture.loadFromFile("characterSprite.png", rec))
    {
        throw std::runtime_error("Can't load ShoutGun Texture\n");

    }
    sprites[1].setTexture(m_SHotGuntexture);

    SetSpritesPos();
}
//====================================
//get the array of the pic sprites
std::vector<std::array<sf::Sprite, 2>>& ShotgunWeap::getShotGunSpriteVec()
{
    return m_ShotGunSpriteVector;
}

void ShotgunWeap::clearVec()
{
    m_ShotGunSpriteVector.clear();
}


