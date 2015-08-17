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
    NSButton *placeHoldersBtn;
}


-(IBAction) onAddMaskBtnHandler:(id)sender;
-(IBAction) onToggleEditBtnHandler:(id)sender;
-(IBAction) onFitToScreenBtnHander:(id)sender;
-(IBAction) onMaskColorPickerHandler:(id)sender;
-(IBAction) onToggleOutputBtnHandler:(id)sender;
-(IBAction) onPlaceholdersBtnHandler:(id)sender;


-(void) setZoom:(string)value;


@property (assign) IBOutlet NSButton *addMaskBtn;
@property (assign) IBOutlet NSButton *toggleEditBtn;
@property (assign) IBOutlet NSButton *fitToScreenBtn;
@property (assign) IBOutlet NSColorWell *maskColorPicker;
@property (assign) IBOutlet NSButton *toggleOutputBtn;
@property (assign) IBOutlet NSTextField *zoomLabel;
@property (assign) IBOutlet NSButton *placeHoldersBtn;


@end
