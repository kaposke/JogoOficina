#include "Map.h"

Map::Map(string path, float width, float height)
{
	imgPath = path;
	this->width = width;
	this->height = height;
}

void Map::init()
{
	img.loadImage(imgPath);
}

void Map::setBehaviours(string path, int w, int h)
{
	gridWidth = w;
	gridHeight = h;

	tileWidth = width / w;
	tileHeight = height / h;

	behaviours.resize(h, vector<int>(w, 0));

	string caminho = path;

	ifstream arquivo(caminho);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int value;
			arquivo >> value;
			behaviours.at(y).at(x) = value;
		}
	}
	arquivo.close();

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			cout << behaviours.at(y).at(x) << " ";
		}
		cout << endl;
	}
}

int Map::getBehaviour(int x, int y) const
{
	return behaviours.at(y).at(x);
}

int Map::getGridWidth()
{
	return gridWidth;
}

int Map::getGridHeight()
{
	return gridHeight;
}

float Map::getTileWidth()
{
	return tileWidth;
}

float Map::getTileHeight()
{
	return tileHeight;
}

void Map::setPosition(float x, float y)
{
	position.set(x,y);
}

void Map::setPosition(ofVec2f position)
{
	this->position = position;
}

void Map::setWidth(float width)
{
	this->width = width;
}

void Map::setHeight(float height)
{
	this->height = height;
}

ofVec2f Map::getPosition()
{
	return position;
}

float Map::getWidth()
{
	return width;
}

float Map::getHeight()
{
	return height;
}

void Map::draw(ofVec2f &camera)
{
	img.draw(position.x - camera.x,position.y - camera.y, width, height);
}
