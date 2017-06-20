#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);

	//Camera Setup
	camera = new Camera(ofGetScreenHeight()/2, ofGetScreenHeight() / 2);

	//Map Setup
	string mapa = "video";
	map = new Map("maps/"+ mapa+".png", ofGetScreenHeight(), ofGetScreenHeight());
	map->init();
	map->setPosition(ofGetScreenWidth()/2 - map->getWidth()/2, ofGetScreenHeight()/2 - map->getHeight()/2);
	map->setBehaviours("bin/data/maps/"+mapa+".txt",16,16);

	//Player Setup
	player = new Player(*map);
	player->setSpeed(1000);

	//World
	world = new World(*map);
}

//--------------------------------------------------------------
void ofApp::update(){
	player->update(ofGetLastFrameTime(), *map, camera->getPosition(), *world);
	world->update(ofGetLastFrameTime(), *map, player->getPosition());
	camera->track(player->getPosition());
	camera->bounds(*map);
	camera->update();

	ofSetWindowTitle(ofToString(ofGetFrameRate(), 0) + "fps");
}

//--------------------------------------------------------------
void ofApp::draw(){
	map->draw(camera->getPosition());
	
	player->draw(camera->getPosition());
	world->draw(camera->getPosition());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
