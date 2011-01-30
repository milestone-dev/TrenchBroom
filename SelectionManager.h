//
//  SelectionManager.h
//  TrenchBroom
//
//  Created by Kristian Duske on 30.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

extern NSString* const SelectionChanged;

typedef enum {
    SM_UNDEFINED,
    SM_FACES,
    SM_GEOMETRY
} ESelectionMode;

@class Face;
@class Brush;
@class Entity;

@interface SelectionManager : NSObject {
    @private
    NSMutableSet* faces;
    NSMutableSet* brushes;
    NSMutableSet* entities;
    ESelectionMode mode;
}

- (void)addFace:(Face *)face;
- (void)addBrush:(Brush *)brush;
- (void)addEntity:(Entity *)entity;

- (ESelectionMode)mode;
- (BOOL)isFaceSelected:(Face *)face;
- (BOOL)isBrushSelected:(Brush *)brush;
- (BOOL)isEntitySelected:(Entity *)entity;
- (BOOL)hasSelectedFaces:(Brush *)brush;

- (void)removeFace:(Face *)face;
- (void)removeBrush:(Brush *)brush;
- (void)removeEntity:(Entity *)entity;

- (void)removeAll;

@end
