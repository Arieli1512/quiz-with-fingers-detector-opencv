#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

using namespace std;
using namespace sf;
using namespace cv;


class Screen {
public:
	Screen(RenderWindow& window) :window(window) {}
protected:
	RenderWindow& window;
	int handleEvent();
};