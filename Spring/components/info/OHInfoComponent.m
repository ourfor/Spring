//
//  OHInfoComponent.m
//  MediaService
//
//  Created by 梁甜 on 2022/8/26.
//

#import "OHInfoComponent.h"

/// obtain program information
@implementation OHInfoComponent

+ (instancetype)component:(id<OHComponentContext>)context {
    return [OHInfoComponent new];
}

@end
