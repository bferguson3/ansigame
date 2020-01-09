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

bool ENABLE_DEBUG = true;

int frames = 0;

int tempx = 0;
int tempy = 0;
//char tempc[4] = "30";

void gameloop()
{
    tx_plot2(std::to_string(frames).c_str(), BCYAN, BLACK, 30, 10);
    const char* e_c = " ";
    int tc = rand() % 8 + 0x30;
    int bc = rand() % 2;
    char tempc[4] = "30";
    tempc[1] = tc;
    if(bc==1){tempc[0]='9';}
    tx_plot2(e_c, "30", tempc, tempx, tempy);
    if (tempc[1] < 0x37) { tempc[1]++; }
    else { if(tempc[0]==0x33){tempc[0] = 0x39;}
           else{ tempc[0] = 0x33;}
           tempc[1] = 0x30; }
    
    tempx++; if(tempx >= X_RESOLUTION){ tempx=0; tempy++; }
    if (tempy >= Y_RESOLUTION) { tempy = 0; }

    frames++;
    if(frames==fps) { frames = 0; }
    
}

int init()
{
    tx_plot2("TEST!", BRED, CYAN, 10, 10);
}

int debug()
{
    cpu_pct = (float)((wait-_wait)*100.0 / wait);
    if(cpu_pct>0){ 
        tx_plot2(std::to_string(cpu_pct).c_str(), BRED, BLACK, 0, 0);
        tx_plot2("% CPU ", WHITE, BLACK, 5, 0);
    }
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
    //
        // run the game loop (bulk of code here!)
        gameloop();
        draw();

    // EXEC CODE MARK:
        gettimeofday(&tv2, NULL);
        _wait = wait - (tv2.tv_usec-tv1.tv_usec); // calc new wait time: this amounts to vblank.
        if(_wait <= 0) { _wait = 1000; }
        else if(_wait >= 16666) { _wait = 10000; }
    //
        if(ENABLE_DEBUG == true) { debug(); }

        // draw will flush entire screen_data[] to terminal. takes about 2% cpu/frame on 2.4ghz dual core
        
        // update screen all at once - don't make more changes after this point.
        fflush(stdout);
    }

    tx_quit();
}

