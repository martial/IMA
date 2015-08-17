//
//  ParticlesCL.h
//  ParticlesApp
//
//  Created by Martial on 23/07/2015.
//
//

#ifndef __ParticlesApp__ParticlesCL__
#define __ParticlesApp__ParticlesCL__

#include "ofMain.h"
#include "ofxDragAndZoomable.h"
#include "ofxVectorField.h"
#include "PolyLineMaker.h"
#include "VectorGradientsManager.h"

class ParticlesCL : public ofxDragAndZoomable {
    
public:
    
    ParticlesCL();
    void setPolyLine(PolylineMaker  * p);
    void setVectorGradient(VectorGradientsManager  * p);

    void setup(int gpuDeviceID = 1);
    void setFBO();
    void setVBO();
    void setParticles();
    void update();
    void prepass();
    void draw();
    
    void setTextureWidth(float width);
    void setTextureHeight(float height);
    
    void setVectorFields();
    
    void onWheelEvent(float & aperture);
    
    void setVFWidth (float width);
    void setVFHeight(float height);
    
    void setNumOfVFs(int nVfs);
    void setVFResolution(int res);
    void setDamp(float damp);
    void setVFScale(float scale);
    void setVFBlur(bool blur);

    void setNumOfParticles(int num);
    void setMinLife(int num);
    void setMaxLife(int num);
    void setRepulsionRadius(float radius);
    void setRepulsionDistance(float dist);
    
    void toggleBoundsVisibility();
    
    void setParticleVFIndex();
    
    ofFbo*  getFbo();
    
    void onPolyChangedHandler(int & e);
    
    void onMousePressedEvent(ofMouseEventArgs & e);
    void onMouseDragEvent(ofMouseEventArgs & e);
    void onMouseReleavedEvent(ofMouseEventArgs & e);
    void onKeyPressedEvent(ofKeyEventArgs & e);

    void randomize();
    
    void drawInnerSmoothedRect(float depth);

    void setInnerSmoothedRect(bool smoothed);
    void setInnerNoisedRect(bool noised);
    
    bool bDebugRepulsionForces;
    bool bBlurVectorField;
    bool bForceRandom;
    bool bAnimate;
    bool bDrawBounds;

    
    ofRectangle vectorFieldsRect;
    
private:
    
    int     nParticles;

    
    ofFbo   fbo;
    ofFbo::Settings fboSettings;

    ofVec2f getRandomPos();
    
    float textureWidth, textureHeight;
    
    
    int     numOfVFs;
    float   vfWidth, vfHeight;
    vector<ofxVectorField*> vectorFields;
    
    
    ofPolyline poly;
    
    float   vfScale, damp;
    int     vfResolution;
    
    bool bNeedReset, bNeedVBOReset;
    
    PolylineMaker * polylineManager;
    
    int numOfVertices;
    
    float repRadius, repDist;
    int minLife, maxLife;
    
    vector<ofImage*> noiseImages;
    
    VectorGradientsManager * vectorGradManager;
    
    
};

#endif /* defined(__ParticlesApp__ParticlesCL__) */
