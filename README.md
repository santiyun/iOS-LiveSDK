## 连麦SDK

连麦SDK使用需要同时下载拉流依赖库[TTTPlayerKit.framework](https://github.com/santiyun/TTTPlayerKit_iOS)

更新连麦SDK时不需要更新**TTTPlayerKit.framework**

如果项目中使用了IJK拉流的库可去掉**TTTPlayerKit.framework**，去掉拉流库出现问题请联系我们

## Pod说明

连麦SDK：**TTTRtcEngineKit_iOS** 

拉流SDK：**TTTPlayerKit_iOS** 

如果pod search不到，请更新Pod环境


## 2.4.0

#### 新增方法

1. 增加**stopAudioPlayAndRecord**停止/恢复音频采集和播放
2. 增加**setRecordingAudioFrameParametersWithSampleRate**设置录制的声音格式
3. 增加**setPlaybackAudioFrameParametersWithSampleRate**设置播放的声音格式
4. 增加**setMixedAudioFrameParametersWithSampleRate**设置录制和播放声音混音后的数据格式
5. 增加**addPublishStreamUrl**增加一路cdn推流地址
6. 增加**removePublishStreamUrl**删除一路cdn推流地址
7. **TTTRtcVideoCompositingLayout** 增加**rtmpUrl**推流地址属性
8. 增加**sendAudioLyric**发送歌词

#### 新增回调

1. **rtmpStreamingCreated** rtmp推流地址创建成功
2. **receiveAudioLyricOfUid** 接收远端用户发来的歌词
3. **mixAudioData** 混音音频数据回调

#### 修改方法

1. **setVideoMixerBackgroundImgUrl**新增推流地址的参数


## 2.3.0

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
