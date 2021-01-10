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

class CategoryScreen {
public:
	CategoryScreen(RenderWindow& window, VideoCapture camera);
	void showCategoryScreen();
	int getCategory();
private:
	VideoCapture camera;
	RenderWindow& window;
	Time elapsed;
	Clock clock;
	vector<Sprite> configureSpritesIcons(vector<Texture>& textures, vector<Image>& images, int x, int y, int shift);
	int category = 0;
	int timer = 3;
	void handleEvent();
	void configureCategoryBoxes(vector<RectangleShape>& categoryBox, vector<Text>& textCategories);
	int detectFingers();
};
