#include "Player.h"

Player::Player(std::string name)
:mName(name)
{

}
Player::~Player()
{
    
}

void Player::init()
{
    char *in;
    bool isRoop = true;

   
    std::cout << " 名前を入力してね " << std::endl;
    std::cin >> in;

    setName(in);
}

void Player::input()
{
    char in;
    bool isRoop = true;

    while(isRoop)
    {
        std::cout << mName << " : グー（０）、　パー（１）、チョキ（２）のどれかを入力してね" << std::endl;
        std::cin >> in;

        if(std::isdigit(static_cast<unsigned char>(in)))
        {
            int intHand = in - '0';
            if(intHand >= 0 && intHand <= 2)
            {
                setHand((Hand)intHand);
                isRoop = false;
            }
        }
        else
        {
            std::cout << " 不正な入力です。もう一度入力してね" << std::endl;
        }   
    }
}

