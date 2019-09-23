#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"
#include <vector>
#include <iostream>

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Particle System");
	window.setFramerateLimit(45);

	std::vector<Particle *> particles;
	ParticleSystem system(particles);

	while (window.isOpen()) {
		sf::Event ev;

		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				window.close();
			else if (ev.type == sf::Event::MouseButtonPressed) {
				Particle *p = new Particle(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 15.f, 10.f);
				if (ev.mouseButton.button == sf::Mouse::Right)
					p = new Particle(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, -15.f, 10.f);
					
				system.addParticle(p);
			}
		}

		window.clear(sf::Color::Black);
		system.update();
		for (auto &p : system.getSystem())
			window.draw(p->getShape());
		window.display();
	}

	return 0;
}