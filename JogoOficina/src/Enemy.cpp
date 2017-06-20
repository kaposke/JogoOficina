#include "Enemy.h"

Enemy::Enemy(float x, float y, Map &map)
{
	position.set(x,y);
	radius = map.getTileWidth() / 3;
	speed = 150;
	isAlive = true;
}

void Enemy::draw(ofVec2f & camera)
{
	if (isAlive)
	{
		ofSetColor(255, 0, 0);
		ofDrawCircle(position - camera, radius);
		ofSetColor(255);
	}
}

void Enemy::update(float secs, ofVec2f &target, Map &map)
{
	ofVec2f dist = target - position;
	ofVec2f dir = dist.normalized();
	acceleration = dir * speed * secs;
	behave(map);
	if(position.distance(target) < 400)
		position += acceleration;
}

void Enemy::behave(Map & map)
{
	//Map limits
	position.x = position.x - radius < map.getPosition().x ? map.getPosition().x + radius : position.x;
	position.x = position.x + radius > map.getPosition().x + map.getWidth() ? map.getPosition().x + map.getWidth() - radius : position.x;

	position.y = position.y - radius < map.getPosition().y ? map.getPosition().y + radius : position.y;
	position.y = position.y + radius > map.getPosition().y + map.getHeight() ? map.getPosition().y + map.getHeight() - radius : position.y;

	//Collision
	int x = (position.x - map.getPosition().x + radius + acceleration.x) / map.getTileWidth();
	int y = (position.y - map.getPosition().y) / map.getTileHeight();
	if (x > 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			position.x = map.getPosition().x + x * map.getTileWidth() - radius;
			acceleration.x = 0;
		}
	}

	x = (position.x - map.getPosition().x - radius + acceleration.x) / map.getTileWidth();
	if (x >= 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			position.x = map.getPosition().x + (x + 1) * map.getTileWidth() + radius;
			acceleration.x = 0;
		}
	}

	x = (position.x - map.getPosition().x) / map.getTileWidth();
	y = (position.y - map.getPosition().y + radius + acceleration.y) / map.getTileHeight();
	if (x >= 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			position.y = map.getPosition().y + y * map.getTileHeight() - radius;
			acceleration.y = 0;
		}
	}

	y = (position.y - map.getPosition().y - radius + acceleration.y) / map.getTileHeight();
	if (x >= 0 && x < map.getGridWidth() && y >= 0 && y < map.getGridHeight())
	{
		if (map.getBehaviour(x, y) == 1)
		{
			position.y = map.getPosition().y + (y + 1)* map.getTileHeight() + radius;
			acceleration.y = 0;
		}
	}
}

ofVec2f Enemy::getPosition() const
{
	return position;
}

float Enemy::getRadius() const
{
	return radius;
}
