//
//  DynamicPolyline.cpp
//  PolyMakerApp
//
//  Created by Martial on 16/07/2015.
//
//

#include "DynamicPolyline.h"

DynamicPolyline::DynamicPolyline () {
    
    ofPolyline::ofPolyline();
    
    
    handlerRadius       = 20.0f;
    bIsInsideHandler    = false;
    bIsSelected         = false;
    bIsEditMode         = false;
    bEditable           = false;
    bLastSelected       = false;
    handlerSelected     = 0;
    enableEvents();
    inactiveColor.set(0,0,0);
    
    bIsNew              = false;
}

DynamicPolyline::~DynamicPolyline() {
    
    ofUnregisterMouseEvents(this);
    ofUnregisterKeyEvents(this);

}

void DynamicPolyline::enableEvents() {
   // ofRegisterMouseEvents(this);
    ofRegisterKeyEvents(this);

}

void DynamicPolyline::disableEvents() {
    
    //ofUnregisterMouseEvents(this);
    //ofUnregisterKeyEvents(this);
}

void DynamicPolyline::setup() {
   
}

void DynamicPolyline::draw() {
    
    if(bIsSelected || !bEditable) {
        
        (bEditable) ? ofSetColor(255, 255, 255, 50) :  ofSetColor(inactiveColor);

        ofBeginShape();
        vector<ofPoint>& vertices = this->getVertices();
        for(int j = 0; j < vertices.size(); j++) {
            ofVertex(vertices[j]);
        }
        ofEndShape();
        
    } else {
        
        if(bLastSelected)
            ofSetColor(255, 0, 0, 255);
        else
            ofSetColor(255, 255,255,50);
        
        ofBeginShape();
        vector<ofPoint>& vertices = this->getVertices();
        for(int j = 0; j < vertices.size(); j++) {
            ofVertex(vertices[j]);
        }
        ofEndShape();
        ofPolyline::draw();

    }
    
    if(bEditable) {
        drawVerticesHandlers();
    }
    
    ofFill();

    
}

void DynamicPolyline::drawVerticesHandlers() {
    
    ofNoFill();

    vector<ofPoint> vertices = this->getVertices();
    
    for(int i=0; i<vertices.size(); i++) {
        
        ofPoint vertex = vertices[i];
        
        if(bIsInsideHandler && i == handlerSelected )
            ofFill();
        else
            ofNoFill();
        
        ofCircle(vertex.x, vertex.y, handlerRadius);
        
    }
    
}

void DynamicPolyline::mouseMoved(ofMouseEventArgs &a) {
    
}

void DynamicPolyline::mouseDragged(ofMouseEventArgs &a) {
    
    if(!bEditable) return;

    
    if(bIsInsideHandler) {
        
        
        vector<ofPoint> * vertices = &this->getVertices();
        vertices->at(handlerSelected).set(a.x, a.y);
        ofNotifyEvent(changedEvent, index, this);
    
    }
    
    if(bIsSelected) {
        
        float xdiff = a.x - lastClicked.x;
        float yDiff = a.y - lastClicked.y;
        
        vector<ofPoint> * vertices = &this->getVertices();
        for(int i=0; i<vertices->size(); i++) {
            
            ofPoint lastVertex = lastVertices[i];
            vertices->at(i).set(lastVertex.x + xdiff, lastVertex.y + yDiff);

        }
        
        ofNotifyEvent(changedEvent, index, this);

    }
    
}

void DynamicPolyline::mousePressed(ofMouseEventArgs &a) {
    
    if(!bEditable) return;
    
    vector<ofPoint> vertices = this->getVertices();
    
    if(bIsEditMode && bLastSelected) {
        
        unsigned int closestIndex;
        this->getClosestPoint(ofPoint(a.x, a.y), &closestIndex);
        this->insertVertex(ofPoint(a.x, a.y), closestIndex);
        
        ofNotifyEvent(changedEvent, index, this);

    }
    
    for(int i=0; i<vertices.size(); i++) {
        
        ofPoint vertex = vertices[i];
        float dist = sqrt(pow(vertex.x - a.x, 2) + pow(vertex.y - a.y, 2));
        
        if (dist <= handlerRadius) {
            
            handlerSelected     = i;
            bIsInsideHandler    = true;
            
        }
        
    }
    
    // check for global lick
    if(!bIsInsideHandler && this->inside(a.x, a.y)) {
        
        bIsSelected = true;
        lastClicked.set(a.x, a.y);
        ofNotifyEvent(selectedEvent, this->index, this);
        
    }
    
    lastVertices = this->getVertices();

    
}
void DynamicPolyline::mouseReleased(ofMouseEventArgs &a) {
    
    bIsInsideHandler    = false;
    bIsSelected         = false;

    
}

void DynamicPolyline::keyPressed(ofKeyEventArgs &a) {
    
    if(!bEditable) return;
    
    
    bIsEditMode =  (a.key == 'a'); // shift key sending two values ?
    
    if(bLastSelected && bIsInsideHandler && a.key == 'd') {
        this->removeVertex(handlerSelected);
        bIsInsideHandler    = false;
        ofNotifyEvent(changedEvent, index, this);

    }
    
    
    
    if(bLastSelected && bIsSelected && a.key == 'd') {
        this->clear();
        bIsSelected    = false;
        ofNotifyEvent(changedEvent, index, this);
    }
    
}

void DynamicPolyline::keyReleased(ofKeyEventArgs &a) {
    bIsEditMode = false;
}

void DynamicPolyline::removeVertex(int index) {
    
    vector<ofPoint> vertices = this->getVertices();
    this->clear();
    
    for(int i =0; i<vertices.size(); i++) {
        if(i!= index)
            this->addVertex(vertices[i]);
    }
    
    this->close();
        
}

void DynamicPolyline::setInactiveColor(float r, float g, float b, float a) {
    
    inactiveColor.set(r, g, b, a);
   
}




