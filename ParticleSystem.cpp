#include "ParticleSystem.h"
#include <iostream>

/* Particle */

Particle::Particle(float pX, float pY, float q, float m) :
	position(sf::Vector2f(pX, pY)), mass(m), charge(q)
{
	shape = sf::CircleShape(m);
	if (q > 0) shape.setFillColor(sf::Color::Color(255, 0, 0, 255));
	else shape.setFillColor(sf::Color::Color(0, 0, 255, 255));

	velocity = sf::Vector2f(0.f, 0.f);
	acceleration = sf::Vector2f(0.f, 0.f);
	force = sf::Vector2f(0.f, 0.f);
}

void Particle::applyForce(float x, float y) { force += sf::Vector2f(x, y); }

void Particle::setForce(float x, float y) { force = sf::Vector2f(x, y); }

void Particle::update()
{
	if (charge > 0) shape.setFillColor(sf::Color::Color(255, 0, 0, 255));
	else shape.setFillColor(sf::Color::Color(0, 0, 255, 255));
	acceleration += sf::Vector2f(force.x / mass, force.y / mass);
	velocity += acceleration;
	position += velocity;
	shape.setPosition(position);
}

sf::Vector2f Particle::getPos() { return position; }

float Particle::getCharge() { return charge; }

float Particle::getMass() { return mass; }

sf::CircleShape &Particle::getShape() { return shape; }

sf::Vector2f Particle::getVel() { return velocity; }

sf::Vector2f Particle::getForce() { return force; }

sf::Vector2f Particle::getAcc() { return acceleration; }

bool Particle::collidesWith(Particle &p)
{
	return powf(position.x - p.getPos().x, 2.f) + powf(position.y - p.getPos().y, 2.f) <= powf(shape.getRadius() + p.getShape().getRadius(), 2.f);
}

void Particle::setVel(float x, float y) { velocity = sf::Vector2f(x, y); }

void Particle::setCharge(float q) { charge = q; }

/* Particle System */

void ParticleSystem::update()
{
	for (int i = 0; i < system.size(); i++) {
		Particle &particle = *system[i];
		sf::Vector2f accumulatedForce = sf::Vector2f(0.f, 0.f);

		for (int j = 0; j < system.size(); j++)
			if (j != i) {
				Particle &p = *system[j];
				float distance = fmax(sqrt(
					powf(particle.getPos().x - p.getPos().x, 2.f)
					+ powf(particle.getPos().y - p.getPos().y, 2.f)),
					powf(particle.getShape().getRadius() + p.getShape().getRadius(), 2.f));
				float angle = atan2f(particle.getPos().y - p.getPos().y, particle.getPos().x - p.getPos().x);
				float totalForce = 0.01f * particle.getCharge() * p.getCharge() / powf(distance, 2.f);
				accumulatedForce += sf::Vector2f(cosf(angle) * totalForce, sinf(angle) * totalForce);
			}

		particle.applyForce(accumulatedForce.x, accumulatedForce.y);
		particle.update();
	}
}

std::vector<Particle *> &ParticleSystem::getSystem()
{
	return system;
}

void ParticleSystem::addParticle(Particle *p)
{
	system.push_back(p);
}