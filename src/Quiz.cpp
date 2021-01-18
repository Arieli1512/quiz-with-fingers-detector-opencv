#include "Quiz.h"


void Quiz::clockReset()
{
	clock.restart();
}

void Quiz::configureCamera() {
	VideoCapture cam1(0);
	this->camera = cam1;

}

void Quiz::showEndingScreen()
{
	window.clear();
	destroyWindow("window");
	destroyWindow("window real");
	this->camera.release();
	RectangleShape endScreen(Vector2f(1200.0f, 650.0f));
	endScreen.setTexture(&questionTexture);

	Text text2;
	text2.setFont(font);
	text2.setCharacterSize(40);
	wstring endPoints;

	Texture texture2;
	Image image2;
	Sprite sprite2;
	Texture texture3;
	Image image3;
	Sprite sprite3;

	if (score == 1) {
		endPoints = L" punkt";
	}
	else if (score > 1 && score < 5) {
		endPoints = L" punkty";
	}
	else
		endPoints = L" punktów";

	text2.setString(L"Gra skoñczona, Twój wynik to: " + to_string(score) + endPoints);
	text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
	text2.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	Text text3;
	text3.setFont(font);
	text3.setCharacterSize(50);
	if (score > 7) {
		text3.setString("Gratulacje!");
		text3.setCharacterSize(50);
		text3.setFillColor(Color::Green);
		image2.loadFromFile("../imagesSfml/fire-cracker.png");
		image3.loadFromFile("../imagesSfml/fire-cracker2.png");
	}
	else if (score >= 5) {
		text3.setString(L"Niez³y wynik!");
		text3.setCharacterSize(40);
		text3.setFillColor(Color::Green);
		image2.loadFromFile("../imagesSfml/smile.png");
		image3.loadFromFile("../imagesSfml/fire-cracker2.png");
	}
	else {
		text3.setString(L"Mo¿e spróbuj jeszce raz?");
		text3.setCharacterSize(35);
		image2.loadFromFile("../imagesSfml/sad.png");
		image3.loadFromFile("../imagesSfml/sad.png");
	}
	texture2.loadFromImage(image2);
	texture3.loadFromImage(image3);

	sprite2.setTexture(texture2);
	sprite2.setPosition(200, 100);

	sprite3.setTexture(texture3);
	sprite3.setPosition(850, 100);

	text3.setOrigin(text3.getLocalBounds().width / 2.0f, text3.getLocalBounds().height / 2.0f);
	text3.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 150);

	while (true)
	{
		window.clear();
		window.draw(endScreen);
		window.draw(text2);
		window.draw(text3);
		window.draw(sprite2);
		window.draw(sprite3);
		window.display();
		handleEvent();
	}
}


vector<Sprite> Quiz::configureSpritesIcons(vector<string>& names, vector<Texture>& textures, vector<Image>& images, int x, int y, int shift) {

	vector<Sprite> sprites;

	for (int i = 0; i < 5; i++) {

		Texture texture2;
		Image image2;
		image2.loadFromFile(names.at(i));
		images.push_back(image2);
		texture2.loadFromImage(images.at(i));
		textures.push_back(texture2);
	}

	for (int i = 0; i < 5; i++) {
		Sprite sprite2;
		sprite2.setTexture(textures.at(i));
		sprite2.setPosition(x + i * shift, y);
		sprites.push_back(sprite2);
	}
	return sprites;
}

void Quiz::configurateStartingScreen(Text& text1, Text& text2, RectangleShape& helloScreen) {
	helloScreen.setTexture(&questionTexture);
	helloScreen.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	helloScreen.setPosition(helloScreen.getLocalBounds().width / 2.0f, helloScreen.getLocalBounds().height / 2.0f);
	text1.setPosition(25, 10);
	text1.setFont(font);
	text1.setCharacterSize(45);
	text1.setString(L"QUIZ");
	text2.setFont(font);
	text2.setCharacterSize(40);
	text2.setString(L"Przed tob¹ Quiz sk³adaj¹cy siê z 10 pytañ.\n"
		"Pokazuj palce, aby odpowiadaæ na pytania!\nAby rozpocz¹æ grê poka¿ 5 palców.");
	text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
	text2.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 60);
}


