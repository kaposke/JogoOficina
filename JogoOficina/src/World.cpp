#include "World.h"

World::World(Map &map)
{
	hitSound.loadSound("sounds/hit.wav");
	hitSound.setMultiPlay(true);
	shootSound.loadSound("sounds/tiro.wav");

	for (int y = 0; y < map.getGridWidth(); y++)
	{
		for (int x = 0; x < map.getGridHeight(); x++)
		{
			if (map.getBehaviour(x, y) == 2)
			{
				createEnemy(new Enemy(map.getPosition().x + x * map.getTileWidth() + map.getTileWidth() / 2, map.getPosition().y + y * map.getTileHeight() + map.getTileHeight() / 2, map));
			}
		}
	}
}

void World::createBullet(Bullet * bullet)
{
	bullets.push_back(bullet);
	if (shootSound.isPlaying())
		shootSound.stop();
	shootSound.play();
}

void World::createEnemy(Enemy * enemy)
{
	enemies.push_back(enemy);
	cout << "Enemy spawned" << endl;
}

void World::updateBullets(float secs, Map & map, ofVec2f &player)
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

void World::updateEnemies(float secs, Map & map, ofVec2f & player)
{
	vector<Enemy*> alive;
	vector<Enemy*> toDelete;

	swap(toDelete, dead);
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(secs, player, map);
		for (int j = 0; j < bullets.size(); j++)
		{
			if (bullets[j]->getPosition().distance(enemies[i]->getPosition()) < bullets[j]->getRadius() + enemies[i]->getRadius())
			{
				bullets[j]->isAlive = false;
				enemies[i]->isAlive = false;
			}
		}
		if (!enemies[i]->isAlive) {
			dead.push_back(enemies[i]);
		}
		else {
			alive.push_back(enemies[i]);
		}
	}
	for (Enemy* object : dead) {
		cout << "Enemy deleted" << endl;
		delete object;
	}
	swap(alive, enemies);
}

void World::update(float secs, Map & map, ofVec2f &player)
{
	updateBullets(secs, map, player);
	updateEnemies(secs, map, player);
}

void World::draw(ofVec2f & camera)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(camera);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(camera);
	}
}
