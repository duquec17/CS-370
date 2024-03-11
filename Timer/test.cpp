#include <stdio.h>
#include <SDL.h>
#include "Timer.h"
#undef main

bool timerADone = false, timerBDone = false;

void timerComplete();
void timerTest();

int testIndex = 0;

int main() {
	timerTest();
	return 0;
}
void blank() { printf("blank\n"); }
void timerTest() {
	printf("Test Begin\n");
	Timer
		testTimerA(timerComplete, 3000, 1000, Timer::OnComplete::STOP),
		testTimerB(timerComplete, 3000, -1, Timer::OnComplete::STOP),
		testTimerC(blank, 1000, 1000, Timer::OnComplete::RESTART),
		testTimerD(blank, 1000, -1, Timer::OnComplete::RESTART);

	//printf("Testing Timer A\n");
	//testTimerA.start();
	//while (!timerADone) { SDL_Delay(1000); printf("Doing Work\n"); };

	//printf("Testing Timer B\n");
	//testTimerB.start();
	//while (!timerBDone);

	SDL_Delay(3000);

	printf("Testing Timer C\n");
	testTimerC.start();
	SDL_Delay(3000);
	testTimerC.stop();

	SDL_Delay(5000);

	printf("Testing Timer D\n");

	testTimerD.start();
	SDL_Delay(3000);
	testTimerD.stop();

	printf("Test Complete\n");
}

void timerComplete() {
	printf("Timer Completed\n");

	switch (testIndex) {
	case(0):
		timerADone = true;
		break;
	case(1):
		timerBDone = true;
		break;
	}

	testIndex++;
}