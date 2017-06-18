#include <curses.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#define DELAY 120000
#define PAUSE

//print pascal's triangle (do symmetric portions simultaneously!)
void print_pascal_triangle();
//visualize factorially the combinations (then pick out the common ones)
void print_factorial_expansion();
//no idea how to do this one yet: be creative! lol (maybe show that they're the same?)
void print_factorial_symmetry();
//show absorption relation because of the adjacency maybe(?)
void print_absorption();
//print pascal's triangle (do symmetric portions simultaneously!)
void print_induction_property();
//this seems hard
void print_negative_combination();
//visualize equivalence with negative combinations
void print_upper_negation();
void print_trinomial_revision();
//OK NOW IT'S THE REAL BREAD AND BUTTER
//expand the binomial theorem graphically(also maybe how the 2^n thing?(that's a side goal I guess, think about how to visualize this some more)
void print_binomial_theorem();
//parallel summation(review)
void print_parallel_summation();
//show upper summation partition trick
void print_upper_summation();
//show convolution! (cool)
void print_vandermonde_convolution();

//I may includ some of the advanced identities later

//12 funcs
#define NUMFUNC 1

enum {NORM=1, HL}; //normal, highlight, dead

void (*demo_ptr_array[ NUMFUNC ])() = { print_pascal_triangle };



int main(int argc, char** argv){
    initscr();
    keypad(stdscr, TRUE); //user can use arrow keys to skip and exit
    curs_set(0);
    noecho();
    start_color();
    init_pair(NORM, COLOR_WHITE,   COLOR_BLACK);
    init_pair(HL,   COLOR_BLACK,  COLOR_CYAN);

    for (int i = 0; i < NUMFUNC; i++){
        clear();
        refresh();
        demo_ptr_array[i]();
#ifdef PAUSE
        mvprintw( LINES - 2 , 2, "hit any key to continue" );
        getch();
#endif
    }


    mvprintw( LINES - 2 , 2, "hit any key to exit" );
    getch();
    endwin();
    return 0;
}

int choose(int n, int k){
    if (k == 0)
        return 1;
    if (k > n-k)
        return (choose(n, n-k));

    return (n*choose(n-1,k-1))/k;
}


void half_pause(){
    usleep( DELAY / 2 );
}

void pause(){
    usleep( DELAY );
}

void print_num(int y, int x, int num){
    attron(COLOR_PAIR(NORM));
    mvprintw(y,x,"%3d",num);
}

void print_highlight_num(int y, int x, int num){
    attron(COLOR_PAIR(HL));
    mvprintw(y,x,"%3d",num);
}

void print_pascal_triangle(){
    int depth = 12;
    int mid = COLS / 2;
    print_num(1,mid, 1);

    for (int i=1; i<depth; i++){
        int start = mid - 6*i/2; //
        int last_start = mid - 6*(i-1)/2; //
        for (int j=0; j<=i; j++){
            //highlight contributors
            int temp = last_start;
            if ((j-1 >= 0)){
                print_highlight_num(i, last_start, choose(i-1,j-1));
                last_start += 6;
            }

            if ((i-1) >= (j)){
                print_highlight_num(i, last_start, choose(i-1,j));
                last_start += 6;
            }
            refresh();
            pause();
            print_highlight_num(i+1, start, choose(i,j));

            refresh();
            pause();
            last_start = temp;

            print_num(i+1, start, choose(i,j));
            start += 6;
            refresh();
            pause();
            

            //unlighlight contributors
            //
            if ((j-1 >= 0)){
                print_num(i, last_start, choose(i-1,j-1));
                last_start += 6;
            }

            if ((i-1) >= (j)){
                print_num(i, last_start, choose(i-1,j));
                last_start += 6;
            }
            last_start -= 6;
        }
    }
}

