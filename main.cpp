#include "Window.h"

int main() {
	Window window;
	while (window.isRunning()) {



		window.update();
		window.render();



		
	}

	return 0;
}	