#include <stdio.h>
#include <iostream>
#include "ansigame.h"
#include <unistd.h>
#include <sys/time.h>
#include <thread>
#include <SFML/Window/Keyboard.hpp>

//#include "icon2.xpm"

using namespace std;

int fps = 60;           // change to 50 or 30 or 15 if you want
float w = 1000000/fps;
int waittime = int(w);
int _wait = waittime;
float cpu_pct = 0.0;
float fpscalc = 0.0;

struct timeval framestart, frameend;

bool ENABLE_DEBUG = true;

int frames = 0;

ANSIGame g;

char inputbuffer[16];

void gameloop()
{
    g.tx_plot2(std::to_string(inputbuffer[0]).c_str(), BCYAN, BLACK, 30, 10);
    
    frames++;
    if(frames==fps) { frames = 0; }
}


void check_input()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            cout << "LEFT";
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        cout << "RIGHT";
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        cout << "UP";
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        cout << "DOWN";
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        cout << "(1)";
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        cout << "(2)";
    }
    cout << "                      ";
}

#include "assets/icon2.xpm"

int init()
{   
    g.key_echo(false);

    g.wait_for_resize();
    g.clear_screen();
    g.show_cursor(false);    

    g.tx_draw_xpm(sample_xpm, 10, 5);

    return 0;
}

int debug()
{
    cpu_pct = (float)((waittime-_wait)*100.0 / waittime);
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

    return 0;
}

int main()
{
    init();
    //thread input_monitor(check_input);

    struct timeval tv1, tv2;

    while(1) // TODO
    { 
        // _wait is the expected FPS in us minus code exec time.
        usleep(_wait);
        //^ somehow replace this with getch?
    // EXEC CODE MARK:
        gettimeofday(&tv1, NULL);
    //
        // run the game loop (bulk of code here!)
        
        gameloop();
        
        g.draw();
        check_input();   
    // EXEC CODE MARK:
        gettimeofday(&tv2, NULL);
        _wait = waittime - (tv2.tv_usec-tv1.tv_usec); // calc new wait time: this amounts to vblank.
        if(_wait <= 0) { _wait = 1; }
        else if(_wait >= waittime) { _wait = waittime; }
    //
        if(ENABLE_DEBUG == true) { debug(); }

        // update screen all at once - don't make more changes after this point.
        
        fflush(stdout);

    }
    //input_monitor.join();
    return g.tx_quit();
}

