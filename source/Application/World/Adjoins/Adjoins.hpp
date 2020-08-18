#pragma once

#include <cstdint>
#include <vector>
class Adjoins {
    private:
        uint8_t adjoins = 0;
    public:
        Adjoins() = default;
        Adjoins(bool Up, bool Down, bool Left, bool Right, bool Front, bool Back);
        explicit Adjoins(uint8_t adjoins) : adjoins(adjoins) {};
        [[nodiscard]] bool isUp   () const;
        [[nodiscard]] bool isDown () const;
        [[nodiscard]] bool isLeft () const;
        [[nodiscard]] bool isRight() const;
        [[nodiscard]] bool isFront() const;
        [[nodiscard]] bool isBack () const;
        [[nodiscard]] uint32_t amount() const;
        [[nodiscard]] Adjoins operator~() const;
        void setUp();
        void setDown();
        void setLeft();
        void setRight();
        void setFront();
        void setBack();
};
