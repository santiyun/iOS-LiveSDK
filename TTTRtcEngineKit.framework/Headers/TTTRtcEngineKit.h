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

/**
 *  错误代码
 */
typedef NS_ENUM(NSUInteger, TTTRtcErrorCode) {
    TTTRtc_Error_NoError             = 0,    // 没有错误
    // 进入房间错误
    TTTRtc_Error_InvalidChannelName  = 9000, // 无效的房间名称
    TTTRtc_Error_Enter_TimeOut       = 9001, // 超时,10秒未收到服务器返回结果
    TTTRtc_Error_Enter_Failed        = 9002, // 无法连接服务器
    TTTRtc_Error_Enter_VerifyFailed  = 9003, // 验证码错误
    TTTRtc_Error_Enter_BadVersion    = 9004, // 版本错误
    TTTRtc_Error_Enter_Unknown       = 9005, // 未知错误
    TTTRtc_Error_Enter_NoAnchor      = 9006, // 房间内没有主播
    //
    TTTRtc_Error_NoAudioData         = 9101, // 长时间没有上行音频数据
    TTTRtc_Error_NoVideoData         = 9102, // 长时间没有上行视频数据
    TTTRtc_Error_NoReceivedAudioData = 9111, // 长时间没有下行音频数据
    TTTRtc_Error_NoReceivedVideoData = 9112, // 长时间没有下行视频数据
    //
    TTTRtc_Error_InvalidChannelKey   = 9200, //无效的channelKey
    TTTRtc_Error_Unknown             = 9999, // 未知错误
};

/**
 *  踢出房间原因
 */
typedef NS_ENUM(NSUInteger, TTTRtcKickedOutReason) {
    TTTRtc_KickedOut_KickedByHost      = 1, // 被主播踢出
    TTTRtc_KickedOut_PushRtmpFailed    = 2, // rtmp推流失败
    TTTRtc_KickedOut_ServerOverload    = 3, // 服务器过载
    TTTRtc_KickedOut_MasterExit        = 4, // 主播已退出
    TTTRtc_KickedOut_ReLogin           = 5, // 重复登录
    TTTRtc_KickedOut_NoAudioData       = 6, // 长时间没有上行音频数据
    TTTRtc_KickedOut_NoVideoData       = 7, // 长时间没有上行视频数据
    TTTRtc_KickedOut_NewChairEnter     = 8, // 其他人以主播身份进入
    TTTRtc_KickedOut_ChannelKeyExpired = 9, // Channel Key失效
};

/**
 *  频道模式
 */
typedef NS_ENUM(NSUInteger, TTTRtcChannelProfile) {
    TTTRtc_ChannelProfile_Communication    = 0, // 通信
    TTTRtc_ChannelProfile_LiveBroadcasting = 1, // 直播
    TTTRtc_ChannelProfile_Game_FreeMode    = 2, // 游戏（自由发言模式）
};

/**
 *  用户角色
 */
typedef NS_ENUM(NSUInteger, TTTRtcClientRole) {
    TTTRtc_ClientRole_Anchor      = 1, // 主播
    TTTRtc_ClientRole_Broadcaster = 2, // 副播
    TTTRtc_ClientRole_Audience    = 3, // 观众(默认)
};

/**
 *  音频编码格式
 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioCodecType) {
    TTTRtc_AudioCodec_AAC     = 1, // 码率范围32kbps~96kbps
    TTTRtc_AudioCodec_ISAC_WB = 2, // 码率范围10kbps~32kbps
    TTTRtc_AudioCodec_OPUS    = 4, // 码率范围32kbps~96kbps
};

/**
 *  视频编码属性
 */
typedef NS_ENUM(NSUInteger, TTTRtcVideoProfile) {
                                       //    res    fps   kbps
    TTTRtc_VideoProfile_120P    =  0,  //  160x120   15     65
    TTTRtc_VideoProfile_180P    = 10,  //  320x180   15    140
    TTTRtc_VideoProfile_240P    = 20,  //  320x240   15    200
    TTTRtc_VideoProfile_360P    = 30,  //  640x360   15    400
    TTTRtc_VideoProfile_480P    = 40,  //  848x480   15    600
    TTTRtc_VideoProfile_720P    = 50,  // 1280x720   15   1130
#if TARGET_OS_IOS
    TTTRtc_VideoProfile_1080P   = 60,  // 1920x1080  15   2080
#endif
    TTTRtc_VideoProfile_Default = TTTRtc_VideoProfile_360P
};

/**
 *  用户离线原因
 */
