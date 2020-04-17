//
//  TTTObjects.h
//  TTTRtcEngineKit
//
//  Created by yanzhen on 2020/1/3.
//  Copyright © 2020 TTT. All rights reserved.
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

/** 通话相关的统计信息 */
@interface TTTRtcStats : NSObject
/** 通话时长，单位为秒，累计值 */
@property (assign, nonatomic) NSUInteger duration;
/** 发送字节数，累计值 */
@property (assign, nonatomic) NSUInteger txBytes;
/** 接收字节数，累计值 */
@property (assign, nonatomic) NSUInteger rxBytes;
/** 音频发送码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger txAudioKBitrate;
/** 音频接收码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger rxAudioKBitrate;
/** 视频发送码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger txVideoKBitrate;
/** 视频接收码率 (kbps)，瞬时值 */
@property (assign, nonatomic) NSUInteger rxVideoKBitrate;
/** 房间内的瞬时人数 */
@property (assign, nonatomic) NSUInteger users;

@end

/**
 *  本地视频统计信息
 */
@interface TTTRtcLocalVideoStats : NSObject
/** 采集的帧率(fps) */
@property (assign, nonatomic) NSUInteger capturedFrameRate;
/** 丢弃的帧率(fps) */
@property (assign, nonatomic) NSUInteger droppedFrameRate;
/** 编码的帧率(fps) */
@property (assign, nonatomic) NSUInteger encodedFrameRate;
/** 发送的帧率(fps) */
@property (assign, nonatomic) NSUInteger sentFrameRate;
/** 编码的码率(kbps) */
@property (assign, nonatomic) NSUInteger encodedBitrate;
/** 发送的码率(kbps) */
@property (assign, nonatomic) NSUInteger sentBitrate;
/** 接收的码率(kbps) */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** 发送的丢包率 */
@property (assign, nonatomic) float sentLossRate;
/** 视频缓冲区大小 */
@property (assign, nonatomic) int bufferDuration;
/** rtt */
@property (assign, nonatomic) NSUInteger rtt;

@end

/** 本地音频统计信息 */
@interface TTTRtcLocalAudioStats : NSObject
/** 编码的码率(kbps) */
@property (assign, nonatomic) NSUInteger encodedBitrate;
/** 发送的码率(kbps) */
@property (assign, nonatomic) NSUInteger sentBitrate;
/** 接收的码率(kbps) */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** 音频采集数据长度(Byte) */
@property (assign, nonatomic) NSUInteger captureDataSize;
/** 发送的丢包率 */
@property (assign, nonatomic) CGFloat sentLossRate;
/** rtt */
@property (assign, nonatomic) NSUInteger rtt;

@end

/** 远端视频统计信息 */
@interface TTTRtcRemoteVideoStats : NSObject
/** 用户id */
@property (assign, nonatomic) int64_t uid;
/** 延迟(ms) */
@property (assign, nonatomic) NSUInteger delay;
/** 宽 */
@property (assign, nonatomic) NSUInteger width;
/** 高 */
@property (assign, nonatomic) NSUInteger height;
/** 接收的码率(kbps) */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** 接收的帧率 */
@property (assign, nonatomic) NSUInteger receivedFrameRate;
/** 接收的帧数 */
@property (assign, nonatomic) NSUInteger receivedFrames;
/** 丢掉的帧数 */
@property (assign, nonatomic) NSUInteger lostFrames;
/** 设备id(远端用户多流必选参数) */
@property (copy, nonatomic) NSString *deviceId;
/** 丢包率 */
@property (assign, nonatomic) CGFloat loseRate;
/** rtt */
@property (assign, nonatomic) NSUInteger rtt;

@end

