#pragma once
#include "ofMain.h"
#include "Map.h"

class Bullet
{
private:
	ofVec2f position;
	ofVec2f direction;
	ofVec2f velocity;

	float speed;

	float radius;

	ofSoundPlayer hit;
public:
	bool isAlive;

	Bullet(float x, float y, float targetX, float targetY);

	void update(float secs, Map &map);
	void behave(Map &map);

	ofVec2f getPosition() const;

	void draw(ofVec2f &camera);

	~Bullet();
};