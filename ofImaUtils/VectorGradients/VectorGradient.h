//
//  VectorGradient.h
//  ParticlesApp
//
//  Created by Martial on 10/08/2015.
//
//

#ifndef __ParticlesApp__VectorGradient__
#define __ParticlesApp__VectorGradient__

#include "ofMain.h"

class VectorGradient : public ofVec2f{
    
public:
    
    VectorGradient();
    void draw();
    void drawVerticesHandlers();
    void drawNormal();
    void drawCanvas();
    
    vector<ofVec2f*> vertices;
    ofVec2f a, b, c;
    float depth;
    
    ofEvent<int> selectedEvent;
    ofEvent<int> changedEvent;
    ofEvent<int> deletedEvent;


    
    virtual void mouseMoved(ofMouseEventArgs &a);
    virtual void mouseDragged(ofMouseEventArgs &a);
    virtual void mousePressed(ofMouseEventArgs &a);
    virtual void mouseReleased(ofMouseEventArgs &a);
    //virtual void keyPressed(ofKeyEventArgs &a);
    //virtual void keyReleased(ofKeyEventArgs &a);
    
    bool    bIsSelected, bIsInsideHandler, bIsInsideDepthHandler, bEditable;

    int index;
    
private:
    
    float       handlerRadius;
    
    ofVec2f *        selectedVertex;
    int              handlerSelected;
    
    ofVec2f          lastClick;
    float            savedLength;
    
    ofRectangle      canvas;
    
    ofImage          img;
    bool             bNeedImgUpdate;

    
};

#endif /* defined(__ParticlesApp__VectorGradient__) */
