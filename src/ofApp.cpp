#include "ofApp.h"

float factor = 0.2f;
// 1.0 = 1 meter
float levelDistance = 3000*factor;
float f0f1Distance = 2150*factor;
float f3f4Distance = 8600*factor;
float f4f5Distance = 4300*factor;
float f5f6Distance = 11100*factor;
float f8f9Distance = 6000*factor;
float f0Long = 4300*factor;
float f0Short = 1700*factor;
float f1Long = 4300*factor;
float f1Short = 1700*factor;
float f2Long = 3950*factor;
float f2Short = 4300*factor;
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

float f4_5Short = 3000*factor;
float f4_5Long = 4300*factor;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    
    syphonServerDirectory.setup();
    ofAddListener(syphonServerDirectory.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(syphonServerDirectory.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(syphonServerDirectory.events.serverRetired, this, &ofApp::serverRetired);
    
    easyCam.setDistance(30000*factor);
    
    f0.set(f0Long, f0Short);
    f0.setPosition(f4f5Distance*.5 + f3f4Distance + f2Long + f0f1Distance, 0, 0);
    f0.rotate(-90, 0, 1, 0);
    f0.rotate(180, 0, 0, 1);
    
    f1.set(f1Long, f1Short);
    f1.setPosition(f4f5Distance*.5 + f3f4Distance + f2Long, levelDistance + f1Short*.5, 0);
    f1.rotate(90, 0, 1, 0);
    f1.rotate(180, 0,0,1);
    
    f2.set(f2Short, f2Long);
    f2.setPosition(f4f5Distance*.5 + f3f4Distance + f2Long *.5, levelDistance, 0);
    f2.rotate(90, 1, 0, 0);
    f2.rotate(90, 0, 1, 0);
    f2.rotate(180, 0,0,1);
    
    f3.set(f3Long, f3Short);
    f3.setPosition(f4f5Distance*.5 + f3f4Distance, levelDistance + f3Short*.5, -(f2Short-f3Long)*.5f);
    f3.rotate(90, 0, 1, 0);
    f3.rotate(180,1,0,0);
    
    f4.set(f4Long, f4Short);
    f4.setPosition(f4f5Distance * 0.5, 0, 0);
    f4.rotate(90, 0, 1, 0);
    f4.rotate(180, 0,0,1);
    
    f5.set(f5Long, f5Short);
    f5.setPosition(-(f4f5Distance * 0.5), 0, 0);
    f5.rotate(-90, 0, 1, 0);
    f5.rotate(180, 0, 0, 1);
    
    f6.set(f6Long, f6Short);
    f6.setPosition(-(f4f5Distance*.5 + f5f6Distance), levelDistance + f5Short*.5, 0);
    f6.rotate(90, 0, 1, 0);
    f6.rotate(180, 0, 0, 1);
    
    f7.set(f7Long, f7Short);
    f7.setPosition(-(f4f5Distance*.5 + f5f6Distance + f7Short*.5), levelDistance, 0);
    f7.rotate(90, 1, 0, 0);
    f7.rotate(90, 0, 1, 0);
    f7.rotate(180, 0, 0, 1);
    
    f8.set(f8Long, f8Short);
    f8.setPosition(-(f4f5Distance*.5 + f5f6Distance + f7Short), levelDistance + f5Short*.5, 0);
    f8.rotate(-90, 0, 1, 0);
    f8.rotate(180, 0, 0, 1);
    
    f9.set(f8Long, f8Short);
    f9.setPosition(-(f4f5Distance*.5 + f5f6Distance + f7Short + f8f9Distance), 0, 0);
    f9.rotate(90, 0, 1, 0);
    f9.rotate(180, 0, 0, 1);
    
    f4_5.set(f4_5Long, f4_5Short);
    f4_5.setPosition(0, -f4Short*.5, 0);
    f4_5.rotate(90, 1, 0, 0);
    
    planes.push_back(&f0);
    planes.push_back(&f1);
    planes.push_back(&f2);
    planes.push_back(&f3);
    planes.push_back(&f4);
    planes.push_back(&f5);
    planes.push_back(&f6);
    planes.push_back(&f7);
    planes.push_back(&f8);
    planes.push_back(&f9);
    planes.push_back(&f4_5);
    
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        plane->fbo.begin();
        ofClear(255);
        plane->syphonClient.draw(0, 0);
        plane->fbo.end();
    }
    
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        plane->rotate(180, 0, 0, 1);
    }
    
    
    ofSetSmoothLighting(true);
    
    light.setPosition(0, -1000, 0);
    light.setDiffuseColor(ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f));
    
    material.setShininess(120);
    material.setSpecularColor(ofFloatColor(1));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (ofGetKeyPressed('l')) {
        ofSetGlobalAmbientColor(ofFloatColor(1));
    }else{
        ofSetGlobalAmbientColor(ofFloatColor(0));
    }
    
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        plane->fbo.begin();
        ofClear(255);
        plane->syphonClient.draw(0, 0);
        plane->fbo.end();
    }
    
    light.setPosition(sin(ofGetElapsedTimef())*25000*factor, light.getPosition().y, light.getPosition().z);
}

