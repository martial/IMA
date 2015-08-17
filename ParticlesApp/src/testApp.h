#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "VideoManager.h"
#include "PolylineMaker.h"
#include "ofxSyphon.h"
#include "ofxSettings.h"
#include "ParticlesCL.h"
#include "VectorGradientsManager.h"

class testApp : public ofBaseApp{
	
public:
	
    testApp();
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);
    
    ofxSyphonServer         syphonServer;
    PolylineMaker           polyLineManager;
    VectorGradientsManager  vectorGradientManger;
    VideoManager            videoManager;
    ofxSettings             settings;
    ParticlesCL             particles;
    
    bool            bReady, bHasSetup;
    
    ofImage img;

    
};

#endif
