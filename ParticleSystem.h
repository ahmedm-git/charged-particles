#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Particle;

class ParticleSystem {
	std::vector<Particle *> system;
public:
	ParticleSystem(std::vector<Particle *> sys) : system(sys) { }

	void addParticle(Particle *p);
	std::vector<Particle *> &getSystem();
	void update();
};

class Particle {
	sf::CircleShape shape;
	sf::Vector2f position, velocity,
				 acceleration, force;
	float charge, mass;
public:
	Particle(float pX, float pY, float q, float m);

	sf::CircleShape &getShape();
	sf::Vector2f getPos();
	sf::Vector2f getVel();
	sf::Vector2f getAcc();
	sf::Vector2f getForce();
	float getCharge();
	float getMass();
	bool collidesWith(Particle &p);

	void applyForce(float x, float y);
	void setForce(float x, float y);
	void setVel(float x, float y);
	void setCharge(float q);
	void update();
};