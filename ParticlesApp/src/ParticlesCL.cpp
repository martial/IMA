//
//  ParticlesCL.cpp
//  ParticlesApp
//
//  Created by Martial on 23/07/2015.
//
//

#include "ParticlesCL.h"
#include "MSAOpenCL.h"

typedef struct{
    float4 target;
    float x;
    float y;
    float2 frc;
    float4 dummy;
    float life = 0;
    float death;
    float2 vel;
    
} Particle;

msa::OpenCL			opencl;
msa::OpenCLBufferManagedT<Particle>	particles;
msa::OpenCLBufferManagedT<float4> particlePos;
msa::OpenCLBufferManagedT<float4> particleCol;
msa::OpenCLBufferManagedT<float2> obstacles;

GLuint				vbo[2];


ParticlesCL::ParticlesCL() {
    
    nParticles              = 100000;
    textureWidth            = 1900 * 3;
    textureHeight           = 1200 * 2;
    vfWidth                 = 1900;
    vfHeight                = 1200;
    vfScale                 = 1.0f;
    vfResolution            = 8;
    damp                    = 0.99f;
    bNeedReset              = false;
    bNeedVBOReset           = false;
    bDebugRepulsionForces   = false;
    repRadius               = 16.0;
    repDist                 = 14;
    minLife                 = 1000;
    maxLife                 = 2000;
    bBlurVectorField        = true;
    bForceRandom            = true;
    bAnimate                = true;
    numOfVFs                = 3;
    bDrawBounds             = true;
    
}

void ParticlesCL::setPolyLine(PolylineMaker  * p) {
    
    this->polylineManager = p;
    ofAddListener(polylineManager->changedEvent, this, &ParticlesCL::onPolyChangedHandler);
    
}

void ParticlesCL::setVectorGradient(VectorGradientsManager * p) {
    
    this->vectorGradManager = p;
    
}

void ParticlesCL::setup(int gpuDeviceID ) {
    
    
    ofAddListener(ofEvents().mouseReleased, this, &ParticlesCL::onMouseReleavedEvent);
    ofAddListener(ofEvents().mousePressed, this, &ParticlesCL::onMousePressedEvent);
    ofAddListener(ofEvents().mouseDragged, this, &ParticlesCL::onMouseDragEvent);
    ofAddListener(ofEvents().keyPressed, this, &ParticlesCL::onKeyPressedEvent);
    ofAddListener(ofEvents().wheelEvent, this, &ParticlesCL::onWheelEvent);
    
    //OpenCL
    opencl.setupFromOpenGL(gpuDeviceID);
    opencl.loadProgramFromFile("Particle.cl");
    opencl.loadKernel("update");
    
    vectorFieldsRect.width      = vfWidth;
    vectorFieldsRect.height     = vfHeight;
    
    setFBO();
    setVectorFields();
    setVBO();
    setParticles();
        
    int e;
    onPolyChangedHandler(e);
    
    fitToScreen();
    
}

void ParticlesCL::setFBO() {
    
    this->width                     = textureWidth;
    this->height                    = textureHeight;
    
    origRect.width                  = width;
    origRect.height                 = height;
    
    fboSettings.width               = width;
    fboSettings.height              = height;
    fboSettings.internalformat      = GL_RGB;
    fboSettings.useDepth			= false;
    fboSettings.numSamples          = 4;
    fbo.allocate(fboSettings);
}

void ParticlesCL::setVBO () {
    
    glGenBuffersARB(2, vbo);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo[0]);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float4) * nParticles, particlePos, GL_DYNAMIC_COPY_ARB);
    glVertexPointer(2, GL_FLOAT, 0, 0);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo[1]);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float4) * nParticles, particleCol, GL_DYNAMIC_COPY_ARB);
    glColorPointer(4, GL_FLOAT, 0, 0);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    
}

void ParticlesCL::setParticles () {
    
    particles.initBuffer( nParticles );
    particlePos.initFromGLObject( vbo[0], nParticles );
    particleCol.initFromGLObject( vbo[1], nParticles );
    obstacles.initBuffer(8192);
    
    for(int i=0; i<nParticles; i++) {
        Particle &p = particles[i];
        
        ofVec2f pos = this->getRandomPos();
        p.target.set( 0.0 , 0.0, 0, 0 );
        p.death =  minLife + ofRandom(maxLife);
        p.life =  2000+ ofRandom(2000);
        
        particlePos[i].x = 0.0f;
        particlePos[i].y = 0.0f;
        
        particleCol[i].x = 1.0f;
        particleCol[i].y = 1.0f;
        particleCol[i].z = 1.0f;
        
    }
    
    setParticleVFIndex();
    
    opencl.kernel("update")->setArg(0, particles.getCLMem());
    opencl.kernel("update")->setArg(4, particleCol.getCLMem());
    opencl.kernel("update")->setArg(3, particlePos.getCLMem());

    particles.writeToDevice();
    particlePos.writeToDevice();
    particleCol.writeToDevice();
    
}

