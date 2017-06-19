#pragma once
#include "ofMain.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Map
{
private:
	ofVec2f position;
	float width, height;

	string imgPath;
	ofImage img;
	
	int gridWidth, gridHeight;
	vector< vector<int> > behaviours;

	float tileWidth, tileHeight;
public:
	Map(string path, float width, float height);

	void init();

	void setBehaviours(string path, int w, int h);
	int getBehaviour(int x, int y) const;

	int getGridWidth();
	int getGridHeight();

	float getTileWidth();
	float getTileHeight();

	void setPosition(float x, float y);
	void setPosition(ofVec2f position);

	void setWidth(float width);
	void setHeight(float height);

	ofVec2f getPosition();
	float getWidth();
	float getHeight();

	void draw(ofVec2f &camera);
};