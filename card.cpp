#include "card.h"

using namespace card;

MoneyCardInc::MoneyCardInc(uint32_t amount, MoneyCardType money_card_type)
    : amount(amount), money_card_type(money_card_type)
{
}

void MoneyCardInc::perform(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    switch (this->money_card_type)
    {
    case MoneyCardType::ALL:
        /* code */
        this->decrease_all(players, plyaer_index);
        return;
    case MoneyCardType::SELF:
        this->increase_self(players, plyaer_index);
        return;
    default:
        break;
    }
}

void MoneyCardInc::decrease_all(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    for (uint32_t i = 0; i < players.size(); i++)
    {
        if (i == plyaer_index || !players[i].active())
        {
            continue;
        }

        players[i].decrease_money_by(this->amount);

        if (players[i].active())
        {
            players[plyaer_index].increase_money_by(this->amount);
        }
    }
}

void MoneyCardInc::increase_self(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    players[plyaer_index].increase_money_by(this->amount);
}

MoneyCardDec::MoneyCardDec(uint32_t amount, MoneyCardType money_card_type)
    : amount(amount), money_card_type(money_card_type)
{
}

void MoneyCardDec::perform(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    switch (this->money_card_type)
    {
    case MoneyCardType::ALL:
        /* code */
        this->increase_all(players, plyaer_index);
        return;
    case MoneyCardType::SELF:
        this->decrease_self(players, plyaer_index);
        return;
    default:
        break;
    }
}

void MoneyCardDec::increase_all(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    uint32_t number_of_owned_players = 0;

    for (uint32_t i = 0; i < players.size(); i++)
    {
        if (i != plyaer_index && players[i].active())
        {
            number_of_owned_players++;
        }
    }

    players[plyaer_index].decrease_money_by(this->amount * number_of_owned_players);

    if (!players[plyaer_index].active())
    {
        return;
    }

    for (uint32_t i = 0; i < players.size(); i++)
    {
        if (i == plyaer_index || !players[i].active())
        {
            continue;
        }
        players[plyaer_index].decrease_money_by(this->amount);
    }
}

void MoneyCardDec::decrease_self(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    players[plyaer_index].decrease_money_by(this->amount);
}

ChangeLocationCardFixed::ChangeLocationCardFixed(uint32_t location)
    : location(location)
{
}

void ChangeLocationCardFixed::perform(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    players[plyaer_index].set_location(this->location);
}

ChangeLocationCardRelative::ChangeLocationCardRelative(uint32_t steps, bool is_forward)
    : steps(steps), is_forward(is_forward)
{
}

void ChangeLocationCardRelative::perform(std::vector<player::Player> &players, uint32_t plyaer_index)
{
    if (this->is_forward)
    {
        players[plyaer_index].set_location((players[plyaer_index].get_location() + this->steps) % board::NormalBoard::NUMBER_OF_COLORS);
    }
    else
    {
        players[plyaer_index].set_location((players[plyaer_index].get_location() - this->steps) % board::NormalBoard::NUMBER_OF_COLORS);
    }
}

ChangeLocationCardNear::ChangeLocationCardNear(board::CellType cell_type)
    : cell_type(cell_type)
{
}
