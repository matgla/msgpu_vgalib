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
    vga_setcolor(color);
    vga_drawpixel(x, y);

    sleep(seconds);

    vga_setmode(TEXT);

    return EXIT_SUCCESS;
}
