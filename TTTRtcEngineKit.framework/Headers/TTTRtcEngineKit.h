#import <Foundation/Foundation.h>
#import "TTTRtcEngineDelegate.h"
#import "TTTEnumerates.h"
#import "TTTObjects.h"

@interface TTTRtcEngineKit : NSObject

/** 应用ID，由连麦平台分配，用于区分不同的客户和应用 */
@property (nonatomic, copy) NSString *appID;

/**  SDK回调对象，由调用方赋值 */
@property (nonatomic, weak) id<TTTRtcEngineDelegate> delegate;

/** 音视频信息统计间隔（默认：2秒） */
@property (nonatomic, assign) NSUInteger statsInterval;


@property (nonatomic, readonly) NSString *defaultVideoDeviceID;

#if TARGET_OS_OSX

/** 视频编码方式 */
@property (nonatomic, assign) TTTRtcVideoCodecMode videoEncodingMode;

/** 视频解码方式 */
@property (nonatomic, assign) TTTRtcVideoCodecMode videoDecodingMode;

/** 视频采集设备 */
@property (nonatomic, weak) AVCaptureDevice *videoCaptureDevice;

/** 音频采集设备 */
@property (nonatomic, weak) TTTRtcAudioDevice *audioCaptureDevice;

/** 音频输出设备 */
@property (nonatomic, weak) TTTRtcAudioDevice *audioPlayoutDevice;

#endif

/**
 *  初始化SDK，加载资源。
 *
 *  @param appId        应用ID，由连麦平台分配，用于区分不同的客户和应用，在同一个连麦平台内保证唯一。
    可以通过([TTTRtcEngineKit.appID])设置新的appID
 *
 *  @param delegate     SDK回调代理, 可以通过([TTTRtcEngineKit.delegate])设置新的代理
 *
 *  @return TTTRtc 对象(单例)
 */
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
 *  相同频道内的所有用户必须使用相同的频道模式
 *  设置该方法之后再设置角色([TTTRtcEngineKit setClientRole:])
 *  加入房间之前设置，在房间内不能做修改
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
 *  离开通话频道
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
 *  开启视频模式
 *  可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启视频模式，在通话中调用则由音频模式切换为视频模式。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableVideo;

/**
 *  关闭视频，开启纯音频模式
 *  可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启纯音频模式，在通话中调用则由视频模式切换为纯音频频模式。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)disableVideo;

/**
 *  禁用/启用本地视频功能
 *  该方法用于只看不发的视频场景，不需要本地有摄像头
 *  加入频道前调用其他用户可通过回调([TTTRtcEngineDelegate rtcEngine:didJoinedOfUid:clientRole:isVideoEnabled:elapsed:])判断视频是否可用
 *  房间内调用其他用户可通过回调([TTTRtcEngineDelegate rtcEngine:didVideoEnabled:byUid:])判断视频是否可用
 *
 *  @param enabled YES: 启用本地视频（默认），NO: 禁用本地视频。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableLocalVideo:(BOOL)enabled;

/**
 *  主动上行本端视频
 *  加入房间之后调用，对于房间内只有单个副播可以主动上行视频
 *
 *  @param up YES: 主动上行视频 NO: 关闭本地主动上行
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)uploadLocalVideo:(BOOL)up;

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
 *  预览本地视频
 *
 *  @param local 本地视频显示属性
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setupLocalVideo:(TTTRtcVideoCanvas *)local;

/**
 *  显示远端视频
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
/**
 * 设置美颜效果
 *
 * @param enable YES-开启美颜， NO-关闭美颜
 *
 * @param beautyLevel: 默认0.5, 0.0~1.0
 *
 * @param brightLevel: 默认0.5, 0.0~1.0
 */
- (void)setBeautyFaceStatus:(BOOL)enable beautyLevel:(CGFloat)beautyLevel brightLevel:(CGFloat)brightLevel;

