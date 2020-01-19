//
//  TTTObjects.h
//  TTTRtcEngineKit
//
//  Copyright © 2019 TTT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "TTTEnumerates.h"

#if TARGET_OS_IOS
#import <UIKit/UIKit.h>
typedef UIView      TView;
typedef UIImage     TImage;
typedef UIImageView TImageView;
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
typedef NSView      TView;
typedef NSImage     TImage;
typedef NSImageView TImageView;
#endif

#if TARGET_OS_OSX
/**
 *  音频设备
 */
@interface TTTRtcAudioDevice : NSObject

@property (assign, nonatomic) AudioDeviceID deviceID;           // 音频设备ID
@property (assign, nonatomic) TTTRtcAudioDeviceType deviceType; // 音频设备类型
@property (copy, nonatomic) NSString *deviceName;               // 音频设备名称

@end
#endif

/**
 *  通话相关的统计信息
 */
@interface TTTRtcStats : NSObject

@property (assign, nonatomic) NSUInteger duration;        // 通话时长，单位为秒，累计值
@property (assign, nonatomic) NSUInteger txBytes;         // 发送字节数，累计值
@property (assign, nonatomic) NSUInteger rxBytes;         // 接收字节数，累计值
@property (assign, nonatomic) NSUInteger txAudioKBitrate; // 音频发送码率 (kbps)，瞬时值
@property (assign, nonatomic) NSUInteger rxAudioKBitrate; // 音频接收码率 (kbps)，瞬时值
@property (assign, nonatomic) NSUInteger txVideoKBitrate; // 视频发送码率 (kbps)，瞬时值
@property (assign, nonatomic) NSUInteger rxVideoKBitrate; // 视频接收码率 (kbps)，瞬时值
@property (assign, nonatomic) NSUInteger users;           // 房间内的瞬时人数

@end

/**
 *  本地视频统计信息
 */
@interface TTTRtcLocalVideoStats : NSObject

@property (assign, nonatomic) NSUInteger encodedBitrate;  // 编码的码率(kbps)
@property (assign, nonatomic) NSUInteger sentBitrate;     // 发送的码率(kbps)
@property (assign, nonatomic) NSUInteger sentFrameRate;   // 发送的帧率(fps)
@property (assign, nonatomic) NSUInteger receivedBitrate; // 接收的码率(kbps)
@property (assign, nonatomic) float sentLossRate;         // 发送的丢包率
@property (assign, nonatomic) int bufferDuration;         // 视频缓冲区大小
@property (assign, nonatomic) NSUInteger rtt;

@end

/**
 *  本地音频统计信息
 */
@interface TTTRtcLocalAudioStats : NSObject

@property (assign, nonatomic) NSUInteger encodedBitrate;  // 编码的码率(kbps)
@property (assign, nonatomic) NSUInteger sentBitrate;     // 发送的码率(kbps)
@property (assign, nonatomic) NSUInteger receivedBitrate; // 接收的码率(kbps)
@property (assign, nonatomic) NSUInteger captureDataSize; // push数据量
@property (assign, nonatomic) CGFloat sentLossRate;       // 发送的丢包率
@property (assign, nonatomic) NSUInteger rtt;

@end

/**
 *  远端视频统计信息
 */
@interface TTTRtcRemoteVideoStats : NSObject

@property (assign, nonatomic) int64_t uid;
@property (assign, nonatomic) NSUInteger delay;             // 延迟
@property (assign, nonatomic) NSUInteger width;
@property (assign, nonatomic) NSUInteger height;
@property (assign, nonatomic) NSUInteger receivedBitrate;   // 接收的码率
@property (assign, nonatomic) NSUInteger receivedFrameRate; // 接收的帧率
@property (assign, nonatomic) NSUInteger receivedFrames;    // 接收的帧数
@property (assign, nonatomic) NSUInteger lostFrames;        // 丢掉的帧数
@property (copy, nonatomic) NSString *deviceId;             // 设备id(远端用户多流必选参数)
@property (assign, nonatomic) CGFloat loseRate;             // 丢包率
@property (assign, nonatomic) NSUInteger rtt;

@end

/**
 *  远端音频统计信息
 */
@interface TTTRtcRemoteAudioStats : NSObject

@property (assign, nonatomic) int64_t uid;
@property (assign, nonatomic) NSUInteger receivedBitrate;   // 接收码率
@property (assign, nonatomic) CGFloat loseRate;             // 丢包率
@property (assign, nonatomic) NSUInteger bufferDuration;    // 缓存时长
@property (assign, nonatomic) NSUInteger delay;             // 延迟
@property (assign, nonatomic) NSUInteger audioCodec;
@property (assign, nonatomic) NSUInteger rtt;

@end

/**
 *  视频属性
 */
@interface TTTRtcVideoCanvas : NSObject

@property (strong, nonatomic) TImageView *view;            // 视频显示窗口。SDK不维护view的生命周期，应用程序应保证view在通话中是有效的。
@property (assign, nonatomic) TTTRtcRenderMode renderMode; // 视频显示模式
@property (assign, nonatomic) int64_t uid;                 // 用户ID
@property (copy, nonatomic) NSString *deviceId;            // 设备id(远端用户多流必选参数)

