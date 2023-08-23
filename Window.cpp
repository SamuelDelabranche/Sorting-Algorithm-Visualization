#include "Window.h"


Window::Window() : m_window(sf::VideoMode(800, 800), "Sorting Algorithm Visualization", sf::Style::Close | sf::Style::Titlebar) {
	m_vertices.setPrimitiveType(sf::Triangles);

	std::random_device rd;
	std::mt19937 g(rd());
	m_elements = m_window.getSize().y;

	for (int i = 0; i < m_elements; i++) { m_posY.push_back(i); }

	std::shuffle(m_posY.begin(), m_posY.end(), g);

	for (int j = 0; j < m_elements; j++) {
		m_line[j].x = j;
		m_line[j].y = m_posY[j];
	}

	m_actualPosX = 0;
	m_top = 0;
	m_count = 0;
	m_limitX = m_window.getSize().x - 1;
	m_timeStep = sf::milliseconds(0.f);

	m_font.loadFromFile("./Ruwudu-Medium.ttf");

}

Window::~Window() {}

void Window::printTime() const {
	std::cout << m_elapsedTime.asSeconds() << std::endl;
}

void Window::update() {

	sf::Event windEvent;
	while (m_window.pollEvent(windEvent)) {
		if (windEvent.type == sf::Event::Closed) { m_window.close(); }
	}

	sf::Time time = m_clock.restart();
	m_elapsedTime += time;

	if (m_elapsedTime > m_timeStep)
	{
		m_elapsedTime -= m_timeStep;

		for (int i = 0; i < m_actualPosX; i++)
		{
			if (m_line[m_actualPosX].y < m_line[m_actualPosX + 1].y) {
				int temp = m_line[m_actualPosX + 1].y;
				m_line[m_actualPosX + 1].y = m_line[m_actualPosX].y;
				m_line[m_actualPosX].y = temp;

				++m_count;
			}

		}
		

	}
}

void Window::restartClock() { m_elapsedTime = m_clock.restart(); }

float Window::getTime() const { return m_elapsedTime.asSeconds(); }


void Window::render() {
	m_window.clear();
	m_vertices.clear();
	sf::Text countText("Steps: " + std::to_string(m_count), m_font, 24);
	countText.setPosition(10, 10);
	countText.setFillColor(sf::Color::Red);

	for (int i = 0; i < m_elements; i++)
	{
		//std::cout << i << " " << m_line[i].x << " " << m_line[i].y << std::endl;

		int dataX = m_line[i].x;
		int dataY = m_line[i].y;
		if(m_actualPosX == i){ appendRect(dataX, dataY, sf::Color::Red); }
		else
		{
			appendRect(dataX, dataY, sf::Color(40, 150, 200));
		}

	}

	++m_actualPosX;

	if (m_actualPosX > m_limitX) { m_actualPosX = 0; --m_limitX; }


	m_window.draw(countText);
	m_window.draw(m_vertices);
	m_window.display();

	//printTime();
}

void Window::appendRect(float BLc, float TRc, sf::Color color) {
	const float y = m_window.getSize().y;

	m_vertices.append({ {BLc,     y}, color });
	m_vertices.append({ {BLc + 1, y}, color });
	m_vertices.append({ {BLc + 1, y - TRc}, color });
	m_vertices.append({ {BLc + 1, y - TRc}, color });
	m_vertices.append({ {BLc,     y - TRc}, color });
	m_vertices.append({ {BLc,     y}, color });
}


bool Window::isRunning() { return m_window.isOpen(); }


