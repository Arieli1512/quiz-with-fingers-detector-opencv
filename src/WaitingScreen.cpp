#include "WaitingScreen.h"

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
		try { fingersDetector->detectFingers(); }
		catch (exception& e) {}
		window.draw(text);
		window.display();
		handleEvent();
	}
}