void ParticlesCL::setParticleVFIndex() {
    
    int step        = floor((float)nParticles / (float)numOfVFs );
    int stepCount   = 0;
    int vfIndex     = 0;
    float color     = 1.0;
    
    for(int i=0; i<nParticles; i++) {
        Particle &p = particles[i];
        if(stepCount > step ) {
            stepCount = 0;
            vfIndex ++;
            
            if(vfIndex > 1) {
                color = ofRandom(.2, 1.0);
            }
            
        }
        stepCount ++;
        
        p.dummy.x = color;
        p.dummy.w = vfIndex;
        
    }
    
    particles.writeToDevice();
    
}

void ParticlesCL::setNumOfVFs(int nVFs) {
    
    this->numOfVFs = nVFs;
    setVectorFields();
    setParticleVFIndex();
    
}

void ParticlesCL::setVectorFields() {
    
    for(int i=0; i<vectorFields.size(); i++) {
        
        delete vectorFields[i];
        vectorFields[i] = NULL;
        
    }
    
    vectorFields.clear();
    
    for(int i=0; i<numOfVFs; i++) {
        
        ofxVectorField * vf = new ofxVectorField();
        vf->setup(vectorFieldsRect.width, vectorFieldsRect.height, this->vfResolution);
        vf->randomize();
        vf->scale(vfScale);
        if(bBlurVectorField)
            vf->blur();
        
        vf->index = i;
        bNeedReset = false;
        
        vectorFields.push_back(vf);
        
    }
    
}


void ParticlesCL::update() {
    
    if(bNeedReset ) {
        
        setFBO();
        setVectorFields();
        bNeedReset = false;
    }
    
    
    if(bNeedVBOReset) {
        
        setVBO();
        setParticles();
        bNeedVBOReset = false;
        
    }

    ofxDragAndZoomable::update();
    
    particlePos.readFromDevice();
    particles.readFromDevice();
    
    ofVec2f direction;
    for(int i=0; i<nParticles; i++) {
        
        Particle &p = particles[i];
        
        if(p.life >= p.death || !vectorFieldsRect.inside(p.x, p.y)) {
            
            ofPoint rdmPos = this->getRandomPos();
            particlePos[i].y = rdmPos.x;
            particlePos[i].x = rdmPos.y;
            
            p.life = 0;
            p.death =  minLife + ofRandom(maxLife);
            
        } else {
            
            int vfIndex =  (int)p.dummy.w;
            
            if(vectorFields[vfIndex]->bIsAllocated ) {
                direction = vectorFields[vfIndex]->getVectorInterpolated(p.x, p.y, origRect.width, origRect.height);
                p.target.set( direction.x, direction.y, 0, 0 );
                
            }
        }
        
    }
    
    //upload to GPU
    particles.writeToDevice();
    particlePos.writeToDevice();

    opencl.kernel("update")->run1D( nParticles );
    
    vectorFieldsRect.x = origRect.width * .5 - vectorFieldsRect.width * .5;
    vectorFieldsRect.y = origRect.height * .5 - vectorFieldsRect.height +  vectorFieldsRect.height * .5;
    
    if(ofGetFrameNum() % 400 == 0 && ofGetFrameNum() > 0  )
        randomize();


}

void ParticlesCL::randomize() {
    
    for(int i=0; i<numOfVFs; i++) {
        
        ofxVectorField * vf = vectorFields[i];
        vf->randomize();
        vf->scale(this->vfScale);
        
    }
    
}


