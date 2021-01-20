#include "GameScreen.h"

void GameScreen::setCategory(int category) {
	this->category = category;
}


int GameScreen::showGameScreen() {
	Time elapsed;
	Clock clock;
	RectangleShape screen(Vector2f(1200.0f, 650.0f));
	vector<RectangleShape> answerBoxes(5, RectangleShape(Vector2f(240, 220)));
	Texture backgroundTexture;
	int question = 0, numOfFingers = 0, qs = 0;
	QuestionList questionList;
	if (readCategoryFile(questionList) == -1)
		return -1;
	backgroundTexture.loadFromFile("../imagesSfml/baner.jpg");
	screen.setTexture(&backgroundTexture);
	font.loadFromFile("../fonts/AllerDisplay.ttf");
	textAnswers.setCharacterSize(24);
	textAnswers.setFont(font);
	vector<Text> answersText(5, textAnswers);
	configureGameScreen(answerBoxes, answersText);
	clock.restart();
	score = 0;
	feedbackText.setString("");
	while (true) {
		window.clear();
		elapsed = clock.getElapsedTime();
		int timeRemained = timer - (int)elapsed.asSeconds();
		if ((int)elapsed.asSeconds() > (timer - 1)) {
			int correctAnswer = questionList.getQuestionArray().at(qs).getCorrectAnswer();
			checkAnswer(numOfFingers, correctAnswer, qs, feedbackText, currentQuestion);
			clock.restart();
			if (qs == totalQuestions)
				break;
		}
		currentScore.setString("Punkty " + to_string(score));
		if (timeRemained < 4)
			timerText.setColor(Color::Red);
		else timerText.setColor(Color::White);

		timerText.setString(to_string(timeRemained));
		string mystr = "Pytanie ";
		mystr.append(to_string(qs + 1));
		mystr.append(" / ");
		mystr.append(to_string(totalQuestions));
		currentQuestion.setString(mystr);
		try { numOfFingers = fingersDetector->detectFingers(); }
		catch (Exception& e) {}
		wstring questionString = questionList.getQuestionArray().at(qs).getQuestion();
		textQuestions.setString(sf::String::fromUtf8(questionString.begin(), questionString.end()));
		textQuestions.setOrigin(textQuestions.getLocalBounds().width / 2.0f, textQuestions.getLocalBounds().height / 2.0f);
		drawOnWindow(screen, answerBoxes, answersText, questionList, qs);
		window.display();
		if (handleEvent() == -1) {
			fingersDetector->closeCamera();
			delete fingersDetector;
			return -1;
		}
	}
}

void GameScreen::drawOnWindow(RectangleShape& screen, vector<RectangleShape>& answerBoxes,
	vector<Text>& answersText, QuestionList& questionList, int qs) {
	window.draw(screen);
	for (int i = 0; i < answerBoxes.size(); i++) {
		wstring answersString = questionList.getQuestionArray().at(qs).getAnswers().at(i);
		answersText[i].setString(sf::String::fromUtf8(answersString.begin(), answersString.end()));
		answersText[i].setFillColor(Color::White);
		answerBoxes[i].setOrigin(answerBoxes[i].getSize().x / 2.0f, answerBoxes[i].getSize().y / 2.0f);
		answersText[i].setOrigin(answersText[i].getLocalBounds().width / 2.0f, answersText[i].getLocalBounds().height / 2.0f);
		window.draw(answerBoxes[i]);
		window.draw(answersText[i]);
	}
	window.draw(currentQuestion);
	window.draw(currentScore);
	window.draw(textQuestions);
	window.draw(feedbackText);
	window.draw(timerText);
}

void GameScreen::configureGameScreen(vector<RectangleShape>& answerBoxes, vector<Text>& answersText) {

	textQuestions.setCharacterSize(35);
	textQuestions.setFont(font);

	answerBoxes[0].setFillColor(sf::Color::Magenta);
	answerBoxes[1].setFillColor(sf::Color::Red);
	answerBoxes[2].setFillColor(sf::Color::Blue);
	answerBoxes[3].setFillColor(sf::Color(0, 153, 51));
	answerBoxes[4].setFillColor(sf::Color(102, 20, 179));

	textQuestions.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 100);

	for (int i = 0; i < answerBoxes.size(); i++) {
		answerBoxes[i].setPosition(120.0f + 240.0f * i, 525.0f);
		answersText[i].setPosition(answerBoxes[i].getPosition());
		answersText[i].setPosition(120.0f + 240.0f * i, 525.0f);
	}
	feedbackText.setPosition(window.getSize().x - 260, 10);
	timerText.setPosition(window.getSize().x - 200, 50);
	timerText.setFont(font);
	timerText.setCharacterSize(35);
	currentQuestion.setFont(font);
	currentScore.setPosition(10, 60);
	currentScore.setCharacterSize(30);
	currentScore.setFont(font);
	feedbackText.setFont(font);
	feedbackText.setCharacterSize(25);
	currentQuestion.setPosition(10, 10);
}

int GameScreen::readCategoryFile(QuestionList& questionList) {
	int x;
	switch (category) {
	case 1:
		x = questionList.readFromFile("../categories/pytania_projekt_sport.txt");
		break;
	case 2:
		x = questionList.readFromFile("../categories/pytania_projekt_zwierzeta.txt");
		break;
	case 3:
		x = questionList.readFromFile("../categories/pytania_projekt_film.txt");
		break;
	case 4:
		x = questionList.readFromFile("../categories/pytania_projekt_geografia.txt");
		break;
	case 5:
		x = questionList.readFromFile("../categories/pytania_projekt.txt");
		break;
	default:
		x = questionList.readFromFile("../categories/pytania_projekt.txt");
		break;
	}
	if (x == -1)
		return x;

	questionList.mixQuestions();
	return 0;
}


void GameScreen::checkAnswer(int numOfFingers, int correctAnswer, int& qs, Text& feedbackText, Text& currentQuestion) {
	if (numOfFingers == correctAnswer) {
		score++;
		feedbackText.setString(L"Poprawna odpowiedŸ");
		feedbackText.setFillColor(Color::Green);
	}
	else {
		feedbackText.setString(L"B³êdna odpowiedŸ");
		feedbackText.setFillColor(Color::Red);
	}
	qs++;
	string mystr = "Pytanie ";
	mystr.append(to_string(qs + 1));
	mystr.append(" / ");
	mystr.append(to_string(totalQuestions));
	currentQuestion.setString(mystr);
}

int GameScreen::getScore() {
	return this->score;
}