#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{

public:
    void configureSyphon();
    void configurePrimitives();
    void configueFramebuffers();
    
    void setup();
    void update();
    void draw();
    
    // ----- Syphon -----
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxSyphonServerDirectory syphonServerDirectory;
    ofxSyphonClient syphonClient;
    
    // ------ Framebuffer -----
    
    ofFbo fbo;
    
    // ----- Primitives -----
    
    ofEasyCam easyCam;
    ofPlanePrimitive f4;
    ofPlanePrimitive f5;
		
};
