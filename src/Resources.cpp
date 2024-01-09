#include "Resources.h"

#include "Direction.h"

#include <stdexcept>

namespace
{
    //making the animationData of blip
    AnimationData Blip()
    {
        auto blip = AnimationData{};

        blip.m_data[Direction::Right].emplace_back(sf::Vector2i(15, 7), sf::Vector2i(65, 28));
        blip.m_data[Direction::Left].emplace_back(sf::Vector2i(6, 40), sf::Vector2i(65, 28));
        blip.m_data[Direction::UpRight].emplace_back(sf::Vector2i(20, 76), sf::Vector2i(55, 55));
        blip.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(20, 133), sf::Vector2i(55, 55));
        blip.m_data[Direction::DownRight].emplace_back(sf::Vector2i(21, 194), sf::Vector2i(54, 46));
        blip.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(18, 247), sf::Vector2i(55, 46));
        blip.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(25, 368), sf::Vector2i(47, 66));
        blip.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(23, 299), sf::Vector2i(48, 65));
        blip.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(24, 438), sf::Vector2i(48, 65));
        blip.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(22, 509), sf::Vector2i(47, 66));


        return blip;
    }


    //gettin the Standard Bullet animation data
    AnimationData StandardBullet()
    {

        auto standardBullet = AnimationData{};

        standardBullet.m_data[Direction::Left].emplace_back(sf::Vector2i(474, 15), sf::Vector2i(19,7));
        standardBullet.m_data[Direction::Right].emplace_back(sf::Vector2i(475, 43), sf::Vector2i(19,7));
        standardBullet.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(480, 162), sf::Vector2i(15, 15));
        standardBullet.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(480, 68), sf::Vector2i(15, 15));
        standardBullet.m_data[Direction::DownRight].emplace_back(sf::Vector2i(481, 129), sf::Vector2i(15, 15));
        standardBullet.m_data[Direction::UpRight].emplace_back(sf::Vector2i(481, 94), sf::Vector2i(16, 16));
        standardBullet.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(483, 189), sf::Vector2i(8, 20));
        standardBullet.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(483, 189), sf::Vector2i(8, 20));
        standardBullet.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(484, 220), sf::Vector2i(8, 20));
        standardBullet.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(484, 220), sf::Vector2i(8, 20));


        return standardBullet;

    }
    //gettin the shotgun character blip animation data

    AnimationData ShotGunChar()
    {
        auto shotGunChar = AnimationData{};


        shotGunChar.m_data[Direction::Left].emplace_back(sf::Vector2i(86, 38), sf::Vector2i(69, 28));
        shotGunChar.m_data[Direction::Right].emplace_back(sf::Vector2i(100, 7), sf::Vector2i(68, 27));
        shotGunChar.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(101, 239), sf::Vector2i(55, 49));
        shotGunChar.m_data[Direction::UpRight].emplace_back(sf::Vector2i(98, 67), sf::Vector2i(59, 53));
        shotGunChar.m_data[Direction::DownRight].emplace_back(sf::Vector2i(104, 184), sf::Vector2i(55, 49));
        shotGunChar.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(97, 125), sf::Vector2i(59, 55));
        shotGunChar.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(110, 506), sf::Vector2i(46, 65));
        shotGunChar.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(102, 292), sf::Vector2i(45, 65));
        shotGunChar.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(113, 439), sf::Vector2i(46, 65));
        shotGunChar.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(109, 359), sf::Vector2i(45, 65));



        return shotGunChar;

    }
    //gettin the shotgun bullet animation data

    AnimationData ShotGunBull()
    {
        auto shotGunBull = AnimationData{};


        shotGunBull.m_data[Direction::Left].emplace_back(sf::Vector2i(465, 500), sf::Vector2i(47, 31));
        shotGunBull.m_data[Direction::Right].emplace_back(sf::Vector2i(468, 540), sf::Vector2i(47, 30));
        shotGunBull.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(472, 707), sf::Vector2i(51, 39));
        shotGunBull.m_data[Direction::UpRight].emplace_back(sf::Vector2i(471, 620), sf::Vector2i(43, 40));
        shotGunBull.m_data[Direction::DownRight].emplace_back(sf::Vector2i(472, 663), sf::Vector2i(39, 42));
        shotGunBull.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(470, 574), sf::Vector2i(39, 42));
        shotGunBull.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(475, 752), sf::Vector2i(30, 47));
        shotGunBull.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(478, 803), sf::Vector2i(28, 47));
        shotGunBull.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(475, 752), sf::Vector2i(30, 47));
        shotGunBull.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(478, 803), sf::Vector2i(28, 47));



        return shotGunBull;

    }
    //gettin the rifle character blip animation data

    AnimationData RifleGunChar()
    {
        auto rifleGunChar = AnimationData{};


        rifleGunChar.m_data[Direction::Left].emplace_back(sf::Vector2i(177, 41), sf::Vector2i(61, 27));
        rifleGunChar.m_data[Direction::Right].emplace_back(sf::Vector2i(185, 8), sf::Vector2i(61, 27));
        rifleGunChar.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(186, 244), sf::Vector2i(48, 40));
        rifleGunChar.m_data[Direction::UpRight].emplace_back(sf::Vector2i(183, 74), sf::Vector2i(53, 41));
        rifleGunChar.m_data[Direction::DownRight].emplace_back(sf::Vector2i(184, 191), sf::Vector2i(48, 40));
        rifleGunChar.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(182, 134), sf::Vector2i(53, 41));
        rifleGunChar.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(187, 516), sf::Vector2i(44, 55));
        rifleGunChar.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(185, 295), sf::Vector2i(45, 54));
        rifleGunChar.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(190, 450), sf::Vector2i(44, 55));
        rifleGunChar.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(186, 362), sf::Vector2i(46, 54));



        return rifleGunChar;

    }
    //gettin the rifle bull animation data

    AnimationData RifleGunBull()
    {
        auto rifleGunBull = AnimationData{};


        rifleGunBull.m_data[Direction::Left].emplace_back(sf::Vector2i(475, 253), sf::Vector2i(26, 9));
        rifleGunBull.m_data[Direction::Right].emplace_back(sf::Vector2i(478, 280), sf::Vector2i(26, 9));
        rifleGunBull.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(479, 400), sf::Vector2i(21, 20));
        rifleGunBull.m_data[Direction::UpRight].emplace_back(sf::Vector2i(476, 330), sf::Vector2i(20, 20));
        rifleGunBull.m_data[Direction::DownRight].emplace_back(sf::Vector2i(479, 359), sf::Vector2i(20, 22));
        rifleGunBull.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(481, 300), sf::Vector2i(20, 21));

        rifleGunBull.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(486, 426), sf::Vector2i(10, 28));
        rifleGunBull.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(486, 459), sf::Vector2i(10, 26));
        rifleGunBull.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(486, 426), sf::Vector2i(10, 28));
        rifleGunBull.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(486, 459), sf::Vector2i(10, 26));



        return rifleGunBull;

    }
    AnimationData standardEnemyData()
    {

        auto standardEnemy = AnimationData{};
        standardEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(519, 0), sf::Vector2i(26, 38));
        standardEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(520, 39), sf::Vector2i(23, 38));
        standardEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(520, 77), sf::Vector2i(23, 39));
        standardEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(521, 116), sf::Vector2i(22, 38));
        standardEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(519, 154), sf::Vector2i(25, 38));
        standardEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(519, 194), sf::Vector2i(26, 38));
        standardEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(521, 233), sf::Vector2i(23, 38));
        standardEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(520, 272), sf::Vector2i(22, 39));
        standardEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(521, 311), sf::Vector2i(22, 38));
        standardEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(520, 351), sf::Vector2i(25, 38));
        standardEnemy.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(518, 392), sf::Vector2i(30, 38));
        standardEnemy.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(518, 392), sf::Vector2i(30, 38));
        standardEnemy.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(518, 392), sf::Vector2i(30, 38));
        standardEnemy.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(518, 392), sf::Vector2i(30, 38));
        standardEnemy.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(518, 392), sf::Vector2i(30, 38));
        standardEnemy.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(518, 430), sf::Vector2i(29, 38));
        standardEnemy.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(518, 430), sf::Vector2i(29, 38));
        standardEnemy.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(518, 430), sf::Vector2i(29, 38));
        standardEnemy.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(518, 430), sf::Vector2i(29, 38));
        standardEnemy.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(518, 430), sf::Vector2i(29, 38));


        //die format
        standardEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(565, 470), sf::Vector2i(24, 39));
        standardEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(563, 509), sf::Vector2i(26, 41));
        standardEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(563, 551), sf::Vector2i(34, 47));
        standardEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(556, 606), sf::Vector2i(50, 54));
        standardEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(539, 663), sf::Vector2i(90, 79));
        standardEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(527, 745), sf::Vector2i(123, 79));
        standardEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(514, 828), sf::Vector2i(142, 79));




        return standardEnemy;
    }

    AnimationData ForkEnemyData()
    {


        auto forkEnemy = AnimationData{};
        forkEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(726, 4), sf::Vector2i(54, 44));
        forkEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(725, 48), sf::Vector2i(51, 45));
        forkEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(723, 95), sf::Vector2i(52, 42));
        forkEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(725, 138), sf::Vector2i(52, 44));
        forkEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(720, 190), sf::Vector2i(54, 44));
        forkEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(724, 234), sf::Vector2i(51, 45));
        forkEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(725, 281), sf::Vector2i(52, 42));
        forkEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(723, 324), sf::Vector2i(52, 44));
        //Die from here!!! (as down)
        forkEnemy.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(719, 376), sf::Vector2i(83, 35));
        forkEnemy.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(720, 413), sf::Vector2i(53, 32));
        forkEnemy.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(721, 448), sf::Vector2i(53, 32));
        forkEnemy.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(719, 481), sf::Vector2i(54, 32));

        forkEnemy.m_data[Direction::DownRight].emplace_back(sf::Vector2i(717, 516), sf::Vector2i(83, 35));
        forkEnemy.m_data[Direction::DownRight].emplace_back(sf::Vector2i(746, 553), sf::Vector2i(53, 32));
        forkEnemy.m_data[Direction::DownRight].emplace_back(sf::Vector2i(745, 588), sf::Vector2i(53, 32));
        forkEnemy.m_data[Direction::DownRight].emplace_back(sf::Vector2i(746, 621), sf::Vector2i(54, 32));


        return forkEnemy;
    }
    AnimationData Blop()
    {


        auto blop = AnimationData{};

        blop.m_data[Direction::Right].emplace_back(sf::Vector2i(263, 2), sf::Vector2i(63, 36));
        blop.m_data[Direction::Left].emplace_back(sf::Vector2i(248, 38), sf::Vector2i(65, 35));
        blop.m_data[Direction::UpRight].emplace_back(sf::Vector2i(258, 75), sf::Vector2i(50, 54));
        blop.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(253, 131), sf::Vector2i(50, 55));
        blop.m_data[Direction::DownRight].emplace_back(sf::Vector2i(257, 188), sf::Vector2i(55, 50));
        blop.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(254, 238), sf::Vector2i(55, 60));
        blop.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(261, 357), sf::Vector2i(42, 60));
        blop.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(257, 290), sf::Vector2i(46, 60));
        blop.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(258, 460), sf::Vector2i(44, 55));
        blop.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(259, 525), sf::Vector2i(45,55));


        return blop;
    }

    AnimationData ShotGunCharBlop()
    {


        auto shotGunCharBlop = AnimationData{};

        shotGunCharBlop.m_data[Direction::Right].emplace_back(sf::Vector2i(342, 1), sf::Vector2i(68, 37));
        shotGunCharBlop.m_data[Direction::Left].emplace_back(sf::Vector2i(318, 38), sf::Vector2i(68, 37));
        shotGunCharBlop.m_data[Direction::UpRight].emplace_back(sf::Vector2i(342, 75), sf::Vector2i(55, 53));
        shotGunCharBlop.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(332, 137), sf::Vector2i(55, 53));
        shotGunCharBlop.m_data[Direction::DownRight].emplace_back(sf::Vector2i(341, 190), sf::Vector2i(53, 49));
        shotGunCharBlop.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(340, 239), sf::Vector2i(53, 49));
        shotGunCharBlop.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(347, 361), sf::Vector2i(43, 73));
        shotGunCharBlop.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(346, 288), sf::Vector2i(44, 73));
        shotGunCharBlop.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(343, 443), sf::Vector2i(46, 67));
        shotGunCharBlop.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(342, 510), sf::Vector2i(46, 67));


        return shotGunCharBlop;
    }

    AnimationData RifleGunCharBlop()
    {


        auto rifleGunCharBlop = AnimationData{};

        rifleGunCharBlop.m_data[Direction::Right].emplace_back(sf::Vector2i(417, 2), sf::Vector2i(55, 37));
        rifleGunCharBlop.m_data[Direction::Left].emplace_back(sf::Vector2i(404, 39), sf::Vector2i(55, 39));
        rifleGunCharBlop.m_data[Direction::UpRight].emplace_back(sf::Vector2i(418, 82), sf::Vector2i(49, 43));
        rifleGunCharBlop.m_data[Direction::UpLeft].emplace_back(sf::Vector2i(413, 145), sf::Vector2i(49, 43));
        rifleGunCharBlop.m_data[Direction::DownRight].emplace_back(sf::Vector2i(419, 189), sf::Vector2i(48, 48));
        rifleGunCharBlop.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(415, 239), sf::Vector2i(48, 48));
        rifleGunCharBlop.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(419, 362), sf::Vector2i(44, 67));
        rifleGunCharBlop.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(416, 291), sf::Vector2i(44, 67));
        rifleGunCharBlop.m_data[Direction::UpHeadLeft].emplace_back(sf::Vector2i(417, 449), sf::Vector2i(41, 59));
        rifleGunCharBlop.m_data[Direction::UpHeadRight].emplace_back(sf::Vector2i(415, 516), sf::Vector2i(42, 59));


        return rifleGunCharBlop;
    }
    AnimationData Boss()
    {


        auto boss = AnimationData{};

        boss.m_data[Direction::Right].emplace_back(sf::Vector2i(12, 1), sf::Vector2i(28, 54));
        boss.m_data[Direction::Right].emplace_back(sf::Vector2i(10, 56), sf::Vector2i(23, 56));
        boss.m_data[Direction::Right].emplace_back(sf::Vector2i(11, 112), sf::Vector2i(25, 56));
        boss.m_data[Direction::Right].emplace_back(sf::Vector2i(8, 168), sf::Vector2i(32, 54));

        boss.m_data[Direction::Left].emplace_back(sf::Vector2i(10, 224), sf::Vector2i(28, 54));
        boss.m_data[Direction::Left].emplace_back(sf::Vector2i(17, 279), sf::Vector2i(23, 56));
        boss.m_data[Direction::Left].emplace_back(sf::Vector2i(14, 335), sf::Vector2i(25, 56));
        boss.m_data[Direction::Left].emplace_back(sf::Vector2i(10, 391), sf::Vector2i(32, 54));
       
       
        boss.m_data[Direction::DownRight].emplace_back(sf::Vector2i(72, 206), sf::Vector2i(33, 50));
        boss.m_data[Direction::DownRight].emplace_back(sf::Vector2i(69, 257), sf::Vector2i(34, 48));
        boss.m_data[Direction::DownRight].emplace_back(sf::Vector2i(62, 307), sf::Vector2i(44, 48));
        boss.m_data[Direction::DownRight].emplace_back(sf::Vector2i(56, 356), sf::Vector2i(49, 48));

        boss.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(56, 2), sf::Vector2i(33, 50));
        boss.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(58, 53), sf::Vector2i(34, 48));
        boss.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(55, 103), sf::Vector2i(44, 48));
        boss.m_data[Direction::DownLeft].emplace_back(sf::Vector2i(56, 152), sf::Vector2i(49, 48));


        boss.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(399, 2), sf::Vector2i(28, 54));
        boss.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(401, 112), sf::Vector2i(32, 46));
        boss.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(399, 214), sf::Vector2i(32, 46));
        boss.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(395, 311), sf::Vector2i(36, 46));
        boss.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(392, 411), sf::Vector2i(39, 45));
        boss.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(385, 459), sf::Vector2i(46, 46));
        boss.m_data[Direction::DownHeadLeft].emplace_back(sf::Vector2i(372, 624), sf::Vector2i(59, 24));
        
        boss.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(302, 2), sf::Vector2i(28, 54));
        boss.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(297, 112), sf::Vector2i(32, 46));
        boss.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(296, 214), sf::Vector2i(32, 46));
        boss.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(298, 311), sf::Vector2i(36, 46));
        boss.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(298, 411), sf::Vector2i(39, 45));
        boss.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(298, 459), sf::Vector2i(46, 46));
        boss.m_data[Direction::DownHeadRight].emplace_back(sf::Vector2i(298, 624), sf::Vector2i(59, 24));

        return boss;
    }

    AnimationData BossBull()
    {

        auto bossBull = AnimationData{};

        bossBull.m_data[Direction::Right].emplace_back(sf::Vector2i(55, 407), sf::Vector2i(44, 35));
        bossBull.m_data[Direction::Right].emplace_back(sf::Vector2i(55, 445), sf::Vector2i(57, 30));

        bossBull.m_data[Direction::Left].emplace_back(sf::Vector2i(68, 480), sf::Vector2i(44, 35));
        bossBull.m_data[Direction::Left].emplace_back(sf::Vector2i(54, 518), sf::Vector2i(57, 30));

        return bossBull;
    }
    AnimationData PresentEnemyData()
    {

        auto pEnemy = AnimationData{};
        pEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(811, 5), sf::Vector2i(55, 50));
        pEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(811, 56), sf::Vector2i(55, 50));
        pEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(812, 107), sf::Vector2i(54, 50));
        pEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(813, 156), sf::Vector2i(53, 51));
        pEnemy.m_data[Direction::Right].emplace_back(sf::Vector2i(813, 207), sf::Vector2i(54, 51));
        pEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(816, 260), sf::Vector2i(55, 50));
        pEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(816, 312), sf::Vector2i(55, 50));
        pEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(816, 362), sf::Vector2i(54, 50));
        pEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(816, 411), sf::Vector2i(53, 51));
        pEnemy.m_data[Direction::Left].emplace_back(sf::Vector2i(815, 461), sf::Vector2i(54, 51));
        
        //die format
        pEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(810, 515), sf::Vector2i(96, 61));
        pEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(810, 515), sf::Vector2i(96, 61));
        pEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(814, 579), sf::Vector2i(89, 73));
        pEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(817, 654), sf::Vector2i(92, 79));
        pEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(817, 654), sf::Vector2i(92, 79));


        return pEnemy;
    }
}



