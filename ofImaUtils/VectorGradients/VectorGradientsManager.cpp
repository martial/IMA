//
//  VectorGradientsManager.cpp
//  ParticlesApp
//
//  Created by Martial on 10/08/2015.
//
//

#include "VectorGradientsManager.h"


VectorGradientsManager::VectorGradientsManager() {
    
    bIsAdding = false;
    bEditMode = false;
    
}
void VectorGradientsManager::setup(){
    
    enableEvents();
    
}


void VectorGradientsManager::loadData() {
    
    xml.loadFile("gradients.xml");
    
    int numOfPolys = xml.getNumTags("poly");
        
    for(int i=0; i<numOfPolys; i++) {
        
        VectorGradient * gradient = new VectorGradient();
        ofAddListener(gradient->selectedEvent, this, &VectorGradientsManager::onSelectedEvent);
        ofAddListener(gradient->changedEvent, this, &VectorGradientsManager::onChangedEvent);
        ofAddListener(gradient->deletedEvent, this, &VectorGradientsManager::onDeletedEvent);
        gradient->index = i;
        
        xml.pushTag("poly", i);

        
        xml.pushTag("a", 0);
        gradient->a.set(ofPoint(xml.getValue("x", 0),xml.getValue("y", 0)));
        xml.popTag();
        
        xml.pushTag("b", 0);
        gradient->b.set(ofPoint(xml.getValue("x", 0),xml.getValue("y", 0)));
        xml.popTag();
        
        gradient->depth = xml.getValue("depth", 0);

        
        xml.popTag();
                
        
        vectors.push_back(gradient);
        
    }
    
    
    
}

void VectorGradientsManager::saveData() {
    
    xml.clear();
    // xml.addTag("root");
    //xml.pushTag("root");
    for (int i = 0; i<vectors.size(); i++) {
                
        xml.addTag("poly");
        xml.pushTag("poly", i);
        
        
        xml.addTag("a");
        xml.pushTag("a", 0);
        xml.addTag("x");
        xml.setValue("x", vectors[i]->a.x);
        xml.addTag("y");
        xml.setValue("y", vectors[i]->a.y);
        xml.popTag();
        
        xml.addTag("b");
        xml.pushTag("b", 0);
        xml.addTag("x");
        xml.setValue("x", vectors[i]->b.x);
        xml.addTag("y");
        xml.setValue("y", vectors[i]->b.y);
        xml.popTag();
        
        xml.addTag("depth");
        xml.setValue("depth", vectors[i]->depth);
        
        xml.popTag();
        
    }
    
    xml.saveFile();
    
}


void VectorGradientsManager::enableEvents() {
    //ofRegisterMouseEvents(this);
    ofRegisterKeyEvents(this);
    
    
    
}

void VectorGradientsManager::disableEvents() {
    
    ofUnregisterMouseEvents(this);
    ofUnregisterKeyEvents(this);
}

void VectorGradientsManager::update(){
    
    if(bIsAdding) {
        //selectedVector->b.set(ofGetMouseX(), ofGetMouseY());
    }
    
}

void VectorGradientsManager::draw(){
    
    
    ofEnableAlphaBlending();
    for(int i=0; i<vectors.size(); i++ ) {
        
        vectors[i]->draw();

        
        if(bEditMode) {
            vectors[i]->drawNormal();
            vectors[i]->drawVerticesHandlers();
            
        }
        
    }
    
    ofDisableAlphaBlending();
    
    
    
    
}


void VectorGradientsManager::toggleEditMode(){
    
    this->bEditMode = !this->bEditMode;
}

bool VectorGradientsManager::getEditMode() {
    return bEditMode;
}

void VectorGradientsManager::setEditMode(bool b) {
    
    this->bEditMode = b;

}


void VectorGradientsManager::addVector(float x, float y){
    
    selectedVector = new VectorGradient();
    selectedVector->a.set(x,y);
    selectedVector->b.set(x+40,y);
    selectedVector->index = vectors.size();

    vectors.push_back(selectedVector);

    ofAddListener(selectedVector->selectedEvent, this, &VectorGradientsManager::onSelectedEvent);
    ofAddListener(selectedVector->changedEvent, this, &VectorGradientsManager::onChangedEvent);
    ofAddListener(selectedVector->deletedEvent, this, &VectorGradientsManager::onDeletedEvent);

    
}

void VectorGradientsManager::endVector(){
    
    
}

void VectorGradientsManager::onSelectedEvent(int & vertex) {
    
    if(!bEditMode)
        return;
    
    for (int i=0; i<vectors.size(); i++) {
        vectors[i]->bIsSelected         = false;
        vectors[i]->bIsInsideHandler    = false;

    }
    
}

void VectorGradientsManager::onDeletedEvent(int & index) {
    
    vectors.erase (vectors.begin()+index);

    
    for(int i =0; i<vectors.size(); i++) {
        vectors[i]->index = i;
    }
    
    saveData();

    
}


void VectorGradientsManager::onChangedEvent(int & index) {
    
    /*
    if(dumm == -1) {
        
        for(int i =0; i<vectors.size(); i++) {
            if(i!= index)
                this->addVertex(vertices[i]);
        }
        
        this->close();
    }
     */
    
    saveData();
    ofNotifyEvent(changedEvent, index);
    
}



void VectorGradientsManager::mouseMoved(ofMouseEventArgs &a) {
    
    
}

void VectorGradientsManager::mouseDragged(ofMouseEventArgs &a) {
    if(!bEditMode)
        return;
    
    for (int i=0; i<vectors.size(); i++) {
        vectors[i]->mouseDragged(a);
    }
    
    
}

void VectorGradientsManager::mousePressed(ofMouseEventArgs &a) {
    
    if(!bEditMode)
        return;
    
    if(ofGetKeyPressed('g')) {
        bIsAdding = true;
        addVector(a.x, a.y);
    }
    
    
    for (int i=0; i<vectors.size(); i++) {
        vectors[i]->mousePressed(a);
    }
    
}

void VectorGradientsManager::mouseReleased(ofMouseEventArgs &a) {
    
    if(!bEditMode)
        return;
    
    for (int i=0; i<vectors.size(); i++) {
        vectors[i]->mouseReleased(a);
    }
    
    // clear actions
    if(bIsAdding) {
        endVector();
    }
    
    bIsAdding = false;
 
    
}

