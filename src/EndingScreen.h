#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "QuestionList.h"
#include "FingersDetector.h"

using namespace std;
using namespace cv;
using namespace sf;


class EndingScreen {
public:
	EndingScreen(RenderWindow& window, VideoCapture camera);
	void showEndingScreen();
	void setScore(int score);
	int getStatus();
private:
	VideoCapture camera;
	RenderWindow& window;
	Texture texture, texture2;
	Image image, image2;
	Sprite sprite, sprite2;
	Text gameOver, summary, proposal;
	Font font;
	int score = 0;
	int status = 0;
	void handleEvent();
	void configureEndingScreen(wstring endPoints);
	int detectFingers();
};