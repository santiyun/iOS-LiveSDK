#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
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

/** Error codes */
typedef NS_ENUM(NSUInteger, TTTRtcErrorCode) {
    /** 0: 没有错误， 接口调用成功 */
    TTTRtc_Error_NoError             = 0,
    /** 9000: 无效的房间名称。 使用可转换大于0的long long类型纯数字字符串 */
    TTTRtc_Error_InvalidChannelName  = 9000,
    /** 9001: 进入房间超时，10s未连接上服务器，说明网络比较差。不处理该回调参数, 我们会继续尝试连接服务器。
    停止这次进入房间操作，调用“leaveChannel”退出房间。 */
    TTTRtc_Error_Enter_TimeOut       = 9001,
    /** 9002: 无法连接服务器 */
    TTTRtc_Error_Enter_Failed        = 9002,
    /** 9003: 验证码错误，可忽略 */
    TTTRtc_Error_Enter_VerifyFailed  = 9003,
    /** 9004: 版本错误 */
    TTTRtc_Error_Enter_BadVersion    = 9004,
    /** 9005: 未知错误， 其它错误 */
    TTTRtc_Error_Enter_Unknown       = 9005,
    /** 9006: 直播模式"TTTRtc_ChannelProfile_LiveBroadcasting"，房间内没有主播 */
    TTTRtc_Error_Enter_NoAnchor      = 9006,
    /** 9101: 需要上行音频的场景，超过40s没有上行音频数据，可不处理 */
    TTTRtc_Error_NoAudioData         = 9101,
    /** 9102: 需要上行视频的场景，超过40s没有上行视频数据，可不处理 */
    TTTRtc_Error_NoVideoData         = 9102,
    /** 9111: 在有接收音频的场景，超过40s没有下行音频数据，可不处理。*/
    TTTRtc_Error_NoReceivedAudioData = 9111,
    /** 9112: 在有接收视频的场景，超过40s没有下行视频数据，可不处理。*/
    TTTRtc_Error_NoReceivedVideoData = 9112,
    /** 9200: 在加入房间做channelKey(token)验证, 传入的channelKey无效 */
    TTTRtc_Error_InvalidChannelKey   = 9200,
    /** 9999: 未知错误 */
    TTTRtc_Error_Unknown             = 9999,
};

/** 踢出房间 */
typedef NS_ENUM(NSUInteger, TTTRtcKickedOutReason) {
    /** 1: 直播模式, 主播通过"kickChannelUser:"把用户踢出房间 */
    TTTRtc_KickedOut_KickedByHost      = 1,
    /** 2: rtmp推流失败 */
    TTTRtc_KickedOut_PushRtmpFailed    = 2,
    /** 3: 服务器过载 */
    TTTRtc_KickedOut_ServerOverload    = 3,
    /** 4: 直播模式下，主播退出房间后，房间被销毁，其它用户收到该回调参数 */
    TTTRtc_KickedOut_MasterExit        = 4,
    /** 5: 同一AppId下，使用相同的用户id登录，前者会被踢出房间 */
    TTTRtc_KickedOut_ReLogin           = 5,
    /** 6: 长时间没有上行音频数据 */
    TTTRtc_KickedOut_NoAudioData       = 6,
    /** 7: 长时间没有上行视频数据 */
    TTTRtc_KickedOut_NoVideoData       = 7,
    /** 8: 直播模式下，主播在直播的情况下，其他人以主播身份加入相同房间，房间内其他用户会被踢出房间 */
    TTTRtc_KickedOut_NewChairEnter     = 8,
    /** 9: channelKey(token)到期 */
    TTTRtc_KickedOut_ChannelKeyExpired = 9,
};

/** 远端用户离线原因 */
typedef NS_ENUM(NSUInteger, TTTRtcUserOfflineReason) {
    /** 1: 用户调用"leaveChannel:"主动退出房间 */
    TTTRtc_UserOffline_Quit           = 1,
    /** 2: 因过长时间收不到对方数据包，超时掉线 */
    TTTRtc_UserOffline_Dropped        = 2,
    /** 3: 用户身份从副播切换为观众 */
    TTTRtc_UserOffline_BecomeAudience = 3,
};

/**  日志过滤器 */
typedef NS_ENUM(NSUInteger, TTTRtcLogFilter) {
    /** 不输出任何日志，默认值 */
    TTTRtc_LogFilter_Off      = 0,
    /** 输出所有类型日志 */
    TTTRtc_LogFilter_Debug    = 0x080f,
    /** 输出Info, Warning, Error 和 Critical 类型的日志 */
    TTTRtc_LogFilter_Info     = 0x000f,
    /** 输出Warning, Error 和 Critical 类型的日志 */
    TTTRtc_LogFilter_Warning  = 0x000e,
    /** 输出Error 和 Critical 类型的日志 */
    TTTRtc_LogFilter_Error    = 0x000c,
    /** 输出 Critical 类型的日志 */
    TTTRtc_LogFilter_Critical = 0x0008
};

/** 频道模式 */
typedef NS_ENUM(NSUInteger, TTTRtcChannelProfile) {
    /** 通信模式(默认值)，一对一自由通话，单用户在房间内不上行视频 */
    TTTRtc_ChannelProfile_Communication    = 0,
    /** 直播模式，主播先创建房间，房间内可以有一个主播，多个副播和多个观众。
     主播和副播可发送和接收音视频，观众只能接收音视频 */
    TTTRtc_ChannelProfile_LiveBroadcasting = 1,
    /** 游戏模式，主要针对游戏场景 */
    TTTRtc_ChannelProfile_Game_FreeMode    = 2, 
};

/** 用户角色 */
typedef NS_ENUM(NSUInteger, TTTRtcClientRole) {
    /** 主播：仅在直播模式下使用，且不能切换其它角色 */
    TTTRtc_ClientRole_Anchor      = 1,
    /** 副播：可在任何模式下使用，可切换为观众 */
    TTTRtc_ClientRole_Broadcaster = 2,
    /** 观众(默认)：可在任何模式下使用，可切换为副播。默认对其它用户是不可见的 */
    TTTRtc_ClientRole_Audience    = 3,
};

/** 音频编码格式 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioCodecType) {
    /** AAC：码率范围32kbps~96kbps */
    TTTRtc_AudioCodec_AAC     = 1,
    /** ISAC_WB：码率范围10kbps~32kbps (默认32kbps)*/
    TTTRtc_AudioCodec_ISAC_WB = 2,
    /** OPUS：码率范围32kbps~96kbps */
    TTTRtc_AudioCodec_OPUS    = 4,
};

/** 视频编码属性 */
typedef NS_ENUM(NSUInteger, TTTRtcVideoProfile) {
    /** Resolution: 160x120, frame rate: 15, bitrate 65 kbps */
    TTTRtc_VideoProfile_120P =  0,
    /** Resolution: 320x180, frame rate: 15, bitrate 140 kbps */
    TTTRtc_VideoProfile_180P = 10,
    /** Resolution: 320x240, frame rate: 15, bitrate 200 kbps */
    TTTRtc_VideoProfile_240P = 20,
    /** Resolution: 640x360, frame rate: 15, bitrate 400 kbps */
    TTTRtc_VideoProfile_360P = 30,
    /** Resolution: 848x480, frame rate: 15, bitrate 600 kbps */
    TTTRtc_VideoProfile_480P = 40,
    /** Resolution: 640x480, frame rate: 15, bitrate 500 kbps */
    TTTRtc_VideoProfile_640x480 = 45,
    /** Resolution: 1280x720, frame rate: 15, bitrate 1130 kbps */
    TTTRtc_VideoProfile_720P = 50,
#if TARGET_OS_IOS
    /** Resolution: 1920x1080, frame rate: 15, bitrate 2080 kbps */
    TTTRtc_VideoProfile_1080P   = 60,
#endif
    /** Resolution: 640x360, frame rate: 15, bitrate 400 kbps */
    TTTRtc_VideoProfile_Default = TTTRtc_VideoProfile_360P
};


