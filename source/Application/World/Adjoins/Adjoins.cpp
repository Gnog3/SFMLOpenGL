#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#include "Adjoins.hpp"

Adjoins::Adjoins(bool Up, bool Down, bool Left, bool Right, bool Front, bool Back) {
    adjoins |= ((uint8_t) Up) << 5u;
    adjoins |= ((uint8_t) Down) << 4u;
    adjoins |= ((uint8_t) Left) << 3u;
    adjoins |= ((uint8_t) Right) << 2u;
    adjoins |= ((uint8_t) Front) << 1u;
    adjoins |= ((uint8_t) Back);
}

bool Adjoins::isUp() const { return adjoins >> 5u; }
bool Adjoins::isDown() const { return (adjoins & 0b10000u) >> 4u; }
bool Adjoins::isLeft() const { return (adjoins & 0b1000u) >> 3u; }
bool Adjoins::isRight() const { return (adjoins & 0b100u) >> 2u; }
bool Adjoins::isFront() const { return (adjoins & 0b10u) >> 1u; }
bool Adjoins::isBack() const { return adjoins & 1u; }

Adjoins Adjoins::operator~() const {
    return Adjoins(0b111111u & (~adjoins));
}
uint32_t Adjoins::amount() const {
    uint8_t adjoins_temp = adjoins;
    uint32_t amount = 0;
    for (uint8_t i = 0; i < 6; i++) {
        amount += adjoins_temp & 1u;
        adjoins_temp >>= 1;
    }
    return amount;
}
void Adjoins::setUp() { adjoins |= 0b100000u; }
void Adjoins::setDown() { adjoins |= 0b10000u; }
void Adjoins::setLeft() { adjoins |= 0b1000u; }
void Adjoins::setRight() { adjoins |= 0b100u; }
void Adjoins::setFront() { adjoins |= 0b10u; }
void Adjoins::setBack() { adjoins |= 0b1u; }


#pragma clang diagnostic pop
