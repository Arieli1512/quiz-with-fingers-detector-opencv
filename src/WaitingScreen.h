#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "FingersDetector.h"
#include "Screen.h"

using namespace std;
using namespace cv;
using namespace sf;


class WaitingScreen : public Screen {
public:
	WaitingScreen(RenderWindow& window, FingersDetector* fingersDetector) :Screen(window) {
		this->fingersDetector = fingersDetector;
	}
	int showWaitingScreen();
private:
	FingersDetector* fingersDetector;
	Time elapsed;
	Clock clock;
	int timer = 8;
};