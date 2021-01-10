#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "FingersDetector.h"

using namespace std;
using namespace cv;
using namespace sf;


class WaitingScreen {
public:
	WaitingScreen(RenderWindow& window, VideoCapture camera);
	void showWaitingScreen();
private:
	VideoCapture camera;
	RenderWindow& window;
	Time elapsed;
	Clock clock;
	int timer = 5;
	int detectFingers();
	void handleEvent();
};