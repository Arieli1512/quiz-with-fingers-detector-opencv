#include "CategoryScreen.h"


void CategoryScreen::showCategoryScreen() {
	RectangleShape categoryScreen(Vector2f(1200.0f, 650.0f));
	vector<RectangleShape> categoryBox(5, RectangleShape(Vector2f(220, 220)));
	Font font;
	Texture questionTexture;
	Text textCategory, text;
	questionTexture.loadFromFile("../imagesSfml/baner.jpg");
	font.loadFromFile("../fonts/AllerDisplay.ttf");
	categoryScreen.setTexture(&questionTexture);
	textCategory.setFont(font);
	textCategory.setCharacterSize(25);
	text.setFont(font);
	text.setCharacterSize(40);
	vector<Text> textCategories(5, textCategory);
	vector<wstring> namesCategory;
	window.clear();
	vector<Texture> textures;
	vector<Image> images;
	vector<Sprite> sprites = configureSpritesIcons(textures, images, 90, 230, 240);
	configureCategoryBoxes(categoryBox, textCategories);
	text.setPosition(window.getSize().x / 2.0f, 120.0f);
	clock.restart();
	int numOfFingers = 0;
	while (true) {
		window.clear();
		window.draw(categoryScreen);
		elapsed = clock.getElapsedTime();
		int timeRemained = timer - (int)elapsed.asSeconds();
		if (timeRemained == 0) {
			category = numOfFingers;
			break;
		}
		for (int i = 0; i < sprites.size(); i++)
			window.draw(sprites.at(i));
		text.setString(L"Wybierz kategoriê w przeci¹gu: " + to_string(timeRemained) + " sekund");
		text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
		for (int i = 0; i < categoryBox.size(); i++) {
			window.draw(categoryBox[i]);
			window.draw(textCategories[i]);
		}
		try { numOfFingers = fingersDetector->detectFingers(); }
		catch (Exception& e) {}
		window.draw(text);
		window.display();
		handleEvent();
	}
	return;
}


void CategoryScreen::configureCategoryBoxes(vector<RectangleShape>& categoryBox, vector<Text>& textCategories) {

	vector<wstring> namesCategory;
	namesCategory.push_back(L"Sport");
	namesCategory.push_back(L"Zwierzêta");
	namesCategory.push_back(L"Film");
	namesCategory.push_back(L"Geografia");
	namesCategory.push_back(L"Ogólne");
	for (int i = 0; i < categoryBox.size(); i++) {
		textCategories[i].setFillColor(Color::White);
		textCategories[i].setString(namesCategory.at(i));
		categoryBox[i].setOrigin(categoryBox[i].getSize().x / 2.0f, categoryBox[i].getSize().y / 2.0f);
		textCategories[i].setOrigin(textCategories[i].getLocalBounds().width / 2.0f, textCategories[i].getLocalBounds().height / 2.0f);
		categoryBox[i].setPosition(120.0f + 240.0f * i, 425.0f);
		textCategories[i].setPosition(categoryBox[i].getPosition());
		textCategories[i].setPosition(120.0f + 240.0f * i, 425.0f);
		window.draw(categoryBox[i]);
		window.draw(textCategories[i]);
	}
	categoryBox[0].setFillColor(sf::Color::Magenta);
	categoryBox[1].setFillColor(sf::Color::Red);
	categoryBox[2].setFillColor(sf::Color::Blue);
	categoryBox[3].setFillColor(sf::Color(0, 153, 51));
	categoryBox[4].setFillColor(sf::Color(102, 20, 179));
}

vector<Sprite> CategoryScreen::configureSpritesIcons(vector<Texture>& textures, vector<Image>& images, int x, int y, int shift) {
	vector<Sprite> sprites;
	vector<string> names;
	names.push_back("../imagesSfml/running-man.png");
	names.push_back("../imagesSfml/podium.png");
	names.push_back("../imagesSfml/video.png");
	names.push_back("../imagesSfml/globe.png");
	names.push_back("../imagesSfml/hat.png");
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


int CategoryScreen::getCategory() {
	return this->category;
}