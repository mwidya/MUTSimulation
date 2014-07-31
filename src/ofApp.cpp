#include "ofApp.h"

float factor = 0.1f;

// 1.0 = 1 meter

float levelDistance = 3000*factor;
float middleDistance = 4300*factor;
float f0f1Distance = 2150*factor;
float f3f4Distance = 8600*factor;
float f0Long = 4300*factor;
float f0Short = 1700*factor;
float f1Long = 3000*factor;
float f1Short = 1700*factor;
float f2Long = 3950*factor;
float f2Short = 3000*factor;
float f3Long = 3000*factor;
float f3Short = 1700*factor;
float f4Long = 3000*factor;
float f4Short = 1700*factor;
float f5Long = 3000*factor;
float f5Short = 1700*factor;
float f6Long = 4300*factor;
float f6Short = 1700*factor;
float f7Long = 4300*factor;
float f7Short = 3950*factor;
float f8Long = 4300*factor;
float f8Short = 1700*factor;
float f9Long = 4300*factor;
float f9Short = 1700*factor;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableDepthTest();
    
    syphonServerDirectory.setup();
    ofAddListener(syphonServerDirectory.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(syphonServerDirectory.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(syphonServerDirectory.events.serverRetired, this, &ofApp::serverRetired);
    
    easyCam.setDistance(20000*factor);
    
    f0.set(f0Long, f0Short);
    f0.setPosition(middleDistance*.5 + f3f4Distance + f2Long + f0f1Distance, 0, 0);
    f0.rotate(90, 0, 1, 0);
    
    f1.set(f1Long, f1Short);
    f1.setPosition(middleDistance*.5 + f3f4Distance + f2Long, levelDistance + f1Short*.5, 0);
    f1.rotate(90, 0, 1, 0);
    f1.rotate(180, 1, 0, 0);
    
    f2.set(f2Long, f2Short);
    f2.setPosition(middleDistance*.5 + f3f4Distance + f2Long *.5, levelDistance, 0);
    f2.rotate(90, 1, 0, 0);
    
    f3.set(f3Long, f3Short);
    f3.setPosition(middleDistance*.5 + f3f4Distance, levelDistance + f3Short*.5, 0);
    f3.rotate(90, 0, 1, 0);
    
    f4.set(f4Long, f4Short);
    f4.setPosition(-(middleDistance * 0.5), 0, 0);
    f4.rotate(90, 0, 1, 0);
    f4.rotate(180, 1, 0, 0);
    
    f5.set(f5Long, f5Short);
    f5.setPosition(middleDistance * 0.5, 0, 0);
    f5.rotate(90, 0, 1, 0);
    
    planes.push_back(&f0);
    planes.push_back(&f1);
    planes.push_back(&f2);
    planes.push_back(&f3);
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

bool drawNormals;

//--------------------------------------------------------------
void ofApp::draw(){
    easyCam.begin();
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        if (plane->isAnnounced) {
            plane->fbo.getTextureReference().bind();
            plane->mapTexCoordsFromTexture(f4.fbo.getTextureReference());
            plane->draw();
            plane->fbo.getTextureReference().unbind();
        }else{
            plane->draw();
        }
        
        if (drawNormals) {
            ofSetColor(0);
            plane->drawNormals(50);
            ofSetColor(255);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'n') {
        drawNormals = !drawNormals;
    }
}

// ----- Syphon Callbacks -----

void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
        if(dir.serverName == "Chessboard"){
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
        if(dir.serverName == "Chessboard"){
            planes[0]->isAnnounced = false;
        }else if(dir.serverName == "F5"){
            planes[1]->isAnnounced = false;
        }
    }
}