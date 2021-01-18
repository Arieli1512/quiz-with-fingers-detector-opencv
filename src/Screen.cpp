#include "Screen.h"


void Screen::handleEvent() {
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