/**
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
 *  暂停/恢复所有远端视频流
 *
 *  @param mute YES: 停止播放接收到的所有视频流，NO: 允许播放接收到的所有视频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteAllRemoteVideoStreams:(BOOL)mute;

/**
 *  打开/关闭指定的远端视频流
 *  默认打开用户视频，通过接口可开启或关闭指定视频流
 *
 *  @param uid   用户ID
 *  @param mute  YES: 关闭 NO: 打开
 *  @param devId 设备id(远端用户多设备), 默认设置nil
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteVideoStream:(int64_t)uid mute:(BOOL)mute deviceId:(NSString *)devId;

/**
 *  静音/取消静音
 *  允许/禁止往网络发送本地音频流
 *  房间内用户可收到([TTTRtcEngineDelegate rtcEngine:didAudioMuted:byUid:])
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
- (int)adjustAudioMixingSoloVolume:(NSInteger)volume;

/**
 *  调节播放人声的音量
 *
 *  @param volume 音量范围为0~500。默认100为原始音量
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;

/**
 *  静音/取消静音所有远端音频
 *  允许/禁止播放远端用户的音频流，即对所有远端用户进行静音与否。
 *
 *  @param mute YES: 停止播放所有所接收的音频流, NO: 恢复播放所有接收的音频流
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/**
 *  静音/取消静音指定远端用户
 *  允许/禁止播放远端用户的音频流。
 *
 *  @param uid  用户id
 *  @param mute YES: 停止播放指定用户的音频流, NO: 恢复播放指定用户的音频流。
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)muteRemoteAudioStream:(int64_t)uid mute:(BOOL)mute;

/**
 *  禁言/取消禁言指定远端用户
 *  仅直播模式下，主播具有该权限
 *  房间内用户可收到([TTTRtcEngineDelegate rtcEngine:didSpeakingMuted:ofUid:])
 *
 *  @param uid  用户id
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
 * 启用/禁用回声消除
 * 加入房间之后调用，默认启用
 *
 * @param enable 是否启用
 *
 * @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableHWAEC:(BOOL)enable;

/**
 * 启用/禁用软件回声消除
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
 *  @param volume 取值范围在 [0,100] 默认值为 100
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
 *  @param defaultToSpeaker YES(默认): 从扬声器出声，NO: 从听筒出声
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setDefaultAudioRouteToSpeakerphone:(BOOL)defaultToSpeaker;

/**
 *  停止/恢复音频采集和播放
 *
 *  @param stop  YES: 停止采集和播放  NO: 恢复采集和播放
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopAudioPlayAndRecord:(BOOL)stop;

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
 *  默认90s, 设置时长需要大于20s, 取值(seconds + 9) / 10
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
 *  设置画中画布局(SEI布局)
 *  控制cdn各路视频在混频的位置，大小
 *
 *  @param layout 画中画布局
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setVideoCompositingLayout:(TTTRtcVideoCompositingLayout*)layout;

/**
 *  配置外部视频源
 *  在([TTTRtcEngineKit enableVideo])/([TTTRtcEngineKit startPreview])之前调用本API。
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
 *  默认仅支持mp3格式音乐文件
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
 *  @return 播放进度ms
 */
- (int)getAudioMixingCurrentPosition;

/**
 *  设置播放进度
 *
 *  @param pos 播放位置，单位为ms
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)setAudioMixingPosition:(NSInteger)pos;

/**
 *  发送歌词
 *
 *  @param lyric 歌词内容
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)sendAudioLyric:(NSString *)lyric;

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
- (int)startRecordScreenWithHandler:(void(^)(NSError *error))handler NS_AVAILABLE_IOS(11_0);

/**
 *  开始录制屏幕并保存
 *
 *  @param path   保存路径，如果值为nil，保存到系统相册。
 *  @param width  视频宽度
 *  @param height 视频高度
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)startRecordScreenAndSave:(NSString *)path width:(NSInteger)width height:(NSInteger)height handler:(void(^)(NSError *error))handler NS_AVAILABLE_IOS(11_0);

/**
 *  停止录制屏幕
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)stopRecordScreenWithHandler:(void(^)(NSError *error))handler;

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
- (int)insertH264SeiContent:(NSString *)content;

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
 *  订阅其它房间主播视频(PK)
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
 *  启用默认音频播放
 *  调用该功能，内部会播放默认静音数据
 *
 *  @param enable  是否启用默认播放
 *
 *  @return 0: 方法调用成功，<0: 方法调用失败。
 */
- (int)enableDefaultAudioPaly:(BOOL)enable;

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
- (void)setVideoMixerParams:(CGSize)videoSize videoFrameRate:(NSUInteger)videoFrameRate videoBitRate:(NSUInteger)videoBitRate DEPRECATED_MSG_ATTRIBUTE("see TTTPublisherConfiguration");
- (void)setAudioMixerParams:(NSUInteger)samplerate channels:(NSUInteger)channels DEPRECATED_MSG_ATTRIBUTE("see TTTPublisherConfiguration");

- (void)setVideoMixerBackgroundImgUrl:(NSString*)url DEPRECATED_MSG_ATTRIBUTE("use setVideoMixerBackgroundImgUrl:forRtmpUrl: instead");
- (int)adjustAudioMixingVolume:(NSInteger)volume DEPRECATED_MSG_ATTRIBUTE("use adjustAudioMixingPlayoutVolume: instead");
- (int)linkOtherAnchor:(int64_t)sessionID userID:(int64_t)userID DEPRECATED_MSG_ATTRIBUTE("use subscribeOtherChannel: instead");
- (int)unlinkOtherAnchor:(int64_t)sessionID userID:(int64_t)userID DEPRECATED_MSG_ATTRIBUTE("use unSubscribeOtherChannel: instead");
@end

