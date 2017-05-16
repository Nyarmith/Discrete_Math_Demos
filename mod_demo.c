#include <curses.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#define DELAY 180000
#define PAUSE

//just the mods for n^p, for each power of n and p
void print_fermat_last_theorem();

void print_mod_congruence();

//system of congruences
void print_mod_residues();

//stern-brocot tree
void print_mod_trees();

//gcd algorithm
void print_euclid_algorithm();

#define NUMFUNC 5

//try pointer array for fun here
void (*demo_ptr_array[ NUMFUNC ])() = {print_fermat_last_theorem, print_mod_congruence, print_mod_residues, print_mod_trees, print_euclid_algorithm};



int main(int argc, char** argv){
    initscr();
    keypad(stdscr, TRUE); //user can use arrow keys to skip and exit



    //run through the functions in our array
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


//just the mods for n^p, for each power of n and p
void print_fermat_last_theorem(){
    int prime = 11;
    int a = 4;
    int cur_a=4;
    for (int i=1; i<= 11; i++){
        mvprintw(i,3,"%d^%d mod %d =%d mod %d = %d", a, i, prime, cur_a, prime, cur_a % prime);
        cur_a *= 4;
        refresh();
        usleep(DELAY);
    }
}

//man, what was this supposed to be again
void print_mod_congruence(){
    //print congruences with some random numbers
    int mod = rand() % 8;
    int a = rand()%4;

    if (mod <= 1){ mod = 2; }

    mvprintw(2,2,"%d mod %d = %d", a, mod, a % mod);
    for (int i=0; i< 8; i++){
        printw(" = %d mod %d", a + (rand()%37)*mod, mod);
        refresh();
        usleep(DELAY);
    }
}

//system of congruences
void print_mod_residues(){
    int a=3;
    int b=5;
    int x=0;
    for (int i=0; i<3; i++){
        for (int j=0; j<5; j++){
            printw("%d mod %d = %d    ", x, b*a, x % (b*a));
            refresh();
            usleep(DELAY / 2);
            printw("%d mod %d = %d    ", x, a, x % a);
            refresh();
            usleep(DELAY / 2);
            printw("%d mod %d = %d\n", x, b, x % b);
            refresh();
            usleep(DELAY);
            x++;
        }
    }
}


void print_tree(int left, int right, int ml, int nl, int mr, int nr, int depth){

    if (depth >= 5) //our base case or whatever
        return ;

    int m = ml + mr;
    int n = nl + nr;
    int medium = (left + right) / 2;

    mvprintw(depth + 2, medium, "%d/%d", m, n);
    refresh();
    usleep( DELAY / 2 );

    print_tree(left,  medium, ml, nl, m, n, depth+1);
    print_tree(medium, right, m, n, mr, nr, depth+1);
}

//stern-brocot tree
void print_mod_trees(){
    int m = 0;
    int n=1;
    int m_ = 1;
    int n_ = 0;
    mvprintw(  1, 1, "0/1");
    refresh();
    usleep( DELAY / 2 );
    mvprintw(  1, COLS - 4 , "1/0" );
    refresh();
    usleep( DELAY / 2 );
    print_tree(1, COLS-1, m, n, m_, n_, 0);
}

void print_gcd(int n, int m){

    printw( "gcd( %d , %d ) = \n", n, m);
    refresh();
    usleep( DELAY / 2 );

    if (n <= 0){
        return 0;
    }
    if (m <= 0){
        return 0;
    }

    print_gcd(m % n, n);

}

//gcd algorithm
void print_euclid_algorithm(){
    move(2,2);   
    print_gcd(1027, 576);
}

