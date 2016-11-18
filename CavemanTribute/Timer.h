#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "Application.h"

class Timer
{
public:

	Timer();
	void start();
	void stop();
	void pause();
	void unpause();


	Uint32 const getTicks();

	bool const isStarted();
	bool const isPaused();

private:

	Uint32 startTicks;

	Uint32 pausedTicks;

	bool paused;
	bool started;

};

#endif // __TIMER_H__