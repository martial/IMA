//
//  MyUIDelegate.h
//  ofxCocoa demo
//
//  Created by Memo Akten on 30/10/2010.
//  Copyright 2010 MSA Visuals Ltd. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface MyUIDelegate : NSObject {
    NSButton *addMaskBtn;
    NSButton *toggleEditBtn;
    NSButton *fitToScreenBtn;
    NSColorWell *maskColorPicker;
    NSButton *toggleOutputBtn;
    NSTextField *zoomLabel;
    NSTextField *vfNumInput;
    NSTextField *vfResInput;
    NSStepper *vfResStepper;
    NSTextField *vfScaleInput;
    NSStepper *vfScaleStepper;
    NSTextField *nParticleInput;
    NSStepper *nParticleStepper;
    NSTextField *repulsionRadiusInput;
    NSStepper *repulsionRadiusStepper;
    NSTextField *repulsionDistanceInput;
    NSStepper *repulsionDistanceStepper;
    NSTextField *minLifeInputHandler;
    NSTextField *maxLifeInputHandler;
    NSButton *debugForcesBox;
    NSButton *vfBlurBox;
    NSButton *vfAnimateBox;
    NSBox *vfRandomizeBtn;
    NSButton *forceRandomPos;
    NSButton *toggleEditVecBtn;
    NSTextField *sceneWidthInput;
    NSTextField *sceneHeightInput;
    NSTextField *textureWidthInput;
    NSTextField *textureHeightInput;

    
    
}


-(IBAction) onAddMaskBtnHandler:(id)sender;
-(IBAction) onToggleEditBtnHandler:(id)sender;
-(IBAction) onFitToScreenBtnHander:(id)sender;
-(IBAction) onMaskColorPickerHandler:(id)sender;
-(IBAction) onToggleOutputBtnHandler:(id)sender;

-(IBAction) onVfNumInputHandler:(id)sender;


-(IBAction) onVfScaleInputHandler:(id)sender;
-(IBAction) onVfScaleStepperHandler:(id)sender;

-(IBAction) onVfResInputHandler:(id)sender;
-(IBAction) onVfResStepperHandler:(id)sender;

-(IBAction) onNParticleInputHandler:(id)sender;
-(IBAction) onNParticleStepperHandler:(id)sender;

-(IBAction) onRepulsionRadiusInputHandler:(id)sender;
-(IBAction) onRepulsionRadiusStepperHandler:(id)sender;

-(IBAction) onRepulsionDistanceInputHandler:(id)sender;
-(IBAction) onRepulsionDistanceStepperHandler:(id)sender;

-(IBAction) onMinLifeInputHandler:(id)sender;
-(IBAction) onMaxLifeInputHandler:(id)sender;

-(IBAction) onDebugForcesHandler:(id)sender;
-(IBAction) onVfBlurBoxHandler:(id)sender;

-(IBAction) onVfAnimateBoxHandler:(id)sender;
-(IBAction) onVfRandomizeBtnHandler:(id)sender;

-(IBAction) onForceRandomHandler:(id)sender;

-(IBAction) onToggleVecBtnHandler:(id)sender;

-(IBAction) onSceneWidthInputHandler:(id)sender;
-(IBAction) onSceneHeightInputHandler:(id)sender;

-(IBAction) onTextureWidthInputHandler:(id)sender;
-(IBAction) onTextureHeightInputHandler:(id)sender;



-(void) setZoom:(string)value;


@property (assign) IBOutlet NSButton *addMaskBtn;
@property (assign) IBOutlet NSButton *toggleEditBtn;
@property (assign) IBOutlet NSButton *fitToScreenBtn;
@property (assign) IBOutlet NSColorWell *maskColorPicker;
@property (assign) IBOutlet NSButton *toggleOutputBtn;
@property (assign) IBOutlet NSTextField *zoomLabel;

@property (assign) IBOutlet NSTextField *vfNumInput;

@property (assign) IBOutlet NSTextField *vfResInput;
@property (assign) IBOutlet NSStepper *vfResStepper;

@property (assign) IBOutlet NSTextField *vfScaleInput;
@property (assign) IBOutlet NSStepper *vfScaleStepper;

@property (assign) IBOutlet NSTextField *nParticleInput;
@property (assign) IBOutlet NSStepper *nParticleStepper;

@property (assign) IBOutlet NSTextField *repulsionRadiusInput;
@property (assign) IBOutlet NSStepper *repulsionRadiusStepper;

@property (assign) IBOutlet NSTextField *repulsionDistanceInput;
@property (assign) IBOutlet NSStepper *repulsionDistanceStepper;

@property (assign) IBOutlet NSTextField *minLifeInputHandler;
@property (assign) IBOutlet NSTextField *maxLifeInputHandler;

@property (assign) IBOutlet NSButton *debugForcesBox;
@property (assign) IBOutlet NSButton *vfBlurBox;
@property (assign) IBOutlet NSButton *vfAnimateBox;
@property (assign) IBOutlet NSBox *vfRandomizeBtn;
@property (assign) IBOutlet NSButton *forceRandomPos;
@property (assign) IBOutlet NSButton *toggleEditVecBtn;
@property (assign) IBOutlet NSTextField *sceneWidthInput;
@property (assign) IBOutlet NSTextField *sceneHeightInput;
@property (assign) IBOutlet NSTextField *textureWidthInput;
@property (assign) IBOutlet NSTextField *textureHeightInput;

@end
