#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "QuestionList.h"
#include "FingersDetector.h"
#include "Screen.h"

using namespace std;
using namespace cv;
using namespace sf;

class CategoryScreen :public Screen {
public:
	CategoryScreen(RenderWindow& window, FingersDetector* fingersDetector) :Screen(window) {
		this->fingersDetector = fingersDetector;
	}
	int showCategoryScreen();
	int getCategory();
private:
	FingersDetector* fingersDetector;
	Time elapsed;
	Clock clock;
	vector<Sprite> configureSpritesIcons(vector<Texture>& textures, vector<Image>& images, int x, int y, int shift);
	int category = 0;
	int timer = 10;
	void configureCategoryBoxes(vector<RectangleShape>& categoryBox, vector<Text>& textCategories);
};