#if TARGET_OS_IOS
/** 音频输出路由 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioOutputRouting)
{
    /** 耳机或蓝牙 */
    TTTRtc_AudioOutput_Headset   = 0,
    /** 扬声器 */
    TTTRtc_AudioOutput_Speaker   = 1,
    /** 手机听筒 */
    TTTRtc_AudioOutput_Headphone = 2
};
#elif TARGET_OS_OSX
/** 音频输出路由 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioOutputRouting)
{
    TTTRtc_AudioOutput_InternalSpeaker = 0, // 内置扬声器
    TTTRtc_AudioOutput_ExternalSpeaker = 1, // 外置扬声器
    TTTRtc_AudioOutput_Headphones      = 2  // 耳机
};

/**
 *  音频设备类型
 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioDeviceType) {
    TTTRtc_AudioDevice_Input_InternalMicrophone = 1,  // 内置麦克风
    TTTRtc_AudioDevice_Input_ExternalMicrophone = 2,  // 外置麦克风
    TTTRtc_AudioDevice_Output_InternalSpeaker   = 11, // 内置扬声器
    TTTRtc_AudioDevice_Output_ExternalSpeaker   = 12, // 外置扬声器
    TTTRtc_AudioDevice_Output_Headphones        = 13, // 耳机
};
#endif

/**
 *  视频显示模式
 */
typedef NS_ENUM(NSUInteger, TTTRtcRenderMode) {
    /** 如果视频尺寸与显示视窗尺寸不一致，则视频流会按照显示视窗的比例进行周边裁剪或图像拉伸后填满视窗 */
    TTTRtc_Render_Hidden   = 1,
    /** 如果视频尺寸与显示视窗尺寸不一致，在保持长宽比的前提下，将视频进行缩放后填满视窗 */
    TTTRtc_Render_Fit      = 2,
    /** 如果自己和对方都是竖屏，或者如果自己和对方都是横屏，使用TTTRtc_Render_Hidden
     如果对方和自己一个竖屏一个横屏，则使用TTTRtc_Render_Fit */
    TTTRtc_Render_Adaptive = 3
};

/** 视频帧格式 */
typedef NS_ENUM(NSUInteger, TTTRtcVideoFrameFormat) {
    /** Texture: 输出采集BGRA格式 CVPixelBufferRef */
    TTTRtc_VideoFrameFormat_Texture = 0,
    /** I420 */
    TTTRtc_VideoFrameFormat_I420    = 1,
    /** NV12 */
    TTTRtc_VideoFrameFormat_NV12    = 2,
    /** NV21 */
    TTTRtc_VideoFrameFormat_NV21    = 3,
    /** RGBA */
    TTTRtc_VideoFrameFormat_RGBA    = 4,
    /** BGRA */
    TTTRtc_VideoFrameFormat_BGRA    = 5,
    /** ARGB */
    TTTRtc_VideoFrameFormat_ARGB    = 6,
};

/** 聊天消息类型 */
typedef NS_ENUM(NSUInteger, TTTRtcChatType) {
    /** 文本 */
    TTTRtc_ChatType_Text    = 1,
    /** 图片 */
    TTTRtc_ChatType_Picture = 2,
    /** 短语音 */
    TTTRtc_ChatType_Audio   = 3,
    /** 自定义类型 */
    TTTRtc_ChatType_Custom  = 4
};

/**  RTMP推流状态 */
typedef NS_ENUM(NSUInteger, TTTRtcRtmpPublishStatus) {
    /** 初始化RTMP发送器失败 */
    TTTRtc_RtmpPublishStatus_InitError     = 0,
    /** 打开RTMP链接失败 */
    TTTRtc_RtmpPublishStatus_OpenError     = 1,
    /** 音频数据缓冲区空间不足 */
    TTTRtc_RtmpPublishStatus_AudioNoBuf    = 2,
    /** 视频数据缓冲区空间不足 */
    TTTRtc_RtmpPublishStatus_VideoNoBuf    = 3,
    /** 发送视频数据失败 */
    TTTRtc_RtmpPublishStatus_LinkFailed    = 4,
    /** 推流成功 */
    TTTRtc_RtmpPublishStatus_LinkSuccessed = 5,
};

/** 双流类型 */
typedef NS_ENUM(NSUInteger, TTTRtcVideoStreamType) {
    /** 视频大流: 原始视频尺寸 */
    TTTRtc_VideoStream_High = 0,
    /** 视频小流: 原始视频宽的一半，高的一半，码率的四分之一 */
    TTTRtc_VideoStream_Low  = 1,
};

/** 网络质量 */
typedef NS_ENUM(NSUInteger, TTTNetworkQuality) {
    TTTNetworkQualityExcellent = 1,
    TTTNetworkQualityGood      = 2,
    TTTNetworkQualityCommon    = 3,
    TTTNetworkQualityPoor      = 4,
    TTTNetworkQualityBad       = 5,
    TTTNetworkQualityDown      = 6,
};

/**
 *  网络连接状态
 */
typedef NS_ENUM(NSUInteger, TTTConnectionState) {
    /** 未加入房间，加入房间失败后，或者离开房间之后 */
    TTTConnectionStateDisconnected = 1,
    /** 加入房间正在建立网络连接 */
    TTTConnectionStateConnecting = 2,
    /** 网络连接建立成功 */
    TTTConnectionStateConnected = 3,
    /** 网络连接重连中 */
    TTTConnectionStateReconnecting = 4,
    /** 网络连接失败 */
    TTTConnectionStateFailed = 5,
};

/**  录音音质 */
typedef NS_ENUM(NSUInteger, TTTAudioRecordQuality) {
    /** 10 分钟的文件大小为 2.4M 左右 */
    TTTAudioRecordQualityLow = 0,
    /** 10 分钟的文件大小为 3.6M 左右 */
    TTTAudioRecordQualityMedium = 1,
    /** 10 分钟的文件大小为 4.8M 左右 */
    TTTAudioRecordQualityHigh = 2,
};

/** 视频设备类型 */
typedef NS_ENUM(NSUInteger, TTTVideoType) {
    TTTVideoTypeVideo      = 0,
    TTTVideoTypeScreen     = 1,
    TTTVideoTypeFile       = 2,
    TTTVideoTypeVideoMixer = 3,
    TTTVideoTypeCamera     = 4
};

/** 连麦主播离开原因 */
typedef NS_ENUM(NSUInteger, TTTRtcAnchorExitReason) {
    TTTRtc_AnchorExit_Unlink    = 0, // 其他主播结束与“我”连麦，正常离开
    TTTRtc_AnchorExit_Timeout   = 1, // 心跳超时断开
    TTTRtc_AnchorExit_LinkClose = 2, // 网络异常断开
} __deprecated;


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
/** 编码的码率(kbps) */
@property (assign, nonatomic) NSUInteger encodedBitrate;
/** 发送的码率(kbps) */
@property (assign, nonatomic) NSUInteger sentBitrate;
/** 发送的帧率(fps) */
@property (assign, nonatomic) NSUInteger sentFrameRate;
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
@property (strong, nonatomic) NSMutableArray *regions;
/** 应用程序自定义的数据 */
@property (copy, nonatomic) NSString *mExtInfos;
/** cdn推流地址,多个cdn推理地址必传参数 */
@property (copy, nonatomic) NSString *rtmpUrl;
@end

/** 直播推流配置 */
@interface TTTPublisherConfiguration : NSObject
/** 旁路直播输出码流的码率。默认设置为 500 Kbps */
@property (assign, nonatomic) NSInteger bitrate;
/** 合图推流地址 */
@property (copy, nonatomic) NSString *publishUrl;
/** 推送纯音频流 */
@property (assign, nonatomic) BOOL isPureAudio;

@end

/** 直播推流配置生成器 */
@interface TTTPublisherConfigurationBuilder : NSObject

- (TTTPublisherConfigurationBuilder *)setBitrate:(NSInteger)bitrate;
- (TTTPublisherConfigurationBuilder *)setPublisherUrl:(NSString *)url;
- (TTTPublisherConfigurationBuilder *)setPublishPureAudio:(BOOL)isPureAudio;
- (TTTPublisherConfiguration *)build;

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
@property (assign, nonatomic) int rotation;
/** 0, 90, 180, 270 */
@property (copy, nonatomic) NSString *deviceId;
/** 视频帧ID */
@property (assign, nonatomic) NSUInteger frameID;

@end

