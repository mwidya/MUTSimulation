//
//  mutLight.cpp
//  MUTSimulation
//
//  Created by Martin Widyanata on 03.10.14.
//
//

#include "mutLight.h"

enum{
    LIGHT_STATUS_LIVES,
    LIGHT_STATUS_POINT_TO_POINT,
    LIGHT_STATUS_MOVE_SOMEWHERE,
    LIGHT_STATUS_DEAD,
};

mutLight::mutLight(){
    this->mutLightID = -1;
    this->isActive = false;
    this->status = LIGHT_STATUS_DEAD;
    this->startPosition.set(0, 0, 0);
    this->targetPosition.set(0, 0, 0);
    this->startOrientation.set(0, 0, 0);
    this->targetOrientation.set(0, 0, 0);
}

mutLight::~mutLight(){
    
}

int mutLight::getMutLightId(){
    return mutLightID;
}
bool mutLight::getIsActive(){
    return isActive;
}
int mutLight::getStatus(){
    return status;
}
ofVec3f mutLight::getStartPosition(){
    return startPosition;
}
ofVec3f mutLight::getTargetPosition(){
    return targetPosition;
}
ofVec3f mutLight::getStartOrientation(){
    return startOrientation;
}
ofVec3f mutLight::getTargetOrientation(){
    return targetOrientation;
}
void mutLight::setMutLightId(int mutLightID){
    this->mutLightID = mutLightID;
}
void mutLight::setIsActive(bool val){
    this->isActive = val;
}
void mutLight::setStatus(int status){
    this->status = status;
}
void mutLight::setStartPosition(ofVec3f startPosition){
    this->startPosition = startPosition;
}
void mutLight::setTargetPosition(ofVec3f targetPosition){
    this->targetPosition = targetPosition;
}
void mutLight::setStartOrientation(ofVec3f startOrientation){
    this->startOrientation = startOrientation;
}
void mutLight::setTargetOrientation(ofVec3f targetOrientation){
    this->targetOrientation = targetOrientation;
}