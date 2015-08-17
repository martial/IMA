//
//  ofxDragAndZoomable.h
//  example_window
//
//  Created by Martial on 20/07/2015.
//
//

#ifndef __example_window__ofxDragAndZoomable__
#define __example_window__ofxDragAndZoomable__

#include "ofMain.h"

class ofxDragAndZoomable : public ofRectangle {
    
    
public:
    
    ofxDragAndZoomable();
    
    void update();
    
    void    scaleFromPoint(float s, ofVec2f pnt);
    ofVec2f getPointAtCoordinate(ofVec2f point, float * scale = NULL);
    
    void    fitToScreen();
    void    drag(float x, float y);
    
    virtual void onWheelEvent(float & aperture);

    float   getScale();
    
protected:
    

    
    int                     lastScrollSens;
    ofPoint                 lastClick;
    ofRectangle             origRect;
    float                   rectScale;
    int                     sens;
    
    bool                    bIsShiftPressed;

    
};

#endif /* defined(__example_window__ofxDragAndZoomable__) */