/**  远端音频统计信息 */
@interface TTTRtcRemoteAudioStats : NSObject
/** 用户id */
@property (assign, nonatomic) int64_t uid;
/** 接收码率(kbps) */
@property (assign, nonatomic) NSUInteger receivedBitrate;
/** 丢包率 */
@property (assign, nonatomic) CGFloat loseRate;
/** 缓存时长(ms) */
@property (assign, nonatomic) NSUInteger bufferDuration;
/** 延迟(ms) */
@property (assign, nonatomic) NSUInteger delay;
/** 音频编码类型 */
@property (assign, nonatomic) NSUInteger audioCodec;
/** rtt */
@property (assign, nonatomic) NSUInteger rtt;

@end

/**  视频属性 */
@interface TTTRtcVideoCanvas : NSObject
/** 视频显示窗口。SDK不维护view的生命周期，应用程序应保证view在通话中是有效的 */
@property (strong, nonatomic) TImageView *view;
/** 视频显示模式 */
@property (assign, nonatomic) TTTRtcRenderMode renderMode;
/** 用户id */
@property (assign, nonatomic) int64_t uid;
/** 设备id(远端用户多流必选参数) */
@property (copy, nonatomic) NSString *deviceId;

@end

/** 混频 */
@interface TTTRtcVideoMixerCanvas : NSObject
/** 视频显示窗口。SDK不维护view的生命周期，应用程序应保证view在通话中是有效的 */
@property (strong, nonatomic) TImageView *view;
/** 视频显示模式 */
@property (assign, nonatomic) TTTRtcRenderMode renderMode;
/** 混频id */
@property (copy, nonatomic) NSString *deviceId;
/** YES:打开 NO:关闭 */
@property (assign, nonatomic) BOOL open;
@end

/**
 *  视频合成区域
 */
@interface TTTRtcVideoCompositingRegion : NSObject
/** 待显示在该区域的主播用户 uid */
@property (assign, nonatomic) int64_t uid;
/** [0.0, 1.0] 屏幕里该区域的横坐标 x+width不能大于1 */
@property (assign, nonatomic) double x;
/** [0.0, 1.0] 屏幕里该区域的纵坐标 y+height不能大于1 */
@property (assign, nonatomic) double y;
/** [0.0, 1.0] 该区域的实际宽度 x+width不能大于1 */
@property (assign, nonatomic) double width;
/** [0.0, 1.0] 该区域的实际高度 y+height不能大于1 */
@property (assign, nonatomic) double height;
/** [0, 100] 用于定义图层。0表示该区域图像位于最下层，而100表示该区域图像位于最上层 */
@property (assign, nonatomic) NSInteger zOrder;
/** [0.0, 1.0] 用于定义图像的透明度。0表示图像为透明的，1表示图像为完全不透明的 */
@property (assign, nonatomic) double alpha;
/** 视频显示模式 */
@property (assign, nonatomic) TTTRtcRenderMode renderMode;
/** 设备id(远端用户多流必选参数) */
@property (copy, nonatomic) NSString *deviceId;

@end

/** 视频合成布局 */
@interface TTTRtcVideoCompositingLayout : NSObject
/** 整个屏幕(画布)的宽度 */
@property (assign, nonatomic) NSInteger canvasWidth;
/** 整个屏幕(画布)的高度 */
@property (assign, nonatomic) NSInteger canvasHeight;
/** 屏幕(画布)的背景颜色，可根据 RGB 填写所需颜色对应的6位符号。e.g. "#c0c0c0" "*/
@property (copy, nonatomic) NSString* backgroundColor;
/** 视频合成区域列表 */
@property (strong, nonatomic) NSMutableArray<TTTRtcVideoCompositingRegion *> *regions;
/** 应用程序自定义的数据 */
@property (copy, nonatomic) NSString *mExtInfos;
/** cdn推流地址,多个cdn推理地址必传参数 */
@property (copy, nonatomic) NSString *rtmpUrl;
@end