typedef NS_ENUM(NSUInteger, TTTRtcUserOfflineReason) {
    TTTRtc_UserOffline_Quit           = 1, // 用户主动离开
    TTTRtc_UserOffline_Dropped        = 2, // 因过长时间收不到对方数据包，超时掉线。
    TTTRtc_UserOffline_BecomeAudience = 3, // 当用户身份从主播切换为观众时触发
};

/**
 *  音频输出路由
 */
#if TARGET_OS_IOS
typedef NS_ENUM(NSUInteger, TTTRtcAudioOutputRouting)
{
    TTTRtc_AudioOutput_Headset   = 0, // 耳机或蓝牙
    TTTRtc_AudioOutput_Speaker   = 1, // 扬声器
    TTTRtc_AudioOutput_Headphone = 2  // 手机听筒
};
#elif TARGET_OS_OSX
typedef NS_ENUM(NSUInteger, TTTRtcAudioOutputRouting)
{
    TTTRtc_AudioOutput_InternalSpeaker = 0, // 内置扬声器
    TTTRtc_AudioOutput_ExternalSpeaker = 1, // 外置扬声器
    TTTRtc_AudioOutput_Headphones      = 2  // 耳机
};
#endif

/**
 *  日志过滤器
 */
typedef NS_ENUM(NSUInteger, TTTRtcLogFilter) {
    TTTRtc_LogFilter_Off      = 0,
    TTTRtc_LogFilter_Debug    = 0x080f,
    TTTRtc_LogFilter_Info     = 0x000f,
    TTTRtc_LogFilter_Warning  = 0x000e,
    TTTRtc_LogFilter_Error    = 0x000c,
    TTTRtc_LogFilter_Critical = 0x0008
};

/**
 *  视频显示模式
 */
typedef NS_ENUM(NSUInteger, TTTRtcRenderMode) {
    // 如果视频尺寸与显示视窗尺寸不一致，则视频流会按照显示视窗的比例进行周边裁剪或图像拉伸后填满视窗。
    TTTRtc_Render_Hidden   = 1,
    // 如果视频尺寸与显示视窗尺寸不一致，在保持长宽比的前提下，将视频进行缩放后填满视窗。
    TTTRtc_Render_Fit      = 2,
    // 如果自己和对方都是竖屏，或者如果自己和对方都是横屏，使用TTTRtc_Render_Hidden；如果对方和自己一个竖屏一个横屏，则使用TTTRtc_Render_Fit。
    TTTRtc_Render_Adaptive = 3
};

/**
 *  聊天消息类型
 */
typedef NS_ENUM(NSUInteger, TTTRtcChatType) {
    TTTRtc_ChatType_Text    = 1,
    TTTRtc_ChatType_Picture = 2,
    TTTRtc_ChatType_Audio   = 3,
    TTTRtc_ChatType_Custom  = 4
};

/**
 *  RTMP推流状态
 */
typedef NS_ENUM(NSUInteger, TTTRtcRtmpPublishStatus) {
    TTTRtc_RtmpPublishStatus_InitError     = 0, // 初始化RTMP发送器失败
    TTTRtc_RtmpPublishStatus_OpenError     = 1, // 打开RTMP链接失败
    TTTRtc_RtmpPublishStatus_AudioNoBuf    = 2, // 音频数据缓冲区空间不足
    TTTRtc_RtmpPublishStatus_VideoNoBuf    = 3, // 视频数据缓冲区空间不足
    TTTRtc_RtmpPublishStatus_LinkFailed    = 4, // 发送视频数据失败
    TTTRtc_RtmpPublishStatus_LinkSuccessed = 5, // 推流成功
};

/**
 *  视频流类型
 */
typedef NS_ENUM(NSUInteger, TTTRtcVideoStreamType) {
    TTTRtc_VideoStream_High = 0, // 视频大流
    TTTRtc_VideoStream_Low  = 1, // 视频小流
};

/**
 *  网络质量
 */
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
    TTTConnectionStateDisconnected = 1, //未加入房间,加入房间失败后，或者离开房间之后
    TTTConnectionStateConnecting = 2,   //加入房间正在建立网络连接
    TTTConnectionStateConnected = 3,    //网络连接建立成功
    TTTConnectionStateReconnecting = 4, //网络连接重连中
    TTTConnectionStateFailed = 5,       //网络连接失败
};

/**
 *  录音音质
 */
typedef NS_ENUM(NSUInteger, TTTAudioRecordQuality) {
    TTTAudioRecordQualityLow = 0,    //10 分钟的文件大小为 2.4M 左右
    TTTAudioRecordQualityMedium = 1, //10 分钟的文件大小为 3.6M 左右
    TTTAudioRecordQualityHigh = 2,   //10 分钟的文件大小为 4.8M 左右
};

