
## 2.3.0

支持Pod **TTTRtcEngineKit_iOS** **TTTPlayerKit_iOS** 如果pod search不到，更新Pod环境


#### 新增方法

1. 增加**setAudioEarBackVolume**设置耳返音量的方法
2. 增加**adjustAudioMixingPlayoutVolume**调节伴奏本地播放音量
3. 增加**adjustAudioMixingPublishVolume**调节伴奏远端播放音量
4. 增加网络连接状态相关接口

 > **getConnectionState**获取网络状态

 > **connectionChangedToState**网络连接状态发生改变回调

 > **TTTConnectionState**网络状态枚举

5. 增加**setRemoteDefaultVideoStreamType**设置默认订阅的视频流类型

6. 增加客户端录音相关方法

 > **startAudioRecording** 开始客户端录音

 > **stopAudioRecording** 停止客户端录音

 > **TTTAudioRecordQuality** 录音音质枚举

7. 增加外置音频源相关方法

 > **setExternalAudioSource** 配置外部音频源

 > **pushExternalAudioFrame** 推送外部音频采集数据

 > **pullRenderingAudioFrame** 拉取音频播放数据

8. **setRemoteVideoMirrored**设置远端用户看视频镜像

9. **isCameraPositionFront**是否前置摄像头



#### 过期方法

1. **adjustAudioMixingVolume**



## 2.2.0

#### 修改
1. **TTTRtcRemoteVideoStats**增加"deviceId"字段
2. **TTTRtcVideoCanvas**增加"deviceId"字段
3. **TTTRtcVideoCompositingRegion**增加"deviceId"字段
4. **TTTRtcVideoFrame**增加"deviceId"字段

5. **TTTRtcErrorCode** 增加"TTTRtc_Error_Enter_NoAnchor"

6. **muteRemoteVideoStream**增加devId参数
7. **firstRemoteVideoFrameDecodedOfUid**回调增加devId参数
8. **firstRemoteVideoFrameOfUid**回调增加devId参数



#### 新增方法
1. 设置水印
2. 推送KTV音频数据
3. 更新rtmp推流地址

#### 新增回调
1. 增加**didVideoEnabled**多流删除/添加设备id
2. 增加**onSetVideoCompositingLayout**设置画中画布局的回调
3. 增加**reportRtmpStatus**RTMP推流回调
4. 增加**pullAudioData**外部音频混音回调

#### 过期方法
1. **setHighQualityAudioParametersWithFullband**
