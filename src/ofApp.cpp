#include "ofApp.h"


#define IP "127.0.0.1"
#define SERVER_IP "127.0.0.1"
#define PORT 12333
#define MAX_LIGHTS 8

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

int markerIds[10] = {691, 268, 581, 761, 528, 286, 484, 99, 222, 903};
enum{
    FLOOR,
    EAST,
    WEST,
    
};


void ofApp::sendPlanePositions(){
    
    for (int j = 0; j < senders.size(); j++) {
        for (int i = 0; i < planes.size(); i++) {
            ofxOscMessage m2;
            string oscAddress = "f"+ofToString(i)+"/position";
            m2.setAddress(oscAddress);
            m2.addFloatArg(planes[i]->getPosition().x);
            m2.addFloatArg(planes[i]->getPosition().y);
            m2.addFloatArg(planes[i]->getPosition().z);
            
            senders[j]->sendMessage(m2);
        }
    }
}

ofVec2f ofApp::normalizedPointToScreenPoint(ofVec2f normalizedPoint, ofPlanePrimitive *aPlane){
    ofVec2f point;
    
    point.x = normalizedPoint.x * aPlane->getWidth() - aPlane->getWidth()*.5f;
    point.y = normalizedPoint.y * aPlane->getHeight() - aPlane->getHeight()*.5f;
    
    return point;
    
    
}

void ofApp::parseJSONString(string str){
    
    jsonElement = ofxJSONElement(str);
    
    event = jsonElement["event"].asString();
    markerId = jsonElement["id"].asInt();
    touchedX = jsonElement["x"].asFloat();
    touchedY = jsonElement["y"].asFloat();
    
}

void ofApp::setup(){
    
    // const int oscPorts[10] = {6000,6000,6000,6001,6000,6000,6002,6001,6000,6002};
    
    
    sender0 = new ofxOscSender();
    sender1 = new ofxOscSender();
    sender2 = new ofxOscSender();
    sender3 = new ofxOscSender();
    sender4 = new ofxOscSender();
    sender5 = new ofxOscSender();
    sender6 = new ofxOscSender();
    sender7 = new ofxOscSender();
    sender8 = new ofxOscSender();
    sender9 = new ofxOscSender();

    bool local = true;
    
    if (local) {
        
        sender0->setup(SERVER_IP, 6000);
        sender1->setup(SERVER_IP, 6001);
        sender2->setup(SERVER_IP, 6002);
        sender3->setup(SERVER_IP, 6003);
        sender4->setup(SERVER_IP, 6004);
        sender5->setup(SERVER_IP, 6005);
        sender6->setup(SERVER_IP, 6006);
        sender7->setup(SERVER_IP, 6007);
        sender8->setup(SERVER_IP, 6008);
        sender9->setup(SERVER_IP, 6009);
    }
    else{
        sender0->setup("10.0.0.12", 6000);
        sender1->setup("10.0.0.10", 6001);
        sender2->setup("10.0.0.14", 6002);
        sender3->setup("10.0.0.12", 6003);
        sender4->setup("10.0.0.11", 6004);
        sender5->setup("10.0.0.13", 6005);
        sender6->setup("10.0.0.12", 6006);
        sender7->setup("10.0.0.14", 6007);
        sender8->setup("10.0.0.15", 6008);
        sender9->setup("10.0.0.14", 6009);
    }
    
    senders.push_back(sender0);
    senders.push_back(sender1);
    senders.push_back(sender2);
    senders.push_back(sender3);
    senders.push_back(sender4);
    senders.push_back(sender5);
    senders.push_back(sender6);
    senders.push_back(sender7);
    senders.push_back(sender8);
    senders.push_back(sender9);
    
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
    
    // Syphon output renders upside down.
    
    if (!isSyphonOutput) {
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->rotate(180, 0, 0, 1);
        }
    }
    
    
    
    ofSetGlobalAmbientColor(ofFloatColor(0.5f));
    
    ofSetSmoothLighting(true);
    
    material.setShininess(120);
    material.setSpecularColor(ofFloatColor(1));
    
    
    sendPlanePositions();
    
    tcpClient.setup(IP, PORT);
    tcpClient.setMessageDelimiter("\n");
    
    mutLightID = 0;
    
    for (int i = 0; i < 8; i++) {
        mutLight *light = (mutLight*)new ofLight;
        light->setSpotlight();
        light->mutLightID = i;
        light->active = false;
        light->setDiffuseColor(ofFloatColor(0.0f, 0.0f, 0.0f));
        light->setSpotlightCutOff(0.0f);
        light->setSpotConcentration(0.0f);
        light->disable();
        lights.push_back(light);
    }
    
    if (isSyphonOutput) {
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->fbo.allocate(plane->getWidth(), plane->getHeight());
            plane->syphonClient.setup();
        }
    }
}