@end

/**
 *  混频
 */
@interface TTTRtcVideoMixerCanvas : NSObject

@property (strong, nonatomic) TImageView *view;            // 视频显示窗口。SDK不维护view的生命周期，应用程序应保证view在通话中是有效的。
@property (assign, nonatomic) TTTRtcRenderMode renderMode; // 视频显示模式

@end

/**
 *  视频合成区域
 */
@interface TTTRtcVideoCompositingRegion : NSObject

@property (assign, nonatomic) int64_t uid;      // 待显示在该区域的主播用户 uid
@property (assign, nonatomic) double x;         // [0.0, 1.0] 屏幕里该区域的横坐标
@property (assign, nonatomic) double y;         // [0.0, 1.0] 屏幕里该区域的纵坐标
@property (assign, nonatomic) double width;     // [0.0, 1.0] 该区域的实际宽度
@property (assign, nonatomic) double height;    // [0.0, 1.0] 该区域的实际高度
@property (assign, nonatomic) NSInteger zOrder; // [0, 100]   用于定义图层。0表示该区域图像位于最下层，而100表示该区域图像位于最上层。
@property (assign, nonatomic) double alpha;     // [0.0, 1.0] 用于定义图像的透明度。0表示图像为透明的，1表示图像为完全不透明的。
@property (assign, nonatomic) TTTRtcRenderMode renderMode; // 视频显示模式
@property (copy, nonatomic) NSString *deviceId; // 设备id(远端用户多流必选参数)

@end

/**
 *  视频合成布局
 */
@interface TTTRtcVideoCompositingLayout : NSObject

@property (assign, nonatomic) NSInteger canvasWidth;   // 整个屏幕(画布)的宽度
@property (assign, nonatomic) NSInteger canvasHeight;  // 整个屏幕(画布)的高度
@property (copy, nonatomic) NSString* backgroundColor; // 屏幕(画布)的背景颜色，可根据 RGB 填写所需颜色对应的6位符号。e.g. "#c0c0c0"
@property (strong, nonatomic) NSMutableArray *regions; // 视频合成区域列表
@property (copy, nonatomic) NSString *mExtInfos;       // 应用程序自定义的数据
@property (copy, nonatomic) NSString *rtmpUrl;         // cdn推流地址,多个cdn推理地址必传参数
@end

/**
 *  直播推流配置
 */
@interface TTTPublisherConfiguration : NSObject

@property (assign, nonatomic) NSInteger bitrate;       // 旁路直播输出码流的码率。默认设置为 500 Kbps
@property (copy, nonatomic) NSString *publishUrl;      // 合图推流地址
@property (assign, nonatomic) BOOL isPureAudio;        // 推送纯音频流

@end

/**
 *  直播推流配置生成器
 */
@interface TTTPublisherConfigurationBuilder : NSObject

- (TTTPublisherConfigurationBuilder *)setBitrate:(NSInteger)bitrate;
- (TTTPublisherConfigurationBuilder *)setPublisherUrl:(NSString *)url;
- (TTTPublisherConfigurationBuilder *)setPublishPureAudio:(BOOL)isPureAudio;
- (TTTPublisherConfiguration *)build;

@end


/**
 *  视频帧
 */
@interface TTTRtcVideoFrame : NSObject

@property (assign, nonatomic) TTTRtcVideoFrameFormat format;  // 视频帧的格式
@property (assign, nonatomic) CMTime time;                    // 视频帧的时间戳，以毫秒为单位。不正确的时间戳会导致丢帧或者音视频不同步
@property (assign, nonatomic) CVPixelBufferRef textureBuffer;
@property (strong, nonatomic) NSData *dataBuffer;             // raw data buffer. in case of ios texture, it is not used
@property (assign, nonatomic) int strideInPixels;             // 视频帧的行间距，单位为像素而不是字节。
@property (assign, nonatomic) int height;                     // how many rows of pixels, in case of ios texture, it is not used
@property (assign, nonatomic) int cropLeft;                   // how many pixels to crop on the left boundary
@property (assign, nonatomic) int cropTop;                    // how many pixels to crop on the top boundary
@property (assign, nonatomic) int cropRight;                  // how many pixels to crop on the right boundary
@property (assign, nonatomic) int cropBottom;                 // how many pixels to crop on the bottom boundary
@property (assign, nonatomic) int rotation;                   // 0, 90, 180, 270.
@property (copy, nonatomic) NSString *deviceId;               // 设备id
@property (assign, nonatomic) NSUInteger frameID;             // 视频帧ID
@end

/**
 *  聊天信息
 */
@interface TTTRtcChatInfo : NSObject

@property (assign, nonatomic) TTTRtcChatType chatType;  // 聊天类型
@property (copy, nonatomic) NSString *seqID;            // 唯一标识
@property (copy, nonatomic) NSString *chatData;         // 聊天内容
@property (assign, nonatomic) NSUInteger audioDuration; // 音频时长（单位“秒”，chatType为“Audio”）

@end