void Quiz::showStartingScreen() {
	Texture texture;
	Image image;
	image.loadFromFile("../imagesSfml/answer.png");
	texture.loadFromImage(image);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(1100, 10);
	vector<string> names;
	vector<Texture> textures;
	vector<Image> images;
	names.push_back("../imagesSfml/finger.png");
	names.push_back("../imagesSfml/two-fingers.png");
	names.push_back("../imagesSfml/three-fingers.png");
	names.push_back("../imagesSfml/four-fingers.png");
	names.push_back("../imagesSfml/five-fingers.png");
	vector<Sprite> sprites = configureSpritesIcons(names, textures, images, 250, 400, 150);
	font.loadFromFile("../fonts/AllerDisplay.ttf");
	questionTexture.loadFromFile("../imagesSfml/baner4.jpg");
	RectangleShape helloScreen(Vector2f(1200.0f, 650.0f));
	Text text1;
	Text text2;
	configurateStartingScreen(text1, text2, helloScreen);
	int flag = 0;

	while (true) {
		try {
			window.clear();
			window.draw(helloScreen);
			window.draw(text1);
			window.draw(text2);
			window.draw(sprite);
			for (int i = 0; i < sprites.size(); i++)
				window.draw(sprites.at(i));

			window.display();
			handleEvent();
			if (flag == 0)
			{
				configureCamera();
				flag = 1;
			}
			int x = detectFingers();
			if (x == 5) {
				cout << "Pokazales 5 placow!" << endl;
				break;
			}
		}
		catch (cv::Exception& e) {
		}
	}

}
void Quiz::showCategoryScreen()
{
	flagCoords = 1;
	vector<RectangleShape> answersBox(5, RectangleShape(Vector2f(220, 220)));
	Text textCategories;
	textCategories.setFont(font);
	textCategories.setCharacterSize(25);
	vector<Text> answersTextx(5, textCategories);

	vector<wstring> namesCategory;
	namesCategory.push_back(L"Sport");
	namesCategory.push_back(L"Zwierzêta");
	namesCategory.push_back(L"Film");
	namesCategory.push_back(L"Geografia");
	namesCategory.push_back(L"Ogólne");


	for (int i = 0; i < answersBox.size(); i++) {
		answersTextx[i].setFillColor(Color::White);
		answersTextx[i].setString(namesCategory.at(i));
		answersBox[i].setOrigin(answersBox[i].getSize().x / 2.0f, answersBox[i].getSize().y / 2.0f);
		answersTextx[i].setOrigin(answersTextx[i].getLocalBounds().width / 2.0f, answersTextx[i].getLocalBounds().height / 2.0f);
		answersBox[i].setPosition(120.0f + 240.0f * i, 425.0f);
		answersTextx[i].setPosition(answersBox[i].getPosition());
		answersTextx[i].setPosition(120.0f + 240.0f * i, 425.0f);
		window.draw(answersBox[i]);
		window.draw(answersTextx[i]);
	}

	answersBox[0].setFillColor(sf::Color::Magenta);
	answersBox[1].setFillColor(sf::Color::Red);
	answersBox[2].setFillColor(sf::Color::Blue);
	answersBox[3].setFillColor(sf::Color(0, 153, 51));
	answersBox[4].setFillColor(sf::Color(102, 20, 179));

	window.clear();
	RectangleShape categoryScreen(Vector2f(1200.0f, 650.0f));
	categoryScreen.setTexture(&questionTexture);
	Text text3, text4;
	text3.setFont(font);
	text3.setCharacterSize(40);
	vector<string> names;
	vector<Texture> textures;
	vector<Image> images;
	names.push_back("../imagesSfml/running-man.png");
	names.push_back("../imagesSfml/podium.png");
	names.push_back("../imagesSfml/video.png");
	names.push_back("../imagesSfml/globe.png");
	names.push_back("../imagesSfml/hat.png");
	vector<Sprite> sprites = configureSpritesIcons(names, textures, images, 90, 230, 240);

	clockReset();
	try
	{
		while (true)
		{

			window.clear();
			window.draw(categoryScreen);

			elapsed = clock.getElapsedTime();
			int timeRemained = timer - (int)elapsed.asSeconds();
			if (timeRemained == 0) {
				try
				{
					category = detectFingers();
				}
				catch (exception& e)
				{
				}
				return;
			}
			for (int i = 0; i < sprites.size(); i++)
				window.draw(sprites.at(i));
			text3.setString(L"Wybierz kategoriê w przeci¹gu: " + to_string(timeRemained) + " sekund");
			text3.setOrigin(text3.getLocalBounds().width / 2.0f, text3.getLocalBounds().height / 2.0f);
			text3.setPosition(window.getSize().x / 2.0f, 120.0f);
			for (int i = 0; i < answersBox.size(); i++) {
				window.draw(answersBox[i]);
				window.draw(answersTextx[i]);
			}

			try { detectFingers(); }
			catch (exception& e)
			{
			}
			window.draw(text3);
			window.draw(text4);
			window.display();
			handleEvent();
		}

	}
	catch (cv::Exception& e) {
	}
	return;
}

