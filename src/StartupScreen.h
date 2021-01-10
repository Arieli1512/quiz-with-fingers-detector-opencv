#pragma once
#include <iostream>
#include<fstream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "FingersDetector.h"

using namespace std;
using namespace sf;
using namespace cv;


class StartupScreen {
public:
	StartupScreen(RenderWindow& window, VideoCapture camera);
	void showStartingScreen();
private:
	RenderWindow& window;
	VideoCapture camera;
	vector<Sprite> configureSpritesIcons(vector<string>& names, vector<Texture>& textures, vector<Image>& images, int x, int y, int shift);
	Point2f readFromFileCoordinates();
	int detectFingers();
	void configurateStartingScreen(Text& text1, Text& text2, RectangleShape& helloScreen, Texture& questionTexture, Font& font);
	void handleEvent();
};
