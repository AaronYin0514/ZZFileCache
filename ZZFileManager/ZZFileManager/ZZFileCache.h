//
//  ZZFileCache.h
//  ZZFileManager
//
//  Created by Aaron on 16/8/4.
//  Copyright © 2016年 Aaron. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^ZZFileManagerStoreCompletedBlock)(NSString *filePath);

typedef void(^ZZFileManagerQueryCompletedBlock)(NSData *fileData);

typedef void(^ZZFileManagerRemoveFileCompletionBlock)(BOOL hasRemoved);

typedef void(^ZZFileManagerCheckCacheCompletionBlock)(BOOL isInCache);

typedef void(^ZZFileManagerCalculateSizeBlock)(NSUInteger fileCount, NSUInteger totalSize);

typedef void(^ZZFileManagerNoParamsBlock)();

@interface ZZFileCache : NSObject
/**
 * 是否解压缩文件
 */
@property (assign, nonatomic) BOOL shouldDecompressFile;
/**
 * 最大存储时间, 单位：秒
 */
@property (assign, nonatomic) NSInteger maxCacheAge;
/**
 * 最大存储空间, 单位：bytes.
 */
@property (assign, nonatomic) NSUInteger maxCacheSize;
/**
 *  单例初始化方法
 *
 *  @return 单例初始化方法
 */
+ (ZZFileCache *)sharedFileCache;
/**
 *  初始化方法
 *
 *  @param ns 命名空间
 *
 *  @return 初始化
 */
- (id)initWithNamespace:(NSString *)ns;
/**
 *  初始化方法
 *
 *  @param ns        命名空间
 *  @param directory 存储目录
 *
 *  @return 初始化方法
 */
- (id)initWithNamespace:(NSString *)ns diskCacheDirectory:(NSString *)directory;
/**
 *  文件缓存
 *
 *  @param data 待缓存的文件
 *  @param key  唯一的key
 */
- (void)storeFileWithData:(NSData *)data forKey:(NSString *)key;
/**
 *  文件缓存，带block回调
 *
 *  @param data       待缓存的文件
 *  @param key        唯一的key
 *  @param completion 回调，返回缓存地址
 */
- (void)storeFileWithData:(NSData *)data forKey:(NSString *)key completion:(ZZFileManagerStoreCompletedBlock)completion;
/**
 *  通过key异步查询磁盘缓存文件
 *
 *  @param key       唯一的key
 *  @param doneBlock 回调函数，返回缓存文件data
 *
 *  @return Operation，如果Cancelle掉Operation，那么就不会回调了
 */
- (NSOperation *)fileFromDiskCacheForKey:(NSString *)key done:(ZZFileManagerQueryCompletedBlock)doneBlock;
/**
 *  通过key同步查询磁盘缓存文件
 *
 *  @param key 唯一的key
 *
 *  @return 返回缓存文件data
 */
- (NSData *)fileFromDiskCacheForKey:(NSString *)key;
/**
 *  同步移除磁盘中缓存的文件
 *
 *  @param key 唯一的key
 *
 *  @return 是否成功移除，失败原因可能为：空key值 或 文件不存在等
 */
- (BOOL)removeFileForKey:(NSString *)key;
/**
 *  异步移除磁盘中缓存的文件
 *
 *  @param key        唯一的key
 *  @param completion 回调，返回是否成功移除
 */
- (void)removeFileForKey:(NSString *)key completion:(ZZFileManagerRemoveFileCompletionBlock)completion;
/**
 *  同步移除所有缓存文件
 *
 *  @return 是否成功移除
 */
- (BOOL)clearDisk;
/**
 *  异步移除所有缓存文件
 *
 *  @param completion 回调，返回是否成功移除
 */
- (void)clearDiskOnCompletion:(ZZFileManagerRemoveFileCompletionBlock)completion;
/**
 *  异步移除过期文件，无block回调。注意：如果设置了文件缓存最大空间值，如果移除后，缓存文件所占空间仍然大于阈值，那么会按照文件修改时间先后，先移除老文件，知道缓存文件所占空间小于等于阈值
 */
- (void)cleanDisk;
/**
 *  异步移除过期文件，有block回调。说明请参考cleanDisk
 *
 *  @param completionBlock 回调
 */
- (void)cleanDiskWithCompletionBlock:(ZZFileManagerRemoveFileCompletionBlock)completionBlock;
/**
 *  获取当前磁盘缓存所占空间大小
 *
 *  @return 当前磁盘缓存所占空间大小
 */
- (NSUInteger)getSize;
/**
 *  获取当前磁盘缓存文件数
 *
 *  @return 当前磁盘缓存文件数
 */
- (NSUInteger)getDiskCount;
/**
 *  异步获取当前磁盘缓存所占空间大小和当前磁盘缓存文件数
 *
 *  @param completionBlock 回调
 */
- (void)calculateSizeWithCompletionBlock:(ZZFileManagerCalculateSizeBlock)completionBlock;
/**
 *  异步判断key文件是否已经缓存
 *
 *  @param key        唯一key值
 *  @param completion 回调，返回是否已经缓存所查询文件
 */
- (void)diskFileExistsWithKey:(NSString *)key completion:(ZZFileManagerCheckCacheCompletionBlock)completion;
/**
 *  同步判断key文件是否已经缓存
 *
 *  @param key 唯一key值
 *
 *  @return 返回是否已经缓存所查询文件
 */
- (BOOL)diskFileExistsWithKey:(NSString *)key;
/**
 *  返回指定目录中缓存文件路径
 *
 *  @param key  唯一key值
 *  @param path 指定目录
 *
 *  @return 缓存文件路径，如果为nil，则表示没有缓存
 */
- (NSString *)cachePathForKey:(NSString *)key inPath:(NSString *)path;
/**
 *  返回默认目录下缓存文件路径
 *
 *  @param key 唯一key值
 *
 *  @return 缓存文件路径，如果为nil，则表示没有缓存
 */
- (NSString *)defaultCachePathForKey:(NSString *)key;


@end
