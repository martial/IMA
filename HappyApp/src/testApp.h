#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "VideoManager.h"
#include "PolylineMaker.h"
#include "ofxSyphon.h"
#include "ofxSettings.h"

class testApp : public ofBaseApp{
	
public:
	
	void setup();
	void update();
	void draw();
	
    
    void mouseDragged(int x, int y, int button);

	void keyPressed  (int key);
	
    
    ofxSyphonServer syphonServer;
    PolylineMaker   polyLineManager;
    VideoManager    videoManager;
    ofxSettings     settings;
    
    bool            bDrawPlaceHolders;
    
};

#endif
