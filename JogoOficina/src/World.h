#pragma once
#include "ofMain.h"
#include "Bullet.h"
#include <iostream>
#include "Enemy.h"

using namespace std;

class World
{
private:
	vector<Bullet*> bullets;
	vector<Bullet*> destroyed;

	vector<Enemy*> enemies;
	vector<Enemy*> dead;

	ofSoundPlayer shootSound;
	ofSoundPlayer hitSound;
public:
	World(Map &map);

	void createBullet(Bullet *bullet);
	void createEnemy(Enemy *enemy);

	void updateBullets(float secs, Map & map, ofVec2f &player);
	void updateEnemies(float secs, Map & map, ofVec2f &player);

	void update(float secs, Map &map, ofVec2f &player);

	void draw(ofVec2f &camera);
};