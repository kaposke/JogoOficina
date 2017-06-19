#pragma once
#include "ofMain.h"
#include "Map.h"

class Camera
{
private:
	ofVec2f position;
	float width, height;
public:
	Camera();
	Camera(float w, float h);

	void update();

	void track(ofVec2f target);

	void bounds(Map &map);

	void mouseBounds();

	ofVec2f getPosition();
};