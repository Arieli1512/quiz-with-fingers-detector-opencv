#include "WaitingScreen.h"

WaitingScreen::WaitingScreen(RenderWindow& window, VideoCapture camera) :window(window) {
	this->camera = camera;
};

void WaitingScreen::handleEvent() {
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::Resized:
			break;
		}
	}
}

void WaitingScreen::showWaitingScreen() {
	window.clear();
	clock.restart();
	Font font;
	Texture questionTexture;
	questionTexture.loadFromFile("../imagesSfml/baner.jpg");
	font.loadFromFile("../fonts/AllerDisplay.ttf");
	RectangleShape waitScreen(Vector2f(1200.0f, 650.0f));
	waitScreen.setTexture(&questionTexture);
	Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));
	while (true) {
		window.clear();
		window.draw(waitScreen);
		elapsed = clock.getElapsedTime();
		int timeRemained = timer - (int)elapsed.asSeconds();
		if (timeRemained == 0) {
			clock.restart();
			return;
		}
		text.setString(L"Quiz rozpocznie siê za " + to_string(timeRemained) + " ...");
		text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
		try { detectFingers(); }
		catch (exception& e) {}
		window.draw(text);
		window.display();
		handleEvent();
	}
}


int WaitingScreen::detectFingers() {
	FingersDetector fingersDetector;
	Mat img, partImg;
	camera.read(img);
	cv::Rect rect = cv::Rect(cv::Point2f(10, 10), cv::Point2f(300 + 10, 300 + 10));
	rectangle(img, cv::Point2f(10, 10), cv::Point2f(300 + 10, 300 + 10), cv::Scalar(255, 0, 0));
	partImg = img(rect);
	cv::imshow("window real", img);
	int numOfFingers = fingersDetector.countFingers(partImg);
	Mat contoursImage = fingersDetector.getContoursImage();
	cv::putText(contoursImage, to_string(numOfFingers), cv::Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 3);
	cv::imshow("window", contoursImage);
	return numOfFingers;
}