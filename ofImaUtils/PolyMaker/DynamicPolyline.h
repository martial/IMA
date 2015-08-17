//
//  DynamicPolyline.h
//  PolyMakerApp
//
//  Created by Martial on 16/07/2015.
//
//

#ifndef __PolyMakerApp__DynamicPolyline__
#define __PolyMakerApp__DynamicPolyline__

#include "ofMain.h"

class DynamicPolyline : public ofPolyline {
    
public:
    
    DynamicPolyline();
    ~DynamicPolyline();

    void setup();
    void draw();

    void drawVerticesHandlers();
    
    void removeVertex(int index);
    
    void setInactiveColor(float r, float g, float b, float a);
    
    int  index;
    
    void enableEvents();
    void disableEvents();
    virtual void mouseMoved(ofMouseEventArgs &a);
    virtual void mouseDragged(ofMouseEventArgs &a);
    virtual void mousePressed(ofMouseEventArgs &a);
    virtual void mouseReleased(ofMouseEventArgs &a);
    virtual void keyPressed(ofKeyEventArgs &a);
    virtual void keyReleased(ofKeyEventArgs &a);
    
    
    ofEvent<int> selectedEvent;
    ofEvent<int> changedEvent;
    
    bool    bEditable, bLastSelected;
    
    void scaleAboutOrigin(const float scaleBy){
        ofPoint origin = getCentroid2D();
        scaleAboutPoint(scaleBy, origin);
    }
    
    void scaleAboutPoint(const float scaleBy, ofPoint& point){
        //TODO: Implement this with a matrix
        std::vector<ofPoint>& pts = getVertices();
        for (std::vector<ofPoint>::iterator pt = pts.begin(); pt != pts.end(); ++pt)
        {
            //TODO: check your math
            //move to origin
            (*pt) = (*pt) - point;
            //scale about origin
            pt->scale(scaleBy);
            //move back
            (*pt) = (*pt) + point;
        }
    }
    
    bool bIsNew;
    
    
private:
    
    
    float   handlerRadius;
    
    int     handlerSelected;
    bool    bIsInsideHandler;
    bool    bIsSelected;
    bool    bIsEditMode;
    
    ofPoint         lastClicked;
    vector<ofPoint> lastVertices;
    
    ofColor inactiveColor;
    
};

#endif /* defined(__PolyMakerApp__DynamicPolyline__) */