/** 聊天信息 */
@interface TTTRtcChatInfo : NSObject
/** 聊天类型 */
@property (assign, nonatomic) TTTRtcChatType chatType;
/** 唯一标识 */
@property (copy, nonatomic) NSString *seqID;
/** 聊天内容 */
@property (copy, nonatomic) NSString *chatData;
/** 音频时长（单位“秒”，chatType为“Audio”） */
@property (assign, nonatomic) NSUInteger audioDuration;

@end


@protocol TTTRtcEngineDelegate;

@interface TTTRtcEngineKit : NSObject

/** 应用ID，由连麦平台分配，用于区分不同的客户和应用 */
@property (nonatomic, copy) NSString *appID;

/**  SDK回调对象，由调用方赋值 */
@property (nonatomic, weak) id<TTTRtcEngineDelegate> delegate;

/** 音视频信息统计间隔（默认：2秒） */
@property (nonatomic, assign) NSUInteger statsInterval;


@property (nonatomic, readonly) NSString *defaultVideoDeviceID;

#if TARGET_OS_OSX

/**
 *  视频采集设备
 */
@property (nonatomic, weak) AVCaptureDevice *videoCaptureDevice;

/**
 *  音频采集设备
 */
@property (nonatomic, weak) TTTRtcAudioDevice *audioCaptureDevice;

/**
 *  音频输出设备
 */
@property (nonatomic, weak) TTTRtcAudioDevice *audioPlayoutDevice;

#endif

/**
 *  初始化SDK，加载资源。
 *
 *  @param appId        应用ID，由连麦平台分配，用于区分不同的客户和应用，在同一个连麦平台内保证唯一。
    可以通过([TTTRtcEngineKit.appID])设置新的appID
 *
 *  @param delegate     SDK回调代理, 可以通过([TTTRtcEngineKit.delegate])设置新的代理
 *  @param enableChat   打开发送聊天功能
 *  @param enableSignal 打开发送信令功能
 *
 *  @return TTTRtc 对象(单例)
 */
+ (instancetype)sharedEngineWithAppId:(NSString *)appId delegate:(id<TTTRtcEngineDelegate>)delegate
                           enableChat:(BOOL)enableChat enableSignal:(BOOL)enableSignal;

+ (instancetype)sharedEngineWithAppId:(NSString *)appId delegate:(id<TTTRtcEngineDelegate>)delegate;

/**
 *  销毁引擎实例
 */
+ (void)destroy;

/**
 *  获取SDK版本号
 */
+ (NSString *)getSdkVersion;

/**
 *  设置服务器地址
 *
 *  @param ip   ip地址或域名
 *  @param port 端口
 */
- (void)setServerIp:(NSString*)ip port:(int)port;

/**
 *  同房间多主播
 *  在加入房间之前调用，若启用该功能，允许房间内进入多个主播
 *
 *  @param enable YES: 同房间可有多个主播 NO: 同一房间只能有一个主播
 */
- (void)enableCrossRoom:(BOOL)enable;

/**
 *  设置频道模式
 *  加入房间之前设置，在房间内不能做修改。设置该方法之后再设置角色([TTTRtcEngineKit setClientRole:])
 *
 *  @param profile 频道模式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setChannelProfile:(TTTRtcChannelProfile)profile;

/**
 *  设置或切换用户角色
 *  加入房间前要确定用户角色，在加入房间的过程中不能修改角色。
 *  加入房间成功之后，副播和观众可以相互切换，角色切换成功之后才能进行下一次切换，切换角色成功的回调 ([TTTRtcEngineDelegate rtcEngine:didClientRoleChangedOfUid:role:])。
 *  切换角色SDK会对用户的音视频权限做对应调整，不需要调用额外接口
 *
 *  @param role          直播场景里的用户角色
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setClientRole:(TTTRtcClientRole)role;

/**
 *  设置视频编码属性
 *  选择SDK标准的视频编码属性，自定义同过([TTTRtcEngineKit setVideoProfile:frameRate:bitRate:])
 *  本地预览尺寸不等同于编码尺寸
 *
 *  @param profile            每个Profile对应一套视频参数，如分辨率、帧率、码率等。
 *  @param swapWidthAndHeight 竖屏模式下需要交换宽高，横屏不需要
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setVideoProfile:(TTTRtcVideoProfile)profile swapWidthAndHeight:(BOOL)swapWidthAndHeight;

/**
 *  自定义视频编码属性
 *
 *  @param videoSize 视频分辨率，竖屏模式下需要交换宽高，横屏不需要
 *  @param frameRate 视频帧率
 *  @param bitRate   视频码率
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setVideoProfile:(CGSize)videoSize frameRate:(NSUInteger)frameRate bitRate:(NSUInteger)bitRate;

/**
 *  加入通话频道
 *
 *  @param channelKey        此为程序生成的ChannelKey(token), 用于SDK鉴权
 *  @param channelName       标识通话的频道名称，使用可转换大于0的long long类型纯数字字符串
 *  @param uid               用户ID
 *  @param joinSuccessBlock  用户加入成功回调, 优先级高于([TTTRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]), 实现block, 回调不会被调用
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)joinChannelByKey:(NSString *)channelKey
            channelName:(NSString *)channelName
                    uid:(int64_t)uid
            joinSuccess:(void(^)(NSString *channel, int64_t uid, NSInteger elapsed))joinSuccessBlock;

/**
 *  离开房间
 *
 *  @param leaveChannelBlock 成功离开房间的回调，优先级高于([TTTRtcEngineDelegate rtcEngine:didLeaveChannelWithStats:]), 实现block, 回调不会被调用
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)leaveChannel:(void(^)(TTTRtcStats *stats))leaveChannelBlock;

/**
 *  更新channelKey
 *  当房间内的channelKey(token)即将过期([TTTRtcEngineDelegate rtcEngine:channelKeyPrivilegeWillExpire:])
 *  通过该方法更新新的channelKey(token), 更新失败([TTTRtcEngineDelegate rtcEngine:didOccurError:])(TTTRtc_Error_InvalidChannelKey)
 *
 *  @param channelKey 此为程序生成的ChannelKey(token)
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)renewChannelByKey:(NSString *)channelKey;

/**
 * 获取网络连接状态
 */
- (TTTConnectionState)getConnectionState;

/**
 *  开启视频模式。
 *  默认开启，可以在加入频道前或者通话中调用，在通话中调用则由音频模式切换为视频模式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableVideo;

/**
 *  关闭视频，开启纯音频模式。
 *  可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启纯音频模式，在通话中调用则由视频模式切换为纯音频频模式。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)disableVideo;

/**
 *  禁用/启用本地视频功能
 *  该方法用于只看不发的视频场景，不需要本地有摄像头。
 *
 *  @param enabled YES: 启用本地视频（默认），NO: 禁用本地视频。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableLocalVideo:(BOOL)enabled;

/**
 *  暂停/恢复发送本地视频流。该方法用于允许/禁止往网络发送本地视频流。
 *
 *  @param mute YES: 暂停发送本地视频流，NO: 恢复发送本地视频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteLocalVideoStream:(BOOL)mute;

/**
 *  启动本地视频预览
 *  上行视频用户需要打开该功能，必须和([TTTRtcEngineKit stopPreview])一一对应
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startPreview;

/**
 *  停止本地视频预览
 *  尽量和([TTTRtcEngineKit startPreview])保持一一对应，退出房间后可多次调用
 *  在房间内如果调用大于预览的次数会导致预览关闭无法上行视频
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopPreview;

/**
 *  设置本地视频显示属性
 *
 *  @param local 本地视频显示属性
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setupLocalVideo:(TTTRtcVideoCanvas*)local;

/**
 *  设置远端视频显示属性
 *
 *  @param remote 远端视频显示属性
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setupRemoteVideo:(TTTRtcVideoCanvas*)remote;

/**
 *  设置使用混频模式
 *
 *  @param enable YES: 使用混频模式 NO: 关闭混频模式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableVideoMixer:(BOOL)enable;

/**
 *  设置远端混频显示属性
 *
 *  @param remote 远端视频混频显示属性, nil: 表示关闭混频
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setupRemoteVideoMixer:(TTTRtcVideoMixerCanvas *)remote;

#if TARGET_OS_IOS
/*
 * 设置美颜效果
 * 参数是全局的，退出房间不会修改参数的值
 *
 * @param enable YES: 开启美颜， NO: 关闭美颜
 *
 * @param beautyLevel: 默认0.5, 0.0~1.0
 *
 * @param brightLevel: 默认0.5, 0.0~1.0
 */