void Quiz::showWaitingScreen() {
	window.clear();

	RectangleShape waitScreen(Vector2f(1200.0f, 650.0f));
	waitScreen.setTexture(&questionTexture);
	Text text2;
	text2.setFont(font);
	text2.setCharacterSize(40);

	while (true)
	{
		window.clear();
		window.draw(waitScreen);
		elapsed = clock.getElapsedTime();
		int timeRemained = timer - (int)elapsed.asSeconds();
		if (timeRemained == 0) {
			clock.restart();
			return;
		}
		text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
		text2.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));
		text2.setString(L"Quiz rozpocznie siê za " + to_string(timeRemained) + " ...");

		try {
			detectFingers();
		}
		catch (exception& e)
		{
		}
		window.draw(text2);
		window.display();
		handleEvent();
	}
}


void Quiz::setUpBoxes() {
	textQuestions.setFillColor(sf::Color::White);
	answersBox[0].setFillColor(sf::Color::Magenta);
	answersBox[1].setFillColor(sf::Color::Red);
	answersBox[2].setFillColor(sf::Color::Blue);
	answersBox[3].setFillColor(sf::Color(0, 153, 51));
	answersBox[4].setFillColor(sf::Color(102, 20, 179));
	questionBox.setTexture(&button);
	questionBox.setFillColor(sf::Color::White);
	textQuestions.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 100);
}



void Quiz::setUp() {
	int x;

	switch (category)
	{
	case 1:
		x = questionList.readFromFile("../pytania_projekt_sport.txt");
		break;
	case 2:
		x = questionList.readFromFile("../pytania_projekt_zwierzeta.txt");
		break;
	case 3:
		x = questionList.readFromFile("../pytania_projekt_film.txt");
		break;
	case 4:
		x = questionList.readFromFile("../pytania_projekt_geografia.txt");
		break;
	case 5:
		x = questionList.readFromFile("../pytania_projekt.txt");
		break;
	default:
		x = questionList.readFromFile("../pytania_projekt.txt");
		break;
	}
	if (x == -1) {
		cout << "Error-file not loaded";
		return;
	}

	questionList.mixQuestions();
	textAnswers.setCharacterSize(25);
	textQuestions.setCharacterSize(35);
	textAnswers.setFont(font);
	textQuestions.setFont(font);
	vector<Text> answersTextx(5, textAnswers);
	this->answersText = answersTextx;
	string str1 = "Pytanie 1 / ";
	str1.append(to_string(totalQuestions));
	currentQuestion.setString(str1);
	font.loadFromFile("../fonts/AllerDisplay.ttf");
	button.loadFromFile("../imagesSfml/baner4.jpg");
	currentQuestion.setFont(font);

	setUpBoxes();

	window.setFramerateLimit(60);
	Text score("Pytanie 1/20", font);
	for (int i = 0; i < answersBox.size(); i++) {
		answersText[i].setFillColor(Color::White);
		answersBox[i].setOrigin(answersBox[i].getSize().x / 2.0f, answersBox[i].getSize().y / 2.0f);
		answersText[i].setOrigin(answersText[i].getLocalBounds().width / 2.0f, answersText[i].getLocalBounds().height / 2.0f);
		answersBox[i].setPosition(120.0f + 240.0f * i, 525.0f);
		answersText[i].setPosition(answersBox[i].getPosition());
		answersText[i].setPosition(120.0f + 240.0f * i, 525.0f);
	}

	cout << category;
}


