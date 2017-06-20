#pragma once
#include "ofMain.h"
#include "Map.h"

class Enemy
{
private:
	ofVec2f position;
	ofVec2f acceleration;
	float speed;
	
	bool spotted;

	float radius;
public:
	bool isAlive;

	Enemy(float x, float y, Map &map);

	void update(float secs, ofVec2f &target, Map &map);

	void behave(Map& map);

	ofVec2f getPosition() const;
	float getRadius() const;

	void draw(ofVec2f &camera);
};