/**
 *  连麦主播离开原因
 */
typedef NS_ENUM(NSUInteger, TTTRtcAnchorExitReason) {
    TTTRtc_AnchorExit_Unlink    = 0, // 其他主播结束与“我”连麦，正常离开
    TTTRtc_AnchorExit_Timeout   = 1, // 心跳超时断开
    TTTRtc_AnchorExit_LinkClose = 2, // 网络异常断开
} __deprecated;

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
 *  视频帧格式
 */
typedef NS_ENUM(NSUInteger, TTTRtcVideoFrameFormat) {
    TTTRtc_VideoFrameFormat_Texture = 0,
    TTTRtc_VideoFrameFormat_I420    = 1,
    TTTRtc_VideoFrameFormat_NV12    = 2,
    TTTRtc_VideoFrameFormat_NV21    = 3,
    TTTRtc_VideoFrameFormat_RGBA    = 4,
    TTTRtc_VideoFrameFormat_BGRA    = 5,
    TTTRtc_VideoFrameFormat_ARGB    = 6,
};

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

#if TARGET_OS_OSX

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

/**
 *  音频设备
 */
@interface TTTRtcAudioDevice : NSObject

@property (assign, nonatomic) AudioDeviceID deviceID;           // 音频设备ID
@property (assign, nonatomic) TTTRtcAudioDeviceType deviceType; // 音频设备类型
@property (copy, nonatomic) NSString *deviceName;               // 音频设备名称

@end

#endif

@protocol TTTRtcEngineDelegate;

@interface TTTRtcEngineKit : NSObject

/**
 *  应用ID，由连麦平台分配，用于区分不同的客户和应用。
 */
@property (nonatomic, copy) NSString *appID;

/**
 *  SDK回调对象，由调用方赋值。
 */
@property (nonatomic, weak) id<TTTRtcEngineDelegate> delegate;

/**
 *  音视频信息统计间隔（默认：2秒）
 */
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
 *  @param delegate     SDK回调代理
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
 *  启用同房间多主播
 *  在加入房间之前调用，若启用该功能，允许房间内进入多个主播
 */
- (void)enableCrossRoom:(BOOL)enable;

/**
 *  设置频道模式
 *
 *  @param profile 频道模式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setChannelProfile:(TTTRtcChannelProfile)profile;

/**
 *  设置用户角色
 *
 *  @param role          直播场景里的用户角色
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setClientRole:(TTTRtcClientRole)role;

/**
 *  设置视频编码属性
 *
 *  @param profile            每个Profile对应一套视频参数，如分辨率、帧率、码率等。
 *  @param swapWidthAndHeight 是否交换宽和高
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setVideoProfile:(TTTRtcVideoProfile)profile swapWidthAndHeight:(BOOL)swapWidthAndHeight;

/**
 *  设置视频编码属性（自定义）
 *
 *  @param videoSize 视频分辨率
 *  @param frameRate 视频帧率
 *  @param bitRate   视频码率
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setVideoProfile:(CGSize)videoSize frameRate:(NSUInteger)frameRate bitRate:(NSUInteger)bitRate;

/**
 *  加入通话频道
 *
 *  @param channelKey        此为程序生成的Channel Key（当用户使用静态Key也即只使用App ID时, 该参数是可选的）
 *  @param channelName       标识通话的频道名称，长度在64字节以内的字符串。
 *  @param uid               用户ID
 *  @param joinSuccessBlock  用户加入成功回调
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)joinChannelByKey:(NSString *)channelKey
            channelName:(NSString *)channelName
                    uid:(int64_t)uid
            joinSuccess:(void(^)(NSString *channel, int64_t uid, NSInteger elapsed))joinSuccessBlock;

/**
 *  离开频道，即挂断或退出通话。
 *
 *  @param leaveChannelBlock 成功离开频道的回调
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)leaveChannel:(void(^)(TTTRtcStats *stats))leaveChannelBlock;

/**
 *  更新 channelKey
 *
 *  @param channelKey 此为程序生成的Channel Key
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)renewChannelByKey:(NSString *)channelKey;

/**
 * 获取网络连接状态
 */
- (TTTConnectionState)getConnectionState;

