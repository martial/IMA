#include "testApp.h"
#include "ofxCocoa.h"
#include "AppDelegate.h"


void testApp::setup() {
	printf("Window dimensions: %i %i\n", ofGetWidth(), ofGetHeight());
	
	ofBackground(0, 0, 0);
    ofEnableSmoothing();
	

	ofSetFrameRate(31);			// run as fast as you can
	
    settings.load("settings.xml");
    
    videoManager.loadMovie("movies/MEE-Sol-sans-anamorphose-003_HAPNOQ.mov");
    videoManager.loadMovie("movies/MEE-projection-derriere-hapy-002_HAPNOQ.mov");
    videoManager.loadMovie("movies/Prologue-Mythe-119_HAPQ.mov");

    videoManager.playAll();
    
    polyLineManager.loadData();
    polyLineManager.setActive(false); // inactive 
    
    videoManager.setPolyLineMaker(&polyLineManager);
    
    syphonServer.setName("Osiris texture");
  
    bDrawPlaceHolders = false;
    
    
    //syphonServer.
    

}


void testApp::update(){
    
    videoManager.update();
    
    
    
    // update scale UI
    float scale = 200 - round((videoManager.getScale()) * 100);
    string scaleString = "Zoom :" + ofToString(scale) + " %";
    AppDelegate * d = (AppDelegate *)[[NSApplication sharedApplication] delegate] ;
    MyUIDelegate *ui = [d uiDelegate];
    [ui setZoom:scaleString];
    

    
}


void testApp::draw(){
    
    ofBackground(0, 0, 0);

    videoManager.prepass(bDrawPlaceHolders);
    videoManager.draw();
    
    syphonServer.publishTexture(&videoManager.getFbo()->getTextureReference());
    
}

void testApp::mouseDragged(int x, int y, int button) {
    
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