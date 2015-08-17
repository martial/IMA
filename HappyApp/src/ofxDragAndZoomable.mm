//
//  ofxDragAndZoomable.cpp
//  example_window
//
//  Created by Martial on 20/07/2015.
//
//

#include "ofxDragAndZoomable.h"
#include "ofxImgSizeUtils.h"

ofxDragAndZoomable::ofxDragAndZoomable () {
    
    width           = 0.0f;
    height          = 0.0f;
    rectScale       = 1.0f;
    lastScrollSens  = 0.0;
    
    sens            = 0;
    bIsShiftPressed = false;
    rectScale       = 1.0;
    


    
}

void ofxDragAndZoomable::fitToScreen() {
    
    int screenW = ofGetWidth();
    int screenH = ofGetHeight();
    
    ofVec2f imgSize = ofxImgSizeUtils::getSizeRatio(screenW, screenH, origRect.getWidth(), origRect.getHeight());
    this->x = screenW *.5 - imgSize.x*.5;
    this->y = screenH *.5 - imgSize.y*.5;
    
    this->width = imgSize.x;
    this->height = imgSize.y;
    
    
}



void ofxDragAndZoomable::update() {
    
    // modifiers
    // ofxCocoa does not handle this – why tell me why
    
    UInt32	modifiers = GetCurrentKeyModifiers();
    if ( modifiers ) {
        
        if (shiftKey && !bIsShiftPressed) {
            // handle shift key...
            bIsShiftPressed = true;
        }
        
        if(!shiftKey) {
            bIsShiftPressed = false;
        }
        
    } else {
        bIsShiftPressed = false;
    }

    
    
}


void ofxDragAndZoomable::drag(float x, float y) {
    
    bool bIsOutsideBox = ( width > ofGetWidth() || height > ofGetHeight());
    this->x = bIsOutsideBox ? x - lastClick.x : ofClamp(x - lastClick.x, 0 , ofGetWidth() - width );
    this->y = bIsOutsideBox ? y - lastClick.y : ofClamp(y - lastClick.y, 0 , ofGetHeight() - height);
    
}

void ofxDragAndZoomable::scaleFromPoint(float s, ofVec2f pnt) {
    
    if(s == 1.0f) return;
    
    float newWidth  = width  * s;
    float newHeight = height * s;
    
    if(newWidth < 100 || newHeight < 100 )
        return;
    
    if(newWidth > ofGetWidth() * 20.0f || newHeight > ofGetHeight() * 20.0f )
        return;
    
    float xPosInRect = pnt.x - x;
    float yPosInRect = pnt.y - y;
    
    // scale ?
    float scalex    =  xPosInRect / width;
    float scaley    =  yPosInRect / height;
    
    x = pnt.x - newWidth  * scalex;
    y = pnt.y - newHeight * scaley;
    
    width  = newWidth;
    height = newHeight;
    
    
}

ofVec2f ofxDragAndZoomable::getPointAtCoordinate(ofVec2f point, float * scale) {
    
    float s = origRect.width / width;
    
    ofVec2f pnt;
    pnt.x = point.x * s - x * s;
    pnt.y = point.y * s - y * s;
    
    return pnt;
    
}

void ofxDragAndZoomable::onWheelEvent(float & aperture) {
    
    
    if(bIsShiftPressed) {
        
        int sens = (aperture > 0 ) ? 1 : 0;
        
        if(sens != lastScrollSens)
            rectScale = 1.0f;
        
        rectScale += aperture;
        rectScale = ofClamp(rectScale, -2.0f, 2.0f);
        
        
        this->scaleFromPoint(rectScale, ofVec2f(ofGetMouseX(), ofGetMouseY()));
        lastScrollSens = sens;
        
    }
    
    
}

float ofxDragAndZoomable::getScale () {
    
    return origRect.width / width;
    
}