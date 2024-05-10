#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>

namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		int m_n;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		Ship m_ship;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		bool Setup(int n)
		{
			m_n = n;
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);
			if (!m_textureBackground.loadFromFile("assets\\background.jpg"))
			{
				std::cout << "Error while loading background.jpg" << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			if (!m_font.loadFromFile("assets\\arial.ttf"))
			{
				std::cout << "Error while loading arial.ttf" << std::endl;
				return false;
			}
			m_fpsText.setFont(m_font);

			if (!m_ship.Setup(100, 100))
				return false;
			 
			srand(time(0));

			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 1;
				int x = rand() % (1000 - 2 * r) + r;
				int y = rand() % (600 - 2 * r) + r;
				int v = rand() % 50 + 10;
				float alfa = rand() % 7;
			}
		}

		void LifeCycle()
		{
			sf::Clock clock;

			float fps = 100;
			int fpsTextViewCnt = 0;

			while (m_window.isOpen())
			{
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_ship.setVelocity(0.01);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_ship.setVelocity(-0.01);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					m_ship.Rotate(-1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					m_ship.Rotate(1);
				}

				float dt = clock.getElapsedTime().asSeconds();
				if (1 / fps > dt)
				{
					sf::Time t = sf::seconds(1 / fps - dt);
					sf::sleep(t);
				}
				dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				fpsTextViewCnt++;
				if (fpsTextViewCnt > fps)
				{
					fpsTextViewCnt = 0;
					m_fpsText.setString(std::to_string(1 / dt));
				}

				m_ship.Move();

				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_ship.Get());
				m_window.draw(m_fpsText);
				m_window.display();
			}
		}
	};

}