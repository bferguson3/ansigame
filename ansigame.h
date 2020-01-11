#include <string>
#include <cstring>
#include <termios.h>
#include <cctype>

#ifndef __ansigame_h_
#define __ansigame_h_


extern const int COLOR_DEPTH;

extern const int X_RESOLUTION;
extern const int Y_RESOLUTION;

// 4-bit color definitions
extern const char* BLACK;     
extern const char* RED;
extern const char* GREEN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* MAGENTA;
extern const char* CYAN;
extern const char* WHITE;
extern const char* BBLACK;
extern const char* BRED;
extern const char* BGREEN;
extern const char* BYELLOW;
extern const char* BBLUE;
extern const char* BMAGENTA;
extern const char* BCYAN;
extern const char* BWHITE;

        
extern const char* x11_names[];

extern const int SCR_DAT_SIZE; //< for 8 bit color depth
//const int SCR_DAT_SIZE = 7;

//extern unsigned char screen_data[X_RESOLUTION * Y_RESOLUTION][SCR_DAT_SIZE];

class ANSIGame
{
    public:
        void main();
        int clear_screen();
        void wait_for_resize();
        int tx_pos(int x, int y);
        int tx_print(const char* p, char* fg, char* bg);
        int tx_plot(const char* p, char* fg, char* bg, int x, int y);
        int tx_quit();
        int show_cursor(bool tf);
        int draw();
        void tx_plot2(const char* p, const char* fg, const char* bg, int x, int y);
        void tx_draw_xpm(const char* const* data, int x, int y);
        void key_echo(bool tf);
    private:
        
};
#endif
