#include "Bit.h"

#include <cassert>
#include <cstdint>
#include <memory>

int main()
{
    Bit b0{};
    Bit b0_0{};
    Bit b0_1{};
    Bit b0_2{};
    assert(static_cast<bool>(b0) == false);
    assert(static_cast<std::uint8_t>(b0) == std::uint8_t(0));

    assert(static_cast<bool>(~b0) == true);
    assert(static_cast<std::uint8_t>(~b0) == std::uint8_t(1));
    assert(static_cast<bool>(!b0) == true);
    assert(static_cast<std::uint8_t>(!b0) == std::uint8_t(1));

    assert(b0 == false);
    assert(b0 != true);
    assert((b0 || false) == false);
    assert((b0 && true) == false);

    b0_0 |= true;
    assert(static_cast<bool>(b0_0) == true);
    assert(static_cast<std::uint8_t>(b0_0) == std::uint8_t(1));

    b0_1 = true;
    b0_1 &= true;
    assert(static_cast<bool>(b0_1) == true);
    assert(static_cast<std::uint8_t>(b0_1) == std::uint8_t(1));

    b0_2 ^= true;
    assert(static_cast<bool>(b0_2) == true);
    assert(static_cast<std::uint8_t>(b0_2) == std::uint8_t(1));

    std::shared_ptr<bytes::ptr::Object> share0 = 
        std::make_shared<bytes::ptr::Object>(1);
    share0->At(0) = 0x10;
    std::shared_ptr<bytes::ptr::Segment> seg0 =
        std::make_shared<bytes::ptr::Segment>(0, 1, share0);
    std::shared_ptr<bytes::ptr::Object> share1 = 
        std::make_shared<bytes::ptr::Object>(1);
    share1->At(0) = 0x00;
    std::shared_ptr<bytes::ptr::Segment> seg1 =
        std::make_shared<bytes::ptr::Segment>(0, 1, share1);
    std::shared_ptr<bytes::ptr::Object> share2 = 
        std::make_shared<bytes::ptr::Object>(1);
    share2->At(0) = 0x00;
    std::shared_ptr<bytes::ptr::Segment> seg2 =
        std::make_shared<bytes::ptr::Segment>(0, 1, share2);
    std::shared_ptr<bytes::ptr::Object> share3 = 
        std::make_shared<bytes::ptr::Object>(1);
    share3->At(0) = 0x00;
    std::shared_ptr<bytes::ptr::Segment> seg3 =
        std::make_shared<bytes::ptr::Segment>(0, 1, share3);
    Bit b1{seg0, 4};
    Bit b1_0{seg1, 4};
    Bit b1_2{seg2, 4};
    Bit b1_3{seg3, 4};
    
    assert(static_cast<bool>(b1) == true);
    assert(static_cast<std::uint8_t>(b1) == std::uint8_t(1));

    assert(b1 == true);
    assert(b1 != false);
    assert((!b1 || false) == false);
    assert((b1 && true) == true);

    b1_0 |= true;
    assert(static_cast<bool>(b1_0) == true);
    assert(static_cast<std::uint8_t>(b1_0) == std::uint8_t(1));
    assert(share1->At(0) == std::uint8_t(0x10));

    b1_2 = true;
    b1_2 &= true;
    assert(static_cast<bool>(b1_2) == true);
    assert(static_cast<std::uint8_t>(b1_2) == std::uint8_t(1));
    assert(share2->At(0) == std::uint8_t(0x10));

    b1_3 ^= true;
    assert(static_cast<bool>(b1_3) == true);
    assert(static_cast<std::uint8_t>(b1_3) == std::uint8_t(1));
    assert(share3->At(0) == std::uint8_t(0x10));

    return 0;
}