/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */

#import "CRLCrashAbort.h"

@implementation CRLCrashAbort

- (NSString *)category {
  return @"SIGTRAP";
}

- (NSString *)title {
  return @"Call abort()";
}

- (NSString *)desc {
  return @"Call abort() to terminate the program.";
}

- (void)crash __attribute__((noreturn)) {
  abort();
}

@end