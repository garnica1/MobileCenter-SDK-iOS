/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */

#import "MSApplicationHelperPrivate.h"
#import "MSUtils.h"
#import <Foundation/Foundation.h>

@implementation MSApplicationHelper

+ (MSApplicationState)applicationState {

  // App extentions must not access sharedApplication.
  if (!MS_IS_APP_EXTENSION) {
    return (MSApplicationState)[[self class] sharedAppState];
  }
  return MSApplicationStateUnknown;
}

+ (UIApplicationState)sharedAppState {

  // Compute selector at runtime for more discretion.
  SEL sharedAppSel = NSSelectorFromString(@"sharedApplication");
  return [[((UIApplication * (*)(id, SEL))[[UIApplication class] methodForSelector:sharedAppSel])(
      [UIApplication class], sharedAppSel) valueForKey:@"applicationState"] longValue];
}

@end