//
//  TTTEnumerates.h
//  TTTRtcEngineKit
//
//  Created by yanzhen on 2020/1/3.
//  Copyright © 2020 TTT. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Error codes */
typedef NS_ENUM(NSUInteger, TTTRtcErrorCode) {
    /** 0: 没有错误， 接口调用成功 */
    TTTRtc_Error_NoError             = 0,
    /** 9000: 无效的房间名称。 使用可转换大于0的long long类型纯数字字符串 */
    TTTRtc_Error_InvalidChannelName  = 9000,
    /** 9001: 进入房间超时，10s未连接上服务器，说明网络比较差。不处理该回调参数, 我们会继续尝试连接服务器。
    停止这次进入房间操作，调用([leaveChannel])退出房间。 */
    TTTRtc_Error_Enter_TimeOut       = 9001,
    /** 9002: 无法连接服务器 */
    TTTRtc_Error_Enter_Failed        = 9002,
    /** 9003: 验证码错误，可忽略 */
    TTTRtc_Error_Enter_VerifyFailed  = 9003,
    /** 9004: 版本错误 */
    TTTRtc_Error_Enter_BadVersion    = 9004,
    /** 9005: 未知错误， 其它错误 */
    TTTRtc_Error_Enter_Unknown       = 9005,
    /** 9006: 直播模式([TTTRtc_ChannelProfile_LiveBroadcasting])，房间内没有主播 */
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
    /** 副播：可在任何模式下使用，可切换为观众(下麦) */
    TTTRtc_ClientRole_Broadcaster = 2,
    /** 观众：可在任何模式下使用，可切换为副播(上麦)。默认对其它用户是不可见的 */
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
    /** Resolution: 960x540, frame rate: 15, bitrate 800 kbps */
    TTTRtc_VideoProfile_960x540 = 48,
    /** Resolution: 1280x720, frame rate: 15, bitrate 1130 kbps */
    TTTRtc_VideoProfile_720P = 50,
    /** Resolution: 1920x1080, frame rate: 15, bitrate 2080 kbps */
    TTTRtc_VideoProfile_1080P   = 60,
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
    /** 内置扬声器 */
    TTTRtc_AudioOutput_InternalSpeaker = 0,
    /** 外置扬声器 */
    TTTRtc_AudioOutput_ExternalSpeaker = 1,
    /** 耳机 */
    TTTRtc_AudioOutput_Headphones      = 2
};

/** 音频设备类型 */
typedef NS_ENUM(NSUInteger, TTTRtcAudioDeviceType) {
    /** 内置麦克风 */
    TTTRtc_AudioDevice_Input_InternalMicrophone = 1,
    /** 外置麦克风 */
    TTTRtc_AudioDevice_Input_ExternalMicrophone = 2,
    /** 内置扬声器 */
    TTTRtc_AudioDevice_Output_InternalSpeaker   = 11,
    /** 外置扬声器 */
    TTTRtc_AudioDevice_Output_ExternalSpeaker   = 12,
    /** 耳机 */
    TTTRtc_AudioDevice_Output_Headphones        = 13,
};

/** 视频编解码方式 */
typedef NS_ENUM(NSUInteger, TTTRtcVideoCodecMode) {
    TTTRtc_VideoCodecMode_HardCoding = 0,
    TTTRtc_VideoCodecMode_SoftCoding = 1,
};
#endif

/** 视频显示模式 */
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

/** 网络连接状态 */
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

/** 录音音质 */
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
