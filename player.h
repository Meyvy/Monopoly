#include <cstdint>

namespace player
{
    class Player
    {
    public:
        Player(uint16_t, uint32_t, uint32_t, bool);
        uint32_t get_money() const;
        uint32_t get_location() const;
        uint16_t get_id() const;
        bool active() const;
        void increase_money_by(uint32_t);
        void decrease_money_by(uint32_t);
        void set_location(uint32_t);
        void set_active(bool);

    private:
        uint32_t money;
        uint32_t location;
        uint16_t id;
        bool is_active;
    };
};