#include <curses.h>
#include <math.h>
#include <unistd.h>
#define DELAY 130000
#define PAUSE

static int n = 8;
static int sv=1;

void print_summation_i_j_normal(){
    printw( "\n    Summation 1<=i<=j<=n  in row->column order\n"
            "    with logic : \n"
            "    for (i=0; i<=n; i++){    \n"
            "        for (j=i; j<=n; j++){ \n"
            "    --------------------------------");

    int offset = 7;
    int i,j;
    for (i=sv; i<=n; i++){
        for (j=i; j<=n; j++){
            mvprintw(offset + i, j*4," %d,%d",i,j);
            refresh();
            usleep(DELAY);
        }
    }
}

void print_summation_i_j_reverse_order(){
    printw( "\n    Summation 1<=i<=j<=n reversed column->row order\n"
            "    with logic : \n"
            "    for (j=0; j<=n; j++){    \n"
            "        for (i=0; i<=j; i++){ \n"
            "    --------------------------------");

    int i,j;
    int offset = 7;
    for (j=sv; j<=n; j++){
        for (i=sv; i<=j; i++){
            mvprintw(offset + i, j*4," %d,%d",i,j);
            refresh();
            usleep(DELAY);
        }
    }
}

int main(int argc, char** argv){
    initscr();
    keypad(stdscr, TRUE); //user can use arrow keys to skip and exit

    print_summation_i_j_normal();

#ifdef PAUSE
    mvprintw( LINES - 2 , 2, "hit any key to continue" );
    getch();
#endif

    clear();
    refresh();

    print_summation_i_j_reverse_order();

    mvprintw( LINES - 2 , 2, "hit any key to exit" );
    getch();
    endwin();
}

