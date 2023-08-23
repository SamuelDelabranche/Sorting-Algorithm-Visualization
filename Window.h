#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <random>

class Window{
	public:
		Window();
		~Window();

		void update();
		void render();
		void printTime() const;
		void restartClock();
		float getTime() const;

		bool isRunning();

		


	private:
		void appendRect(float BLc, float TRc, sf::Color color); 

		sf::Clock m_clock;
		sf::Time m_elapsedTime;
		sf::Time m_timeStep;

		sf::RenderWindow m_window;
		sf::VertexArray m_vertices;

		struct m_data {
			float x, y;
		}m_line[800];
		std::vector<int> m_posX;
		std::vector<int> m_posY;

		int m_actualPosX;
		int m_limitX;
		int m_top;

		int m_elements;
		int m_count;

		sf::Font m_font;

};

#endif