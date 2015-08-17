//
//  MyUIDelegate.m
//  ofxCocoa demo
//
//  Created by Memo Akten on 30/10/2010.
//  Copyright 2010 MSA Visuals Ltd. All rights reserved.
//

#include "testApp.h"

#import "MyUIDelegate.h"


@implementation MyUIDelegate
@synthesize addMaskBtn;
@synthesize toggleEditBtn;
@synthesize fitToScreenBtn;
@synthesize maskColorPicker;
@synthesize toggleOutputBtn;
@synthesize zoomLabel;
@synthesize placeHoldersBtn;


-(void)awakeFromNib {
	NSLog(@"MyUIDelegate::awakeFromNib");
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    app->settings.load("settings.xml");
    
    ofVec3f color = app->settings.getVec3("maskColor");
    float alpha = app->settings.getFloat("maskAlpha");
    
    NSColor * c = [NSColor colorWithCalibratedRed:(color.x) green:(color.y) blue:(color.z) alpha:alpha];
    
    [maskColorPicker setColor:c];
    
    app->polyLineManager.setInactiveMaskColor(color.x*255.0f,color.y*255.0f,color.z*255.0f,alpha*255.0f);
    
   
    
}


-(void) setZoom:(string)value {
    
    NSString * label = [NSString stringWithCString:value.c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    
    [self.zoomLabel setStringValue:label];
   // [label release];
    
}



-(IBAction) onAddMaskBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->polyLineManager.addQuad();
    
}

-(IBAction) onToggleEditBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->polyLineManager.toggleEditMode();
    
    
}

-(IBAction) onFitToScreenBtnHander:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->videoManager.fitToScreen();
    
}

-(IBAction) onMaskColorPickerHandler:(id)sender {
    
    NSColor *nsColor = [sender color];
    //ofColor c;
    //[nsColor getRed:&c.r green:&c.g blue:&c.b alpha:&c.a];
    float r, g, b, a;
    [nsColor getRed:&r green:&g blue:&b alpha:&a];
    
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->polyLineManager.setInactiveMaskColor(r*255.0f,g*255.0f,b*255.0f,a*255.0f);

    settings.set("maskColor", ofVec3f(r,g,b));
    settings.set("maskAlpha", a);

    
    
}

-(IBAction) onToggleOutputBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->videoManager.toggleVideoVisible();
}

-(IBAction) onPlaceholdersBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();

    app->bDrawPlaceHolders = !app->bDrawPlaceHolders;
}



@end
