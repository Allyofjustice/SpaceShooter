class MyTimer{

public:
	MyTimer();
	void start();
	void pause();
	void unpause();
	void stop();

	bool isStarted();
	bool isPaused();

	int getTicks();

private:
	int startTicks;
	int pausedTicks;

	bool paused;
	bool started;

};

