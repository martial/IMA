//
//  VideoManager.cpp
//  example_window
//
//  Created by Martial on 17/07/2015.
//
//

#include "VideoManager.h"
#include "ofxImgSizeUtils.h"


VideoManager::VideoManager() {
    
    ofxDragAndZoomable();
    
    bHasChanged     = true;
    bIsVertical     = false;
    bFitToScreen    = true;
    bIsScaling      = false;
    bIsVideoVisible = true;
    
    // wheel event ( works only w/ ofxCocoa + custom OF
    
    ofAddListener(ofEvents().mouseReleased, this, &VideoManager::onMouseReleavedEvent);
    ofAddListener(ofEvents().mousePressed, this, &VideoManager::onMousePressedEvent);
    ofAddListener(ofEvents().mouseDragged, this, &VideoManager::onMouseDragEvent);
    ofAddListener(ofEvents().keyPressed, this, &VideoManager::onKeyPressedEvent);
    ofAddListener(ofEvents().wheelEvent, this, &VideoManager::onWheelEvent);

}

void VideoManager::setPolyLineMaker(PolylineMaker * p){
    
    this->polyLineManager = p;
}


void VideoManager::update() {
    
    ofxDragAndZoomable::update();
    
    
    if(areAllVideosLoaded() ) {
        
        if(bHasChanged) {
            allocateFbo();
            fitToScreen();
            bHasChanged = false;
            
        }
        
        for(vector<ofxHapPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
            ofxHapPlayer * player = *it;
            player->update();
            
        }
        
    }
    
    
    bIsScaling = false;
    
}

void VideoManager::prepass() {
    
    fbo.begin();
    ofBackground(0);
    ofSetColor(255, 255, 255);
    ofEnableSmoothing();
    
    if(bIsVideoVisible) {
        float x, y;
        x = 0.0f;
        y = 0.0f;
        
        for(int i =0; i<players.size(); i++) {
            
            ofxHapPlayer * player = players[i];
            
            if(bIsVertical) {
                if(i>0) y += players[i-1]->getHeight();
            } else {
                if(i>0) x += players[i-1]->getWidth();
            }
            
            ofSetColor(255, 255, 255);
            player->draw(x,y);
            
        }
        
       
    ofSetColor(255, 255, 255);
    polyLineManager->draw();
        
    }
    

    ofSetColor(255, 255, 255);
    
    fbo.end();
    
}


void VideoManager::draw() {
    
    //fitToScreen();
    ofSetColor(255,255,255);
    fbo.draw(this->x, this->y, this->width, this->height);
    
}

void VideoManager::loadMovie(string path) {
    
    ofxHapPlayer * player = new ofxHapPlayer();
    player->loadMovie(path);
    players.push_back(player);
    
    bHasChanged = true;
    
}

void VideoManager::playAll() {
    
    for(vector<ofxHapPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        
        ofxHapPlayer * player = *it;
        player->play();
        
    }
    
}
void VideoManager::pauseAll() {
    for(vector<ofxHapPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        
        ofxHapPlayer * player = *it;
        player->stop();
        
    }
    
}
void VideoManager::stopAll() {
    for(vector<ofxHapPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        
        ofxHapPlayer * player = *it;
        player->stop();
        
    }
    
}

bool VideoManager::areAllVideosLoaded () {
    
    // wait for all videos to be loaded
    
    int numLoaded = 0;
    for(vector<ofxHapPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        
        ofxHapPlayer * player = *it;
        if (player->isLoaded())
            numLoaded ++;
    }
    
    return (numLoaded == players.size()) ;
    
}

void VideoManager::allocateFbo() {
    
    float width   = 0.0f;
    float height  = 0.0f;
    
    for(int i =0; i<players.size(); i++) {
        
        ofxHapPlayer * player = players[i];
        
        if(i == 0) {
            width   += player->getWidth();
            height  += player->getHeight();
        }
        
        if(i>0) {
            
            if(!bIsVertical )
                width   += player->getWidth();
            else
                height  += player->getHeight();
        }
        
    }
    
    fbo.allocate(width, height);
    this->setWidth(width);
    this->setHeight(height);
    
    // store original in rect as we'll need later
    origRect.set(x,y,width, height);
    
}

ofFbo* VideoManager::getFbo() {
    
    return &fbo;
    
}


void VideoManager::onMousePressedEvent(ofMouseEventArgs & e) {
    
    if(bIsShiftPressed) {
        lastClick.set(e.x - x, e.y - y);
    }
    
    ofVec2f pntAtCoords = getPointAtCoordinate(ofVec2f(e.x, e.y));
    polyLineManager->mousePressed(pntAtCoords.x, pntAtCoords.y);
    
}

void VideoManager::onMouseDragEvent(ofMouseEventArgs & e) {
    
    if(bIsShiftPressed) {
        drag(e.x, e.y);
    }
    
    ofVec2f pntAtCoords = getPointAtCoordinate(ofVec2f(e.x, e.y));
    polyLineManager->mouseDragged(pntAtCoords.x, pntAtCoords.y);
}

void VideoManager::onMouseReleavedEvent(ofMouseEventArgs & e) {
    
    ofVec2f pntAtCoords = getPointAtCoordinate(ofVec2f(e.x, e.y));
    polyLineManager->mouseReleased(pntAtCoords.x, pntAtCoords.y);
    
}

void VideoManager::toggleVideoVisible() {
    
    bIsVideoVisible = !bIsVideoVisible;
    
}


void VideoManager::onKeyPressedEvent(ofKeyEventArgs & e) {
    
    
    switch (e.key) {
        case OF_KEY_SHIFT:
            
            break;
            
            
        default:
            break;
    }
    
}

void VideoManager::onWheelEvent(float & aperture) {
    
    ofxDragAndZoomable::onWheelEvent(aperture);
}


