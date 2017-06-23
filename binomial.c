#include <curses.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#define DELAY 120000
#define PAUSE

void print_pascal_triangle();
void print_factorial_expansion();
//void print_factorial_symmetry();
//void print_negative_combination();
//void print_upper_negation();
void print_trinomial_revision();
//OK NOW IT'S THE REAL BREAD AND BUTTER
void print_parallel_summation();
void print_upper_summation();
void print_vandermonde_convolution();

//I may includ some of the advanced identities later

//12 funcs
#define NUMFUNC 2

enum {NORM=1, HL, REDHL, GREENHL, YELLOWHL, WHITEHL, BLUEHL};

void (*demo_ptr_array[ NUMFUNC ])() = { print_pascal_triangle, print_factorial_expansion};



int main(int argc, char** argv){
    initscr();
    keypad(stdscr, TRUE); //user can use arrow keys to skip and exit
    curs_set(0);
    noecho();
    start_color();
    init_pair(NORM, COLOR_WHITE,   COLOR_BLACK);
    init_pair(HL,   COLOR_BLACK,  COLOR_CYAN);
    init_pair(REDHL,   COLOR_BLACK,  COLOR_RED);
    init_pair(GREENHL,   COLOR_BLACK,  COLOR_GREEN);
    init_pair(YELLOWHL,   COLOR_BLACK,  COLOR_YELLOW);
    init_pair(WHITEHL,   COLOR_BLACK,  COLOR_WHITE);
    init_pair(BLUEHL,   COLOR_WHITE,  COLOR_BLUE);

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

void print_highlight_num(int y, int x, int num, int myHL){
    attron(COLOR_PAIR(myHL));
    mvprintw(y,x,"%3d",num);
}


//print pascal's triangle (do symmetric portions simultaneously!)
void print_pascal_triangle(){
    int depth = 2;
    int mid = COLS / 2;
    print_num(1,mid, 1);

    for (int i=1; i<depth; i++){
        int start = mid - 6*i/2; //
        int last_start = mid - 6*(i-1)/2; //
        for (int j=0; j<=i; j++){
            //highlight contributors
            int temp = last_start;
            if ((j-1 >= 0)){
                print_highlight_num(i, last_start, choose(i-1,j-1), HL);
                last_start += 6;
            }

            if ((i-1) >= (j)){
                print_highlight_num(i, last_start, choose(i-1,j), HL);
                last_start += 6;
            }
            refresh();
            pause();
            print_highlight_num(i+1, start, choose(i,j), HL);

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


/*
//this is the worst
int tuple[10][10][10] = {0};
int have_i_seen_this_tuple(int x, int y, int z){
    int min, med, max;
    if (x < y && x < z){
        min = x;
        if (y < z){
            med = y;
            max = z;
        }
        else{
            med = z;
            max = y;
        }
    }

    else if (y < x && y < z){
        min = y;
        if (x < z){
            med = x;
            max = z;
        }
        else{
            med = z;
            max = x;
        }
    }

    else{
        min = z;
        if (y < x){
            med = y;
            max = x;
        }
        else{
            med = x;
            max = y;
        }
    }
    if(tuple[min][med][max] == 0){
        tuple[min][med][max] = 1;
        return 0;
    }
    return 1;
}*/

//visualize factorially the combinations (then pick out the common ones)
void print_factorial_expansion(){
    int o_x = 3;
    int o_y = 3;
    int space = 6;
    int n=5;
    int k=3;

    //first print all the numbers
    for (int i=1; i<=n; i++){
        print_num(o_y, o_x + space*i, i);
    }

    //now enumerate all combinations
    for (int x=1; x<=n; x++){
        print_highlight_num(o_y, o_x + space*x, x, HL);
        int spacing = 1;
        for (int y=1; y<=n; y++){
            for (int z=1; z<=n; z++){
                if (y != x && z != y && x != z){
                    attron(COLOR_PAIR(NORM));
                    mvprintw(o_y + spacing, o_x + space*x,"%d,%d,%d", x,y,z);
                    print_highlight_num(o_y, o_x + space*y, y, REDHL);
                    print_highlight_num(o_y, o_x + space*z, z, GREENHL);
                    spacing++;
                    refresh();
                    pause();

                    print_num(o_y, o_x + space*y, y);
                    print_num(o_y, o_x + space*z, z);
                }
            }
        }
        print_num(o_y, o_x + space*x, x);
    }

    //ok, now just highlight all the repetitions
    for (int x=1; x<=n; x++){
        print_highlight_num(o_y, o_x + space*x, x, HL);
        int spacing = 1;
        for (int y=1; y<=n; y++){
            for (int z=1; z<=n; z++){
                if (y != x && z != y && x != z){
                    int color = (x + y + z) % 6 + 2;
                    attron(COLOR_PAIR( color ));
                    mvprintw(o_y + spacing, o_x + space*x,"%d,%d,%d", x,y,z);
                    spacing++;

                    print_num(o_y, o_x + space*y, y);
                    print_num(o_y, o_x + space*z, z);
                }
            }
        }
        print_num(o_y, o_x + space*x, x);
    }
    refresh();
    pause();
    
}

//no idea how to do this one yet: be creative! lol (maybe show that they're the same?)
//void print_factorial_symmetry(){}

//this seems hard
//void print_negative_combination(){
//}

//visualize equivalence with negative combinations
//void print_upper_negation(){
//}

//thing
//void print_trinomial_revision(){}


//parallel summation(review)
void print_parallel_summation(){
}

//show upper summation partition trick
void print_upper_summation(){
}

//show convolution! (cool)
void print_vandermonde_convolution(){
}
