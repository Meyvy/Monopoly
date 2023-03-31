#pragma once

#include <cstdint>
#include <vector>
#include "player.h"
#include "board.h"

namespace card
{

    class NormalCard
    {
    public:
        NormalCard() {}
        virtual ~NormalCard() {}
        virtual void perform(std::vector<player::Player> &, uint32_t) = 0;

    private:
    };

    enum class NormalMoneyCardType : uint8_t
    {
        SELF = 0,
        ALL
    };

    class MoneyCardInc : public NormalCard
    {
    public:
        explicit MoneyCardInc(uint32_t, NormalMoneyCardType);
        void perform(std::vector<player::Player> &, uint32_t) override;

    private:
        uint32_t amount;
        MoneyCardType money_card_type;
        void increase_self(std::vector<player::Player> &, uint32_t);
        void decrease_all(std::vector<player::Player> &, uint32_t);
    };

    class MoneyCardDec : public Card
    {
    public:
        explicit MoneyCardDec(uint32_t, MoneyCardType);
        void perform(std::vector<player::Player> &, uint32_t) override;

    private:
        uint32_t amount;
        MoneyCardType money_card_type;
        void decrease_self(std::vector<player::Player> &, uint32_t);
        void increase_all(std::vector<player::Player> &, uint32_t);
    };

    class ChangeLocationCardFixed : public Card
    {
    public:
        explicit ChangeLocationCardFixed(uint32_t);
        void perform(std::vector<player::Player> &, uint32_t) override;

    private:
        uint32_t location;
    };

    class ChangeLocationCardRelative : public Card
    {
    public:
        explicit ChangeLocationCardRelative(uint32_t, bool);
        void perform(std::vector<player::Player> &, uint32_t) override;

    private:
        uint32_t steps;
        bool is_forward;
    };

    class ChangeLocationCardNear : public Card
    {
    public:
        explicit ChangeLocationCardNear(board::CellType);
        void perform(std::vector<player::Player> &, uint32_t) override;

    private:
        uint32_t get_location() const;
        board::CellType cell_type;
    };

};