- (void)setBeautyFaceStatus:(BOOL)enable beautyLevel:(CGFloat)beautyLevel brightLevel:(CGFloat)brightLevel;

/*
 * 设置水印
 * 水印的大小位置以及透明度均由view自身属性制定, 视图显示位置需要按照采集大小(640x360, 960x540, 1280x720)来设置
 * 注意：由于渲染模式不同也会出现显示位置的偏差
 *
 * @param view: 非空显示视图水印，nil清除水印，
 */
- (void)setWaterMarkView:(TView *)view;
#elif TARGET_OS_OSX
/**
 *  添加本地视频水印
 *  当前只支持添加一个水印，后添加的水印会替换掉之前添加的水印
 *
 *  @param imageURL 待添加的水印图片地址
 *  @param rect     图片在视频帧上的位置和大小
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)addVideoWatermark:(NSURL *)imageURL rect:(CGRect)rect;

/**
 *  删除已添加的视频水印
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)clearVideoWatermarks;
#endif

/**
 *  是否设置水印
 *
 *  @return YES: 是，NO: 否。
 */
- (BOOL)isVideoWatermarkEnabled;

#if TARGET_OS_IOS
/**
 *  切换摄像头
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)switchCamera;

/**
 *  是否前置摄像头
 */
- (BOOL)isCameraPositionFront;

/**
*  设置前置摄像头镜像
*  默认开启，参数是全局的，退出房间不会修改参数的值
*
*  @param mirror YES: 开启镜像，NO: 关闭镜像。
*
*  @return 0: 方法调用成功，<0: 方法调用失败。
*/
- (int)setVideoMirrored:(BOOL)mirror;

/**
 *  设置远端用户看视频镜像
 *  对应本地预览结果进行镜像，包含前后摄像头
 *
 *  @param mirror YES: 开启镜像，NO: 关闭镜像。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setRemoteVideoMirrored:(BOOL)mirror;

/**
 *  闪光灯操作
 */
- (BOOL)isCameraTorchSupported;
- (int)setCameraTorchOn:(BOOL)isOn;

/**
 *  摄像头缩放比例
 */
- (CGFloat)cameraMaxZoomFactor;
- (int)setCameraZoomFactor:(CGFloat)zoom;

/**
 *  手动曝光[0~1][0~1]
 *  SDK内部采集分辨率大小分为3档 640x360 960x540 1280x720,
 *  设置大小时保证设置的点对应采集的尺寸相应的位置
 */
- (BOOL)isCameraExposurePointOfInterestSupported;
- (int)setCameraExposurePointOfInterest:(CGPoint)point;

/**
 *  手动对焦位置，并触发对焦 [0~1][0~1]
 *  SDK内部采集分辨率大小分为3档 640x360 960x540 1280x720,
 *  设置大小时保证设置的点对应采集的尺寸相应的位置
 */
- (BOOL)isCameraFocusPointOfInterestSupported;
- (int)setCameraFocusPointOfInterest:(CGPoint)point;

#elif TARGET_OS_OSX

/**
 *  获取视频采集设备（摄像头）
 *
 *  @return 视频采集设备数组
 */
- (NSArray<AVCaptureDevice *> *)videoCaptureDevices;

/**
 *  获取音频采集设备（麦克风）
 *
 *  @return 音频采集设备数组
 */
- (NSArray<TTTRtcAudioDevice *> *)audioCaptureDevices;

/**
 *  获取音频输出设备（扬声器）
 *
 *  @return 音频输出设备数组
 */
- (NSArray<TTTRtcAudioDevice *> *)audioPlayoutDevices;

#endif

/**
 *  暂停/恢复所有远端视频流
 *
 *  @param mute YES: 停止播放接收到的所有视频流，NO: 允许播放接收到的所有视频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteAllRemoteVideoStreams:(BOOL)mute;

/**
 *  允许/禁止播放指定的远端视频流
 *
 *  @param uid   用户ID
 *  @param mute  YES: 停止播放接收到的视频流，NO: 允许播放接收到的视频流。
 *  @param devId 设备id(远端用户多设备)
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteVideoStream:(int64_t)uid mute:(BOOL)mute deviceId:(NSString *)devId;

/**
 *  静音/取消静音
 *  允许/禁止往网络发送本地音频流
 *
 *  @param mute YES: 麦克风静音, NO: 取消静音。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteLocalAudioStream:(BOOL)mute;

/**
 *  调节本地说话音量
 *
 *  @param volume 音量范围为0~500。默认100为原始音量
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustAudioMixingSoloVolume:(NSInteger)scale;

/**
*  调节播放人声的音量
*
*  @param volume 音量范围为0~500。默认100为原始音量
*
*  @return 0: 方法调用成功，<0: 方法调用失败。
*/
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;

/**
 *  静音所有远端音频/对所有远端音频取消静音
 *  允许/禁止播放远端用户的音频流，即对所有远端用户进行静音与否。
 *
 *  @param mute YES: 停止播放所接收的音频流, NO: 恢复播放所接收的音频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/**
 *  静音指定远端用户/对指定远端用户取消静音
 *  允许/禁止播放远端用户的音频流。
 *
 *  @param mute YES: 停止播放指定用户的音频流, NO: 恢复播放指定用户的音频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteAudioStream:(int64_t)uid mute:(BOOL)mute;

/**
 *  禁言指定远端用户/对指定远端用户取消禁言
 *
 *  @param mute YES: 禁止发言, NO: 允许发言。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteSpeaking:(int64_t)uid mute:(BOOL)mute;

/**
 *  停止/恢复远端用户音频混流到rtmp
 *
 *  @param uid     用户ID
 *  @param mute    YES: 停止混音频流, NO: 恢复混音频流。
 *  @param rtmpUrl rtmp推流地址, 推单路流可设置为nil
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteRtmpAudioStream:(int64_t)uid mute:(BOOL)mute rtmpUrl:(NSString *)rtmpUrl;

/**
 * 启用/禁用硬件回声消除
 * 加入房间之后调用，默认启用
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableHWAEC:(BOOL)enable;

/**
 * 启用/禁用软件回声消除
 * 针对于部分硬件消除不起作用的iPhone设备，默认不开启
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableSoftAEC:(BOOL)enable;

/**
 *  打开/关闭耳返功能
 *  在插入耳机的情况下有效
 *
 *  @param enable YES: 打开耳返功能，NO: 关闭耳返功能。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioEarBack:(BOOL)enable;

/**
 *  设置耳返音量
 *  在打开耳返的情况下有效
 *
 *  @param volume 设置耳返音量，取值范围在 [0,100] 默认值为 100
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setAudioEarBackVolume:(NSUInteger)volume;

/**
 *  是否打开耳返
 *
 *  @return YES: 耳返是打开状态，NO: 耳返是关闭状态。
 */
- (BOOL)isAudioEarBackEnabled;

/**
 *  启用/关闭本地音频和远端音频数据回调
 *  本地音频裸数据回调([TTTRtcEngineDelegate rtcEngine:localAudioData:dataSize:sampleRate:channels:])
 *  远端用户混音数据回调([TTTRtcEngineDelegate rtcEngine:remoteAudioData:dataSize:sampleRate:channels:])
 *
 *  @param enableLocal YES: 获取本地音频数据，NO: 关闭获取本地音频数据。
 *
 *  @param enableRemote YES: 获取远端音频数据，NO: 关闭获取远端音频数据。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioDataReport:(BOOL)enableLocal remote:(BOOL)enableRemote;

#if TARGET_OS_IOS

/**
 *  切换音频路由
 *  在插入耳机或蓝牙耳机状态下，不建议调用该接口
 *
 *  @param enableSpeaker YES: 音频输出至扬声器，NO: 语音会根据默认路由出声。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/**
 *  是否是扬声器状态
 *
 *  @return YES: 表明输出到扬声器，NO: 表明输出到非扬声器(听筒，耳机等)。
 */
