#pragma once
#include "ofMain.h"
#include "Map.h"
#include "World.h"
#include "Bullet.h"

class Player
{
private:
	ofVec2f position;
	ofVec2f acceleration;

	float speed;
	float radius;

	bool canShoot;
	float delay;
	float time;
public:
	Player();
	
	void setPosition(float x, float y);
	ofVec2f getPosition();

	void setSpeed(float speed);

	void move(float secs, Map &map);
	void update(float secs, Map &map, ofVec2f &camera , World & world);
	void behave(Map &map);
	void shoot(float secs, ofVec2f &camera, World &world);

	void draw(ofVec2f &camera);
};