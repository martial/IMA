//
//  PolylineMaker.cpp
//  PolyMakerApp
//
//  Created by Martial on 16/07/2015.
//
//

#include "PolylineMaker.h"

PolylineMaker::PolylineMaker() {
    
    bEditMode       = false;
    lastSelected    = 0;
    
    ///inactiveMaskColor.set(0,0,0);
    
}



void  PolylineMaker::draw() {
    
    ofEnableAlphaBlending();
    ofFill();


    for (int i=0; i<polylines.size(); i++) {
        polylines[i]->draw();
    }
    ofDisableAlphaBlending();
}

void  PolylineMaker::loadData() {
    
    xml.loadFile("polylines.xml");
    
    int numOfPolys = xml.getNumTags("poly");
    
    for(int i=0; i<numOfPolys; i++) {
        
        DynamicPolyline * poly = new DynamicPolyline();
        ofAddListener(poly->changedEvent, this, &PolylineMaker::onPolyChangedHandler);
        ofAddListener(poly->selectedEvent, this, &PolylineMaker::onPolySelectedHandler);
        
        poly->setInactiveColor(inactiveMaskColor.r, inactiveMaskColor.g, inactiveMaskColor.b, inactiveMaskColor.a);

        poly->bEditable = bEditMode;
        poly->index = i;
        
        xml.pushTag("poly", i);
        int numOfVertices =xml.getNumTags("vertex");
        
        for(int j=0; j<numOfVertices; j++) {
            
            xml.pushTag("vertex", j);
            poly->addVertex(ofPoint(xml.getValue("x", 0),xml.getValue("y", 0)));
            xml.popTag();

        }
        
        poly->close();
        
        xml.popTag();
        polylines.push_back(poly);
        
    }
    
    
}

void  PolylineMaker::saveData() {
    
    xml.clear();
   // xml.addTag("root");
    //xml.pushTag("root");
    for (int i = 0; i<polylines.size(); i++) {
        
        xml.addTag("poly");
        xml.pushTag("poly", i);
        
        vector<ofPoint> vertices = polylines[i]->getVertices();
        for(int j=0; j<vertices.size(); j++) {
            
            xml.addTag("vertex");
            xml.pushTag("vertex", j);
            
            xml.addTag("x");
            xml.setValue("x", vertices[j].x);
            
            xml.addTag("y");
            xml.setValue("y", vertices[j].y);
            
            xml.popTag();

        }
        
        xml.popTag();
                
    }
    
    xml.saveFile();
    
}

void PolylineMaker::toggleEditMode() {
    
    bEditMode = !bEditMode;
    
    for (int i=0; i<polylines.size(); i++) {
        
        polylines[i]->bEditable = bEditMode;
    }
    
}

bool PolylineMaker::getEditMode() {
    return bEditMode;
}

void PolylineMaker::setEditMode(bool b) {
    
    this->bEditMode = b;
    
    for (int i=0; i<polylines.size(); i++) {
        
        polylines[i]->bEditable = bEditMode;
    }

    
}


void PolylineMaker::setActive(bool b) {
    
    for (int i=0; i<polylines.size(); i++) {
        
        if(!b)
            polylines[i]->disableEvents();
        else
            polylines[i]->enableEvents();
    }

    
}

void PolylineMaker::addQuad() {
    
    DynamicPolyline * poly = new DynamicPolyline();
    ofAddListener(poly->changedEvent, this, &PolylineMaker::onPolyChangedHandler);
    ofAddListener(poly->selectedEvent, this, &PolylineMaker::onPolySelectedHandler);

    poly->bEditable = bEditMode;

    
    poly->addVertex(ofPoint(0.0, 0.0));
    poly->addVertex(ofPoint(100.0, 0.0));
    poly->addVertex(ofPoint(100.0, 100.0));
    poly->addVertex(ofPoint(0.0, 100.0));
    poly->close();
    
    poly->index = polylines.size();
    
    poly->disableEvents();

    poly->setInactiveColor(inactiveMaskColor.r, inactiveMaskColor.g, inactiveMaskColor.b, inactiveMaskColor.a);

    polylines.push_back(poly);
    
    
}

void PolylineMaker::onPolySelectedHandler(int & index){
    
    this->lastSelected = index;
    for (int i=0; i<polylines.size(); i++) {
            this->polylines[i]->bLastSelected = (i == lastSelected);
    }
    
    
}

void PolylineMaker::onPolyChangedHandler(int & index) {
    
    //  if polyline empty, delete it
    
    if(this->polylines[index]->getVertices().size() == 0 ) {
        
        if (index < polylines.size())
        {
            
            delete polylines[index];
            polylines.erase(polylines.begin()+index);
            
            // reset indexes
            for (int i=0; i<polylines.size(); i++)
                polylines[i]->index = i;
        }
        
    }
    
    
    saveData();
    
    ofNotifyEvent(changedEvent, index);
}

void PolylineMaker::PolylineMaker::onMouseMoved(float x, float y) {
    
    
    ofMouseEventArgs e;
    e.x = x;
    e.y = y;
    
    for (int i=0; i<polylines.size(); i++) {
        polylines[i]->mouseMoved(e);
    }

    
}

void PolylineMaker::mouseDragged(float x, float y) {
    
    ofMouseEventArgs e;
    e.x = x;
    e.y = y;
    

    
    for (int i=0; i<polylines.size(); i++) {
        polylines[i]->mouseDragged(e);

    }

    
}

void PolylineMaker::mousePressed(float x, float y) {
    
    ofMouseEventArgs e;
    e.x = x;
    e.y = y;
    
    if(isnan(e.x) || isnan(e.y))
        return;
    ofLog(OF_LOG_NOTICE, "pnts at coords from poly %f %f", e.x, e.y);

    
    for (int i=0; i<polylines.size(); i++) {
        polylines[i]->mousePressed(e);
    }
    
}

void PolylineMaker::mouseReleased(float x, float y) {
    
    ofMouseEventArgs e;
    e.x = x;
    e.y = y;
    
    for (int i=0; i<polylines.size(); i++) {
        polylines[i]->mouseReleased(e);
    }
    
}

void PolylineMaker::setInactiveMaskColor(float r, float g, float b, float a) {
    
    inactiveMaskColor.set(r,g,b,a);
    for (int i=0; i<polylines.size(); i++) {
        polylines[i]->setInactiveColor(r, g, b, a);
    }
    
}

void PolylineMaker::keyPressed(int key) {
    
}

void PolylineMaker::keyReleased() {
    
}


void  PolylineMaker::begin() {
    
}

void  PolylineMaker::end() {
    
}