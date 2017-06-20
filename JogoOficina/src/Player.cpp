#include "Player.h"

Player::Player(Map &map)
{
	for (int y = 0; y < map.getGridWidth(); y++)
	{
		for (int x = 0; x < map.getGridHeight(); x++)
		{
			if (map.getBehaviour(x, y) == 3)
			{
				position.set(map.getPosition().x + x * map.getTileWidth() + map.getTileWidth() / 2, map.getPosition().y + y * map.getTileHeight() + map.getTileHeight() / 2);
				break;
			}

		}
	}

	this->radius = map.getTileWidth() /3;
	canShoot = true; 
	delay = 1;
	time = delay;
}

void Player::setPosition(float x, float y)
{
	position.set(x, y);
}

ofVec2f Player::getPosition()
{
	return position;
}

void Player::setSpeed(float speed)
{
	this->speed = speed;
}

void Player::move(float secs, Map &map)
{
	acceleration *= 0.7f;
	if (ofGetKeyPressed('a') || ofGetKeyPressed(OF_KEY_LEFT) || ofGetKeyPressed('A'))
		acceleration.x -= 0.1f;
	if (ofGetKeyPressed('d') || ofGetKeyPressed(OF_KEY_RIGHT) || ofGetKeyPressed('D'))
		acceleration.x += 0.1f;
	if (ofGetKeyPressed('s') || ofGetKeyPressed(OF_KEY_DOWN) || ofGetKeyPressed('S'))
		acceleration.y += 0.1f;
	if (ofGetKeyPressed('w') || ofGetKeyPressed(OF_KEY_UP) || ofGetKeyPressed('W'))
		acceleration.y -= 0.1f;

	position += acceleration * speed * secs;
	behave(map);
}

void Player::update(float secs, Map &map, ofVec2f &camera, World & world)
{
	move(secs, map);
	shoot(secs, camera, world);
}

void Player::behave(Map & map)
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

void Player::shoot(float secs, ofVec2f &camera, World & world)
{
	if (!canShoot)
	{
		time -= 10 * secs;
		if (time <= 0)
		{
			time = delay;
			canShoot = true;
		}
	}
	if (ofGetMousePressed(OF_MOUSE_BUTTON_1) && canShoot)
	{
		canShoot = false;
		world.createBullet(new Bullet(position.x, position.y, ofGetMouseX() + camera.x , ofGetMouseY() + camera.y));
	}
}

void Player::draw(ofVec2f &camera)
{
	ofSetCircleResolution(50);
	ofSetColor(0,200,255);
	ofDrawCircle(position - camera, radius);
	ofSetColor(255);
}
