#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "mutPlane.h"
#include "ofxOsc.h"
#include "ofxNetwork.h"
#include "ofxJSONElement.h"
#include "mutLight.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);

    void sendPlanePositions();
    
    void playSound();
    
    ofVec2f normalizedPointToScreenPoint(ofVec2f, ofPlanePrimitive *aPlane);
    
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
    
    ofPlanePrimitive *p = NULL;
    
    vector<mutPlane*> planes;
    
    ofMaterial material;
    deque<mutLight*> lights;
    long mutLightID;
    
    
    
    int lightEvent;
    
    
    ofVec3f startPos;
    ofVec3f targetPos;
    ofVec3f lerpPos;
    float amnt;
    float speed;
    
    
    
    
    
    
    ofVec3f lightOrientationFloor;
    ofVec3f lightOrientationEast;
    ofVec3f lightOrientationWest;
    
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
    
    ofxTCPClient tcpClient;
    int deltaTime = 0;
    int connectTime = 0;
    
    
    ofSoundPlayer soundPlayer;
    
    int orientation;
    
    bool isSyphonOutput = true;
    bool markerOn = true;
    bool drawNormals = false;
    bool drawLights = true;
};