void Quiz::handleEvent() {
	while (window.pollEvent(event))
	{
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

Point2f Quiz::readFromFileCoordinates() {
	ifstream file;
	string coordX;
	string coordY;

	file.open("../config.txt");
	if (file.fail() == true)
		return NULL;

	getline(file, coordX);
	int resX = stoi(coordX);
	getline(file, coordY);
	int resY = stoi(coordY);

	Point2f point = Point2f(resX, resY);

	file.close();
	return point;
}

int Quiz::detectFingers() {

	Mat img, partImg;
	camera.read(img);
	if (flagCoords == 0)
		point = readFromFileCoordinates();

	cv::Rect rect = cv::Rect(cv::Point2f(point.x, point.y), cv::Point2f(300 + point.x, 300 + point.y));
	rectangle(img, cv::Point2f(point.x, point.y), cv::Point2f(300 + point.x, 300 + point.y), cv::Scalar(255, 0, 0));
	partImg = img(rect);
	cv::imshow("window real", img);
	int numOfFingers = fingersDetector.countFingers(partImg);
	Mat contoursImage = fingersDetector.getContoursImage();
	cv::putText(contoursImage, to_string(numOfFingers), cv::Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 3);
	cv::imshow("window", contoursImage);
	return numOfFingers;
}


void Quiz::checkAnswer() {
	if (numOfFingers == questionList.getQuestionArray().at(qs).getCorrectAnswer()) {
		score++;
		flag = 1;
		cout << "Poprawna odp" << numOfFingers << "  corr answ :" << questionList.getQuestionArray().at(qs).getCorrectAnswer() << endl;
	}
	else {
		flag = 2;
		cout << "Zla odp" << numOfFingers << "  corr answ :" << questionList.getQuestionArray().at(qs).getCorrectAnswer() << endl;
	}

	qs++;
	string mystr = "Pytanie ";
	mystr.append(to_string(qs + 1));
	mystr.append(" / ");
	mystr.append(to_string(totalQuestions));
	currentQuestion.setString(mystr);
	clock.restart();
}


void Quiz::configureText(Text& textP, Text& currentScore, Text& timerW) {

	textP.setPosition(window.getSize().x - 250, 10);
	timerW.setPosition(window.getSize().x - 200, 50);
	timerW.setFont(font);
	timerW.setCharacterSize(35);
	timerW.setFillColor(Color::White);
	textP.setFont(font);
	textP.setCharacterSize(25);
	currentScore.setPosition(10, 60);
	currentScore.setCharacterSize(30);
	currentScore.setFont(font);
}


void Quiz::showContentOnScreen(int i) {
	wstring questionString = questionList.getQuestionArray().at(qs).getQuestion();
	wstring answersString = questionList.getQuestionArray().at(qs).getAnswers().at(i);
	textQuestions.setString(sf::String::fromUtf8(questionString.begin(), questionString.end()));
	answersText[i].setString(sf::String::fromUtf8(answersString.begin(), answersString.end()));
	textQuestions.setOrigin(textQuestions.getLocalBounds().width / 2.0f, textQuestions.getLocalBounds().height / 2.0f);
	answersText[i].setOrigin(answersText[i].getLocalBounds().width / 2.0f, answersText[i].getLocalBounds().height / 2.0f);
	window.draw(answersBox[i]);
	window.draw(answersText[i]);
	window.draw(textQuestions);
}


int Quiz::handleAnswers() {
	window.draw(questionBox);
	Text textP, currentScore, timerW;
	switch (flag) {
	case 1:
		textP.setString(L"Poprawna odpowiedŸ");
		textP.setFillColor(Color::Green);
		break;
	case 2:
		textP.setString(L"B³êdna odpowiedŸ");
		textP.setFillColor(Color::Red);
		break;
	}
	configureText(textP, currentScore, timerW);

	elapsed = clock.getElapsedTime();
	int timeRemained = timer - (int)elapsed.asSeconds();
	timerW.setString(to_string(timeRemained));

	if ((int)elapsed.asSeconds() > (timer - 1))
		checkAnswer();

	currentScore.setString("Punkty " + to_string(score));
	window.draw(textP);
	window.draw(currentScore);
	if (timeRemained < 4)
		timerW.setColor(Color::Red);
	else timerW.setColor(Color::White);
	window.draw(timerW);
	for (int i = 0; i < answersBox.size(); i++) {

		if (qs == totalQuestions)
			return 1;

		showContentOnScreen(i);
	}

	currentQuestion.setPosition(10, 10);
	window.draw(currentQuestion);
	window.display();
	return 0;
}