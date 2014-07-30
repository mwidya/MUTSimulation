#include "ofApp.h"

float middleDistance = 430;
float f4Long = 300;
float f4Short = 170;
float f5Long = 300;
float f5Short = 170;

void ofApp::configureSyphon()
{
    syphonServerDirectory.setup();
    ofAddListener(syphonServerDirectory.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(syphonServerDirectory.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(syphonServerDirectory.events.serverRetired, this, &ofApp::serverRetired);

    syphonClient.setup();
}

void ofApp::configurePrimitives()
{

    f4.set(f4Long, f4Short);
    f4.rotate(270, 0, 1, 0);
    f4.setPosition(-(middleDistance * 0.5), 0, 0);
    
    f5.set(f5Long, f5Short);
    f5.rotate(90, 0, 1, 0);
    f5.setPosition(middleDistance * 0.5, 0, 0);
    
}

void ofApp::configueFramebuffers()
{
    fbo.allocate(f4.getWidth(), f4.getHeight());
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableDepthTest();
    
    configureSyphon();
    configurePrimitives();
    configueFramebuffers();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
    ofClear(255);
    fbo.end();
    fbo.begin();
    syphonClient.draw(0, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    easyCam.begin();
    
    fbo.getTextureReference().bind();
    f4.mapTexCoordsFromTexture(fbo.getTextureReference());
    f4.draw();
    f4.drawNormals(20);
    fbo.getTextureReference().unbind();
    
    f5.draw();
    f5.drawNormals(20);
    
    easyCam.end();
    
}

// ----- Syphon Callbacks -----

void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
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
    }
}