Resources& Resources::instance()
{
    static Resources instance;
    return instance;
}
sf::Music& Resources::getMenuMusic()
{
    music.openFromFile("Menu_Music.ogg");
    // Change some parameters
    music.setPosition(0, 1, 10); // change its 3D position
    music.setVolume(50);         // reduce the volume
    music.setLoop(true);         // make it loop

    return music;
}
sf::Music& Resources::getGameMusic()
{
    GameMusic.openFromFile("ALittlePieceofHeaven.ogg");
    // Change some parameters
    GameMusic.setPosition(0, 1, 10); // change its 3D position
    GameMusic.setVolume(50);         // reduce the volume
    GameMusic.setLoop(true);         // make it loop

    return GameMusic;
}
//-------------------- get buffer ---------------------------------------------
sf::SoundBuffer* Resources::getBuffer(const std::string path)
{
    if (sound_buffers.find(path) == sound_buffers.end())
    {
        sf::SoundBuffer* sbuffer = new sf::SoundBuffer;
        sbuffer->loadFromFile(path);

        sound_buffers[path] = sbuffer;
    }
    return sound_buffers[path];
}
void Resources::PopResourcesVectors()
{
    m_data.clear();
 
    sound_buffers.clear();
}

Resources::Resources()
    : m_data(Max)
{
    if (!m_texture.loadFromFile("characterSprite.png"))
    {
        throw std::runtime_error("Can't load file");
    }
  
    if (!m_texture2.loadFromFile("bossSprites.png"))
    {
        throw std::runtime_error("Can't load Boss file");
    }
    m_data[BLIP] = Blip();
    m_data[STANDARDBULLET] = StandardBullet();
    m_data[SHOTGUNCHAR] = ShotGunChar();
    m_data[SHOTGUNBULLET] = ShotGunBull();

    m_data[RIFLEGUNCHAR] = RifleGunChar();
    m_data[RIFLEGUNBULLET] = RifleGunBull();
    m_data[STANDARDENEMY] = standardEnemyData();
    m_data[FORKENEMY] = ForkEnemyData();
    m_data[PRESENTENEMY] = PresentEnemyData();

    m_data[BLOP] = Blop();
    m_data[SHOTGUNCHARBLOP] = ShotGunCharBlop();
    m_data[RIFLEGUNCHARBLOP] = RifleGunCharBlop();
    m_data[BOSS] = Boss();
    m_data[BOSSBULL] = BossBull();

}
Resources::~Resources()
{
    for (std::unordered_map<std::string, sf::SoundBuffer*>::iterator
        it = sound_buffers.begin(); it != sound_buffers.end(); ++it)
    {
        delete it->second;
    }
}
