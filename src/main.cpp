#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "StartupScreen.h"
#include "WaitingScreen.h"
#include "CategoryScreen.h"
#include "GameScreen.h"
#include "EndingScreen.h"
#include "FingersDetector.h"

using namespace std;
using namespace sf;
using namespace cv;

int main() {
	FingersDetector* fingersDetector = new FingersDetector();
	RenderWindow window(VideoMode(1200.0f, 650.0f), "Quiz", Style::Close | Style::Resize);
	StartupScreen startupScreen(window, fingersDetector);
	WaitingScreen waitingScreen(window, fingersDetector);
	CategoryScreen categoryScreen(window, fingersDetector);
	GameScreen gameScreen(window, fingersDetector);
	EndingScreen endingScreen(window, fingersDetector);
	int score = 0, status = 0;

	while (true) {
		startupScreen.showStartingScreen();
		categoryScreen.showCategoryScreen();
		int category = categoryScreen.getCategory();
		waitingScreen.showWaitingScreen();
		gameScreen.setCategory(category);
		gameScreen.showGameScreen();
		score = gameScreen.getScore();
		endingScreen.setScore(score);
		endingScreen.showEndingScreen();
		status = endingScreen.getStatus();
		if (status == 1) {
			delete fingersDetector;
			break;
		}
	}

	return 0;
}
