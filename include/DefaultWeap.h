#ifndef _DEFAULTWEAPON
#define _DEFAULTWEAPON
#include"Weapon.h"

//class DefaultWeap that inheritance from Weapon
class DefaultWeap :public Weapon {
public:
	DefaultWeap();
	void Draw(sf::RenderWindow& window);
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

private:
	int m_damage = 1;
	int m_ammo = -1;
	sf::Texture m_BulletsTexture;
	sf::Sprite m_bulletsSprite;
	Animations m_animation;
	sf::Vector2f m_position, m_velocity ;
	float m_dx = 0;
	Direction m_dir;
};

#endif