#pragma once

static class Time {
public:
	static int frameCount;

	static float time;
	static float timeScale;
	static float deltaTime;
	static float realTimeSinceStartup;
	static float realTimeDeltaTime;

	static void Start();
	static void Pause();
	static void Stop();
	static void Update(float dt);

	static bool isPaused;
	static bool isPlaying;
	static bool isStop;
};