#include "Screen.h"


int Screen::handleEvent() {
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case Event::Closed: {
			window.close();
			return -1;
		}

		case Event::Resized:
			break;
		}
	}
}