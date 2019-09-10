#include "Bytes.h"
#include <cassert>

int main()
{
    Bytes a0({0x01, 0x02, 0x03, 0x04}, bytes::Endian::big);
    bytes::Trait trait0 {
        bytes::Endian::big,
        std::make_shared<bytes::trait::capacity::Fixed>(),
        std::make_shared<bytes::trait::element::Direct>(),
        std::make_shared<bytes::trait::modifier::Direct>()};
    auto a0_1 = a0.Slice(0, std::size_t(2), trait0);
    auto a0_2 = a0.Slice(2, std::size_t(2), trait0);
    assert(a0_1[0] == std::uint8_t(0x01));
    assert(a0_1[1] == std::uint8_t(0x02));
    assert(a0_2[0] == std::uint8_t(0x03));
    assert(a0_2[1] == std::uint8_t(0x04));
    assert(a0.Size() == 4);
    assert(a0_1.Size() == 2);
    assert(a0_2.Size() == 2);
    a0_1 = {0xaa, 0xbb};
    a0_2 = {0xcc, 0xdd};
    assert(a0[0] == std::uint8_t(0xaa));
    assert(a0[1] == std::uint8_t(0xbb));
    assert(a0[2] == std::uint8_t(0xcc));
    assert(a0[3] == std::uint8_t(0xdd));
    a0_2 = ~a0_2;
    assert(a0[2] == std::uint8_t(0x33));
    assert(a0[3] == std::uint8_t(0x22));
    a0_1 |= Bytes{{0x44, 0x44}};
    assert(a0[0] == std::uint8_t(0xee));
    assert(a0[1] == std::uint8_t(0xff));
    a0_2 &= Bytes{{0xaa, 0x66}};
    assert(a0[2] == std::uint8_t(0x22));
    assert(a0[3] == std::uint8_t(0x22));
    a0_1 ^= Bytes{{0xbb, 0xcc}};
    assert(a0[0] == std::uint8_t(0x55));
    assert(a0[1] == std::uint8_t(0x33));
    a0_2 >>= 5;
    assert(a0[2] == std::uint8_t(0x01));
    assert(a0[3] == std::uint8_t(0x11));
    a0_1 <<= 9;
    assert(a0[0] == std::uint8_t(0x66));
    assert(a0[1] == std::uint8_t(0x00));
    a0_2 += Bytes{{0x0E, 0xFF}};
    assert(a0[2] == std::uint8_t(0x10));
    assert(a0[3] == std::uint8_t(0x10));
    a0_1 -= Bytes{{0x11, 0x01}};
    assert(a0[0] == std::uint8_t(0x54));
    assert(a0[1] == std::uint8_t(0xFF));
    a0_2 *= Bytes{{0x0E, 0x0E}};
    assert(a0[2] == std::uint8_t(0xC0));
    assert(a0[3] == std::uint8_t(0xE0));
    a0_1 /= Bytes{{0x0A}};
    assert(a0[0] == std::uint8_t(0x08));
    assert(a0[1] == std::uint8_t(0x7F));
    a0_2 %= Bytes{{0x11, 0x11}};
    assert(a0[2] == std::uint8_t(0x05));
    assert(a0[3] == std::uint8_t(0x25));
    Bytes a1{{0x01, 0x02}};
    Bytes a2{{0x02, 0x01}};
    Bytes a3{{0x01, 0x02, 0x03, 0x04}, bytes::Endian::big};
    auto a3_0 = a3.Slice(0, std::size_t(2));
    auto a3_1 = a3.Slice(2, std::size_t(2));
    assert(a1 != a2);
    assert(a1 == a3_0);
    assert(a2 <= a3_1);

    Bytes a11({0x01, 0x02, 0x03, 0x04}, bytes::Endian::little);
    bytes::Trait trait11 {
        bytes::Endian::little,
        std::make_shared<bytes::trait::capacity::Fixed>(),
        std::make_shared<bytes::trait::element::Direct>(),
        std::make_shared<bytes::trait::modifier::Direct>()};
    auto a11_1 = a11.Slice(0, std::size_t(2), trait11);
    auto a11_2 = a11.Slice(2, std::size_t(2), trait11);
    assert(a11_1[0] == std::uint8_t(0x03));
    assert(a11_1[1] == std::uint8_t(0x04));
    assert(a11_2[0] == std::uint8_t(0x01));
    assert(a11_2[1] == std::uint8_t(0x02));

    return 0;
}