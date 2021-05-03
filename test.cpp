#include <cstdlib> 

#include <unistd.h>
#include <vga.h>

int main(void)
{
    int color = 4;
    int x = 10;
    int y = 10; 

    unsigned int seconds = 5;

    if (vga_init() < 0) 
        return EXIT_FAILURE;

    vga_setmode(G320x240x4K);
    vga_clear();
    vga_setcolor(color);
    vga_drawline(0, 0, 319, 239);
    vga_drawline(319, 0, 0, 239);
    vga_drawline(160, 0, 160, 239);
    vga_drawline(0, 120, 319, 120);

    // vga_setmode(TEXT);

    return EXIT_SUCCESS;
}
