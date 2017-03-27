#include <curses.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 150000

#define MAX 32

enum {NORM=1, HL, DEAD}; //normal, highlight, dead

bool is_dead[MAX]={0}; /* 1 is dead, 0 is alive*/


//better thing to do is make all these functions one function but you should send me that version dude
void highlight_guy(int i){
    int pos = i*3 + 2;
    attron(COLOR_PAIR(HL));
    mvprintw(2, pos,  "%02d",i+1);
}
void unhighlight_guy(int i){
    int pos = i*3 + 2;
    attron(COLOR_PAIR(NORM));
    mvprintw(2, pos, "%02d",i+1);
}
void kill_guy(int i){
    int pos = i*3 + 2;
    attron(COLOR_PAIR(DEAD));
    mvprintw(2, pos, "%02d",i+1);
}

int main(int argc, char** argv){

    int k=2;   //every Kth person commits peer pressured suicide
    int k_c=1; //counter for above
    int i;     //main counter
    int left_alive;
    int number_of_dudes; 
    if (argc > 1){
        number_of_dudes = left_alive = atoi(argv[1] > MAX) ? MAX : atoi(argv[1]);
    } else {
        number_of_dudes = left_alive = MAX;
    }
    //ok we have everything we need for the problem

    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    start_color();
    init_pair(NORM, COLOR_WHITE,   COLOR_BLACK); //normal
    init_pair(HL,   COLOR_YELLOW,  COLOR_CYAN);  //highlight
    init_pair(DEAD, COLOR_MAGENTA, COLOR_RED);   //dead

    //print all of these out, starting on the second line
    move(2,1);
    for (i=0; i<number_of_dudes; i++){
        addch(' ');
        printw("%02d",i+1);
    }
    i=0;

    refresh();
    usleep(DELAY);

    while(left_alive > 1) {
        i++;
        i = i>=number_of_dudes ? 0 : i;
        if (!is_dead[i]){
            k_c++;
            highlight_guy(i);
            refresh();
            usleep(DELAY);
    
            if (k_c == k){
                kill_guy(i);
                is_dead[i]=1;
                left_alive--;
                refresh();
                usleep(DELAY);
                k_c = 0;
            }
            else{
                unhighlight_guy(i);
                usleep(DELAY / 2);
            }
        }
    }

    //wait for input before exiting
    getch();
    endwin();
}
