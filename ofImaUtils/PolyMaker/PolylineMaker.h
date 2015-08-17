//
//  PolylineMaker.h
//  PolyMakerApp
//
//  Created by Martial on 16/07/2015.
//
//

#ifndef __PolyMakerApp__PolylineMaker__
#define __PolyMakerApp__PolylineMaker__

#include "ofMain.h"
#include "DynamicPolyline.h"
#include "ofxXmlSettings.h"

class PolylineMaker {
    
public:
    
    PolylineMaker();
    void draw();
    
    void loadData();
    void saveData();
    
    bool bAddMode;
    
    bool getEditMode();
    void setEditMode(bool b);

    void toggleEditMode();
    
    void setActive(bool b);
    void onPolyChangedHandler(int & index);
    void onPolySelectedHandler(int & index);
    
    void addQuad();
    
    void setInactiveMaskColor(float r, float g, float b, float a);
    
    
    void onMouseMoved(float x, float y);
    void mouseDragged(float x, float y);
    void mousePressed(float x, float y);
    void mouseReleased(float x, float y);
    void keyPressed(int key);
    void keyReleased();
    
    vector<DynamicPolyline*> polylines;

    ofEvent<int> changedEvent;

    
private:
    
    int  lastSelected;
    
    bool bEditMode;
    
    void begin();
    void end();
    
    ofColor inactiveMaskColor;
    
    ofxXmlSettings xml;
    
    
    
    
};

#endif /* defined(__PolyMakerApp__PolylineMaker__) */
