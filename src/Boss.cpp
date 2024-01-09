#include"Boss.h"

//getting the direction of the key pressed
std::optional<Direction> tDirection(sf::Keyboard::Key keys, Direction headingTowards)
{
    switch (keys)
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
//===================================
//constructor
Boss::Boss()
	: m_animation(Resources::instance().animationData(Resources::BOSS), Direction::Left, m_sprite,1)
{
	m_sprite.setScale(MAPSCALE, MAPSCALE);

}
//==================================
//move function
void Boss::move(const sf::Vector2f v)
{
	m_sprite.move(v);
}
//==================================
//die function that returns true if the hp <=0
bool Boss::Die()
{
	if (m_hp <= 0)
		return true;

	return false;
}
//==================================
//Draw functtion to draw the sprite
void Boss::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
//==================================
//setting that the character is jumping 
void Boss::setIsJumping(const bool isit)
{
    isJumping = isit;
}
//==================================
//geting the sprite 
sf::Sprite Boss::getSprite()
{
    return m_sprite;
}
//==================================
//function to get the velocity
sf::Vector2f Boss::getVelocity() const
{
    return velocity;
}
//==================================
///function to set the velocity
void Boss::setVelocity(const sf::Vector2f v)
{
    velocity = v;
}
//==================================
//function to set the postion
void Boss::setPosition(sf::Vector2f v)
{
    m_sprite.setPosition(v);
}
//==================================
//function to get the speed
float Boss::GetSpeed()
{
    return movementSpeed;
}
//==================================
//update function
void Boss::update(sf::Time deltaTime, sf::RenderWindow& window, const bool Gcollis, const sf::Vector2f whereTo)
{
    sf::Time t = sf::Time();
    t = sf::seconds(0.01f); // Use sf::seconds to set the time in seconds
    //cooldown timer for the bullet of the boss
    m_coolDownTimer -= deltaTime;
    //if its around the time to shot then he needs to stop
    if (m_coolDownTimer >= sf::seconds(6.3) && m_whileSkill) {
        velocity = { 0,0 };
    }
    else {
        HandleInput(window, whereTo);
    }
    //setting the time frame of the textures 
    if(m_coolDownTimer <= sf::seconds(7) && m_coolDownTimer >= sf::seconds(6.3) && m_whileSkill)
        t = sf::seconds(0.1f);
    //if its not jumping
    if ((Gcollis && !isJumping))
        velocity.y = 0;
    else if (isJumping && (jumpStartedFrom - m_sprite.getPosition().y) >= WINDOW_HEIGHT/2) {
        velocity.y = 0;
        m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 1));
    }
    else
        velocity.y = m_dy + (BossGravity * deltaTime.asSeconds());  //physics rule for gravity
    m_dy = velocity.y;
    if (velocity.y > 0)
        m_isGoingDown = true;
    else
        m_isGoingDown = false;
    velocity.x *= deltaTime.asSeconds();
    //getting the pos where it died
    m_diePosVEc = sf::Vector2f(m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2, m_sprite.getPosition().y);

    m_animation.update(t);
    if (Die()) {
        //run on  the die textures 
        setPosition(sf::Vector2f(m_diePosVEc.x - m_sprite.getGlobalBounds().width / 2, m_diePosVEc.y));
        if (c.getElapsedTime().asSeconds() > 0.1f) {
            m_dieSpriteCounter++;
            c.restart();
        }
    }
    m_sprite.move(velocity);
}
//================================================
//handle the inputs of the user and set the velocity 
void Boss::HandleInput(sf::RenderWindow& window, const sf::Vector2f whereTo)
{
    velocity.x = 0.f;
    velocity.y = 0.f;
    //if its going to fire then we put the texture of the firing and wont make any velocity
    if (m_coolDownTimer <= sf::seconds(0))
    {
        if (m_sprite.getPosition().x > whereTo.x) {
            m_headingLeftOrRight = Direction::Left;
            m_animation.direction(Direction::DownLeft);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
            m_dir = Direction::DownLeft;
        }
        else {
            m_headingLeftOrRight = Direction::Right;
            m_animation.direction(Direction::DownRight);
            m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
            m_dir = Direction::DownRight;
        }
        m_coolDownTimer = sf::seconds(7);
        m_whileSkill = true;
        m_readyToFire = false;
    }
    else { //else if is going regular and moving and still not time to shoot
        if (m_whileSkill)
            m_readyToFire = true;
        m_whileSkill = false;
        if (m_dir != Direction::DownHeadLeft && m_dir != Direction::DownHeadRight) {

            //checking the x position of the blip or blop and if its > then it needs the right texture and direction
            //if its < then it need the left direction with left texture and left velocity
            if (m_sprite.getPosition().x > whereTo.x) {
                velocity.x = -movementSpeed;
                m_headingLeftOrRight = Direction::Left;
                if (!isJumping) {

                    m_animation.direction(Direction::Left);
                    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
                    m_dir = Direction::Left;
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

            }//if it worked fine we add the pic of jump we need to change right and left to headupright and left
            if (m_sprite.getPosition().y > whereTo.y && !isJumping) {
                if (m_sprite.getPosition().x > whereTo.x) {
                    isJumping = true;
                    m_dy = -4.5;
                    jumpStartedFrom = m_sprite.getPosition().y;
                    m_dir = Direction::Left;
                    m_animation.direction(Direction::Left);
                    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
                }
                else {
                    isJumping = true;
                    m_dy = -4.5;
                    jumpStartedFrom = m_sprite.getPosition().y;
                    m_dir = Direction::Right;
                    m_animation.direction(Direction::Right);
                    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
                }
            }
        }
        else { //setting the die texture we used these names of dirrection to not add more because there no need for them here so we
            //sed them for the die textures
            if (m_dir == Direction::DownHeadLeft)
                setAnimationByDirection(Direction::DownHeadLeft);
            else
                setAnimationByDirection(Direction::DownHeadRight);

        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    m_sprite.setScale(MAPSCALE, MAPSCALE);
}
//===========================
//checking the collision with the ground
bool Boss::CheckGroundCollision()
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
//======================
//checking if the boss is falling
bool Boss::getIfGoingDown()
{
    return m_isGoingDown;
}
//==================================
//set the direction of the boss
void Boss::direction(sf::Keyboard::Key keys)
{
    if (auto dir = tDirection(keys, m_headingLeftOrRight))
    {
        m_dir = *dir;
        m_animation.direction(*dir);
    }
}
//=======================================
//getting the direction
Direction Boss::getDir()
{
    return m_dir;
}
//==================================
//setting the texture and direction of the boss
void Boss::setAnimationByDirection(Direction dir)
{
    m_dir = dir;
    m_animation.direction(dir);
    m_sprite.setTextureRect(m_animation.GetAnimationSprite().getTextureRect());
}
//==================================
//set the hp 
void Boss::setHp()
{
    m_hp = 30;
}
//==================================
//lose hp 
void Boss::LostHp(int GunDamage)
{
    m_hp -= GunDamage;
}
//==================================
//get hp
int Boss::GetHp()
{
    return m_hp;
}
//==================================
//lose a life
void Boss::LostLife()
{
    m_lives--;
}
//==================================
//get the lifes
int Boss::GetLives()
{
    return m_lives;
}
//==================================
//die time reset 
void Boss::DieTimerReset()
{
    m_timer.restart();
}
//==================================
//get the damage of the boss
int Boss::getDamage() const
{
    return m_damage;
}
//==================================
//set the damage of the boss
void Boss::setDamage(int dmg)
{
    m_damage = dmg;
}
//==================================
//if died and end the die textures then we set that its died
void Boss::setDied()
{
    m_died = true;
}
//==================================
//getting if its died
bool Boss::getDied() const
{
    return m_died;
}
//==================================
//getting the timer of the die texture
int Boss::getDieSpriteCount() const
{
    return m_dieSpriteCounter;
}
//==================================
//getting if its ready to fire 
bool Boss::getCDIsReadyToFire()
{
    if (m_readyToFire) {
        m_readyToFire = false;        
        return true;
    }
    return false;
}
//==================================
//getting where the head of the texture is heading
Direction Boss::HeadTo()
{
    return m_headingLeftOrRight;
}
