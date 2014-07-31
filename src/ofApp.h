#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "mutPlane.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    bool isF4;
    
    // ----- Syphon -----
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxSyphonServerDirectory syphonServerDirectory;
    
    // ----- Primitives -----
    
    ofEasyCam easyCam;
    
    mutPlane f0;
    mutPlane f1;
    mutPlane f2;
    mutPlane f3;
    mutPlane f4;
    mutPlane f5;
    mutPlane f6;
    mutPlane f7;
    mutPlane f8;
    mutPlane f9;
    
    vector<mutPlane*> planes;
		
};
