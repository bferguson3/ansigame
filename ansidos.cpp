// ANSIGame for DOS
// (c) 2020 Ben Ferguson

#include <IOSTREAM.H>
#include <dos.h>
#include <TIME.H>
#include "../icon2.xpm"

#define GREEN 32
#define FUSCHIA 35
#define BLACK 30
#define WHITE 37
#define RED 31
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36

#define KB_RETURN 0x1c
#define KB_UP 0x48
#define KB_DOWN 0x50
#define KB_LEFT 0x4b
#define KB_RIGHT 0x4d
#define KB_Z 0x2c
#define KB_X 0x2d
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_LEFT 4
#define BUTTON_RIGHT 8
#define BUTTON_A 16
#define BUTTON_B 32


int QUITFLAG = 0;
unsigned char input1 = 0;
unsigned const char ESC = 0x1b;
int fps = 60;
int _wait = 1000 / fps;
int frameskip = 0;

// COLOR SEQ: [##;##m  % BG, FG
// Note: Turbo C++ 3.0's ANSI library does not support 8-bit color
//  and only supports bright toggle function on FG.

void color(int fg, int bg)
{
    //Sets FG and BG at the same time. BG value is FG+10
    cout << ESC << "[" << fg << ";" << bg+10 << "m";
}

void brighten()
{
    //Sets foreground to "bright"
    cout << ESC << "[1m";
}

void reset()
{
    //Clears all break codes, sets text to default colors
    cout << ESC << "[0m";
}

void cls()
{
    //Fills entire screen with " " and positions cursor to top left.
    cout << ESC << "[2J";
}

unsigned char read_key()
{
   //8255 PPI uses ports 60h and 61h for kb control
   unsigned char KB_STATE;
   asm {
       in al, 60h     // read keyboard state into al
       mov KB_STATE, al     //and write to var
       in al, 61h    // get kb control state
       or al, 128
       out 61h, al   // keyboard ack
       xor al, 128
       out 61h, al   // reset PB control
   }
   return KB_STATE;
}

void gameloop()
{
   unsigned char k = read_key();
   if (k >= 128)
   {
       unsigned char kk = k - 128;
       if (kk == KB_UP)
       {
	   input1 &= 0xfe;//-BUTTON_UP - 1;
       }
       else if (kk == KB_DOWN)
       {
	   input1 &= 0xfd;//-BUTTON_DOWN - 1;
       }
       else if (kk == KB_RIGHT)
       {
	   input1 &= -BUTTON_RIGHT - 1;
       }
       else if (kk == KB_LEFT)
       {
	   input1 &= -BUTTON_LEFT - 1;
       }
       else if (kk == KB_Z)
       {
	   input1 &= -BUTTON_A - 1;
       }
       else if (kk == KB_X)
       {
	   input1 &= -BUTTON_B - 1;
       }
   }
   else
   {
       if (k == KB_UP)
       {
	   input1 |= BUTTON_UP;
       }
       else if (k == KB_DOWN)
       {
	   input1 |= BUTTON_DOWN;
       }
       else if (k == KB_LEFT)
       {
	   input1 |= BUTTON_LEFT;
       }
       else if (k == KB_RIGHT)
       {
	   input1 |= BUTTON_RIGHT;
       }
       else if (k == KB_Z)
       {
	   input1 |= BUTTON_A;
       }
       else if (k == KB_X)
       {
	   input1 |= BUTTON_B;
       }
       else if (k == KB_RETURN)
       {
	   QUITFLAG = 1;
       }
   }

}

void movecursor(int x, int y)
{
    if(y < 0)
    {
	cout << ESC << "[" << -y << "A";
    }
    else
    {
	cout << ESC << "[" << y << "B";
    }
    if(x < 0)
    {
	cout << ESC << "[" << -x << "D";
    }
    else
    {
	cout << ESC << "[" << x << "C";
    }
}

int substring(const char* dat, unsigned char sub[], int index, char tgt)
{
    int i = index;
    int p = 0;
    while ((dat[i] != tgt) && (i < 99))
    {
	sub[p] = dat[i];
	i++;
	p++;
    }
    //i--; p--;
    return i;
}

int cstr2int(unsigned char cstr[], int offset)
{
    int m = 1;
    int v = 0;
    for(int p = offset-1; p >= 0; p--)
    {
	v += (cstr[p] - 0x30) * m;
	m *= 10;
    }
    return v;
}

int len(unsigned char c[])
{
   int i = 0;
   while(c[i] != 0)
   {
       i++;
   }
   return i;
}

void draw_xpm(const char* const* data, int x, int y)
{
    movecursor(-99, -99);
    movecursor(x, y);

    // helper routine: substring(0, ' ')
    unsigned char imgx[4];
    int pos = substring(data[0], imgx, 0, ' ');
    int xint = cstr2int(imgx, len(imgx)-1);

    unsigned char imgy[4];
    int pos2 = substring(data[0], imgy, pos+1, ' ');
    int yint = cstr2int(imgy, len(imgy));

    unsigned char cols[3] = {0, 0, 0};
    int pos3 = substring(data[0], cols, pos2+1, ' ');
    int colors = cstr2int(cols, len(cols));

    unsigned char cppx[1] = {0};
    substring(data[0], cppx, pos3+1, ' ');

    cout << "W:" << xint << "H:" << yint << "Clr:" << colors << "Cpp:" << cppx;
}

int main()
{
    //Init:
    reset();
    cls();

    // 18.2 ticks per second means that is our highest FPS.
    if(CLK_TCK < fps)
    {
	fps = CLK_TCK;
	frameskip = 0;
    }

    clock_t start = clock();
    clock_t end = 0;

    while(1)
    {

	gameloop();     //checkinput()

	end = clock();

	if (end-start > frameskip) // Minimum measurable time is 1 tick
	{
	    //DRAW!
	    cls();

	    cout << "FPS:" << fps;

	    draw_xpm(sample_xpm, 10, 10);

	    movecursor(-99, 24);
	    char u,d,l,r;
	    u = 0x1e; d = 0x1f; l = 0x11; r = 0x10;

	    if (input1 & 1)
	    {
		cout << u;
	    }
	    if (input1 & 2)
	    {
		cout << d;
	    }
	    if (input1 & 4)
	    {
		cout << l;
	    }
	    if (input1 & 8)
	    {
		cout << r;
	    }
	    if (input1 & 16)
	    {
		cout << "1";
	    }
	    if (input1 & 32)
	    {
		cout << "2";
	    }

	    movecursor(99, 0);
	    movecursor(-20, 0);
	    color(RED, BLACK);
	    cout << "Press ENTER to quit";
	    reset();

	    cout << flush;
	    start = clock();
	}
	if (QUITFLAG)
	{
	    return 0;
	}
    }
    return 0;
}