/**
 *  该方法用于开启视频模式。
 *  可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启视频模式，在通话中调用则由音频模式切换为视频模式。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableVideo;

/**
 *  该方法用于关闭视频，开启纯音频模式。
 *  可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启纯音频模式，在通话中调用则由视频模式切换为纯音频频模式。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)disableVideo;

/**
 *  禁用/启用本地视频功能。该方法用于只看不发的视频场景。该方法不需要本地有摄像头。
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
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startPreview;

/**
 *  停止本地视频预览
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
 *
 * @param enable YES-开启美颜， NO-关闭美颜
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
 *  切换前置/后置摄像头
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
*  默认打开前置摄像头镜像
*
*  @param mirror YES: 开启镜像，NO: 关闭镜像。
*
*  @return 0: 方法调用成功，<0: 方法调用失败。
*/
- (int)setVideoMirrored:(BOOL)mirror;

/**
 *  设置远端用户看视频镜像
 *  该接口对应本地预览结果进行镜像，包含前后摄像头
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
 *  暂停所有远端视频流
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
 *  静音/取消静音。该方法用于允许/禁止往网络发送本地音频流。
 *
 *  @param mute YES: 麦克风静音, NO: 取消静音。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteLocalAudioStream:(BOOL)mute;

/**
 *  调节本地说话音量
 *
 *  @param scale 音量范围为0~500。默认100为原始音量
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustAudioMixingSoloVolume:(NSInteger)scale;

/**
 *  静音所有远端音频/对所有远端音频取消静音。该方法用于允许/禁止播放远端用户的音频流，即对所有远端用户进行静音与否。
 *
 *  @param mute YES: 停止播放所接收的音频流, NO: 恢复播放所接收的音频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/**
 *  静音指定远端用户/对指定远端用户取消静音。本方法用于允许/禁止播放远端用户的音频流。
 *
 *  @param mute YES: 停止播放指定用户的音频流, NO: 恢复播放指定用户的音频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteAudioStream:(int64_t)uid mute:(BOOL)mute;

/**
 *  禁言指定远端用户/对指定远端用户取消禁言。
 *
 *  @param mute YES: 禁止发言, NO: 允许发言。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteSpeaking:(int64_t)uid mute:(BOOL)mute;

/*
 * 启用/禁用回声消除
 * 加入房间之后调用
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableHWAEC:(BOOL)enable;

/*
 * 启用/禁用软件回声消除
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableSoftAEC:(BOOL)enable;

/**
 *  打开/关闭耳返功能，在插入耳机的情况下有效
 *
 *  @param enable YES: 打开耳返功能，NO: 关闭耳返功能。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioEarBack:(BOOL)enable;

/**
 *  设置耳返音量，在打开耳返的情况下有效
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
 *  对应本地和远端音频数据的代理回调
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
 *  切换音频输出方式：扬声器或听筒
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
 *  @param defaultToSpeaker YES: 从扬声器出声，NO: 语音聊天：从听筒出声；视频聊天：从扬声器出声。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setDefaultAudioRouteToSpeakerphone:(BOOL)defaultToSpeaker;

#endif

/**
 *  启用说话者音量提示
 *
 *  @param interval 指定音量提示的时间间隔（<=0: 禁用音量提示功能；>0: 提示间隔，单位为毫秒。建议设置到大于200毫秒。）
 *  @param smooth   平滑系数。默认可以设置为3。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval smooth:(NSInteger)smooth;

/**
 *  设置日志文件
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
 *  往日志文件中增加自定义日志（进入房间后才可使用）
 *
 *  @param log 日志内容
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)addLog:(NSString *)log;

/**
 *  设置信令超时时间
 *
 *  @param seconds 超时时间（秒）
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setSignalTimeout:(NSUInteger)seconds;

/**
 * 是否启用上行加速
 *
 * @param enable 是否启用
 */
- (void)enableUplinkAccelerate:(BOOL)enable;

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
 *
 *  @param config 直播推流配置
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)configPublisher:(TTTPublisherConfiguration *)config;

/**
 *  设置画中画布局
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
 *
 *  @param data 音频数据
 *
 *  @return YES: 推送成功，NO: 推送失败。
 */
- (BOOL)pushExternalAudioData:(NSData *)data;

