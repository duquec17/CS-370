#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__

#include <iostream>
#include <functional>
#include <thread>
#include <future>
#include <vector>
#include <chrono>

class Timer {
public:
	enum OnComplete { STOP, RESET, RESTART };

	Timer(std::function<void()> callback, int duration, int timeStep, OnComplete CompletionBehaviour);
	~Timer();

	void start(), stop(), reset(), restart(), complete();

	int timeRemaining();

private:
	bool mIsRunning = false;
	OnComplete mCompletionBehaviour;
	int mDuration, mTimeRemaining, mTimeStep;
	std::function<void()> mCallback;
	std::thread mThread;

	std::condition_variable mCv;
	std::mutex mMtx;

	void runTimer(), beginThread();
};

#endif  /* __TIMER_H__ */