- (BOOL)isSpeakerphoneEnabled;

/**
 *  设置默认的语音路由
 *
 *  @param defaultToSpeaker YES: 从扬声器出声，NO: 从听筒出声
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setDefaultAudioRouteToSpeakerphone:(BOOL)defaultToSpeaker;

#endif

/**
 *  启用说话者音量提示
 *  音量回调([TTTRtcEngineDelegate rtcEngine:reportAudioLevel:audioLevel:audioLevelFullRange:])
 *
 *  @param interval 指定音量提示的时间间隔（<=0: 禁用音量提示功能；>0: 提示间隔，单位为毫秒。建议设置到大于200毫秒。）
 *  @param smooth   平滑系数。默认可以设置为3。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval smooth:(NSInteger)smooth;

/**
 *  设置日志文件
 *  正式发版或上线不建议设置该路径，有需求的用户需要管理日志文件
 *
 *  @param filePath 日志文件的完整路径。该日志文件为UTF-8编码。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setLogFile:(NSString *)filePath;

/**
 *  设置日志文件过滤器
 *
 *  @param filter 日志过滤器
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setLogFilter:(TTTRtcLogFilter)filter;

/**
 *  往日志文件中增加自定义日志
 *  进入房间后才可使用
 *
 *  @param log 日志内容
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)addLog:(NSString *)log;

/**
 *  设置信令超时时间
 *  默认90s, 设置时长需要大于20s
 *
 *  @param seconds 超时时间（秒）
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setSignalTimeout:(NSUInteger)seconds;

/**
 *  设置音频编码选项
 *
 *  @param codecType 音频编码格式
 *  @param bitrate   码率
 *  @param channels  声道
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setPreferAudioCodec:(TTTRtcAudioCodecType)codecType bitrate:(int)bitrate channels:(int)channels;

/**
 *  配置旁路直播推流
 *  在加入房间前设置，具体参数参考直播demo
 *
 *  @param config 直播推流配置
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)configPublisher:(TTTPublisherConfiguration *)config;

/**
 *  设置画中画布局
 *  控制cdn各路视频在混频的位置，大小
 *
 *  @param layout 画中画布局
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setVideoCompositingLayout:(TTTRtcVideoCompositingLayout*)layout;

/**
 *  配置外部视频源
 *  如果使用外部视频源，在“enableVideo/startPreview”之前调用本API。
 *
 *  @param enable     是否使用外部视频源
 *  @param useTexture 是否使用 Texture 作为输入
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setExternalVideoSource:(BOOL)enable useTexture:(BOOL)useTexture;

/**
 *  推送外部视频帧
 *
 *  @param videoFrame 包含待编码数据的视频帧
 *
 *  @return YES: 该帧推送成功，NO: 该帧推送失败。
 */
- (BOOL)pushExternalVideoFrame:(TTTRtcVideoFrame *)videoFrame;

/**
 *  推送外部音频数据
 *  仅对于KTV场景有效
 *
 *  @param data 音频数据
 *
 *  @return YES: 推送成功，NO: 推送失败。
 */
- (BOOL)pushExternalAudioData:(NSData *)data;

/**
 *  设置本地视频帧采集格式
 *  加入房间前设置，默认格式(TTTRtc_VideoFrameFormat_BGRA),输出data数据
 *  视频帧回调([rtcEngine:localVideoFrameCaptured:videoFrame:])
 *  如果做外部美颜，设置(TTTRtc_VideoFrameFormat_Texture)输出BGRA格式CVPixelBufferRef
 *
 *  @param format                     视频帧的格式
 *  @param isVideoSizeSameWithProfile 采集的视频尺寸是否和VideoProfile相同，iPhone用户设置为NO
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setLocalVideoFrameCaptureFormat:(TTTRtcVideoFrameFormat)format isVideoSizeSameWithProfile:(BOOL)isVideoSizeSameWithProfile;

/**
 *  设置远端视频帧输出格式
 *  加入房间前设置，默认格式(TTTRtc_VideoFrameFormat_NV12),输出data数据
 *  视频帧回调([rtcEngine:remoteVideoFrameDecodedOfUid:videoFrame:])
 *
 *  @param format 视频帧的格式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setRemoteVideoFrameOutputFormat:(TTTRtcVideoFrameFormat)format;

/**
 *  开始客户端本地混音
 *  默认支持本地、网络mp3格式音乐文件
 *  对于播放通话开始或结束提示音，可以使用该接口，结束需要调用([TTTRtcEngineKit stopAudioMixing])
 *  播放开始([TTTRtcEngineDelegate rtcEngineAudioMixingDidStart:])
 *  播放结束([TTTRtcEngineDelegate rtcEngineAudioMixingDidFinish:])
 *
 *  @param filePath 指定需要混音的本地音频文件名和文件路径
 *  @param loopback YES: 只有本地可以听到混音后的音频流，NO: 本地和对方都可以听到混音后的音频流。
 *  @param cycle    指定音频文件循环播放的次数, 0:无限循环
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startAudioMixing:(NSString *)filePath loopback:(BOOL)loopback cycle:(NSInteger)cycle;

/**
 *  停止客户端本地混音
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopAudioMixing;

/**
 *  暂停播放伴奏
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)pauseAudioMixing;

/**
 *  恢复播放伴奏
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)resumeAudioMixing;

/**
 *  调节伴奏本地播放音量
 *
 *  @param volume 伴奏音量范围为0~100。默认100为原始文件音量。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustAudioMixingPlayoutVolume:(NSUInteger)volume;

/**
 *  调节伴奏远端播放音量
 *
 *  @param volume 伴奏音量范围为0~100。默认100为原始文件音量。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustAudioMixingPublishVolume:(NSUInteger)volume;

/**
 *  获取伴奏时长
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)getAudioMixingDuration;

/**
 *  获取伴奏播放进度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)getAudioMixingCurrentPosition;

/**
 *  拖动语音进度条
 *
 *  @param pos 进度条位置，单位为毫秒。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setAudioMixingPosition:(NSInteger)pos;

#pragma mark - 音效接口
- (double)getEffectsVolume;//0~1
- (int)setEffectsVolume:(double)volume;
- (int)setVolumeOfEffect:(int)soundId withVolume:(double)volume;
- (int)playEffect:(int)soundId filePath:(NSString *)filePath loopCount:(int)loopCount pitch:(double)pitch pan:(double)pan gain:(double)gain publish:(BOOL)publish;
- (int)stopEffect:(int)soundId;
- (int)stopAllEffects;
- (int)preloadEffect:(int)soundId filePath:(NSString *)filePath;
- (int)unloadEffect:(int)soundId;
- (int)pauseEffect:(int)soundId;
- (int)pauseAllEffects;
- (int)resumeEffect:(int)soundId;
- (int)resumeAllEffects;

/**
 *  踢出房间
 *  直播模式(TTTRtc_ClientRole_Anchor)调用有效
 *
 *  @param uid 被踢者uid
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)kickChannelUser:(int64_t)uid;

/**
 *  发送聊天消息
 *
 *  @param userID   用户ID
 *  @param chatType 聊天消息类型
 *  @param seqID    唯一标识
 *  @param data     消息内容
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)sendChatMessageWithUserID:(int64_t)userID chatType:(TTTRtcChatType)chatType seqID:(NSString *)seqID data:(NSString *)data;

/**
 *  发送信令
 *
 *  @param userID 用户ID
 *  @param seqID  唯一标识
 *  @param data   信令内容
 */
- (int)sendSignalWithUserID:(int64_t)userID seqID:(NSString *)seqID data:(NSString *)data;

#if TARGET_OS_IOS

/**
 *  是否正在屏幕录制
 *
 *  @return YES: 是，NO: 否。
 */
- (BOOL)isScreenRecording;

