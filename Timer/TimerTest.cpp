#include "Timer.h"


#define STOP Timer::OnComplete::STOP
#define RESET Timer::OnComplete::RESET
#define RESTART Timer::OnComplete::RESTART

bool is_done = false;
int runs = 1;

void complete_timer() {
    std::cout << "\tTimer Completed" << std::endl;
    is_done = true;
    return;
}
void step_timer() {
    runs ++;
    std::cout << "Run: " << runs << std::endl;
    return;
}

int main(int argc, char *argv[]) {
    std::cout << "\t1 Second in twentieths" << std::endl;
    Timer t1(complete_timer, 1000, 50, STOP);
    t1.start();
    while(!is_done) {};
    is_done = false;
    t1.start();
    while(!is_done) {std::cout << "Didn't reset" << std::endl;}
    is_done = false;

    std::cout << std::endl << "\t1 second ran 5 times" << std::endl;
    Timer t2(step_timer, 1000, 200, RESET);
    std::cout << "Run: " << runs << std::endl;
    while(runs < 5) {t2.start();}
    runs = 1;

    std::cout << std::endl << "\t6 second timer stopped after 3 seconds, then resumed after another 3" << std::endl;
    Timer t3a(complete_timer, 6000, 1000, STOP);
    Timer t3b(complete_timer, 3000, 5, RESTART);
    t3a.start();
    t3b.start();
    while(runs < 2) {
        while(!is_done) {};
        t3a.stop();
        is_done = false;
        while(!is_done) {};
        t3a.start();
        t3b.stop();
        is_done = false;
        while(!is_done) {};
        runs ++;
    }
    is_done = false;
    runs = 1;

    std::cout << std::endl << "\t6 second timer forcibly completed after 3 seconds" << std::endl;
    Timer t4a(complete_timer, 6000, 1000, STOP);
    Timer t4b(complete_timer, 3000, -1, STOP);
    t4a.start();
    t4b.start();
    while(runs < 2) {
        while(!is_done) {};
        is_done = false;
        t3a.complete();
        while(!is_done) {};
        runs ++;
    }
    is_done = false;
    runs = 1;

    std::cout << "\n\nDone!" << std::endl;
    exit(EXIT_SUCCESS);
}
