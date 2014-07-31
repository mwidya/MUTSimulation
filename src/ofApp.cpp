#include "ofApp.h"

float middleDistance = 430;
float f4Long = 300;
float f4Short = 170;
float f5Long = 300;
float f5Short = 170;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableDepthTest();
    
    syphonServerDirectory.setup();
    ofAddListener(syphonServerDirectory.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(syphonServerDirectory.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(syphonServerDirectory.events.serverRetired, this, &ofApp::serverRetired);
    
    f4.set(f4Long, f4Short);
    f4.rotate(270, 0, 1, 0);
    f4.setPosition(-(middleDistance * 0.5), 0, 0);
    
    f5.set(f5Long, f5Short);
    f5.rotate(90, 0, 1, 0);
    f5.setPosition(middleDistance * 0.5, 0, 0);
    
    planes.push_back(&f4);
    planes.push_back(&f5);
    
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        plane->fbo.allocate(plane->getWidth(), plane->getHeight());
        plane->syphonClient.setup();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        plane->fbo.begin();
        ofClear(255);
        plane->syphonClient.draw(0, 0);
        plane->fbo.end();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    easyCam.begin();
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        if (plane->isAnnounced) {
            plane->fbo.getTextureReference().bind();
            plane->mapTexCoordsFromTexture(f4.fbo.getTextureReference());
            plane->draw();
            plane->drawNormals(20);
            plane->fbo.getTextureReference().unbind();
        }else{
            plane->draw();
            plane->drawNormals(20);
        }
    }
}

// ----- Syphon Callbacks -----

void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
        if(dir.serverName == "F4"){
            planes[0]->isAnnounced = true;
            planes[0]->syphonClient.set(dir);
        }else if(dir.serverName == "F5"){
            planes[1]->isAnnounced = true;
            planes[1]->syphonClient.set(dir);
        }
    }
}

void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
        if(dir.serverName == "F4"){
            planes[0]->isAnnounced = false;
        }else if(dir.serverName == "F5"){
            planes[1]->isAnnounced = false;
        }
    }
}