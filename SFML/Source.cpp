#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(VideoMode(1400, 650), "Quiz", Style::Close | Style::Resize);

	RectangleShape pytanieBox(Vector2f(1400.0f, 350.0f)); 
	vector<RectangleShape> odpowiedziBox(5,RectangleShape (Vector2f(280, 300)));
	String abc[5] = { "Zielony","Fioletowy", "Niebieski", "Czerwony", "Czarny", };

	sf::Texture button;

	sf::Font font;
	font.loadFromFile("arial.ttf");

	vector<Text> odpowiedziText(5, Text("A", font));
	sf::Text pytanieText("Test",font);
	pytanieText.setString("Pytanie 1\n Jaki kolor ma trawa?");
	button.loadFromFile("baner.png");
	sf::Texture pytanieTexture;
	pytanieTexture.loadFromFile("button.png");
	pytanieBox.setTexture(&button);
	pytanieBox.setFillColor(sf::Color::White);
	window.setFramerateLimit(60);
	window.clear(sf::Color(255, 255, 255));
	Event event;

	while (window.isOpen())
	{
		window.clear(Color::White);
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				printf("New window width %i \nNew window height %i \n", event.size.width, event.size.height);
				break;
				
			}
		}
		if (sf::Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePos = Mouse::getPosition(window);
			printf("%f %f", (float)mousePos.x,static_cast<float>(mousePos.y));
		}
		
		window.clear();
		window.draw(pytanieBox);

		pytanieText.setFillColor(sf::Color::Black);
		odpowiedziBox[1].setFillColor(sf::Color::Red);
		odpowiedziBox[2].setFillColor(sf::Color::Blue);
		odpowiedziBox[3].setFillColor(sf::Color(0, 153, 51));
		odpowiedziBox[4].setFillColor(sf::Color(102, 20, 179));
		odpowiedziBox[0].setFillColor(sf::Color::Magenta);

		pytanieText.setCharacterSize(30);
		pytanieBox.setPosition(0,0);
		pytanieText.setPosition(500, 170);

		for (int i = 0; i < odpowiedziBox.size(); ++i)
		{
			odpowiedziText[i].setString(abc[i]);
			odpowiedziText[i].setFillColor(sf::Color::White);
			odpowiedziBox[i].setPosition(0.0f+ 280.0f * i, 400.0f);
			odpowiedziText[i].setPosition(80.0f + 280.0f * i, 500.0f);
			window.draw(odpowiedziBox[i]);
			window.draw(odpowiedziText[i]);
			window.draw(pytanieText);	
		}
		window.display();
		
	}
	return 0;
}