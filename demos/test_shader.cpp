#include <fstream>
#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring>

uint8_t binary[] = { 0x55, 0x48, 0x89, 0xe5, 0x89, 0x7d, 0xfc, 0x89, 0x7d, 0xfc, 0x89, 0x75, 0xf8, 0x8b, 0x45, 0xfc, 0x0f, 0xaf, 0x45, 0xf8, 0x5d, 0xc3 };

int main(int argc, char* argv[])
{
    int i = 0;
    for (const auto c : binary)
    {
        std::cout << "0x" << std::hex << static_cast<int>(c) << ",";
        if (i % 10 == 9)
        {
            std::cout << std::endl;
        }
        ++i;
    }
    std::cout << std::endl;

    void* buf = mmap(0, sizeof(binary), PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON,-1,0);
    memcpy(buf, binary, sizeof(binary));

    __builtin___clear_cache(buf, buf+sizeof(binary)-1);
    int (*mul)(int, int);
    mul = reinterpret_cast<int(*)(int, int)>(buf);
    std::cout << " 5 * 8 = " << std::dec << mul(1234,4215) << std::endl;
}
