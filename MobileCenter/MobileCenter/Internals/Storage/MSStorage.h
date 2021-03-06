/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */

#import "MSLog.h"
#import "MSLogContainer.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^MSLoadDataCompletionBlock)(BOOL succeeded, NSArray<MSLog> *logArray, NSString *batchId);

/**
 Defines the storage component which is responsible for file i/o and file
 management.
 */
@protocol MSStorage <NSObject>

/*
 * Defines the maximum count of app log files per storage key on the file system.
 *
 * Default: 7
 */
@property(nonatomic) NSUInteger bucketFileCountLimit;

/*
 * Defines the maximum count of app logs per storage key in a file.
 *
 * Default: 50
 */
@property(nonatomic) NSUInteger bucketFileLogCountLimit;

@required

/**
 * Writes a log to the file system.
 *
 * param log The log item that should be written to disk
 * param storageKey The key used for grouping
 */
- (void)saveLog:(id<MSLog>)log withStorageKey:(NSString *)storageKey;

/**
 * Delete logs related to given storage key from the file system.
 *
 * param storageKey The key used for grouping.
 */
- (void)deleteLogsForStorageKey:(NSString *)storageKey;

/**
 * Delete a log from the file system.
 *
 * param log The log item that should be deleted from disk.
 * param storageKey The key used for grouping.
 */
- (void)deleteLogsForId:(NSString *)logsId withStorageKey:(NSString *)storageKey;

/**
 * Returns the most recent logs for a given storage key.
 *
 * param storageKey The key used for grouping.
 *
 * @return a list of logs.
 */
- (BOOL)loadLogsForStorageKey:(NSString *)storageKey withCompletion:(nullable MSLoadDataCompletionBlock)completion;

/**
 *  FIXME: The number of logs per batch and the number of logs per files are currently tied together. The storage loads
 * what's contained in the available file and this could be higher than the batch max size going to be sent. To mitigate
 * this kind of scenario the file is closed when the max size of the log batch is reached.
 *
 *  @param storageKey The key used for grouping.
 */
- (void)closeBatchWithStorageKey:(NSString *)storageKey;

@end

NS_ASSUME_NONNULL_END
