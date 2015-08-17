//
//  VideoManager.h
//  example_window
//
//  Created by Martial on 17/07/2015.
//
//

#ifndef __example_window__VideoManager__
#define __example_window__VideoManager__

#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "PolyLineMaker.h"
#include "ofxDragAndZoomable.h"


class VideoManager : public ofxDragAndZoomable {
    
public:
    
    VideoManager();
    
    void    setPolyLineMaker(PolylineMaker * p);
    
    void    update();
    void    prepass();
    void    draw();
    
    
    void    loadMovie(string path);
    
    void    playAll();
    void    pauseAll();
    void    stopAll();
    
    void    setVertical(bool b);

    void    allocateFbo();
    ofFbo*  getFbo();
    
    
    bool    areAllVideosLoaded();
    
    void    toggleVideoVisible();
    
    
    void onWheelEvent(float & aperture);

private:
    
    PolylineMaker *         polyLineManager;
    
    bool                    bIsVertical;
    bool                    bHasChanged;
    bool                    bFitToScreen;
    bool                    bIsScaling;
    
    bool                    bIsVideoVisible;
    
    ofFbo                   fbo;
    vector<ofxHapPlayer*>   players;
    
    
    void onMousePressedEvent(ofMouseEventArgs & e);
    void onMouseDragEvent(ofMouseEventArgs & e);
    void onMouseReleavedEvent(ofMouseEventArgs & e);
    void onKeyPressedEvent(ofKeyEventArgs & e);
    
    
};

#endif /* defined(__example_window__VideoManager__) */
