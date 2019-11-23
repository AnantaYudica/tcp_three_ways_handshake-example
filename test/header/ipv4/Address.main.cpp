#include "header/ipv4/Address.h"

#include <cassert>
#include <cstring>

int main()
{
    header::ipv4::Address addr1(127,0,0,1);
    assert(addr1[0] == 127);
    assert(addr1[1] == 0);
    assert(addr1[2] == 0);
    assert(addr1[3] == 1);
    assert(strcmp(addr1.ToString().c_str(), "127.0.0.1") == 0);
    assert(addr1.GetValue() == 2130706433);

    
    header::ipv4::Address addr2;
    auto failed_cast_from_string = addr2.FromString("127.0.0.100");
    assert(failed_cast_from_string);
    assert(addr2[0] == 127);
    assert(addr2[1] == 0);
    assert(addr2[2] == 0);
    assert(addr2[3] == 100);
    assert(addr2.GetValue() == 2130706532);

    header::ipv4::Address addr3(2130706687);
    assert(addr3[0] == 127);
    assert(addr3[1] == 0);
    assert(addr3[2] == 0);
    assert(addr3[3] == 255);
    assert(strcmp(addr3.ToString().c_str(), "127.0.0.255") == 0);

    return 0;
}
