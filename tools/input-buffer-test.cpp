//#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <thread>

using namespace std;
 
char c = ' ';

void check_input()
{
    
    struct termios t;
    tcgetattr(0, &t);    
    t.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSAFLUSH, &t);

    fstream fs;
    fs.open("output", ios::out);
    streambuf* sb_cout = cout.rdbuf();
    streambuf* sb_cin = cin.rdbuf();
    streambuf* sb_file = fs.rdbuf();
    cout.rdbuf(sb_file);
    while(1){
        cin >> c;
        cout << c;
    }

    fs.close();
}


int main()
{
    thread t(check_input);
    while(1){
        printf("%c[100D!", 0x1b);
    }
    t.join();
    return 0;
}

