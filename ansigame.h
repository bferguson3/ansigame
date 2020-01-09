#include <string>
#include <cstring>

const int COLOR_DEPTH = 4; // if 8 then 256 colors, else 16fg/8bg

const int X_RESOLUTION = 80;
const int Y_RESOLUTION = 24;

// 4-bit color definitions
const char* BLACK = "30";       // on ubuntu/mint this color is #343434
const char* RED = "31";
const char* GREEN = "32";
const char* YELLOW = "33";
const char* BLUE = "34";
const char* MAGENTA = "35";
const char* CYAN = "36";
const char* WHITE = "37";
const char* BBLACK = "90";
const char* BRED = "91";
const char* BGREEN = "92";
const char* BYELLOW = "93";
const char* BBLUE = "94";
const char* BMAGENTA = "95";
const char* BCYAN = "96";
const char* BWHITE = "97";

const int SCR_DAT_SIZE = 14; //< for 8 bit color depth
//const int SCR_DAT_SIZE = 7;

unsigned char screen_data[X_RESOLUTION * Y_RESOLUTION][SCR_DAT_SIZE];

class ANSIGame
{
    public:
        int clear_screen();
        void wait_for_resize();
        int tx_pos(int x, int y);
        int tx_print(const char* p, char* fg, char* bg);
        int tx_plot(const char* p, char* fg, char* bg, int x, int y);
        int tx_quit();
        int show_cursor(bool tf);
        int draw();
        void tx_plot2(const char* p, const char* fg, const char* bg, int x, int y);
    private:
        
};
//#include "ansigame.h"

int clear_screen()
{
    // some terminals reset cursor to 0,0; mine does not
    printf("%c[2J", 0x1b);
    for (int i = 0; i < (X_RESOLUTION * Y_RESOLUTION); i++)
    {
        unsigned char blank[SCR_DAT_SIZE] = " [\x00\x00\x00;\x00\x00\x00m \xff";
        blank[0] = 0x1b; 
        for(int p=0;p<SCR_DAT_SIZE;p++){ screen_data[i][p] = blank[p]; }
    }

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

int tx_print(const char* p, char* fg, char* bg)
{
    // Not all terminals support bright colors on BG!
    bg = bg + 10;
    printf("%c[%s;%sm%s", 0x1b, fg, bg, p);

}

int tx_plot(const char* p, char* fg, char* bg, int x, int y)
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


int draw()
{
    tx_pos(0, 0);
    
    for(int i=0;i<(X_RESOLUTION*Y_RESOLUTION); i++)
    {   
        for(int v=0;v<SCR_DAT_SIZE;v++){ 
            if(screen_data[i][v]==255) { break; }
            printf("%c", screen_data[i][v]);
        }
    }
}

void tx_plot2(const char* p, const char* fg, const char* bg, int x, int y)
{
    for(int c=0;c<std::strlen(p);c++){

        unsigned char out[SCR_DAT_SIZE] = " [\x00\x33\x32;\x00\x34\x31m \xff";    

        char f1 = fg[0];
        char f2 = fg[1];
        char b1 = bg[0];
        char b2 = bg[1];

        b1 = b1 + 1; //background brightness weirdness
        if(b1>'9'){
            out[6]=0x31; out[7]=0x30; out[8]=b2;
        }else{
            out[7]=b1; out[8]=b2;
        }
        
        out[3]=f1; out[4]=f2; 
        out[0] = 0x1b;
        out[10] = p[c];

        for(int u=0;u<SCR_DAT_SIZE;u++){
            screen_data[(y*X_RESOLUTION)+x+c][u]=out[u];
        }
    }   
}
