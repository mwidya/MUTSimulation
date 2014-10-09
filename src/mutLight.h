//
//  mutLight.h
//  MUTSimulation
//
//  Created by Martin Widyanata on 03.10.14.
//
//

#ifndef __MUTSimulation__mutLight__
#define __MUTSimulation__mutLight__


#include <iostream>
#include "ofMain.h"

class mutLight : public ofLight{
public:
    mutLight();
    ~mutLight();
    
    int getMutLightId();
    bool getIsActive();
    int getStatus();
    ofVec3f getStartPosition();
    ofVec3f getTargetPosition();
    ofVec3f getStartOrientation();
    ofVec3f getTargetOrientation();
    void setMutLightId(int mutLightId);
    void setIsActive(bool val);
    void setStatus(int status);
    void setStartPosition(ofVec3f startPosition);
    void setTargetPosition(ofVec3f targetPosition);
    void setStartOrientation(ofVec3f startOrientation);
    void setTargetOrientation(ofVec3f targetOrientation);
    
private:
    long mutLightID;
    bool isActive;
    int status;
    ofVec3f startPosition;
    ofVec3f targetPosition;
    ofVec3f startOrientation;
    ofVec3f targetOrientation;
};

#endif /* defined(__MUTSimulation__mutLight__) */
