//
//  Mount.h
//  Hackintool
//
//  Created by ghltbm on 11/15/25.
//  Copyright © 2025 Headsoft. All rights reserved.
//

@implementation RootVolumeManager: NSObject
- (NSString *)fetchRootVolumeIdentifier {
    
    
    /*
     Resolve path to disk identifier
     
     ex. / -> disk1s1
     */
    
    
    NSTask *task = [[NSTask alloc] init];
    [task setLaunchPath:@"/usr/sbin/diskutil"];
    [task setArguments:@[@"info", @"-plist", @"/"]];
    
    NSPipe *pipe = [NSPipe pipe];
    [task setStandardOutput:pipe];
    

    [task launch];
    [task waitUntilExit];
    

    NSData *outputData = [[pipe fileHandleForReading] readDataToEndOfFile];
    

    NSError *error = nil;
    NSDictionary *content = [NSPropertyListSerialization propertyListWithData:outputData
                                                                    options:NSPropertyListImmutable
                                                                     format:nil
                                                                      error:&error];
    

    if (error != nil) {
        @throw [NSException exceptionWithName:@"NSInternalInconsistencyException"
                                       reason:@"Failed to parse diskutil output."
                                     userInfo:nil];
    }
    

    NSString *disk = content[@"DeviceIdentifier"];
    

    if ([content[@"APFSSnapshot"] boolValue]) {
        disk = [disk substringToIndex:[disk length] - 2];
    }
    
    return disk;

}
@end
