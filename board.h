#pragma once

#include <cstdint>
#include <vector>
#include <array>

namespace player
{
    class Player;
};

namespace card
{
    class Card;
};

namespace board
{

    enum class NormalStreetColor : uint8_t
    {
        Brown = 0,
        LightBlue,
        Magenta,
        Orange,
        Red,
        Yellow,
        Green,
        Blue,

    };

    enum class PropertyType : uint8_t
    {
        Utility = 0,
        Railroad,
    };

    enum class RandomType : uint8_t
    {
        Chance = 0,
        Community,
    };

    enum class SpecialCellType : uint8_t
    {
        Go = 0,
        GoToJail,
        Jail,
        FreeParkingSpace
    };

    class NormalBoard
    {
    public:
        uint32_t get_nearest_location(uint32_t, ) const;
        static constexpr uint16_t NUMBER_OF_COLORS = 8;
        static constexpr uint16_t NUMBER_OF_SPECIAL_PROPERTY = 2;
        static constexpr uint16_t NUMBER_OF_HOUSES = 4;
        static constexpr float MORTAGE_INTEREST_RATE = 0.1;
        static constexpr uint32_t BAIL_COST = 50;
        static constexpr uint32_t MAX_JAIL_TURN = 5;
        static constexpr uint32_t GO_SALARY = 200;
        static constexpr uint32_t NUMBER_OF_CELLS = 40;

    private:
    };

    class NormalCell
    {
    public:
        NormalCell() {}
        virtual ~NormalCell() {}
        virtual void perform(std::vector<player::Player> &, uint32_t) = 0;

    private:
    };

    class SpecialNormalCell : public NormalCell
    {
    public:
        explicit SpecialCell(SpecialCellType);
        virtual void perform(std::vector<player::Player> &, uint32_t) = 0;

    private:
        SpecialCellType special_cell_type;
    };

    class RandomCell : public Cell
    {
    public:
        explicit RandomCell(RandomType);
        virtual void perform(std::list<player::Player> &, uint32_t) = 0;

    private:
        static std::list<card::Card *> community_deck;
        static std::list<card::Card *> chance_deck;
        RandomType random_type;
    };

    class PropertyCell : public Cell
    {
    public:
        PropertyCell(uint32_t, uint32_t, PropertyType, bool);
        void perform(std::list<player::Player> &, uint32_t) override;

    private:
        uint32_t base_price;
        uint32_t mortage_price;
        PropertyType property_type;
        bool is_mortaged;
    };

    class StreetCell : public Cell
    {
    public:
        StreetCell(uint32_t, std::array<uint32_t, NormalBoard::NUMBER_OF_HOUSES>, uint32_t, uint32_t,
                   bool, uint32_t, StreetColor, uint32_t, bool);
        void perform(std::list<player::Player> &, uint32_t) override;

    private:
        uint32_t base_price;
        std::array<uint32_t, NormalBoard::NUMBER_OF_HOUSES> prices_per_houses;
        uint32_t number_of_house;
        uint32_t price_per_hotel;
        bool has_hotel;
        uint32_t owner_id;
        StreetColor color;
        uint32_t mortage_price;
        bool is_mortaged;
    };

};