#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "mutPlane.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    
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
    mutPlane f4_5;
    
    vector<mutPlane*> planes;
    
    ofMaterial material;
    ofLight light;
    
    vector<ofxOscSender*> senders;
    ofxOscSender *sender0;
    ofxOscSender *sender1;
    ofxOscSender *sender2;
    ofxOscSender *sender3;
    ofxOscSender *sender4;
    ofxOscSender *sender5;
    ofxOscSender *sender6;
    ofxOscSender *sender7;
    ofxOscSender *sender8;
    ofxOscSender *sender9;
};