/**
 *  设置本地视频帧采集格式
 *  如果不设置，回调rtcEngine:localVideoFrameCaptured:videoFrame:默认格式为“BGRA”。
 *
 *  @param format                     视频帧的格式
 *  @param isVideoSizeSameWithProfile 采集的视频尺寸是否和VideoProfile相同
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setLocalVideoFrameCaptureFormat:(TTTRtcVideoFrameFormat)format isVideoSizeSameWithProfile:(BOOL)isVideoSizeSameWithProfile;

/**
 *  设置远端视频帧输出格式
 *  如果不设置，回调rtcEngine:remoteVideoFrameDecodedOfUid:videoFrame:默认格式为“NV12”。
 *
 *  @param format 视频帧的格式
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setRemoteVideoFrameOutputFormat:(TTTRtcVideoFrameFormat)format;

/**
 *  开始客户端本地混音
 *
 *  @param filePath 指定需要混音的本地音频文件名和文件路径
 *  @param loopback True: 只有本地可以听到混音或替换后的音频流，False: 本地和对方都可以听到混音或替换后的音频流。
 *  @param cycle    指定音频文件循环播放的次数
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
 *  角色为“TTTRtc_ClientRole_Anchor”调用有效
 *
 *  @param uid 被踢者userID
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
 *  设置CDN推流视频参数，在加入房间之前调用
 *
 *  @param videoSize      视频分辨率
 *  @param videoFrameRate 视频帧率
 *  @param videoBitRate   视频码率
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
 *  在加入房间之前调用rtmpUrl设置为nil。加入房间之后推单路cdn流可以设置nil或者对应推流地址，推多路流必须设置对应cdn推流地址
 *
 *  @param url     背景图片所在的地址
 *  @param rtmpUrl 背景图对应的cdn推流地址
 */
- (void)setVideoMixerBackgroundImgUrl:(NSString *)url forRtmpUrl:(NSString *)rtmpUrl;

/**
 *  开启网络质量检测
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
 *
 *  @param channelId 其它房间Id
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
 *
 *  @param url rtmp流地址
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)updateRtmpUrl:(NSString *)url;

/**
 *  开始客户端录音
 *  建议在加入房间后开启
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
 *  在加入房间之前开启, 开启该功能需要同时做采集和播放, SDK音频路由相关设置也没有效果
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
 *  回调数据包含本地和所有远端用户混音数据
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
 *  回调数据包含本地和所有远端用户混音数据
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
*  在加入房间成功后设置，设置成功之后收到回调"rtmpStreamingCreated"
   然后可通过TTTRtcVideoCompositingLayout.rtmpUrl设置对应布局，也可设置对应的背景图
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
 *  通常情况下，SDK上报的错误意味着SDK无法自动恢复，需要应用程序干预或提示用户。
 *
 *  @param errorCode 错误代码
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didOccurError:(TTTRtcErrorCode)errorCode;

/**
 *  网络连接丢失回调
 */
- (void)rtcEngineConnectionDidLost:(TTTRtcEngineKit *)engine;

/**
 *  当网络异常断开后，将尝试重连，
 *  若在服务器容忍的超时范围外才重连上服务器，服务器将会拒绝，其房间状态将不可用。
 *  此时触发该回调，上层应该在收到此回调后，调用“leaveChannel”退出房间。
 */
- (void)rtcEngineReconnectServerTimeout:(TTTRtcEngineKit *)engine;

/**
 *  当网络异常断开后，重连成功。
 */
- (void)rtcEngineReconnectServerSucceed:(TTTRtcEngineKit *)engine;

/**
 *  网络连接状态发生改变
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
 *  用户启用/关闭视频回调
 *
 *  @param enabled YES: 该用户已启用了视频功能，NO: 该用户已关闭了视频功能。
 *  @param uid     用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didVideoEnabled:(BOOL)enabled byUid:(int64_t)uid;

/**
 *  用户添加/删除视频设备(多流)
 *
 *  @param enabled YES: 该用户已启用了视频功能，NO: 该用户已关闭了视频功能。
 *  @param devId   设备Id
 *  @param uid     用户ID
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didVideoEnabled:(BOOL)enabled deviceId:(NSString *)devId byUid:(int64_t)uid;

/**
 *  音频输出路由发生变化
 *
 *  @param routing 当前音频输出路由
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine didAudioRouteChanged:(TTTRtcAudioOutputRouting)routing;

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
 *  提示谁在说话及其音量，默认禁用。可通过enableAudioVolumeIndication方法设置。
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
 *  通过"setMixedAudioFrameParametersWithSampleRate"启用
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
 *
 *  @param videoFrame 视频帧
 */
- (void)rtcEngine:(TTTRtcEngineKit *)engine localVideoFrameCaptured:(TTTRtcVideoFrame *)videoFrame;

/**
 *  远端视频接收解码回调
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
 *  "- (int)enableLastmileTest;"调用该方法开启
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
 * 收到回调时，可以"- (int)renewChannelByKey:(NSString *)channelKey"更新新的channelKey
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