/**
 *  开始录制屏幕用作视频源
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startRecordScreen NS_AVAILABLE_IOS(11_0);

/**
 *  开始录制屏幕并保存
 *
 *  @param path   保存路径，如果值为nil，保存到系统相册。
 *  @param width  视频宽度
 *  @param height 视频高度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startRecordScreenAndSave:(NSString *)path width:(NSInteger)width height:(NSInteger)height NS_AVAILABLE_IOS(11_0);

/**
 *  停止录制屏幕
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopRecordScreen;

#endif

/**
 *  开始RTMP推流
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startRtmpPublish:(NSString *)rtmpUrl;

/**
 *  停止RTMP推流
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopRtmpPublish;

/**
 *  暂停RTMP推流
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)pauseRtmpPublish;

/**
 *  恢复RTMP推流
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)resumeRtmpPublish;

/**
 * 向h.264码流中插入sei内容
 *
 * @param content 字符串内容
 *
 * @return 0:成功
 */
- (int)insertH264SeiContent:(NSString*)content;

/**
 *  设置是否启用视频双流模式
 *
 *  @param enabled 是否启用视频双流模式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableDualStreamMode:(BOOL)enabled;

/**
 *  设置视频大小流
 *  如果远端用户选择发送双流(视频大流和小流), 该方法指定接收远端用户的视频流大小。
 *
 *  @param uid        用户ID
 *  @param streamType 视频流类型
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setRemoteVideoStream:(int64_t)uid type:(TTTRtcVideoStreamType)streamType;

/**
 *  设置默认订阅的视频流类型
 *
 *  @param streamType 视频流类型
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setRemoteDefaultVideoStreamType:(TTTRtcVideoStreamType)streamType;

/**
 *  设置CDN推流视频参数
 *  在加入房间之前调用。
 *  单主播：H264格式，不设置背景图，接口参数不起作用
 *  单主播：H265格式或设置背景图，转推cdn使用接口参数
 *  主播连麦：分辨率使用([TTTRtcVideoCompositingLayout.canvasWidth])和([TTTRtcVideoCompositingLayout.canvasHeight])，帧率和码率使用接口参数
 *
 *  @param videoSize      视频分辨率, 默认352x640
 *  @param videoFrameRate 视频帧率, 默认15
 *  @param videoBitRate   视频码率, 默认750
 *
 */
- (void)setVideoMixerParams:(CGSize)videoSize videoFrameRate:(NSUInteger)videoFrameRate videoBitRate:(NSUInteger)videoBitRate;

/**
 *  设置CDN推流音频参数
 *
 *  @param samplerate 采样率 8000 ,16000 ,24000, 32000 , 44100 ,48000
 *  @param channels   1单声道，2双声道
 *
 */
- (void)setAudioMixerParams:(NSUInteger)samplerate channels:(NSUInteger)channels;

/**
 *  设置混屏背景图片
 *  在加入房间之前调用rtmpUrl设置为nil。
 *  加入房间之后推单路cdn流可以设置nil或者对应推流地址，推多路流必须设置对应cdn推流地址
 *
 *  @param url     背景图片所在的地址
 *  @param rtmpUrl 背景图对应的cdn推流地址
 */
- (void)setVideoMixerBackgroundImgUrl:(NSString *)url forRtmpUrl:(NSString *)rtmpUrl;

/**
 *  开启网络质量检测
 *  对应回调([TTTRtcEngineDelegate rtcEngine:lastmileQuality:])
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableLastmileTest;

/**
 *  关闭网络质量检测
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)disableLastmileTest;

/**
 *  订阅其它房间主播视频
 *  订阅成功([TTTRtcEngineDelegate rtcEngine:didJoinedOfUid:clientRole:isVideoEnabled:elapsed:]), 其它房间主播以副播身份加入本房间
 *  其它主播退出房间，自己退房间都必须取消订阅([TTTRtcEngineKit subscribeOtherChannel:])
 *
 *  @param channelId 其它房间id
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)subscribeOtherChannel:(int64_t)channelId;

/**
 *  取消订阅其它房间主播视频
 *
 *  @param channelId 其它房间Id
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)unSubscribeOtherChannel:(int64_t)channelId;

/**
 *  更新rtmp推流地址
 *  收到([TTTRtcEngineDelegate rtcEngine:reportRtmpStatus:rtmpUrl:])失败，可以更新一个新的推流地址
 *
 *  @param url rtmp流地址
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)updateRtmpUrl:(NSString *)url;

/**
 *  开始客户端录音
 *  录音房间内所有用户的声音，建议在加入房间后开启
 *
 *  @param filePath 录音文件的本地保存路径: xxx/.../xxx.aac
 *  @param quality  录音质量
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startAudioRecording:(NSString *)filePath quality:(TTTAudioRecordQuality)quality;

/**
 *  停止客户端录音
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopAudioRecording;

/**
 *  配置外部音频源
 *  在加入房间之前开启, 开启该功能需要同时做采集和播放。
 *  音频路由相关需要开发者自己控制
 *
 *  @param enable      是否启用外部音频源
 *  @param sampleRate  外部音频源的采样率
 *  @param channels    外部音频源的通道数
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setExternalAudioSource:(BOOL)enable sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  推送外部音频采集数据
 *
 *  @param data        PCM数据
 *  @param len         PCM数据长度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)pushExternalAudioFrame:(int8_t *)data length:(int)len;

/**
 *  拉取音频播放数据
 *  外置音频源前提下，拉取用于渲染的数据
 *
 *  @param data        PCM数据
 *  @param len         PCM数据长度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)pullRenderingAudioFrame:(int8_t *)data length:(int)len;

/**
 *  停止/恢复音频采集和播放
 *
 *  @param stop  YES: 停止采集和播放  NO: 恢复采集和播放
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
*/
- (int)stopAudioPlayAndRecord:(BOOL)stop;

/**
 *  设置录制的声音格式
 *  回调([TTTRtcEngineDelegate rtcEngine:localAudioData:dataSize:sampleRate:channels:])
 *  如果只需要本地采集音频裸数据可以使用([TTTRtcEngineKit enableAudioDataReport:remote:])
 *
 *  @param sampleRate     采样率，建议设置为AVAudioSession.sharedInstance.sampleRate
 *  @param channel        声道数，可设置：1或2
 *  @param samplesPerCall 采样点数，建议设置：1024或2048
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setRecordingAudioFrameParametersWithSampleRate:(NSInteger)sampleRate channel:(NSInteger)channel samplesPerCall:(NSInteger)samplesPerCall;

/**
 *  设置播放的声音格式
 *  回调([TTTRtcEngineDelegate rtcEngine:remoteAudioData:dataSize:sampleRate:channels:])
 *  如果只需要远端用户音频裸数据可以使用([TTTRtcEngineKit enableAudioDataReport:remote:])
 *
 *  @param sampleRate     采样率，建议设置为AVAudioSession.sharedInstance.sampleRate
 *  @param channel        声道数，可设置：1或2
 *  @param samplesPerCall 采样点数，建议设置：1024或2048
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setPlaybackAudioFrameParametersWithSampleRate:(NSInteger)sampleRate channel:(NSInteger)channel samplesPerCall:(NSInteger)samplesPerCall;

/**
 *  设置录制和播放声音混音后的数据格式
 *  回调([TTTRtcEngineDelegate rtcEngine:mixAudioData:dataSize:sampleRate:channels:])
 *
 *  @param sampleRate     采样率
 *  @param channel        声道数，可设置：1或2
 *  @param samplesPerCall 采样点数，建议设置：1024或2048
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setMixedAudioFrameParametersWithSampleRate:(NSInteger)sampleRate channel:(NSInteger)channel samplesPerCall:(NSInteger)samplesPerCall;

/**
 *  增加一路cdn推流地址
 *  在加入房间成功后设置，成功回调([TTTRtcEngineDelegate rtcEngine:rtmpStreamingCreated:])
 *  然后可通过([TTTRtcVideoCompositingLayout.rtmpUrl])设置对应布局，
 *  也可设置对应的背景图([TTTRtcEngineKit setVideoMixerBackgroundImgUrl:forRtmpUrl:])
 *
 *  @param url cdn推流地址
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)addPublishStreamUrl:(NSString *)url;

/**
*  删除一路cdn推流地址
*  在加入房间成功后设置
*
*  @param url cdn推流地址
*
*  @return 0: 方法调用成功，<0: 方法调用失败。
*/
- (int)removePublishStreamUrl:(NSString *)url;

/**
*  发送歌词
*
*  @param lyric 歌词内容
*
*  @return 0: 方法调用成功，<0: 方法调用失败。
*/
- (int)sendAudioLyric:(NSString *)lyric;

