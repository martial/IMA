#include "testApp.h"
#include "ofxCocoa.h"
#include "AppDelegate.h"

testApp::testApp () {
    
    bHasSetup = false;
}

void testApp::setup() {
	
    ofSetLogLevel(OF_LOG_NOTICE);
    
    ofEnableSmoothing();
	
    ofSetVerticalSync(true);
	//ofSetFrameRate(41);			// run as fast as you can
	
    settings.load("settings.xml");
    
    vectorGradientManger.setup();
    vectorGradientManger.loadData();
    
    polyLineManager.loadData();
    polyLineManager.setActive(false); // inactive

    videoManager.setPolyLineMaker(&polyLineManager);

    particles.setPolyLine(&polyLineManager);
    particles.setVectorGradient(&vectorGradientManger);
    particles.setup(settings.getInt("gpuDeviceID"));
    particles.setNumOfVFs(settings.getInt("numOfVfs"));
    particles.setNumOfParticles(settings.getInt("nParticles", 80000));
    particles.setRepulsionDistance(settings.getFloat("repDist", 16));
    particles.setRepulsionRadius(settings.getFloat("repRadius", 18));
    particles.setVFScale(settings.getFloat("vfScale", 1.0f));
    particles.setVFResolution(settings.getInt("vfRes", 4));
    particles.setMaxLife(settings.getInt("maxLife", 1000));
    particles.setMinLife(settings.getInt("minLife", 1000));
    particles.setTextureWidth(settings.getInt("texWidth", 1000));
    particles.setTextureHeight(settings.getInt("texHeight", 1000));
    particles.setVFWidth(settings.getInt("vfWidth", 1000));
    particles.setVFHeight(settings.getInt("vfHeight", 1000));

    syphonServer.setName("[IMA] Particles texture");
  
    
    bReady      = false;
    bHasSetup   = true;
    
    ofSetWindowTitle("IMA App");
    
    
    /*
    int w = 200;
    int h = 100;
    img.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
    img.setColor(ofColor::white);
    
    
    for (int i = 0; i < w; i++) {
        
        
        ofLog(OF_LOG_NOTICE, "-----");

        for (int j = 0; j < h; j++) {
            
            ofColor color= ofColor(255,0,0);
            
            
            float rdmStep = j / (float)h;
            
            float rdm = ofRandom(1.0);
            if (rdm < rdmStep) {
                color.set(0,0,0);
            }
            
            ofLog(OF_LOG_NOTICE, "rdm %f", rdmStep);

            
            
            img.setColor(i , j , color);
        }
    }
    
    
    img.update();
     
     */

}


void testApp::update(){
    
    vectorGradientManger.update();
    
    particles.update();
    particles.prepass();
    syphonServer.publishTexture(&particles.getFbo()->getTextureReference());

    ofSetWindowTitle("IMA App [" + ofToString(ceil(ofGetFrameRate())) + "] FPS");
    
    float scale = 200 - round((particles.getScale()) * 100);
    string scaleString = "Zoom :" + ofToString(scale) + " %";
    AppDelegate * d = (AppDelegate *)[[NSApplication sharedApplication] delegate] ;
    MyUIDelegate *ui = [d uiDelegate];
    [ui setZoom:scaleString];

    
    
}


void testApp::draw(){
    
    ofBackground(0, 0, 0);
    ofSetColor(255,255,255, 255);
    particles.draw();
    
    //vectorGradientManger.draw();
    
    // test with noise gradient

    
    //img.draw(0,0);
}

void testApp::keyPressed(int key){
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
            
        case ' ':
            polyLineManager.toggleEditMode();
            break;
					
			
	}
    
}