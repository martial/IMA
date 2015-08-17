//
//  VectorGradient.cpp
//  ParticlesApp
//
//  Created by Martial on 10/08/2015.
//
//

#include "VectorGradient.h"

VectorGradient::VectorGradient() {
    
    handlerRadius           = 20.0f;
    bIsSelected             = false;
    bIsInsideHandler        = false;
    bIsInsideDepthHandler   = false;
    bEditable               = true;
    selectedVertex          = NULL;
    bNeedImgUpdate          = true;
    depth                   = 100.0f;
    
    vertices.push_back(&a);
    vertices.push_back(&b);
    vertices.push_back(&c);

}

void VectorGradient::draw() {
    
    drawCanvas();
    
}

void VectorGradient::drawVerticesHandlers() {
    
    (handlerSelected == 0 ) ? ofFill() : ofNoFill();
    ofCircle(a.x, a.y, handlerRadius);
    
    (handlerSelected == 1 ) ? ofFill() : ofNoFill();
    ofCircle(b.x, b.y, handlerRadius);
    
    (handlerSelected == 2 ) ? ofFill() : ofNoFill();
    ofCircle(c.x, c.y, handlerRadius);

    ofFill();

}

void VectorGradient::drawNormal() {
    
    ofSetColor(255, 255, 255, 255);
    ofLine(a.x, a.y, b.x, b.y);
    
    
    ofVec2f mid = a.getMiddle(b);
    ofVec2f perpendicular = ofVec2f( (b - a) ).getPerpendicular() * depth;
    ofVec2f midPerpendicular = mid+ perpendicular;
    c.set(midPerpendicular);
    
    ofLine(mid, c);
 
}

void VectorGradient::drawCanvas() {
    
    canvas.set(0,0, a.distance(b), depth);
    
    float angle = (float)ofRadToDeg(atan2(b.y - a.y, b.x - a.x));
    
    if(angle < 0){
        angle += 360;
    }
    
    if(bNeedImgUpdate) {
        
        
        int w = canvas.getWidth();
        int h = canvas.getHeight();
        img.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
        //img.setColor(ofColor::white);
        
        
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                
                ofColor color= ofColor(0,0,0,0);
                
                float rdmStep = j / (float)h;
                
                float rdm = ofRandom(1.0);
                if (rdm < rdmStep) {
                    color.set(0,0,0, 255);
                }
                
                img.setColor(i , h-j-1 , color);
            }
        }
        
        
        img.update();
        bNeedImgUpdate = false;
        
    }
    
    ofNoFill();

    ofSetColor(255, 255,255,255);

    ofPushMatrix();
    ofTranslate(a.x, a.y);
    ofRotate( angle);
    //ofRect(canvas);
    img.draw(0.0, 0.0);
    ofPopMatrix();
    
}


void VectorGradient::mouseMoved(ofMouseEventArgs &a) {
    
}

void VectorGradient::mouseDragged(ofMouseEventArgs &a) {
    
    
    if(!bEditable) return;
    
    int dumm = 0;

    if(bIsInsideHandler) {
        selectedVertex->set(a.x, a.y);
        bNeedImgUpdate = true;
        ofNotifyEvent(changedEvent, dumm);

    }
    
    
    if(bIsInsideDepthHandler) {
        
        // go fun !
        
        ofVec2f mid = this->a.getMiddle(this->b);
        ofVec2f target(a.x, a.y);
        
        // reverse
        float l = target.distance(mid);
        if(this->a.x < this->b.x && target.y < mid.y )
            l *= -1;
        else if(this->a.x > this->b.x && target.y > mid.y )
            l *= -1;
        
        // add
        depth  = ofClamp(savedLength + l, -2000, 2000 );
        
        bNeedImgUpdate = true;
        
        ofNotifyEvent(changedEvent, dumm);

        
    }
    
}

void VectorGradient::mousePressed(ofMouseEventArgs &a) {
    
    if(!bEditable) return;
    
    if(ofGetKeyPressed('d')) {
        ofNotifyEvent(deletedEvent, index);
    }
    
   
    
    for(int i=0; i<this->vertices.size(); i++) {
        
        ofVec2f  * vertex = this->vertices[i];
        float dist = sqrt(pow(vertex->x - a.x, 2) + pow(vertex->y - a.y, 2));
        
        if (dist <= handlerRadius ) {
            
            if(i< 2) {
            
                ofNotifyEvent(selectedEvent, i);
                bIsInsideHandler    = true;
                
                
            } else {
                
                bIsInsideDepthHandler = true;
            }
            
            selectedVertex      = vertex;
            handlerSelected     = i;
            
            
            
            
        }
        
    }
    
    lastClick.set(a.x, a.x);
    
    
    
}
void VectorGradient::mouseReleased(ofMouseEventArgs &a) {
    
    bIsInsideHandler        = false;
    bIsSelected             = false;
    bIsInsideDepthHandler   = false;
    
}