bool drawNormals;

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0, 0, 0);
    easyCam.begin();
    
    light.enable();
    light.draw();
    
    material.begin();
    
    for (int i = 0; i < planes.size(); i++) {
        mutPlane *plane = planes[i];
        if (plane->isAnnounced) {
            plane->fbo.getTextureReference().bind();
            plane->mapTexCoordsFromTexture(plane->fbo.getTextureReference());
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
    
    material.end();
    
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'n') {
        drawNormals = !drawNormals;
    }
}

void ofApp::mouseDragged(int x, int y, int button){
    
}

// ----- Syphon Callbacks -----

void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg){
    for (auto &dir : arg.servers) {
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
        if(dir.serverName == "f0"){
            planes[0]->isAnnounced = true;
            planes[0]->syphonClient.set(dir);
        }else if(dir.serverName == "f1"){
            planes[1]->isAnnounced = true;
            planes[1]->syphonClient.set(dir);
        }else if(dir.serverName == "f2"){
            planes[2]->isAnnounced = true;
            planes[2]->syphonClient.set(dir);
        }else if(dir.serverName == "f3"){
            planes[3]->isAnnounced = true;
            planes[3]->syphonClient.set(dir);
        }else if(dir.serverName == "f4"){
            planes[4]->isAnnounced = true;
            planes[4]->syphonClient.set(dir);
        }else if(dir.serverName == "f5"){
            planes[5]->isAnnounced = true;
            planes[5]->syphonClient.set(dir);
        }else if(dir.serverName == "f6"){
            planes[6]->isAnnounced = true;
            planes[6]->syphonClient.set(dir);
        }else if(dir.serverName == "f7"){
            planes[7]->isAnnounced = true;
            planes[7]->syphonClient.set(dir);
        }else if(dir.serverName == "f8"){
            planes[8]->isAnnounced = true;
            planes[8]->syphonClient.set(dir);
        }else if(dir.serverName == "f9"){
            planes[9]->isAnnounced = true;
            planes[9]->syphonClient.set(dir);
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
        if(dir.serverName == "F0"){
            planes[0]->isAnnounced = false;
        }else if(dir.serverName == "F1"){
            planes[1]->isAnnounced = false;
        }else if(dir.serverName == "F2"){
            planes[2]->isAnnounced = false;
        }else if(dir.serverName == "F3"){
            planes[3]->isAnnounced = false;
        }else if(dir.serverName == "F4"){
            planes[4]->isAnnounced = false;
        }else if(dir.serverName == "F5"){
            planes[5]->isAnnounced = false;
        }else if(dir.serverName == "F6"){
            planes[6]->isAnnounced = false;
        }else if(dir.serverName == "F7"){
            planes[7]->isAnnounced = false;
        }else if(dir.serverName == "F8"){
            planes[8]->isAnnounced = false;
        }else if(dir.serverName == "F9"){
            planes[9]->isAnnounced = false;
        }
    }
}