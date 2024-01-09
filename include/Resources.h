#pragma once

#include "AnimationData.h"
#include"Globals.h"
#include <SFML\Audio.hpp>
#include <SFML/graphics.hpp>
#include <vector>

// ~Resources class
class Resources
{
public:
    //enum objects
    enum Objects
    {
        BLIP,
        STANDARDBULLET,
        SHOTGUNCHAR,
        SHOTGUNBULLET,
        RIFLEGUNCHAR,
        RIFLEGUNBULLET,
        STANDARDENEMY,
        FORKENEMY,
        BLOP,
        SHOTGUNCHARBLOP,
        RIFLEGUNCHARBLOP,
        BOSS,
        BOSSBULL,
        PRESENTENEMY,
        Max,
    };

    static Resources& instance();   //instance 
    Resources();    //c-tor
    ~Resources();


    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    //getting menu music and background
    sf::Music& getMenuMusic();

    sf::Music& getGameMusic();
        
    sf::SoundBuffer* getBuffer(const std::string path);

    const sf::Texture& texture(int png) const {
        if(!png)
            return m_texture;
        
        return m_texture2;
    }
    AnimationData& animationData(Objects object) { return m_data[object]; }
    void  PopResourcesVectors();
private:
    sf::Music music;
    sf::Music GameMusic;
    std::unordered_map<std::string, sf::SoundBuffer*> sound_buffers;
    sf::Texture m_texture;
    sf::Texture m_texture2;
    std::vector<AnimationData> m_data;


};
