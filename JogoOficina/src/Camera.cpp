#include "Camera.h"

Camera::Camera()
{
	width = ofGetWidth();
	height = ofGetHeight();
}

Camera::Camera(float w, float h)
{
	width = w;
	height = h;
}

void Camera::update()
{
	ofSetWindowShape(width,height);
	ofSetWindowPosition(position.x,position.y);
	mouseBounds();
}

void Camera::track(ofVec2f target)
{
	position.set(target.x - width/2, target.y - height/2);
}

void Camera::bounds(Map & map)
{
	position.x = position.x < map.getPosition().x ? map.getPosition().x : position.x;
	position.x = position.x > map.getPosition().x + map.getWidth() - width ? map.getPosition().x + map.getWidth() - width : position.x;

	position.y = position.y < map.getPosition().y ? map.getPosition().y : position.y;
	position.y = position.y > map.getPosition().y + map.getHeight() - height ? map.getPosition().y + map.getHeight() - height : position.y;
}

void Camera::mouseBounds()
{
	POINT curPos;
	BOOL result = GetCursorPos(&curPos);
	if (curPos.x < position.x)
		SetCursorPos(position.x, curPos.y);
	if (curPos.x > position.x + width)
		SetCursorPos(position.x + width, curPos.y);
	if (curPos.y < position.y)
		SetCursorPos(curPos.x, position.y);
	if (curPos.y > position.y + height)
		SetCursorPos(curPos.x, position.y + height);
}

ofVec2f Camera::getPosition()
{
	return position;
}
