//
//  ViewController.m
//  ZZFileManager
//
//  Created by Aaron on 16/8/4.
//  Copyright © 2016年 Aaron. All rights reserved.
//

#import "ViewController.h"
#import "ZZFileCache.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSURL *url = [[NSBundle mainBundle] URLForResource:@"zhuoku050" withExtension:@"jpg"];
    NSData *data = [NSData dataWithContentsOfURL:url];
    
    //异步缓存图片
    [[ZZFileCache sharedFileCache] storeFileWithData:data forKey:@"https://ip:8080/uri" completion:^(NSString *filePath) {
        NSLog(@"file path : %@", filePath);
    }];
    
    [NSThread sleepForTimeInterval:15.0];
    
    //检查文件是否缓存了
    if ([[ZZFileCache sharedFileCache] diskFileExistsWithKey:@"https://ip:8080/uri"]) {
        NSLog(@"该文件已经缓存");
    }
    
    NSLog(@"file path : %@", [[ZZFileCache sharedFileCache] defaultCachePathForKey:@"https://ip:8080/uri"]);
}

@end
