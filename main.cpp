#include <stdio.h>
#include "ansigame.h"
#include <unistd.h>
#include <string>
#include <sys/time.h>
//#include <math.h>

int fps = 60; // change to 50 or 30 or 15 if you want
float w = 1000000/fps;
int wait = int(w);
int _wait = wait;
float cpu_pct = 0.0;

int frames = 0;

void game_loop()
{
    tx_pos(0, 0);
    tx_print("!", BWHITE, BLACK);
    tx_print("!", WHITE, BLACK);
    tx_print("", 0, 0); // This resets terminal to default colors
    tx_plot("TEST! FRAME:", BRED, BBLACK, 10, 10);    
    tx_plot(std::to_string(frames).c_str(), BRED, BLACK, 23, 10);
    frames++;
    if(frames==61) { frames = 0; }
}

int main()
{
    wait_for_resize();
    clear_screen();

    show_cursor(false);    

    struct timeval tv1, tv2;

    int inch = 0;
    while(inch == 0) // TODO
    {
        // _wait is the expected FPS in us minus code exec time.
        usleep(_wait); 
        // EXEC CODE MARK:
        gettimeofday(&tv1, NULL);
        // run the game loop (bulk of code here!)
        game_loop();
        // TODO: add flush to screen

        // EXEC CODE MARK:
        gettimeofday(&tv2, NULL);
        _wait = wait - (tv2.tv_usec-tv1.tv_usec); // calc new wait time: this amounts to vblank.

        cpu_pct = (float)((wait-_wait)*100.0 / wait);
        
        tx_plot(std::to_string(pct).c_str(), BRED, BLACK, 70, 23);
        tx_plot("CPU ", 0, 0, 74, 23);
    }

    tx_quit();
}

