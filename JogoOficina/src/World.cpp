#include "World.h"

World::World()
{
	hitSound.loadSound("sounds/hit.wav");
	hitSound.setMultiPlay(true);
	shootSound.loadSound("sounds/tiro.wav");
}

void World::createBullet(Bullet * bullet)
{
	bullets.push_back(bullet);
	if (shootSound.isPlaying())
		shootSound.stop();
	shootSound.play();
}

void World::update(float secs, Map & map, ofVec2f &player)
{
	vector<Bullet*> alive;
	vector<Bullet*> toDelete;

	swap(toDelete, destroyed);
	//Para cada objeto object em bullets
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->update(secs, map);
		if (!bullets[i]->isAlive) {
			float dist = player.distance(bullets[i]->getPosition());
			float vol = ofMap(dist, 0, map.getWidth(), 1.0f, 0.0f);
			ofVec2f panSide = (bullets[i]->getPosition() - player).normalized();
			hitSound.setPan(panSide.x);
			hitSound.setVolume(vol);
			hitSound.play();
			hitSound.setPositionMS(50);
			destroyed.push_back(bullets[i]);
		}
		else {
			alive.push_back(bullets[i]);
		}
	}

	for (Bullet* object : toDelete) {
		delete object;
	}
	swap(alive, bullets);
}

void World::draw(ofVec2f & camera)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(camera);
	}
}
