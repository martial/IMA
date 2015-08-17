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
@synthesize vfNumInput;
@synthesize vfResInput;
@synthesize vfResStepper;
@synthesize vfScaleInput;
@synthesize vfScaleStepper;
@synthesize nParticleInput;
@synthesize nParticleStepper;
@synthesize repulsionRadiusInput;
@synthesize repulsionRadiusStepper;
@synthesize repulsionDistanceInput;
@synthesize repulsionDistanceStepper;
@synthesize minLifeInputHandler;
@synthesize maxLifeInputHandler;
@synthesize debugForcesBox;
@synthesize vfBlurBox;
@synthesize vfAnimateBox;
@synthesize vfRandomizeBtn;
@synthesize forceRandomPos;
@synthesize toggleEditVecBtn;
@synthesize sceneWidthInput;
@synthesize sceneHeightInput;
@synthesize textureWidthInput;
@synthesize textureHeightInput;
@synthesize drawBoundsBtn;


-(void)awakeFromNib {
	NSLog(@"MyUIDelegate::awakeFromNib");
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    app->settings.load("settings.xml");
    
    ofVec3f color = app->settings.getVec3("maskColor");
    float alpha = app->settings.getFloat("maskAlpha");
    
    NSColor * c = [NSColor colorWithCalibratedRed:(color.x) green:(color.y) blue:(color.z) alpha:alpha];
    
    [maskColorPicker setColor:c];
    
    app->polyLineManager.setInactiveMaskColor(color.x*255.0f,color.y*255.0f,color.z*255.0f,alpha*255.0f);
    
    NSNumberFormatter *formatter = [[[NSNumberFormatter alloc] init] autorelease];
    [formatter setNumberStyle:NSNumberFormatterDecimalStyle];
    [self.maxLifeInputHandler setFormatter:formatter];
    
    
    [self.vfResInput        setIntValue:ofToInt(app->settings.get("vfRes"))];
    [self.vfResStepper      setIntValue:ofToInt(app->settings.get("vfRes"))];
    
    [self.vfScaleInput      setFloatValue:ofToFloat(app->settings.get("vfScale"))];
    [self.vfScaleStepper    setFloatValue:ofToFloat(app->settings.get("vfScale"))];
    
    [self.minLifeInputHandler setIntValue:ofToInt(app->settings.get("minLife"))];
    [self.maxLifeInputHandler setIntValue:ofToInt(app->settings.get("maxLife"))];
    
    [self.nParticleInput setIntValue:ofToInt(app->settings.get("nParticles"))];
    
    [self.repulsionDistanceInput setIntValue:ofToInt(app->settings.get("repDist"))];
    [self.repulsionRadiusInput setIntValue:ofToInt(app->settings.get("repRadius"))];

    //[self.vfAnimateBox setIntValue:ofToInt(app->settings.get("repRadius"))];
    [self.vfBlurBox setIntValue:ofToInt(app->settings.get("vfBlur"))];
    [self.forceRandomPos setIntValue:ofToInt(app->settings.get("forceRandom"))];
    [self.vfAnimateBox setIntValue:ofToInt(app->settings.get("vfAnimate"))];
    
    [self.vfNumInput setIntValue:app->settings.getInt("numOfVfs")];
    
    [self.sceneWidthInput setIntValue:app->settings.getInt("vfWidth")];
    [self.sceneHeightInput setIntValue:app->settings.getInt("vfHeight")];
    
    
    [self.textureWidthInput setIntValue:app->settings.getInt("texWidth")];
    [self.textureHeightInput setIntValue:app->settings.getInt("texHeight")];
    
    
    /*
     
     
     particles.setVFScale(ofToFloat(settings.get("vfScale")));
     particles.setVFResolution(ofToInt(settings.get("vfRes")));
     
     particles.setMaxLife(ofToInt(settings.get("maxLife")));
     particles.setMinLife(ofToInt(settings.get("minLife")));
     
     particles.setRepulsionDistance(ofToFloat(settings.get("repDist")));
     particles.setRepulsionRadius(ofToFloat(settings.get("repRadius")));
     
     */
    
    
}


-(void) setZoom:(string)value {
    
    NSString * label = [NSString stringWithCString:value.c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    
    [self.zoomLabel setStringValue:label];

    
}



-(IBAction) onAddMaskBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->polyLineManager.addQuad();
    
}

-(IBAction) onToggleEditBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->polyLineManager.toggleEditMode();
    
    if(app->vectorGradientManger.getEditMode())
        app->vectorGradientManger.setEditMode(false);
}

-(IBAction) onToggleVecBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->vectorGradientManger.toggleEditMode();
    
    if(app->polyLineManager.getEditMode())
        app->polyLineManager.setEditMode(false);


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

-(IBAction) onVfScaleInputHandler:(id)sender {
    testApp *app = (testApp*)ofGetAppPtr();
    app->particles.setVFScale([sender floatValue]);
    app->settings.set("vfScale", [sender floatValue]);

}

-(IBAction) onVfNumInputHandler:(id)sender {
    
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if(!app->bHasSetup)
        return;
    
    int value = [sender intValue];
    value = ofClamp(value, 1, 15);
    app->particles.setNumOfVFs(value);
    app->settings.set("numOfVfs", value);
    
}

