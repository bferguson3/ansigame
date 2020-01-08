#include <stdio.h>
#include <iostream>
#include "ansigame.h"
#include <unistd.h>
//#include <string>
#include <sys/time.h>
//#include <math.h>

int fps = 60; // change to 50 or 30 or 15 if you want
float w = 1000000/fps;
int wait = int(w);
int _wait = wait;
float cpu_pct = 0.0;

int frames = 0;

void gameloop()
{
    tx_plot2(std::to_string(frames).c_str(), CYAN, BLACK, 30, 10);

    frames++;
    if(frames==61) { frames = 0; }
    
}

int init()
{
    tx_plot2("TEST!", BRED, BBLACK, 10, 10);
}

int main()
{
    wait_for_resize();
    clear_screen();

    show_cursor(false);    

    struct timeval tv1, tv2;

    init();

    int inch = 0;
    while(inch == 0) // TODO
    {
        // _wait is the expected FPS in us minus code exec time.
        usleep(_wait); 

    // EXEC CODE MARK:
        gettimeofday(&tv1, NULL);

        // run the game loop (bulk of code here!)
        gameloop();
        draw();

    // EXEC CODE MARK:
        gettimeofday(&tv2, NULL);
        _wait = wait - (tv2.tv_usec-tv1.tv_usec); // calc new wait time: this amounts to vblank.
        cpu_pct = (float)((wait-_wait)*100.0 / wait);
        if(cpu_pct>0)
        { 
            tx_plot2(std::to_string(cpu_pct).c_str(), BRED, "0", 70, 23);
            tx_plot2("% CPU ", WHITE, "0", 74, 23);
        }
        // draw will flush entire screen_data[] to terminal. takes about 2% cpu/frame on 2.4ghz dual core
        
        // update screen all at once - don't make more changes after this point.
        fflush(stdout);
    }

    tx_quit();
}

