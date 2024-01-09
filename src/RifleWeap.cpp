

#include"RifleWeap.h"

#include<iostream>

//====================================
//~c-tor
RifleWeap::RifleWeap()
    :m_animation(Resources::instance().animationData(Resources::RIFLEGUNBULLET), Direction::Right, m_bulletsSprite,0)

{
    m_bulletsSprite.setScale(1.87, 1.87);

}
//====================================
//draw function 
void RifleWeap::Draw(sf::RenderWindow& window)
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
    for (auto r : m_RifleGunSpriteVector)
    {
        window.draw(r[index]);
    }

}
//====================================
//set damage
void RifleWeap::setDamage()
{
    m_damage = 2;
}
//====================================
//get Damage
int RifleWeap::getDamage()
{
    return m_damage;
}
//====================================
//check if its out of ammo
bool RifleWeap::isOutOFAmmo()
{
    if (m_ammo > 0)
        return false;

    return true;
}
//====================================
//udate
void RifleWeap::update(sf::Time deltaTime)
{

    float gunForce = 1000;

    m_bulletsSprite.move(m_velocity * deltaTime.asSeconds() * gunForce);

}
//====================================
//get bullet sprite
sf::Sprite& RifleWeap::GetBulletSprite()
{
    return m_bulletsSprite;
}
//====================================
//set postion
void RifleWeap::SetPosition(sf::Sprite p)
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
//====================================
//set texture
void RifleWeap::setTexture(Direction dir)
{
    m_animation.direction(dir);
    m_bulletsSprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());

}
//====================================
//set velocity
void RifleWeap::setVelocity(sf::Vector2f vec)
{
    m_velocity = vec;
}

void RifleWeap::setDirection(Direction dir)
{
    m_dir = dir;
}
//====================================
//set the rifle pic on the map 
void RifleWeap::SetSpritesPos()
{

        sprites[0].setPosition(4241 * MAPSCALE , 209 *MAPSCALE);
        sprites[1].setPosition(4241 * MAPSCALE , 209 * MAPSCALE);
        sprites[0].setScale(1.87, 1.87);
        sprites[1].setScale(1.57, 1.57);
        std::array<sf::Sprite, 2> vSprite = { sprites[0], sprites[1] };

        m_RifleGunSpriteVector.push_back(vSprite);


        sprites[0].setPosition(7136 * MAPSCALE, 217 * MAPSCALE);
        sprites[1].setPosition(7136 * MAPSCALE, 217 * MAPSCALE);
        sprites[0].setScale(1.87, 1.87);
        sprites[1].setScale(1.57, 1.57);
        vSprite = { sprites[0], sprites[1] };

        m_RifleGunSpriteVector.push_back(vSprite);



        sprites[0].setPosition(13529 * MAPSCALE, 310 * MAPSCALE);
        sprites[1].setPosition(13529 * MAPSCALE, 310 * MAPSCALE);
        sprites[0].setScale(1.87, 1.87);
        sprites[1].setScale(1.57, 1.57);
         vSprite = { sprites[0], sprites[1] };

        m_RifleGunSpriteVector.push_back(vSprite);
}

void RifleWeap::fireAmmo()
{
    m_ammo--;
}

void RifleWeap::AddAmmo(int num)
{
    m_ammo += num;
}
//====================================
//seting the sprite textures
void RifleWeap::setSpritesOfGun()
{
    sf::IntRect rec = sf::IntRect(sf::Vector2i(186, 607), sf::Vector2i(53, 14));

    if (!m_RifleGuntexture.loadFromFile("characterSprite.png", rec))
    {
        throw std::runtime_error("Can't load ShoutGun Texture\n");

    }
    //m_ShotGunSprite[0].setTexture(m_SHotGuntexture);
    sprites[0].setTexture(m_RifleGuntexture);

    rec = sf::IntRect(sf::Vector2i(186, 685), sf::Vector2i(53, 14));

    if (!m_RifleGuntexture.loadFromFile("characterSprite.png", rec))
    {
        throw std::runtime_error("Can't load ShoutGun Texture\n");

    }
    //m_ShotGunSprite[1].setTexture(m_SHotGuntexture);
    sprites[1].setTexture(m_RifleGuntexture);

    SetSpritesPos();
}
//gettign the array of the sprites 
std::vector<std::array<sf::Sprite, 2>>& RifleWeap::getGunSpriteVec()
{
    return m_RifleGunSpriteVector;
}
//====================================
//clear the vectors
void RifleWeap::clearVec()
{
    m_RifleGunSpriteVector.clear();
}

