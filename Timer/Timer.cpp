#include "Timer.h"

//Note that if timestep is in -1 mode, timer will be issued directly to a delay, meaning it cannot be stopped.

Timer::Timer(std::function<void()> callback, int duration, int timeStep, OnComplete CompletionBehaviour)
{
	mCompletionBehaviour = CompletionBehaviour;
	mDuration = duration;
	mCallback = callback;

	//All values less than 10 for timestep will be processed as -1
	if (timeStep < 10 && timeStep != -1) {
		printf("WARNING :: Using a timestep lower than 10 is not reccomended, steps will not be used.");
		mTimeStep = -1;
	}
	else {
		mTimeStep = timeStep;
	}

	mTimeRemaining = duration;

	beginThread();
}

Timer::~Timer() {
	if (mThread.joinable()) {
		mThread.join();
	}
}

void Timer::beginThread() {
	mThread = std::thread([this]() {
		runTimer();
		});
	mThread.detach();
}

void Timer::start() {
	mIsRunning = true;
	mCv.notify_one();  // Notify the timer thread to resume
}
void Timer::stop() {
	mIsRunning = false;
	mCv.notify_one();  // Notify the timer thread to stop
}
void Timer::reset() {
	mTimeRemaining = mDuration;
	stop();
	return;
}
void Timer::restart() {
	reset();
	start();
	return;
}
void Timer::complete() {
	mCallback();
	switch (mCompletionBehaviour) {
	case(OnComplete::STOP):
		stop();
		break;
	case(OnComplete::RESET):
		reset();
		break;
	case(OnComplete::RESTART):
		restart();
		break;
	}
	return;
}

void Timer::runTimer()
{
	std::unique_lock<std::mutex> mLock(mMtx);
	while (true) {
		mCv.wait(mLock, [this] { return mIsRunning; });
		if (mTimeStep == -1) {
			mLock.unlock();  // Unlock before sleeping to avoid mutex destruction while holding the lock
			std::this_thread::sleep_for(std::chrono::milliseconds(mDuration));
			mLock.lock();  // Reacquire the lock after waking up
		}
		else {
			while (mIsRunning) {
				if (mTimeRemaining <= 0) {
					break;
				}
				printf("Time Remaining : %f\n", mTimeRemaining / 1000.0f);
				mLock.unlock();  // Unlock before sleeping to avoid mutex destruction while holding the lock
				std::this_thread::sleep_for(std::chrono::milliseconds(mTimeStep));
				mLock.lock();  // Reacquire the lock after waking up
				mTimeRemaining -= mTimeStep;
			}
		}
		if (mIsRunning) {
			complete();
		}
	}
}