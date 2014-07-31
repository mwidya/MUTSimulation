#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "mutPlane.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    bool isF4;
    
    // ----- Syphon -----
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxSyphonServerDirectory syphonServerDirectory;
    
    // ----- Primitives -----
    
    ofEasyCam easyCam;
    
    mutPlane f4;
    mutPlane f5;
    
    vector<mutPlane*> planes;
		
};