/**
 *  获取Akamai的拉流地址
 *
 *  @param appID     应用ID，由连麦平台分配
 *  @param channelId 房间ID
 *  @param handler   获取的结果
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
+ (int)getAkamai:(NSString *)appID channel:(NSString *)channelId completionHandler:(void(^)(NSError *error, NSString *serverid))handler;

#pragma mark - deprecated API
- (void)setVideoMixerBackgroundImgUrl:(NSString*)url DEPRECATED_MSG_ATTRIBUTE("use setVideoMixerBackgroundImgUrl:forRtmpUrl: instead");
- (int)adjustAudioMixingVolume:(NSInteger)volume DEPRECATED_MSG_ATTRIBUTE("use adjustAudioMixingPlayoutVolume: instead");

- (int)muteRemoteVideoStream:(int64_t)uid mute:(BOOL)mute DEPRECATED_MSG_ATTRIBUTE("use muteRemoteVideoStream:mute:deviceId: instead");
- (int)setHighQualityAudioParametersWithFullband:(BOOL)fullband stereo:(BOOL)stereo fullBitrate:(BOOL)fullBitrate DEPRECATED_MSG_ATTRIBUTE("use setPreferAudioCodec:bitrate:channels: instead");

- (int)linkOtherAnchor:(int64_t)sessionID userID:(int64_t)userID DEPRECATED_MSG_ATTRIBUTE("use subscribeOtherChannel: instead");
- (int)unlinkOtherAnchor:(int64_t)sessionID userID:(int64_t)userID DEPRECATED_MSG_ATTRIBUTE("use unSubscribeOtherChannel: instead");
@end

/**
 *  SDK回调代理，由调用方实现。
 */
@protocol TTTRtcEngineDelegate <NSObject>

@optional

/**
 *  发生错误回调
 *  SDK上报的错误意味着SDK无法自动恢复，需要应用程序干预或提示用户。
 *
 *  @param errorCode 错误代码
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didOccurError:(TTTRtcErrorCode)errorCode;

/**
 *  网络连接丢失回调, 提示用户网络异常。
 *  SDK会自动重连，重连失败([TTTRtcEngineDelegate rtcEngineReconnectServerTimeout:])
 *  重连成功([TTTRtcEngineDelegate rtcEngineReconnectServerSucceed:])
 */
- (void)rtcEngineConnectionDidLost:(TTTRtcEngineKit *)engine;

/**
 *  网络重连失败
 *  网络异常断开后，将尝试重连, 默认90s, 可通过([TTTRtcEngineKit setSignalTimeout:])设置
 *  在重连时间范围内无法连接上服务器触发该回调，需要调用([TTTRtcEngineKit leaveChannel:])
 *  若在重连时间范围外才重连上服务器，服务器将会拒绝，其房间状态将不可用。
 */
- (void)rtcEngineReconnectServerTimeout:(TTTRtcEngineKit *)engine;

/**
 *  重连成功
 *  重连成功之后SDK所有状态恢复
 */
- (void)rtcEngineReconnectServerSucceed:(TTTRtcEngineKit *)engine;

/**
 *  网络连接状态发生改变
 *  也可使用([TTTRtcEngineKit getConnectionState])获取SDK网络连接状态
 *
 *  @param state 当前网络连接状态
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine connectionChangedToState:(TTTConnectionState)state;

/**
 *  加入频道成功回调
 *
 *  @param channel 频道名
 *  @param uid     用户ID
 *  @param elapsed 从joinChannel开始到该事件产生的延迟（毫秒）
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didJoinChannel:(NSString*)channel withUid:(int64_t)uid elapsed:(NSInteger) elapsed;

/**
 *  成功离开频道的回调
 *
 *  @param stats 统计数据
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didLeaveChannelWithStats:(TTTRtcStats *)stats;

/**
 *  用户加入回调
 *
 *  @param uid            用户ID
 *  @param clientRole     用户角色
 *  @param isVideoEnabled 是否启用本地视频
 *  @param elapsed        加入频道开始到该回调触发的延迟（毫秒)
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didJoinedOfUid:(int64_t)uid clientRole:(TTTRtcClientRole)clientRole
    isVideoEnabled:(BOOL)isVideoEnabled elapsed:(NSInteger)elapsed;

/**
 *  用户离线回调
 *
 *  @param uid    用户ID
 *  @param reason 离线原因
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didOfflineOfUid:(int64_t)uid reason:(TTTRtcUserOfflineReason)reason;

/**
 *  用户被踢出回调
 *
 *  @param uid    用户ID
 *  @param reason 用户被踢出的原因
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didKickedOutOfUid:(int64_t)uid reason:(TTTRtcKickedOutReason)reason;

/**
 *  用户角色切换回调
 *
 *  @param uid  用户ID
 *  @param role 用户角色
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didClientRoleChangedOfUid:(int64_t)uid role:(TTTRtcClientRole)role;

/**
 *  禁止/允许用户发言回调
 *
 *  @param muted YES: 禁止发言，NO: 允许发言。
 *  @param uid   用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didSpeakingMuted:(BOOL)muted ofUid:(int64_t)uid;

/**
 *  用户音频静音回调
 *
 *  @param muted YES: 静音，NO: 取消静音。
 *  @param uid   用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didAudioMuted:(BOOL)muted byUid:(int64_t)uid;

/**
 *  音频输出路由发生变化
 *
 *  @param routing 当前音频输出路由
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didAudioRouteChanged:(TTTRtcAudioOutputRouting)routing;

/**
 *  用户启用/关闭视频回调
 *  远端用户通过([TTTRtcEngineKit enableLocalVideo:])触发该回调
 *
 *  @param enabled YES: 该用户已启用了视频功能，NO: 该用户已关闭了视频功能。
 *  @param uid     用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didVideoEnabled:(BOOL)enabled byUid:(int64_t)uid;

/**
 *  添加/删除视频设备(多流)
 *  远端用户通过([TTTRtcEngineKit enableLocalVideo:])触发该回调
 *
 *  @param enabled   YES: 该用户已启用了视频功能，NO: 该用户已关闭了视频功能。
 *  @param devId     设备Id
 *  @param videoType 设备类型
 *  @param uid       用户Id
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didVideoEnabled:(BOOL)enabled deviceId:(NSString *)devId videoType:(TTTVideoType)videoType byUid:(int64_t)uid;

/**
 *  RtcEngine统计数据回调
 *
 *  @param stats 通话相关的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine reportRtcStats:(TTTRtcStats *)stats;

/**
 *  本地视频统计回调
 *
 *  @param stats 本地视频的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine localVideoStats:(TTTRtcLocalVideoStats *)stats;

/**
 *  本地音频统计回调
 *
 *  @param stats 本地音频的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine localAudioStats:(TTTRtcLocalAudioStats *)stats;

/**
 *  远端视频统计回调
 *
 *  @param stats 远端视频的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine remoteVideoStats:(TTTRtcRemoteVideoStats *)stats;

/**
 *  远端音频统计回调
 *
 *  @param stats 远端音频的统计信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine remoteAudioStats:(TTTRtcRemoteAudioStats *)stats;

/**
 *  远端音频第一帧解码回调
 *
 *  @param uid 用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstAudioFrameDecoded:(int64_t)uid;

/**
 *  远端用户音量回调
 *  提示谁在说话及其音量，默认禁用。
 *  可通过([TTTRtcEngineKit enableAudioVolumeIndication:smooth:])方法设置。
 *
 *  @param userID              用户ID
 *  @param audioLevel          非线性区间[0,9]
 *  @param audioLevelFullRange 线性区间[0,32768]
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine reportAudioLevel:(int64_t)userID
       audioLevel:(NSUInteger)audioLevel audioLevelFullRange:(NSUInteger)audioLevelFullRange;

/**
 *  本端音频采集数据回调
 *
 *  @param data        PCM数据
 *  @param size        PCM数据长度
 *  @param sampleRate  采样率
 *  @param channels    声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine localAudioData:(char *)data dataSize:(NSUInteger)size sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  远端音频数据回调
 *
 *  @param data        音频数据
 *  @param size        数据长度
 *  @param sampleRate  采样率
 *  @param channels    声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine remoteAudioData:(char *)data dataSize:(NSUInteger)size sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  混音音频数据回调
 *  通过[([TTTRtcEngineKit setMixedAudioFrameParametersWithSampleRate:channel:samplesPerCall:])启用
 *
 *  @param data        音频数据
 *  @param size        数据长度
 *  @param sampleRate  采样率
 *  @param channels    声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine mixAudioData:(char *)data dataSize:(NSUInteger)size sampleRate:(NSUInteger)sampleRate channels:(NSUInteger)channels;

/**
 *  伴奏播放开始的回调
 */
