//
//  VectorGradientsManager.h
//  ParticlesApp
//
//  Created by Martial on 10/08/2015.
//
//

#ifndef __ParticlesApp__VectorGradientsManager__
#define __ParticlesApp__VectorGradientsManager__

#include "ofMain.h"
#include "VectorGradient.h"
#include "ofxXmlSettings.h"


class VectorGradientsManager {
    
public:
    
    VectorGradientsManager();
    void setup();
    void update();
    void draw();
    
    void loadData();
    void saveData();

    bool getEditMode();
    void setEditMode(bool b);

    void toggleEditMode();
    
    void addVector(float x, float y);
    void endVector();
    
    void enableEvents();
    void disableEvents();
    
    virtual void mouseMoved(ofMouseEventArgs &a);
    virtual void mouseDragged(ofMouseEventArgs &a);
    virtual void mousePressed(ofMouseEventArgs &a);
    virtual void mouseReleased(ofMouseEventArgs &a);
    
    virtual void mouseMoved(float x, float y) {
        ofMouseEventArgs a;
        a.x = x;
        a.y = y;
        mouseMoved(a);
        
    }
    virtual void mouseDragged(float x, float y){
        ofMouseEventArgs a;
        a.x = x;
        a.y = y;
        mouseDragged(a);
        
    }

    virtual void mousePressed(float x, float y){
        ofMouseEventArgs a;
        a.x = x;
        a.y = y;
        mousePressed(a);
        
    }

    virtual void mouseReleased(float x, float y){
        ofMouseEventArgs a;
        a.x = x;
        a.y = y;
        mouseReleased(a);
        
    }

    
    virtual void keyPressed(ofKeyEventArgs &a) {};
    virtual void keyReleased(ofKeyEventArgs &a){};
    
    ofEvent<int> changedEvent;

    
private:
    
    void onChangedEvent(int & index);
    void onSelectedEvent(int & vertex);
    void onDeletedEvent(int & index);
    
    vector<VectorGradient* >    vectors;
    VectorGradient           *  selectedVector;
    
    bool    bEditMode;
    bool    bIsAdding;
    
    ofxXmlSettings xml;

    
};

#endif /* defined(__ParticlesApp__VectorGradientsManager__) */
