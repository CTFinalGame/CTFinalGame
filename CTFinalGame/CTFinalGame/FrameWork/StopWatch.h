
#ifndef __STOP_WATCH__
#define __STOP_WATCH__

#include "GameTime.h"

NS_FRAMEWORK
NS_FRAMEWORK_BEGIN

typedef void(*pFunction)(void);

class StopWatch
{
public:
	StopWatch();
	~StopWatch();

	bool isFinish();
	bool isTimeLoop(float time);
	bool isStopWatch(float time);
	void restart();
private:
	float	_stopwatch;
	bool	_isStart;
	bool	_isFinish;
};

NS_FRAMEWORK_END

#endif // !__STOP_WATCH__
