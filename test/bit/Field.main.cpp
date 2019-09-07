#include "bit/Field.h"

#include <cassert>
#include <cstdint>
#include <memory>

int main()
{
    bit::Field<2> uint8_1{0};
    uint8_1 = 4;
    assert(uint8_1 == (std::uint8_t)4);
    assert(static_cast<std::uint8_t>(uint8_1) == 4);

}
