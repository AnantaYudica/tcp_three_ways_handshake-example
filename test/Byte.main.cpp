#include "Byte.h"

#include <cassert>
#include <cstdint>
#include <memory>

int main()
{
    Byte a0{1};
    Byte a1{0};
    Byte a2{2};
    assert(a0 == std::uint8_t(1));
    assert(a0 != std::uint8_t(2));
    assert(a0 < std::uint8_t(2));
    assert(a0 > std::uint8_t(0));
    assert(a0 <= std::uint8_t(1));
    assert(a0 >= std::uint8_t(1));
    assert(std::uint8_t(1) == a0);
    assert(std::uint8_t(2) != a0);
    assert(std::uint8_t(2) > a0);
    assert(std::uint8_t(0) < a0);
    assert(std::uint8_t(1) <= a0);
    assert(std::uint8_t(1) >= a0);
    a0 = a1;
    assert(a0 == std::uint8_t(0));
    assert(a0 == a1);
    assert(a0 != a2);
    assert(a0 < a2);
    assert(a2 > a0);
    assert(a0 <= a1);
    assert(a0 >= a1);
    a0 = std::uint8_t(4);
    assert(a0 == std::uint8_t(4));
    assert(static_cast<std::uint8_t>(a0) == std::uint8_t(4));
    a0 = ~a1;
    assert(a0 == std::uint8_t(255));
    return 0;
}