- (void)rtcEngineAudioMixingDidStart:(TTTRtcEngineKit *)engine;

/**
 *  伴奏播放完成的回调
 */
- (void)rtcEngineAudioMixingDidFinish:(TTTRtcEngineKit *)engine;

/**
 *  音效播放完成的回调
 */
- (void)rtcEngineDidAudioEffectFinish:(TTTRtcEngineKit *)engine soundId:(NSInteger)soundId;

/**
 *  本地首帧视频显示回调
 *
 *  @param size    视频流尺寸（宽度和高度）
 *  @param elapsed 加入频道开始到该回调触发的延迟（毫秒)
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  远端首帧视频接收解码回调
 *
 *  @param uid     用户ID，指定是哪个用户的视频流
 *  @param devId   设备id
 *  @param size    视频流尺寸（宽度和高度）
 *  @param elapsed 加入频道开始到该回调触发的延迟（毫秒)
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstRemoteVideoFrameDecodedOfUid:(int64_t)uid deviceId:(NSString *)devId size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  已显示远端视频首帧回调
 *
 *  @param uid     用户ID，指定是哪个用户的视频流
 *  @param size    视频流尺寸（宽度和高度）
 *  @param elapsed 加入频道开始到该回调触发的延迟（毫秒)
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstRemoteVideoFrameOfUid:(int64_t)uid deviceId:(NSString *)devId size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  摄像头启用回调
 */
- (void)rtcEngineCameraDidReady:(TTTRtcEngineKit *)engine;

/**
 *  视频功能停止回调
 */
- (void)rtcEngineVideoDidStop:(TTTRtcEngineKit *)engine;

/**
 *  本地视频采集回调
 *  可做外部美颜(不能改变回调线程)，获取视频裸数据
 *  视频格式设置([TTTRtcEngineKit setLocalVideoFrameCaptureFormat:isVideoSizeSameWithProfile:])
 *
 *  @param videoFrame 视频帧
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine localVideoFrameCaptured:(TTTRtcVideoFrame *)videoFrame;

/**
 *  远端视频接收解码回调
 *  远端用户视频裸数据
 *  视频格式设置([TTTRtcEngineKit setRemoteVideoFrameOutputFormat:])
 *
 *  @param uid        用户ID，指定是哪个用户的视频流
 *  @param videoFrame 视频帧
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine remoteVideoFrameDecodedOfUid:(int64_t)uid videoFrame:(TTTRtcVideoFrame *)videoFrame;

/**
 *  设置SEI的回调
 *
 *  @param SEI JSON格式的SEI
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine onSetSEI:(NSString *)SEI;

/**
 *  设置画中画布局的回调
 *
 *  @param layout 画中画布局
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine onSetVideoCompositingLayout:(TTTRtcVideoCompositingLayout*)layout;

/**
 *  发送聊天消息的回调
 *
 *  @param chatInfo  聊天信息
 *  @param errorCode 错误代码
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine chatMessageSentOfChatInfo:(TTTRtcChatInfo *)chatInfo errorCode:(TTTRtcErrorCode)errorCode;

/**
 *  收到聊天消息的回调
 *
 *  @param userID   用户ID
 *  @param chatInfo 聊天信息
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine chatMessageReceivedOfUserID:(int64_t)userID chatInfo:(TTTRtcChatInfo *)chatInfo;

/**
 *  发送信令的回调
 *
 *  @param seqID     唯一标识
 *  @param errorCode 错误代码
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine signalSentOfSeqID:(NSString *)seqID data:(NSString *)data errorCode:(TTTRtcErrorCode)errorCode;

/**
 *  收到信令的回调
 *
 *  @param userID 用户ID
 *  @param seqID  唯一标识
 *  @param data   信令内容
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine signalReceivedOfUserID:(int64_t)userID seqID:(NSString *)seqID data:(NSString *)data;

/**
 *  直推RTMP推流回调
 *
 *  @param status RTMP推流状态
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine onStatusOfRtmpPublish:(TTTRtcRtmpPublishStatus)status;

/**
 *  RTMP推流回调
 *
 * @param status  成功或者失败
 * @param rtmpUrl 当前推流地址
 *
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine  reportRtmpStatus:(BOOL)status rtmpUrl:(NSString*)rtmpUrl;


- (void)rtcEngine:(TTTRtcEngineKit *)engine reportH264SeiContent:(NSString*)content uid:(int64_t)uid;

- (void)rtcEngineOnMediaSending:(TTTRtcEngineKit *)engine;

/**
 *  远端用户是否启用双流的回调
 *
 *  @param enabled 是否启用了双流
 *  @param userID  用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine dualStreamModeEnabled:(BOOL)enabled userID:(int64_t)userID;

/**
 *  网络质量检测回调
 *  调用([TTTRtcEngineKit enableLastmileTest])开启
 *
 *  @param quality 网络质量
 *
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine lastmileQuality:(TTTNetworkQuality)quality;

/**
 *  rtmp推流地址创建成功
 *
 *  @param rtmpUrl rtmp推流地址
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine rtmpStreamingCreated:(NSString *)rtmpUrl;

/**
 * channelKey即将过期
 * 时间距即将过期10~60s, 取channelKe有效时间的1/6，大于60s按照60s计算
 * 收到回调时，可以([TTTRtcEngineKit renewChannelByKey:])更新新的channelKey
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine channelKeyPrivilegeWillExpire:(NSString *)channelKey;

/**
 *  外部音频混音
 *
 *  @param data        混音的数据
 *  @param size        混音的音频数据长度
 *  @param sampleRate  混音的采样率
 *  @param channels    混音数据声道数
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine pullAudioData:(char *)data size:(int)size sampleRate:(NSUInteger)sampleRate channels:(int)channels;

/**
 *  请求改变视频采集帧率(用于外置视频源)
 *  当网络发生拥塞时，会请求下调帧率，反之会请求上调帧率
 *
 *  @param frameRate 帧率
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine changeVideoFrameRate:(NSUInteger)frameRate;

/**
 *  接收远端用户发来的歌词
 *
 *  @param uid   用户id
 *  @param lyric 歌词内容
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine receiveAudioLyricOfUid:(int64_t)uid lyric:(NSString *)lyric;

#pragma mark - deprecated delegate
- (void)rtcEngine:(TTTRtcEngineKit *)engine onAnchorEnter:(int64_t)sessionID userID:(int64_t)userID error:(TTTRtcErrorCode)error __deprecated;
- (void)rtcEngine:(TTTRtcEngineKit *)engine onAnchorExit:(int64_t)sessionID userID:(int64_t)userID __deprecated;
- (void)rtcEngine:(TTTRtcEngineKit *)engine onAnchorLinkResponse:(int64_t)sessionID userID:(int64_t)userID __deprecated;
- (void)rtcEngine:(TTTRtcEngineKit *)engine onAnchorUnlinkResponse:(int64_t)sessionID userID:(int64_t)userID reason:(TTTRtcAnchorExitReason)reason __deprecated;

/*      废弃回调，不再支持        */
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstRemoteVideoFrameDecodedOfUid:(int64_t)uid size:(CGSize)size elapsed:(NSInteger)elapsed DEPRECATED_MSG_ATTRIBUTE("use rtcEngine:firstRemoteVideoFrameDecodedOfUid:deviceId:size:elapsed: instead");
- (void)rtcEngine:(TTTRtcEngineKit *)engine firstRemoteVideoFrameOfUid:(int64_t)uid size:(CGSize)size elapsed:(NSInteger)elapsed DEPRECATED_MSG_ATTRIBUTE("use rtcEngine:firstRemoteVideoFrameOfUid:deviceId:size:elapsed: instead");
@end