/** 直播推流配置 */
@interface TTTPublisherConfiguration : NSObject
/** cdn推流地址 */
@property (copy, nonatomic) NSString *publishUrl;
/** 推送纯音频流 */
@property (assign, nonatomic) BOOL isPureAudio;
/** cdn视频分辨率, 默认352x640
    最终分辨率([TTTRtcVideoCompositingLayout.canvasWidth])和([TTTRtcVideoCompositingLayout.canvasHeight])
 */
@property (assign, nonatomic) CGSize videoSize;
/** cdn视频帧率, 默认15 */
@property (assign, nonatomic) int videoFrameRate;
/** cdn视频码率, 默认750 */
@property (assign, nonatomic) int videoBitrate;
/** cdn流背景图地址，使用([TTTRtcEngineDelegate setVideoMixerBackgroundImgUrl:forRtmpUrl:])修改 */
@property (copy, nonatomic) NSString *backgroundImageUrl;
/** cdn音频采样率, 默认48000 可选择8000, 16000, 24000, 32000, 44100, 48000 */
@property (assign, nonatomic) int samplerate;
/** cdn1音频单声道，2双声道 */
@property (assign, nonatomic) int channels;

@property (assign, nonatomic) NSInteger __deprecated bitrate;
@end

/** 直播推流配置生成器 */
@interface TTTPublisherConfigurationBuilder : NSObject

- (TTTPublisherConfigurationBuilder *)setBitrate:(NSInteger)bitrate DEPRECATED_MSG_ATTRIBUTE("");
- (TTTPublisherConfigurationBuilder *)setPublisherUrl:(NSString *)url DEPRECATED_MSG_ATTRIBUTE("use TTTPublisherConfiguration.publishUrl instead");
- (TTTPublisherConfigurationBuilder *)setPublishPureAudio:(BOOL)isPureAudio DEPRECATED_MSG_ATTRIBUTE("use TTTPublisherConfiguration.isPureAudio instead");
- (TTTPublisherConfiguration *)build DEPRECATED_MSG_ATTRIBUTE("");

@end

/** 视频帧 */
@interface TTTRtcVideoFrame : NSObject
/** 视频帧的格式 */
@property (assign, nonatomic) TTTRtcVideoFrameFormat format;
/** 视频帧的时间戳，以毫秒为单位。不正确的时间戳会导致丢帧或者音视频不同步 */
@property (assign, nonatomic) CMTime time;
/** 视频采集帧 通过接口"setLocalVideoFrameCaptureFormat:"设置参数
 TTTRtc_VideoFrameFormat_Texture
 */
@property (assign, nonatomic) CVPixelBufferRef textureBuffer;
/** TTTRtc_VideoFrameFormat_Texture该参数未nil */
@property (strong, nonatomic) NSData *dataBuffer;
/** 视频帧的行间距，单位为像素而不是字节, 视频宽 */
@property (assign, nonatomic) int strideInPixels;
/** 视频高 */
@property (assign, nonatomic) int height;
/** how many pixels to crop on the left boundary */
@property (assign, nonatomic) int cropLeft;
/** how many pixels to crop on the top boundary */
@property (assign, nonatomic) int cropTop;
/** how many pixels to crop on the right boundary */
@property (assign, nonatomic) int cropRight;
/** how many pixels to crop on the bottom boundary */
@property (assign, nonatomic) int cropBottom;
/** 0, 90, 180, 270 */
@property (assign, nonatomic) int rotation;
/** 设备id */
@property (copy, nonatomic) NSString *deviceId;
/** 视频帧ID */
@property (assign, nonatomic) NSUInteger frameID;

@end

#if TARGET_OS_OSX
/** 音频设备 */
@interface TTTRtcAudioDevice : NSObject
/** 音频设备ID */
@property (assign, nonatomic) AudioDeviceID deviceID;
/** 音频设备类型 */
@property (assign, nonatomic) TTTRtcAudioDeviceType deviceType;
/** 音频设备名称 */
@property (copy, nonatomic) NSString *deviceName;

@end
#endif
