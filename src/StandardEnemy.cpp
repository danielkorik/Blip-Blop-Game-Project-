#include"StandardEnemy.h"

std::optional<Direction> toDirection(sf::Keyboard::Key key, Direction headingTowards)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        return Direction::Left;
    case sf::Keyboard::Right:
        return Direction::Right;
    case sf::Keyboard::Up: {
        if (headingTowards == Direction::Left)
            return Direction::UpHeadLeft;
        else
            return Direction::UpHeadRight;
    }
    case sf::Keyboard::Space:
        return Direction::Stay;
    default:
        return {};
    }
}
//====================================
//~ctor
StandardEnemy::StandardEnemy()
	: m_animation(Resources::instance().animationData(Resources::STANDARDENEMY), Direction::Left, m_sprite,0)
{
	m_sprite.setScale(MAPSCALE, MAPSCALE);
  
}
//==========================================
//move function
void StandardEnemy::move(const sf::Vector2f v)
{
	m_sprite.move(v);
}
//==========================================
//die function
bool StandardEnemy::Die()
{
    if (m_hp <= 0)
        return true;

    return false;
}
//==========================================
//draw function
void StandardEnemy::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

//==========================================
void StandardEnemy::setIsJumping(const bool isit)
{
	isJumping = isit;
}
//==========================================
sf::Sprite StandardEnemy::getSprite()
{
	return m_sprite;
}
//==========================================
sf::Vector2f StandardEnemy::getVelocity() const
{
	return velocity;
}
//==========================================
void StandardEnemy::setVelocity(const sf::Vector2f v)
{
	velocity = v;
}
//==========================================
void StandardEnemy::setPosition(sf::Vector2f v)
{
	m_sprite.setPosition(v);
}
//==========================================
float StandardEnemy::GetSpeed()
{
	return movementSpeed;
}
//==========================================
//update function
void StandardEnemy::update(sf::Time deltaTime, sf::RenderWindow& window,const bool Gcollis, const sf::Vector2f whereTo)
{
    sf::Time t = sf::Time();
    t = sf::seconds(0.01f); // Use sf::seconds to set the time in seconds

    HandleInput(window, whereTo);

    if ((Gcollis && !isJumping))
        velocity.y = 0;
    else if (isJumping && (jumpStartedFrom - m_sprite.getPosition().y) >= 100) {
        velocity.y = 0;
        m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 1));
    }
    else
        velocity.y = m_dy + (staeneGravity * deltaTime.asSeconds());  //physics rule for gravity
    m_dy = velocity.y;
    if (velocity.y > 0)
        m_isGoingDown = true;
    else
        m_isGoingDown = false;
    velocity.x *= deltaTime.asSeconds();

    m_diePosVEc = sf::Vector2f(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y);

    m_animation.update(t);
    //looping on the die format textures 
    if (Die()) {

        setPosition(sf::Vector2f(m_diePosVEc.x - m_sprite.getGlobalBounds().width / 2, m_diePosVEc.y));
        if (c.getElapsedTime().asSeconds() > 0.1f) {
            m_dieSpriteCounter++;
            c.restart();
        }
    }
    m_sprite.move(velocity);
}
//==========================================
//handle the inputs function and the directions
void StandardEnemy::HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo)
{
    velocity.x = 0.f;
    velocity.y = 0.f;
    if (m_dir != Direction::Stay) {


        if (m_sprite.getPosition().x > whereTo.x) {
            velocity.x = -movementSpeed;
            m_headingLeftOrRight = Direction::Left;
            if (!isJumping) {

                m_animation.direction(Direction::Left);
                m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
                m_dir = Direction::Left;
            }
            if (m_animation.Getdirection() == Direction::UpHeadRight && isJumping) {
                m_animation.direction(Direction::UpHeadLeft);
                m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
                m_dir = Direction::UpHeadLeft;
            }
        }
        if (m_sprite.getPosition().x < whereTo.x) {
            velocity.x = movementSpeed;
            m_headingLeftOrRight = Direction::Right;
            if (!isJumping) {
                m_animation.direction(Direction::Right);
                m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
                m_dir = Direction::Right;
            }
            if (m_animation.Getdirection() == Direction::UpHeadLeft && isJumping) {
                m_animation.direction(Direction::UpHeadRight);
                m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
                m_dir = Direction::UpHeadRight;
            }
        }
        if (m_sprite.getPosition().y > whereTo.y && !isJumping) {
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
        }
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
bool StandardEnemy::CheckGroundCollision()
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
bool StandardEnemy::getIfGoingDown()
{
	return m_isGoingDown;
}
//==========================================
void StandardEnemy::direction(sf::Keyboard::Key key)
{
	if (auto dir = toDirection(key, m_headingLeftOrRight))
	{
		m_dir = *dir;
		m_animation.direction(*dir);
	}
}
//==========================================
Direction StandardEnemy::getDir()
{
	return m_dir;
}
//==========================================
void StandardEnemy::setAnimationByDirection(Direction dir)
{
	m_dir = dir;
	m_animation.direction(dir);
	m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
}
//==========================================
void StandardEnemy::setHp()
{
    m_hp = 3;
}
//==========================================
void StandardEnemy::LostHp(int GunDamage)
{
    m_hp -= GunDamage;
}
//==========================================
int StandardEnemy::GetHp()
{
    return m_hp;
}
//==========================================
void StandardEnemy::LostLife()
{
    m_lives--;
}
//==========================================
int StandardEnemy::GetLives()
{
    return m_lives;
}
//==========================================
void StandardEnemy::DieTimerReset()
{
    m_timer.restart();
}
//==========================================
int StandardEnemy::getDamage() const
{
    return m_damage;
}
//==========================================
void StandardEnemy::setDamage(int dmg)
{
    m_damage = dmg;
}
//==========================================
void StandardEnemy::setDied()
{
    m_died = true;
}
//==========================================
bool StandardEnemy::getDied() const
{
    return m_died;
}
//==========================================
int StandardEnemy::getDieSpriteCount() const
{
    return m_dieSpriteCounter;
}
