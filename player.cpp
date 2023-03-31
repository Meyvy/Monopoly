#include "player.h"

using namespace player;

Player::Player(uint16_t id, uint32_t money, uint32_t location, bool in_game)
    : id(id), money(money), location(location), in_game(in_game)
{
}

// simple read methods

uint32_t Player::get_money() const
{
    return this->id;
}

uint32_t Player::get_location() const
{
    return this->location;
}

uint16_t Player::get_id() const
{
    return this->id;
}

// modification methods

void Player::increase_money_by(uint32_t amount)
{
    this->money += amount;
}

void Player::decrease_money_by(uint32_t amount)
{
    if (amount > this->money)
    {
        // implemnet later
    }
    else
    {
        this->money -= amount;
    }
}

void Player::set_location(uint32_t location)
{
    this->location = location;
}