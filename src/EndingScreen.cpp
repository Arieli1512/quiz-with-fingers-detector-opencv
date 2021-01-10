#include "EndingScreen.h"


EndingScreen::EndingScreen(RenderWindow& window, VideoCapture camera) :window(window) {
	this->camera = camera;
};

void EndingScreen::setScore(int score) {
	this->score = score;
}
void EndingScreen::handleEvent() {
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			window.close();
			break;
		case Event::Resized:
			break;
		}
	}
}

int EndingScreen::getStatus() {
	return this->status;
}
int EndingScreen::detectFingers() {
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
	cout << numOfFingers << endl;
	return numOfFingers;
}

void EndingScreen::configureEndingScreen(wstring endPoints) {
	font.loadFromFile("../fonts/AllerDisplay.ttf");
	gameOver.setFont(font);
	gameOver.setCharacterSize(40);
	gameOver.setString(L"Gra skoñczona, Twój wynik to: " + to_string(score) + endPoints);
	gameOver.setOrigin(gameOver.getLocalBounds().width / 2.0f, gameOver.getLocalBounds().height / 2.0f);
	gameOver.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	summary.setFont(font);
	summary.setCharacterSize(50);
	proposal.setFont(font);
	proposal.setCharacterSize(45);
	proposal.setString(L"5 ...");
	proposal.setOrigin(proposal.getLocalBounds().width / 2.0f, proposal.getLocalBounds().height / 2.0f);
	proposal.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + 180);

	if (score > 7) {
		summary.setString("Gratulacje!");
		summary.setCharacterSize(50);
		summary.setFillColor(Color::Green);
		image.loadFromFile("../imagesSfml/fire-cracker.png");
		image2.loadFromFile("../imagesSfml/fire-cracker2.png");
	}
	else if (score >= 5) {
		summary.setString(L"Niez³y wynik!");
		summary.setCharacterSize(40);
		summary.setFillColor(Color::Green);
		image.loadFromFile("../imagesSfml/smile.png");
		image2.loadFromFile("../imagesSfml/fire-cracker2.png");
	}
	else {
		summary.setString(L"Mo¿e spróbuj jeszce raz?");
		summary.setCharacterSize(35);
		image.loadFromFile("../imagesSfml/sad.png");
		image2.loadFromFile("../imagesSfml/sad.png");
	}
	texture.loadFromImage(image);
	texture2.loadFromImage(image2);
	sprite.setTexture(texture);
	sprite.setPosition(200, 100);
	sprite2.setTexture(texture2);
	sprite2.setPosition(850, 100);
	summary.setOrigin(summary.getLocalBounds().width / 2.0f, summary.getLocalBounds().height / 2.0f);
	summary.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 150);
}

void EndingScreen::showEndingScreen() {
	RectangleShape screen(Vector2f(1200.0f, 650.0f));
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("../imagesSfml/baner.jpg");
	screen.setTexture(&backgroundTexture);
	wstring endPoints;
	if (score == 1) {
		endPoints = L" punkt";
	}
	else if (score > 1 && score < 5) {
		endPoints = L" punkty";
	}
	else
		endPoints = L" punktów";
	configureEndingScreen(endPoints);
	int numOfFingers = 0;
	Time elapsed;
	Clock clock;
	clock.restart();
	int timer = 5;
	while (true)
	{
		window.clear();
		try { numOfFingers = detectFingers(); }
		catch (Exception& e) {};
		elapsed = clock.getElapsedTime();
		int timeRemained = timer - (int)elapsed.asSeconds();
		proposal.setString(to_string(timeRemained)+" ...");

		if ((int)elapsed.asSeconds() > (timer - 1)) {
			proposal.setString(L"Aby zagraæ jeszcze raz, poka¿ 4 palce!");
			proposal.setOrigin(proposal.getLocalBounds().width / 2.0f, proposal.getLocalBounds().height / 2.0f);
			if (numOfFingers == 4) {
				status = 1;
				break;
			}
		}
		window.draw(screen);
		window.draw(gameOver);
		window.draw(summary);
		window.draw(proposal);
		window.draw(sprite);
		window.draw(sprite2);
		window.display();
		handleEvent();
	}
}

