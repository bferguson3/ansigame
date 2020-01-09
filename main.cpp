#include <stdio.h>
#include <iostream>
#include "ansigame.h"
#include <unistd.h>
#include <sys/time.h>

//#include "icon2.xpm"

int fps = 60;           // change to 50 or 30 or 15 if you want
float w = 1000000/fps;
int wait = int(w);
int _wait = wait;
float cpu_pct = 0.0;
float fpscalc = 0.0;

struct timeval framestart, frameend;

bool ENABLE_DEBUG = true;

int frames = 0;

ANSIGame g;

void gameloop()
{
    g.tx_plot2("This is a rendering test!", BCYAN, BLACK, 30, 10);
    // plot colors
/*
    const char* e_c = " ";
    int tc = rand() % 8 + 0x30;
    int bc = rand() % 2;
    char tempc[4] = "30";
    tempc[1] = tc;
    if(bc==1){tempc[0]='9';}
    tx_plot2(e_c, "30", tempc, rand()%X_RESOLUTION, rand()%Y_RESOLUTION);    
*/    
    
    frames++;
    if(frames==fps) { frames = 0; }
}

#include "assets/icon2.xpm"

int init()
{   
    g.disable_key_echo();    
    g.tx_draw_xpm(sample_xpm, 10, 5);
}

int debug()
{
    cpu_pct = (float)((wait-_wait)*100.0 / wait);
    if(cpu_pct>0)
    { 
        g.tx_plot2(std::to_string(cpu_pct).c_str(), BRED, BLACK, 0, 0);
        g.tx_plot2(" % CPU ", WHITE, BLACK, 5, 0);
    }
    
    gettimeofday(&frameend, NULL);
    fpscalc = 1000000.0/((frameend.tv_usec - framestart.tv_usec));
    framestart = frameend;
    if(fpscalc>0)
    {
        g.tx_plot2(std::to_string(fpscalc).c_str(), BCYAN, BLACK, 20, 0);
        g.tx_plot2(" FPS   ", BCYAN, BLACK, 25, 0);
    }
}

int main()
{
    g.wait_for_resize();

    g.clear_screen();

    g.show_cursor(false);    

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
        g.draw();

    // EXEC CODE MARK:
        gettimeofday(&tv2, NULL);
        _wait = wait - (tv2.tv_usec-tv1.tv_usec); // calc new wait time: this amounts to vblank.
        if(_wait <= 0) { _wait = 1; }
        else if(_wait >= wait) { _wait = wait; }
    //
        if(ENABLE_DEBUG == true) { debug(); }

        // update screen all at once - don't make more changes after this point.
        
        fflush(stdout);
    }

    return g.tx_quit();
}

