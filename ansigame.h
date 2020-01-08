const int COLOR_DEPTH = 4; // if 8 then 256 colors, else 16fg/8bg

const int X_RESOLUTION = 80;
const int Y_RESOLUTION = 24;

// 4-bit color definitions
const int BLACK = 30;       // on ubuntu/mint this color is #343434
const int RED = 31;
const int GREEN = 32;
const int YELLOW = 33;
const int BLUE = 34;
const int MAGENTA = 35;
const int CYAN = 36;
const int WHITE = 37;
const int BBLACK = 90;
const int BRED = 91;
const int BGREEN = 92;
const int BYELLOW = 93;
const int BBLUE = 94;
const int BMAGENTA = 95;
const int BCYAN = 96;
const int BWHITE = 97;


int clear_screen()
{
    // some terminals reset cursor to 0,0; mine does not
    printf("%c[2J", 0x1b);
    return 1;
}

void wait_for_resize()
{
    // necessary evil
    printf("Resize terminal to %dx%d and press RETURN to continue...", X_RESOLUTION, Y_RESOLUTION);
    int ch = 0;
    while (ch == 0)
    {    
        ch = fgetc( stdin );
    }
}

int tx_pos(int x, int y)
{
    // reset to 0,0
    printf("%c[%dD%c[%dA", 0x1b, X_RESOLUTION, 0x1b, Y_RESOLUTION);
    // only if not 0, increase position
    if (x > 0) { printf("%c[%dC", 0x1b, x); }
    if (y > 0) { printf("%c[%dB", 0x1b, y); }

    return 1;
}

int tx_print(const char* p, int fg, int bg)
{
    // Not all terminals support bright colors on BG!
    bg = bg + 10;
    printf("%c[%d;%dm%s", 0x1b, fg, bg, p);
    fflush(stdout);
}

int tx_plot(const char* p, int fg, int bg, int x, int y)
{
    tx_pos(x, y);
    tx_print(p, fg, bg);
}

int tx_quit()
{
    //clean quit
    printf("%c[0m\n", 0x1b);
    printf("%c[9999C", 0x1b); 
    printf("%c[9999B\n", 0x1b); 
    return 1;
}

int show_cursor(bool tf)
{
    if(tf == false) { printf("%c[?25l", 0x1b); }
    else { printf("%c[?25h", 0x1b); }
    return 1;
}

