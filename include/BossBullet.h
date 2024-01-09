#ifndef _BOSSBUL
#define _BOSSBUL

#include"Weapon.h"
#include<array>


class BossBullet : public Weapon {
public:
	BossBullet();
	void Draw(sf::RenderWindow& window) {};
	void setDamage();
	int getDamage();
	bool isOutOFAmmo();
	void update(sf::Time deltaTime);
	sf::Sprite& GetBulletSprite();
	void SetPosition(sf::Sprite p);
	void setTexture(Direction dir);
	void setVelocity(sf::Vector2f vec);
	void setDirection(Direction dir);
	void SetSpritesPos() {};
	int getAmmo() { return m_ammo; }
	void setAmmo(int ammo) { m_ammo = ammo; }

private:
	int m_damage = 2;
	int m_ammo = 50;
	sf::Texture m_BulletsTexture;
	sf::Sprite m_bulletsSprite;
	Animations m_animation;
	sf::Vector2f m_position, m_velocity;
	float m_dx = 0;
	Direction m_dir = Direction::DownRight;
	sf::Texture m_RifleGuntexture = sf::Texture();
	sf::Sprite sprites[2];
};

#endif