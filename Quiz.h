#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Question.h"
#include "QuestionList.h"
#include "FingersDetector.h"

using namespace std;
using namespace sf;
using namespace cv;

class Quiz {
private:
	RenderWindow window;
	RectangleShape questionBox;
	vector<RectangleShape> answersBox;
	QuestionList questionList;
	FingersDetector fingersDetector;
	Texture button, questionTexture;
	Text textAnswers, textQuestions;
	vector<Text> answersText;
	Font font;
	Event event;
	Text currentQuestion;
	VideoCapture camera;
	Mat drawing;
	Time elapsed;
	Clock clock;

	int qs = 0;
	int timer = 10;
	int totalQuestions = 10;
	int flag = 0;
	int score = 0;
	int numOfFingers = 0;

	vector<Sprite> configureSpritesIcons(vector<string>& names, vector<Texture>& textures, vector<Image>& images);
	void configurateStartingScreen(Text& text1, Text& text2, RectangleShape& helloScreen);
	void setUpBoxes();
	void checkAnswer();
	void configureText(Text& textP, Text& currentScore, Text& timerW);
	void showContentOnScreen(int i);
public:
	Quiz(RectangleShape questionBox, vector<RectangleShape> answersBox)
		:window(VideoMode(1200.0f, 650.0f), "Quiz", Style::Close | Style::Resize)
	{
		this->questionBox = questionBox;
		this->answersBox = answersBox;
	}
	void setUp();
	void clockReset();
	void configureCamera();
	void showStartingScreen();
	void showWaitingScreen();
	void showEndingScreen();
	void handleEvent();
	int detectFingers();
	int handleAnswers();
};