ofVec2f ParticlesCL::getRandomPos() {
    
    float px, py;
    px = ofRandom(vectorFieldsRect.x, vectorFieldsRect.x + vectorFieldsRect.width);
    py = ofRandom(vectorFieldsRect.y, vectorFieldsRect.y + vectorFieldsRect.height);
    
    if(bForceRandom) {
        
        bool bInside = true;
        
        while (bInside) {
            
            px = ofRandom(vectorFieldsRect.x, vectorFieldsRect.x + vectorFieldsRect.width);
            py = ofRandom(vectorFieldsRect.y, vectorFieldsRect.y + vectorFieldsRect.height);

            bInside = false;
            
            for(int i=0; i<this->polylineManager->polylines.size(); i++) {
                
                DynamicPolyline * p = this->polylineManager->polylines[i];
                if (p->getBoundingBox().inside(px, py)) {
                    bInside =  p->inside(px, py);
                }
                
            }
            
        }
        
    }

   return ofPoint(py, px);
    
}



//--------------------------------------------------------------
void ParticlesCL::prepass(){
    
    //opencl.finish();
    //opencl.flush();
    
    fbo.begin();
    ofBackground(0,0,0);
    
    ofPushMatrix();
    
    ofSetColor( 255,255,255, 255 );
    glPointSize( 1 );
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo[0]);
    glVertexPointer(2, GL_FLOAT, 0, 0);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo[1]);
    glColorPointer(4, GL_FLOAT, 0, 0);
    glDrawArrays(GL_POINTS, 0, nParticles);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    ofSetColor(255, 255, 255);
    polylineManager->draw();
    vectorGradManager->draw();
    
    ofPopMatrix();
   
    if(bDrawBounds) {
        
        ofNoFill();
        ofSetColor(255, 0, 0);
        ofRect(vectorFieldsRect);
        ofFill();
        
    }

    if(bDebugRepulsionForces) {
        ofSetColor(255,255,255);
        for (int i=0; i<numOfVertices; i++) {
            
            float2 vert = obstacles[i];
            ofCircle(vert.x, vert.y, repRadius*2);
            
        }
    }
    
    
    ofSetColor(255,255,255);

    fbo.end();

        
}

void ParticlesCL::draw(){
    
    ofEnableAlphaBlending();
    ofSetColor(255,255,255, 255);
    fbo.draw(x, y, width, height);
    ofDisableAlphaBlending();
    
    if(bDrawBounds) {
        ofNoFill();
        ofRect(this->x, this->y, this->width, this->height);
        ofFill();
    }
    
    
}

void ParticlesCL::drawInnerSmoothedRect(float depth) {
    
    ofEnableAlphaBlending();
    glBegin(GL_QUAD_STRIP);
    glColor4f(0,0,0, 1);
    glVertex3f(origRect.x, origRect.y,0);
    glVertex3f( origRect.x + origRect.width,origRect.y,0);

    glColor4f(0,0,0, 0);
    glVertex3f(origRect.x, origRect.y + depth,0);
    glVertex3f( origRect.x + origRect.width,origRect.y + depth,0);
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor4f(0,0,0, 1);
    glVertex3f(origRect.x, origRect.y,0);
    glVertex3f( origRect.x,origRect.y + origRect.height,0);
    
    glColor4f(0,0,0, 0);
    glVertex3f(origRect.x + depth, origRect.y,0);
    glVertex3f( origRect.x + depth,origRect.y + origRect.height,0);
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor4f(0,0,0, 1);
    glVertex3f(origRect.x + origRect.width, origRect.y,0);
    glVertex3f( origRect.x + origRect.width, origRect.y + origRect.height,0);
    
    
    glColor4f(0,0,0, 0);
    glVertex3f(origRect.x  + origRect.width - depth, origRect.y,0);
    glVertex3f(origRect.x + origRect.width - depth,origRect.y + origRect.height,0);
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor4f(0,0,0, 1);
    glVertex3f(origRect.x, origRect.y  + origRect.height ,0);
    glVertex3f( origRect.x + origRect.width,origRect.y  + origRect.height,0);
    
    
    glColor4f(0,0,0, 0);
    glVertex3f(origRect.x, origRect.y  + origRect.height - depth,0);
    glVertex3f( origRect.x + origRect.width,origRect.y   + origRect.height - depth,0);
    glEnd();
    
    ofDisableAlphaBlending();
    
}

void ParticlesCL::onWheelEvent(float & aperture) {
    
    ofxDragAndZoomable::onWheelEvent(aperture);
}

ofFbo* ParticlesCL::getFbo() {
    
    return &fbo;
    
}


void ParticlesCL::setNumOfParticles(int num) {
    
    nParticles = num;
    bNeedVBOReset = true;

}

void ParticlesCL::setMinLife(int num) {
    
    this->minLife = num;
    
}

void ParticlesCL::setMaxLife(int num) {
    
    this->maxLife = num;
    
}

