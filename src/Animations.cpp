#include "Animations.h"

//time of animations frames
const auto AnimationTime = sf::seconds(0.5f);

//animation constructor for moveable characters
Animations::Animations(AnimationData& data, Direction dir, sf::Sprite& sprite,int png)
    :m_data(data), m_dir(dir), m_sprite(sprite)
{
    m_sprite.setTexture(Resources::instance().texture(png));
    update();
}

//this function is for checking if there is any change in the 
//movement of the character
void Animations::direction(Direction dir)
{
    if (m_dir != dir)
        m_index = 0;
    m_dir = dir;
    update();
}
//both next functions are for changes in the animations while walking
//by indexes in sprite sheet
void Animations::update(sf::Time delta)
{
        m_elapsed += delta;
        if (m_elapsed >= AnimationTime )
        {
            m_elapsed -= AnimationTime;
            ++m_index;
            m_index %= m_data.m_data.find(m_dir)->second.size();
            update();
        }
    
}
//update the texture of the animation
void Animations::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
}
//=======================
//get the sprite
sf::Sprite Animations::GetAnimationSprite() {
    return m_sprite;
}
//================
//get direction
Direction Animations::Getdirection()
{
    return m_dir;

}