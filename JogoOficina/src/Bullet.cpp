#include "Bullet.h"

Bullet::Bullet(float x, float y, float targetX, float targetY)
{
	position.set(x,y);
	ofVec2f target = ofVec2f(targetX, targetY);
	direction = (target - position).normalized();
	speed = 1000;
	isAlive = true;
	radius = 5;
}

void Bullet::update(float secs, Map &map)
{
	velocity = direction * speed * secs;
	position += velocity;
	behave(map);
}

void Bullet::behave(Map & map)
{
	//Map limits
	if (position.x + radius > map.getPosition().x && position.x - radius < map.getPosition().x + map.getWidth() && position.y + radius > map.getPosition().y && position.y - radius < map.getPosition().y + map.getHeight())
		isAlive = true;
	else
		isAlive = false;

	//Collision
	int x = (position.x - map.getPosition().x + radius) / map.getTileWidth();
	int y = (position.y - map.getPosition().y) / map.getTileHeight();
	if (x > 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			isAlive = false;
		}
	}

	x = (position.x - map.getPosition().x - radius) / map.getTileWidth();
	if (x >= 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			isAlive = false;
		}
	}

	x = (position.x - map.getPosition().x) / map.getTileWidth();
	y = (position.y - map.getPosition().y + radius) / map.getTileHeight();
	if (x >= 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			isAlive = false;
		}
	}

	y = (position.y - map.getPosition().y - radius) / map.getTileHeight();
	if (x >= 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			isAlive = false;
		}
	}
}

ofVec2f Bullet::getPosition() const
{
	return position;
}

void Bullet::draw(ofVec2f & camera)
{
	if (isAlive)
	{
		ofSetColor(255, 255, 0);
		ofDrawCircle(position - camera, radius);
		ofSetColor(255);
	}
}

Bullet::~Bullet()
{
}