void ofApp::playSound(){
    if (ofRandom(1)<0.5f) {
        soundPlayer.loadSound("StereoVocal.aif");
    }
    else{
        soundPlayer.loadSound("audio_5.aif");
    }
    soundPlayer.play();
}

void ofApp::update(){
    
    if (tcpClient.isConnected())
    {
        string str = tcpClient.receive();
        
        if( str.length() > 0 )
        {
            
            printf("str = %s\n", str.c_str());
            
            parseJSONString(str);
            
            for (int i = 0; i<planes.size(); i++) {
                ofPlanePrimitive *plane = planes[i];
                screenPoint = normalizedPointToScreenPoint(ofVec2f(touchedX, touchedY), plane);
                
                /*cout << "markerId: "+ ofToString(markerId) + ", screenPoint = " << screenPoint << endl;*/
            }
            
            
            if ((event == "press")) {
                float planeDistance = 30.0f;
                
                mutLightID  = (mutLightID+1)%8;
                
                for (int i = 0; i<lights.size(); i++) {
                    lightPtr = lights[i];
                    if (lightPtr->mutLightID == mutLightID) {
                        lightPtr->enable();
                        lightPtr->active = true;
                        lightPtr->setDiffuseColor(ofColor(ofRandom(255.0f), ofRandom(255.0f), ofRandom(255.0f)));
                        lightPtr->setSpotlight();
                        lightPtr->setSpotlightCutOff(90.0f);
                        lightPtr->setSpotConcentration(128.0f);
                        switch (markerId) {
                            case 691:
                            {
                                p = planes[0];
                                lightPtr->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
                                orientation = WEST;
                                break;
                            }
                            case 268:
                            {
                                p = planes[1];
                                lightPtr->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
                                orientation = EAST;
                                break;
                            }
                            case 581:
                            {
                                p = planes[2];
                                lightPtr->setPosition(p->getPosition().x - screenPoint.y , p->getPosition().y - planeDistance, p->getPosition().z - screenPoint.x);
                                orientation = FLOOR;
                                break;
                            }
                            case 761:
                            {
                                p = planes[3];
                                lightPtr->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
                                orientation = WEST;
                                break;
                            }
                            case 528:
                            {
                                p = planes[4];
                                lightPtr->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
                                orientation = EAST;
                                break;
                            }
                            case 286:
                            {
                                p = planes[5];
                                lightPtr->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
                                orientation = WEST;
                                break;
                            }
                            case 484:
                            {
                                p = planes[6];
                                lightPtr->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
                                orientation = EAST;
                                break;
                            }
                            case 99:
                            {
                                p = planes[7];
                                lightPtr->setPosition(p->getPosition().x - screenPoint.y , p->getPosition().y-planeDistance, p->getPosition().z - screenPoint.x);
                                orientation = FLOOR;
                                break;
                            }
                            case 222:
                            {
                                p = planes[8];
                                lightPtr->setPosition(p->getPosition().x - planeDistance , p->getPosition().y - screenPoint.y, -(p->getPosition().z - screenPoint.x));
                                orientation = WEST;
                                break;
                            }
                            case 903:
                            {
                                p = planes[9];
                                lightPtr->setPosition(p->getPosition().x + planeDistance , p->getPosition().y - screenPoint.y, p->getPosition().z - screenPoint.x);
                                orientation = EAST;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                
                lights.push_back(lightPtr);
                
                /*cout << "light.getPosition() = " << light.getPosition() << endl;*/
               
                playSound();
                
            }
            
            markerId = -1;
        }
    }
    else
    {
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
		if( deltaTime > 5000 ){
			
            tcpClient.setup(IP, PORT);
            tcpClient.setMessageDelimiter("\n");
            
			connectTime = ofGetElapsedTimeMillis();
		}
	}
    
    if (p != NULL) {
        for (int i = 0; i<lights.size(); i++) {
            mutLight *l = lights[i];
            if (l->active == true) {
                switch (orientation) {
                    case FLOOR:
                        l->setPosition(l->getPosition().x + sin(ofGetElapsedTimef())*20,
                                       p->getPosition().y - 100,
                                       l->getPosition().z + cos(ofGetElapsedTimef())*20);
                        
                        /*light.setPosition(light.getPosition().x-cos(ofGetElapsedTimef())*150, light.getPosition().y-sin(ofGetElapsedTimef())*150, light.getPosition().z);*/
                        break;
                    case EAST:
                        l->setPosition(p->getPosition().x + 100,
                                       l->getPosition().y + sin(ofGetElapsedTimef())*20,
                                       l->getPosition().z + cos(ofGetElapsedTimef())*20);
                        
                        /*light.setPosition(light.getPosition().x-cos(ofGetElapsedTimef())*150, light.getPosition().y-sin(ofGetElapsedTimef())*150, light.getPosition().z);*/
                        break;
                    case WEST:
                        l->setPosition(p->getPosition().x - 100,
                                       l->getPosition().y + sin(ofGetElapsedTimef())*20,
                                       l->getPosition().z + cos(ofGetElapsedTimef())*20);
                        
                        /*light.setPosition(light.getPosition().x-cos(ofGetElapsedTimef())*150, light.getPosition().y-sin(ofGetElapsedTimef())*150, light.getPosition().z);*/
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
    
    for (int j = 0; j < senders.size(); j++) {
        for (int i = 0; i<lights.size(); i++) {
            ofxOscMessage m;
            m.setAddress("/light/position");
            m.addFloatArg(lights[i]->getPosition().x);
            m.addFloatArg(lights[i]->getPosition().y);
            m.addFloatArg(lights[i]->getPosition().z);
            m.addFloatArg(lights[i]->getDiffuseColor().r);
            m.addFloatArg(lights[i]->getDiffuseColor().g);
            m.addFloatArg(lights[i]->getDiffuseColor().b);
            m.addFloatArg(lights[i]->getSpotlightCutOff());
            m.addFloatArg(lights[i]->getSpotConcentration());
            m.addInt64Arg(lights[i]->mutLightID);
            m.addIntArg((int)lights[i]->active);
            
            senders[j]->sendMessage(m);
        }
    }
    
    sendPlanePositions();
    
    if (isSyphonOutput) {
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->fbo.begin();
            ofClear(255);
            plane->syphonClient.draw(0, 0);
            plane->fbo.end();
        }
    }
}

void ofApp::draw(){
    ofClear(0, 0, 0);
    
    
    ofEnableDepthTest();
    
    easyCam.begin();
    
    if (isSyphonOutput) {
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
    }
    else{
        
        material.begin();
        
        for (int i = 0; i < planes.size(); i++) {
            mutPlane *plane = planes[i];
            plane->draw();
            
            if (drawNormals) {
                ofSetColor(0);
                plane->drawNormals(50);
                ofSetColor(255);
            }
        }
    }
    
    if (drawLights) {
        for (int i = 0; i<lights.size(); i++) {
            if (lights[i]->active) {
                lights[i]->draw();
            }
        }
    }
    
    material.end();
    
    easyCam.end();
    
    ofDisableDepthTest();
}

void ofApp::keyPressed(int key){
    
    if (key == 'n') {
        drawNormals = !drawNormals;
    }
    
    if (key == 'l'){
        drawLights = !drawLights;
    }
    
    if (key == 't') {
        sendPlanePositions();
    }
    
    if (key == 'm') {
        ofxOscMessage m;
        m.setAddress("/marker/on");
        markerOn = !markerOn;
        m.addIntArg(markerOn);
        for(int i = 0; i<senders.size(); i++){
            senders[i]->sendMessage(m);
        }
    }
    
    if (key == 's') {
        isSyphonOutput = !isSyphonOutput;
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
