void ParticlesCL::setRepulsionRadius(float radius) {
    this->repRadius = radius;
    
    if (!opencl.isSetup) {
        return;
    }
    opencl.kernel("update")->setArg(5, repRadius);
    float repScale = repRadius * 2.0;
    opencl.kernel("update")->setArg(6, vfScale+1);

}

void ParticlesCL::setRepulsionDistance(float dist) {
    
    this->repDist = dist;
    
    int e;
    onPolyChangedHandler(e);
    
}

void ParticlesCL::setVFResolution(int res) {
    
    this->vfResolution = res;
    bNeedReset = true;
    
}

void ParticlesCL::setVFBlur(bool blur) {
    
    this->bBlurVectorField = blur;
    bNeedReset = true;
    
}

void ParticlesCL::setDamp(float damp) {
    
}
void ParticlesCL::setVFScale(float scale) {
    
    this->vfScale = scale * 0.2;
    bNeedReset = true;

}

void ParticlesCL::toggleBoundsVisibility() {
    
    this->bDrawBounds = !this->bDrawBounds;
    
}

void ParticlesCL::onMousePressedEvent(ofMouseEventArgs & e) {
    
    if(bIsShiftPressed) {
        lastClick.set(e.x - x, e.y - y);
    }
    
    ofVec2f pnt =   ofVec2f(ofGetMouseX(), ofGetMouseY());
    ofVec2f coords =  getPointAtCoordinate(pnt);
    
    polylineManager->mousePressed(coords.x, coords.y);
    vectorGradManager->mousePressed(coords.x, coords.y);

}

void ParticlesCL::onMouseDragEvent(ofMouseEventArgs & e) {
    
    if(bIsShiftPressed) {
        drag(e.x, e.y);
    }
    
    ofVec2f pnt =   ofVec2f(ofGetMouseX(), ofGetMouseY());
    ofVec2f coords =  getPointAtCoordinate(pnt);

    polylineManager->mouseDragged(coords.x, coords.y);
    vectorGradManager->mouseDragged(coords.x, coords.y);
    
}

void ParticlesCL::onMouseReleavedEvent(ofMouseEventArgs & e) {
    
    ofVec2f pnt =   ofVec2f(ofGetMouseX(), ofGetMouseY());
    ofVec2f coords =  getPointAtCoordinate(pnt);
    
    polylineManager->mouseReleased(coords.x, coords.y);
    vectorGradManager->mouseReleased(coords.x, coords.y);
    
}

void ParticlesCL::onKeyPressedEvent(ofKeyEventArgs & e) {
    
    switch (e.key) {
            
        default:
        break;
    }
    
}

void ParticlesCL::onPolyChangedHandler(int & e) {
    
    if(!opencl.isSetup)
        return;
    
    numOfVertices = 0;
    
    int verticeIndex = 0;
    for (int i=0; i<polylineManager->polylines.size(); i++) {
        
        vector<ofPoint> vertices = polylineManager->polylines[i]->getVertices();
        
        for(int j=0; j<vertices.size(); j++) {
            
            ofVec2f pntA, pntB;
            if(j<vertices.size() -1) {
                
                pntA.set(vertices[j]);
                pntB.set(vertices[j+1]);
                
            } else {
                pntA.set(vertices[j]);
                pntB.set(vertices[0]);
            }
            
            float dist = pntA.distance(pntB);
            float res = repDist;
            int steps = floor(dist/ res);
            
            for (int z=0; z<steps; z++) {
                ofVec2f pnt = pntA.getInterpolated(pntB,  (float)z / (float)steps);
                
                float2 f;
                f.x =pnt.x ;
                f.y =pnt.y ;
                obstacles[numOfVertices] = f;
                numOfVertices++;
                
            }
            
        }
        
        opencl.kernel("update")->setArg(1, numOfVertices);
        opencl.kernel("update")->setArg(2, obstacles);
        
        obstacles.writeToDevice();
        
    }
    
}

void ParticlesCL::setVFWidth(float width) {
    this->vfWidth = width;
    vectorFieldsRect.width = width;
    bNeedReset = true;
    
}

void ParticlesCL::setVFHeight(float height) {
    this->vfHeight = height;
    vectorFieldsRect.height = height;

    bNeedReset = true;
}

void ParticlesCL::setTextureWidth(float width) {
    this->textureWidth = width;
    bNeedReset = true;
}
void ParticlesCL::setTextureHeight(float height) {
    this->textureHeight = height;
    bNeedReset = true;
}