-(IBAction) onVfScaleStepperHandler:(id)sender {
    
    [self.vfScaleInput setIntValue:[sender floatValue]];
    testApp *app = (testApp*)ofGetAppPtr();
    app->settings.set("vfScale", [sender floatValue]);
    app->particles.setVFScale([sender floatValue]);
    
}

-(IBAction) onVfResInputHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->particles.setVFResolution([sender intValue]);
    app->settings.set("vfRes", [sender intValue]);
    
   
    
}

-(IBAction) onVfResStepperHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
   
    
    int value = [sender intValue];
    int currentValue = ofToInt(app->settings.get("vfRes"));
    
    /*
    if(value < currentValue && value % 2 != 0 )
    value --;
    
    if(value > currentValue && value % 2 != 0 )
    value ++;
     */
    
    if(value < 1)
        value = 1;
    
    [sender setIntValue:value];
    [self.vfResInput setIntValue:[sender intValue]];

    app->settings.set("vfRes", [sender intValue]);
    app->particles.setVFResolution([sender intValue]);
    
}

-(IBAction) onNParticleInputHandler:(id)sender {
    
    
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if(!app->bHasSetup)
        return;
    
    int value = [sender intValue];
    int currentValue = ofToInt(app->settings.get("vfRes"));
    
    if(value < 0)
        value = 0;
    
    if(value > 200000 )
        value = 200000;
    
    if(value < 4)
        value = 4;

    
    app->particles.setNumOfParticles(value);
    app->settings.set("nParticles", value);

    
}
-(IBAction) onNParticleStepperHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    
    int value = [sender intValue];
    int currentValue = ofToInt(app->settings.get("nParticles"));
    
    if(value < 0)
        value = 0;
    
    if(value > 200000 )
        value = 200000;
    
    if(value < 4)
        value = 4;
    
    [sender setIntValue:value];
    [self.nParticleInput setIntValue:[sender intValue]];
    
    app->settings.set("nParticles", [sender intValue]);
    app->particles.setVFResolution([sender intValue]);
    
}

-(IBAction) onRepulsionRadiusInputHandler:(id)sender; {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if(!app->bHasSetup)
        return;
    
    int value = ofClamp([sender intValue], 1, 24);
    
    
    
    app->particles.setRepulsionRadius(value);
    app->settings.set("repRadius", value);
    
}

-(IBAction) onRepulsionRadiusStepperHandler:(id)sender {
    
}


-(IBAction) onRepulsionDistanceInputHandler:(id)sender {
    
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if(!app->bHasSetup)
        return;
    
    int value = ofClamp([sender intValue], 0.1, 30.0);
    
    app->particles.setRepulsionDistance(value);
    app->settings.set("repDist", value);

    
}
-(IBAction) onRepulsionDistanceStepperHandler:(id)sender {
    
}

-(IBAction) onMinLifeInputHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if(!app->bHasSetup)
        return;
    
    int value = ofClamp([sender intValue], 0, 1000);
    
    app->particles.setMinLife(value);
    app->settings.set("minLife", value);
    
    
}
-(IBAction) onMaxLifeInputHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if(!app->bHasSetup)
        return;
    
    int value = ofClamp([sender intValue], 0, 1000);
    
    app->particles.setMaxLife(value);
    app->settings.set("maxLife", value);

}

-(IBAction) onDebugForcesHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if( [sender state] == 1) {
        app->particles.bDebugRepulsionForces = true;
    } else {
        app->particles.bDebugRepulsionForces = false;

    }
    
    app->settings.set("debugForces", [sender state]);

    
}

-(IBAction) onForceRandomHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if( [sender state] == 1) {
        app->particles.bForceRandom = true;
    } else {
        app->particles.bForceRandom = false;
        
    }
    
    app->settings.set("forceRandom", [sender state]);


    
}

-(IBAction) onVfBlurBoxHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if( [sender state] == 1) {
        app->particles.bBlurVectorField = true;
    } else {
        app->particles.bBlurVectorField = false;
        
    }
    
    app->settings.set("vfBlur", [sender state]);

}

-(IBAction) onVfAnimateBoxHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    
    if( [sender state] == 1) {
        app->particles.bAnimate = true;
    } else {
        app->particles.bAnimate = false;
        
    }
    
    app->settings.set("vfAnimate", [sender state]);
    
}

-(IBAction) onSceneWidthInputHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    int value = ofClamp([sender intValue], 0, 48000);
    app->particles.setVFWidth(value);
    app->settings.set("vfWidth", value);

    
}

-(IBAction) onSceneHeightInputHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    int value = ofClamp([sender intValue], 0, 48000);
    app->particles.setVFHeight(value);
    app->settings.set("vfHeight", value);
}

-(IBAction) onTextureWidthInputHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    int value = ofClamp([sender intValue], 0, 48000);
    app->particles.setTextureWidth(value);
    app->settings.set("texWidth", value);

    
}
-(IBAction) onTextureHeightInputHandler:(id)sender {
    testApp *app = (testApp*)ofGetAppPtr();
    int value = ofClamp([sender intValue], 0, 48000);
    app->particles.setTextureHeight(value);
    app->settings.set("texHeight", value);
}


-(IBAction) onDrawBoundsBtnHandler:(id)sender {
    
    testApp *app = (testApp*)ofGetAppPtr();
    app->particles.bDrawBounds = !app->particles.bDrawBounds;
    
}
 





@end
