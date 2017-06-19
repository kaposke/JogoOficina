#pragma once
#include "ofMain.h"
#include "Bullet.h"
#include <iostream>

using namespace std;

class World
{
private:
	vector<Bullet*> bullets;
	vector<Bullet*> destroyed;

	ofSoundPlayer shootSound;
	ofSoundPlayer hitSound;
public:
	World();

	void createBullet(Bullet *bullet);

	void update(float secs, Map &map, ofVec2f &player);

	void draw(ofVec2f &camera);
};