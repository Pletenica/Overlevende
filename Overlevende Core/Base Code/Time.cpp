#include "Time.h"

float Time::time;
float Time::timeScale=1;
float Time::deltaTime;
int Time::frameCount;
float Time::realTimeDeltaTime;
float Time::realTimeSinceStartup;

bool Time::isPaused = false;
bool Time::isPlaying = false;
bool Time::isStop = true;


void Time::Start()
{
	isStop = false;
	isPlaying = true;
	isPaused = false;
}

void Time::Pause()
{
	isStop = false;
	isPlaying = false;
	isPaused = true;
	deltaTime = 0;
}

void Time::Stop()
{
	isStop = true;
	isPlaying = false;
	isPaused = false;

	deltaTime = 0;
	frameCount = 0;
	time = 0;
}

void Time::Update(float dt)
{
	if (isStop == false) {
		
		if (isPlaying == true) {
			deltaTime = dt * timeScale;
			frameCount++;
			time += realTimeDeltaTime;
		}
	}
}