﻿
#ifndef __ZEGOEXPRESSHANDLERS_H__
#define __ZEGOEXPRESSHANDLERS_H__

#include "ZegoExpressDefines.h"

namespace ZEGO {
    namespace EXPRESS {

        class IZegoMediaPlayer;


        class IZegoEventHandler
        {
        protected:

            virtual ~IZegoEventHandler() {}

        public:

            /**
             * The callback for obtaining debugging error information.
             *
             * When the APIs are not used correctly, the callback prompts for detailed error information, which is controlled by the [setDebugVerbose] interface
             *
             * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
             * @param funcName Function name
             * @param info Detailed error information
             */
            virtual void onDebugError(int /*errorCode*/, const std::string& /*funcName*/, const std::string& /*info*/) {

            }

            /**
             * The callback triggered when the audio/video engine state changes.
             *
             * When the developer calls the API that enables audio and video related functions, such as calling [startPreview], [startPublishingStream], [startPlayingStream] and MediaPlayer related API, the audio/video engine will start; when all audio and video functions are stopped, the engine state will become stopped.
             * When the developer has been [loginRoom], once [logoutRoom] is called, the audio/video engine will stop (preview, publishing/playing stream, MediaPlayer and other audio and video related functions will also stop).
             *
             * @param state The audio/video engine state
             */
            virtual void onEngineStateUpdate(ZegoEngineState /*state*/) {

            }

            /**
             * The callback triggered when the room connection state changes.
             *
             * This callback is triggered when the connection status of the room changes, and the reason for the change is notified. Developers can use this callback to determine the status of the current user in the room. If the connection is being requested for a long time, the general probability is that the user's network is unstable.
             *
             * @param roomID Room ID, a string of up to 128 bytes in length.
             * @param state Changed room state
             * @param errorCode Error code, please refer to the [common error code document](https://doc-en.zego.im/en/308.html) for details
             * @param extendedData Extended Information with state updates. As the standby, only an empty json table is currently returned
             */
            virtual void onRoomStateUpdate(const std::string& /*roomID*/, ZegoRoomState /*state*/, int /*errorCode*/, const std::string& /*extendedData*/) {

            }

            /**
             * The callback triggered when the number of other users in the room increases or decreases.
             *
             * Note that the callback is only triggered when the isUserStatusNotify parameter in the ZegoRoomConfig passed loginRoom function is true. Developers can use this callback to determine the situation of users in the room.
             * If developers need to use ZEGO room users notifications, please make sure that each login user sets isUserStatusNotify to true
             * When a user logs in to a room for the first time, other users already exist in this room, and a user list of the type of addition is received.
             * When the user is already in the room, other users in this room will trigger this callback to notify the changed users when they enter or exit the room.
             *
             * @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
             * @param updateType Update type (add/delete)
             * @param userList List of users changed in the current room
             */
            virtual void onRoomUserUpdate(const std::string& /*roomID*/, ZegoUpdateType /*updateType*/, const std::vector<ZegoUser>& /*userList*/) {

            }

            /**
             * The callback triggered every 30 seconds to report the current number of online users.
             *
             * This interface is called back every 30 seconds.
             * Developers can use this callback to show the number of user online in the current room.
             *
             * @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
             * @param count Count of online users
             */
            virtual void onRoomOnlineUserCountUpdate(const std::string& /*roomID*/, int /*count*/) {

            }

            /**
             * The callback triggered when the number of streams published by the other users in the same room increases or decreases.
             *
             * When a user logs in to a room for the first time, there are other users in the room who are publishing streams, and will receive a stream list of the added type.
             * When the user is already in the room, other users in this room will trigger this callback to notify the changed stream list when adding or deleting streams.
             * Developers can use this callback to determine if there are other users in the same room who have added or stopped streaming, in order to implement active play stream [startPlayingStream] or active stop playing stream [stopPlayingStream], and use simultaneous Changes to Streaming render UI widget;
             *
             * @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
             * @param updateType Update type (add/delete)
             * @param streamList Updated stream list
             */
            virtual void onRoomStreamUpdate(const std::string& /*roomID*/, ZegoUpdateType /*updateType*/, const std::vector<ZegoStream>& /*streamList*/) {

            }

            /**
             * The callback triggered when there is an update on the extra information of the streams published by other users in the same room.
             *
             * When a user publishing the stream update the extra information of the stream in the same room, other users in the same room will receive the callback.
             * The stream extra information is an extra information identifier of the stream ID. Unlike the stream ID, which cannot be modified during the publishing process, the stream extra information can be modified midway through the stream corresponding to the stream ID.
             * Developers can synchronize variable content related to stream IDs based on stream additional information.
             *
             * @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
             * @param streamList List of streams that the extra info was updated.
             */
            virtual void onRoomStreamExtraInfoUpdate(const std::string& /*roomID*/, const std::vector<ZegoStream>& /*streamList*/) {

            }

            /**
             * The callback triggered when there is an update on the extra information of the room.
             *
             * When a user update the room extra information, other users in the same room will receive the callback.
             *
             * @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
             * @param roomExtraInfoList List of the extra info updated.
             */
            virtual void onRoomExtraInfoUpdate(const std::string& /*roomID*/, const std::vector<ZegoRoomExtraInfo>& /*roomExtraInfoList*/) {

            }

            /**
             * The callback triggered when the state of stream publishing changes.
             *
             * After publishing the stream successfully, the notification of the publish stream state change can be obtained through the callback interface.
             * You can roughly judge the user's uplink network status based on whether the state parameter is in [PUBLISH_REQUESTING].
             * ExtendedData is extended information with state updates. If you use ZEGO's CDN content distribution network, after the stream is successfully published, the keys of the content of this parameter are flv_url_list, rtmp_url_list, hls_url_list. These correspond to the publishing stream URLs of the flv, rtmp, and hls protocols.
             *
             * @param streamID Stream ID
             * @param state Status of publishing stream
             * @param errorCode The error code corresponding to the status change of the publish stream. Please refer to the common error code documentation [https://doc-en.zego.im/en/308.html] for details.
             * @param extendedData Extended information with state updates.
             */
            virtual void onPublisherStateUpdate(const std::string& /*streamID*/, ZegoPublisherState /*state*/, int /*errorCode*/, const std::string& /*extendedData*/) {

            }

            /**
             * The callback triggered every 3 seconds to report the current stream publishing quality.
             *
             * After the successful publish, the callback will be received every 3 seconds. Through the callback, the collection frame rate, bit rate, RTT, packet loss rate and other quality data of the published audio and video stream can be obtained, and the health of the publish stream can be monitored in real time.
             * You can monitor the health of the published audio and video streams in real time according to the quality parameters of the callback api, in order to show the uplink network status in real time on the device UI interface.
             * If you does not know how to use the parameters of this callback api, you can only pay attention to the level field of the quality parameter, which is a comprehensive value describing the uplink network calculated by SDK based on the quality parameters.
             *
             * @param streamID Stream ID
             * @param quality Published stream quality, including audio and video frame rate, bit rate, resolution, RTT, etc.
             */
            virtual void onPublisherQualityUpdate(const std::string& /*streamID*/, const ZegoPublishStreamQuality& /*quality*/) {

            }

            /**
             * The callback triggered when the first audio frame is captured.
             *
             * After the startPublishingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of audio data.
             * In the case of no startPublishingStream audio and video stream or preview, the first startPublishingStream audio and video stream or first preview, that is, when the engine of the audio and video module inside SDK starts, it will collect audio data of the local device and receive this callback.
             * Developers can use this callback to determine whether SDK has actually collected audio data. If the callback is not received, the audio capture device is occupied or abnormal.
             */
            virtual void onPublisherCapturedAudioFirstFrame() {

            }

            /**
             * The callback triggered when the first video frame is captured.
             *
             * After the startPublishingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of video data.
             * In the case of no startPublishingStream video stream or preview, the first startPublishingStream video stream or first preview, that is, when the engine of the audio and video module inside SDK starts, it will collect video data of the local device and receive this callback.
             * Developers can use this callback to determine whether SDK has actually collected video data. If the callback is not received, the video capture device is occupied or abnormal.
             *
             * @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
             */
            virtual void onPublisherCapturedVideoFirstFrame(ZegoPublishChannel /*channel*/) {

            }

            /**
             * The callback triggered when the video capture resolution changes.
             *
             * After the successful publish, the callback will be received if there is a change in the video capture resolution in the process of publishing the stream.
             * When the audio and video stream is not published or previewed for the first time, the publishing stream or preview first time, that is, the engine of the audio and video module inside the SDK is started, the video data of the local device will be collected, and the collection resolution will change at this time.
             * You can use this callback to remove the cover of the local preview UI and similar operations.You can also dynamically adjust the scale of the preview view based on the resolution of the callback.
             *
             * @param width Video capture resolution width
             * @param height Video capture resolution width
             * @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
             */
            virtual void onPublisherVideoSizeChanged(int /*width*/, int /*height*/, ZegoPublishChannel /*channel*/) {

            }

            /**
             * The callback triggered when the state of relayed streaming to CDN changes.
             *
             * After the ZEGO real-time audio and video cloud relays the audio and video streams to the CDN, this callback will be received if the CDN relay status changes, such as a stop or a retry.
             * Developers can use this callback to determine whether the audio and video streams of the relay CDN are normal. If they are abnormal, further locate the cause of the abnormal audio and video streams of the relay CDN and make corresponding disaster recovery strategies.
             * If you do not understand the cause of the abnormality, you can contact ZEGO technicians to analyze the specific cause of the abnormality.
             *
             * @param streamID Stream ID
             * @param infoList List of information that the current CDN is relaying
             */
            virtual void onPublisherRelayCDNStateUpdate(const std::string& /*streamID*/, const std::vector<ZegoStreamRelayCDNInfo>& /*infoList*/) {

            }

            /**
             * The callback triggered when the state of stream playing changes.
             *
             * After publishing the stream successfully, the notification of the publish stream state change can be obtained through the callback interface.
             * You can roughly judge the user's downlink network status based on whether the state parameter is in [PLAY_REQUESTING].
             *
             * @param streamID stream ID
             * @param state Current play state
             * @param errorCode The error code corresponding to the status change of the playing stream. Please refer to the common error code documentation [https://doc-en.zego.im/en/308.html] for details.
             * @param extendedData Extended Information with state updates. As the standby, only an empty json table is currently returned
             */
            virtual void onPlayerStateUpdate(const std::string& /*streamID*/, ZegoPlayerState /*state*/, int /*errorCode*/, const std::string& /*extendedData*/) {

            }

            /**
             * The callback triggered every 3 seconds to report the current stream playing quality.
             *
             * After calling the startPlayingStream successfully, this callback will be triggered every 3 seconds. The collection frame rate, bit rate, RTT, packet loss rate and other quality data  can be obtained, such the health of the publish stream can be monitored in real time.
             * You can monitor the health of the played audio and video streams in real time according to the quality parameters of the callback api, in order to show the downlink network status on the device UI interface in real time.
             * If you does not know how to use the various parameters of the callback api, you can only focus on the level field of the quality parameter, which is a comprehensive value describing the downlink network calculated by SDK based on the quality parameters.
             *
             * @param streamID Stream ID
             * @param quality Playing stream quality, including audio and video frame rate, bit rate, resolution, RTT, etc.
             */
            virtual void onPlayerQualityUpdate(const std::string& /*streamID*/, const ZegoPlayStreamQuality& /*quality*/) {

            }

            /**
             * The callback triggered when a media event occurs during streaming playing.
             *
             * This callback is triggered when an event such as audio and video jamming and recovery occurs in the playing stream.
             * You can use this callback to make statistics on stutters or to make friendly displays in the UI interface of the app.
             *
             * @param streamID Stream ID
             * @param event Play media event callback
             */
            virtual void onPlayerMediaEvent(const std::string& /*streamID*/, ZegoPlayerMediaEvent /*event*/) {

            }

            /**
             * The callback triggered when the first audio frame is received.
             *
             * After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of audio data.
             *
             * @param streamID Stream ID
             */
            virtual void onPlayerRecvAudioFirstFrame(const std::string& /*streamID*/) {

            }

            /**
             * The callback triggered when the first video frame is received.
             *
             * After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of video  data.
             *
             * @param streamID Stream ID
             */
            virtual void onPlayerRecvVideoFirstFrame(const std::string& /*streamID*/) {

            }

            /**
             * The callback triggered when the first video frame is rendered.
             *
             * After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it rendered the first frame of video  data.
             * You can use this callback to count time consuming that take the first frame time or update the playback stream.
             *
             * @param streamID Stream ID
             */
            virtual void onPlayerRenderVideoFirstFrame(const std::string& /*streamID*/) {

            }

            /**
             * The callback triggered when the stream playback resolution changes.
             *
             * If there is a change in the video resolution of the playing stream, the callback will be triggered, and the user can adjust the display for that stream dynamically.
             * If the publishing stream end triggers the internal stream flow control of SDK due to a network problem, the encoding resolution of the streaming end may be dynamically reduced, and this callback will also be received at this time.
             * If the stream is only audio data, the callback will not be received.
             * This callback will be triggered when the played audio and video stream is actually rendered to the set UI play canvas. You can use this callback notification to update or switch UI components that actually play the stream.
             *
             * @param streamID Stream ID
             * @param width The width of the video
             * @param height The height of the video
             */
            virtual void onPlayerVideoSizeChanged(const std::string& /*streamID*/, int /*width*/, int /*height*/) {

            }

            /**
             * The callback triggered when Supplemental Enhancement Information is received.
             *
             * After the remote stream is successfully played, when the remote stream sends SEI (such as directly calling [sendSEI], audio mixing with SEI data, and sending custom video capture encoded data with SEI, etc.), the local end will receive this callback.
             *
             * @param streamID Stream ID
             * @param data SEI content
             * @param dataLength SEI content length.
             */
            virtual void onPlayerRecvSEI(const std::string& /*streamID*/, const unsigned char* /*data*/, unsigned int /*dataLength*/) {

            }

            /**
             * The callback triggered when the state of relayed streaming of the mixed stream to CDN changes.
             *
             * In the general case of the ZEGO audio and video cloud mixing stream task, the output stream is published to the CDN using the rtmp protocol, and changes in the state during the publish will be notified from this callback api.
             *
             * @param taskID Mix stream task ID
             * @param infoList List of information that the current CDN is being mixed
             */
            virtual void onMixerRelayCDNStateUpdate(const std::string& /*taskID*/, const std::vector<ZegoStreamRelayCDNInfo>& /*infoList*/) {

            }

            /**
             * The callback triggered when the sound level of any input stream changes in the stream mixing process.
             *
             * You can use this callback to show the effect of the anchors sound level when the audience plays the mixed stream. So audience can notice which anchor is speaking.
             *
             * @param soundLevels Sound level hash map, key is the soundLevelID of every single stream in this mixer stream, value is the sound level value of that single stream, value ranging from 0.0 to 100.0
             */
            virtual void onMixerSoundLevelUpdate(const std::unordered_map<unsigned int, float>& /*soundLevels*/) {

            }

            /**
             * The callback triggered when there is a change to audio devices (i.e. new device added or existing device deleted).
             *
             * This callback is triggered when an audio device is added or removed from the system. By listening to this callback, users can update the sound collection or output using a specific device when necessary.
             *
             * @param updateType Update type (add/delete)
             * @param deviceType Audio device type
             * @param deviceInfo Audio device information
             */
            virtual void onAudioDeviceStateChanged(ZegoUpdateType /*updateType*/, ZegoAudioDeviceType /*deviceType*/, const ZegoDeviceInfo& /*deviceInfo*/) {

            }

            /**
             * The callback triggered when there is a change to video devices (i.e. new device added or existing device deleted).
             *
             * This callback is triggered when a video device is added or removed from the system. By listening to this callback, users can update the video capture using a specific device when necessary.
             *
             * @param updateType Update type (add/delete)
             * @param deviceInfo Audio device information
             */
            virtual void onVideoDeviceStateChanged(ZegoUpdateType /*updateType*/, const ZegoDeviceInfo& /*deviceInfo*/) {

            }

            /**
             * The callback triggered every 100ms to report the sound level of the locally captured audio.
             *
             * Callback notification period is 100 ms'. To trigger this callback API, the [startSoundLevelMonitor] interface must be called to start the sound level monitor and you must be in a state where it is publishing the audio and video stream or be in [startPreview] state.
             *
             * @param soundLevel Locally captured sound level value, ranging from 0.0 to 100.0
             */
            virtual void onCapturedSoundLevelUpdate(float /*soundLevel*/) {

            }

            /**
             * The callback triggered every 100ms to report the sound level of the remote stream.
             *
             * Callback notification period is 100 ms'. To trigger this callback API, the [startSoundLevelMonitor] interface must be called to start the sound level monitor and you must be in a state where it is playing the audio and video stream.
             *
             * @param soundLevels Remote sound level hash map, key is the streamID, value is the sound level value of the corresponding streamID, value ranging from 0.0 to 100.0
             */
            virtual void onRemoteSoundLevelUpdate(const std::unordered_map<std::string, float>& /*soundLevels*/) {

            }

            /**
             * The callback triggered every 100ms to report the audio spectrum of the locally captured audio.
             *
             * Callback notification period is 100 ms'. To trigger this callback API, the [startAudioSpectrumMonitor] interface must be called to start the audio spectrum monitor and you must be in a state where it is publishing the audio and video stream or be in [startPreview] state.
             *
             * @param audioSpectrum Locally captured audio spectrum value list. Spectrum value range is [0-2^30]
             */
            virtual void onCapturedAudioSpectrumUpdate(const ZegoAudioSpectrum& /*audioSpectrum*/) {

            }

            /**
             * The callback triggered every 100ms to report the audio spectrum of the remote stream.
             *
             * Callback notification period is 100 ms'. To trigger this callback API, the [startAudioSpectrumMonitor] interface must be called to start the audio spectrum monitor and you must be in a state where it is playing the audio and video stream.
             *
             * @param audioSpectrums Remote audio spectrum hash map, key is the streamID, value is the audio spectrum list of the corresponding streamID. Spectrum value range is [0-2^30]
             */
            virtual void onRemoteAudioSpectrumUpdate(const std::unordered_map<std::string, ZegoAudioSpectrum>& /*audioSpectrums*/) {

            }

            /**
             * The callback triggered when a device exception occurs.
             *
             * This callback is triggered when an exception occurs when reading or writing the audio and video device.
             *
             * @param errorCode The error code corresponding to the status change of the playing stream. Please refer to the common error code documentation [https://doc-en.zego.im/en/308.html] for details
             * @param deviceName device name
             */
            virtual void onDeviceError(int /*errorCode*/, const std::string& /*deviceName*/) {

            }

            /**
             * The callback triggered when the state of the remote camera changes.
             *
             * When the state of the remote camera device changes, such as switching the camera, by monitoring this callback, it is possible to obtain an event related to the far-end camera, which can be used to prompt the user that the video may be abnormal.
             * Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the camera device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
             *
             * @param streamID Stream ID
             * @param state Remote camera status
             */
            virtual void onRemoteCameraStateUpdate(const std::string& /*streamID*/, ZegoRemoteDeviceState /*state*/) {

            }

            /**
             * The callback triggered when the state of the remote microphone changes.
             *
             * When the state of the remote microphone device is changed, such as switching a microphone, etc., by listening to the callback, it is possible to obtain an event related to the remote microphone, which can be used to prompt the user that the audio may be abnormal.
             * Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the microphone device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
             *
             * @param streamID Stream ID
             * @param state Remote microphone status
             */
            virtual void onRemoteMicStateUpdate(const std::string& /*streamID*/, ZegoRemoteDeviceState /*state*/) {

            }

            /**
             * The callback triggered when Broadcast Messages are received.
             *
             * @param roomID Room ID
             * @param messageList list of received messages.
             */
            virtual void onIMRecvBroadcastMessage(const std::string& /*roomID*/, std::vector<ZegoBroadcastMessageInfo> /*messageList*/) {

            }

            /**
             * The callback triggered when Barrage Messages are received.
             *
             * @param roomID Room ID
             * @param messageList list of received messages.
             */
            virtual void onIMRecvBarrageMessage(const std::string& /*roomID*/, std::vector<ZegoBarrageMessageInfo> /*messageList*/) {

            }

            /**
             * The callback triggered when a Custom Command is received.
             *
             * @param roomID Room ID
             * @param fromUser Sender of the command
             * @param command Command content received
             */
            virtual void onIMRecvCustomCommand(const std::string& /*roomID*/, ZegoUser /*fromUser*/, const std::string& /*command*/) {

            }

        };


        class IZegoAudioMixingHandler
        {
        protected:

            virtual ~IZegoAudioMixingHandler() {}

        public:

            /**
             * The callback for copying audio data to the SDK for audio mixing. This API should be used together with enableAudioMixing.
             *
             * Supports 16k 32k 44.1k 48k sample rate, mono or dual channel, 16-bit deep PCM audio data
             * This callback is a high frequency callback. To ensure the quality of the mixing data, please do not handle time-consuming operations in this callback
             *
             * @param data audio mixing data
             */
            virtual void onAudioMixingCopyData(ZegoAudioMixingData* /*data*/) {

            }

        };


        class IZegoMediaPlayerEventHandler
        {
        protected:

            virtual ~IZegoMediaPlayerEventHandler() {}

        public:

            /**
             * The callback triggered when the state of the media player changes.
             *
             * @param mediaPlayer Callback player object
             * @param state Media player status
             * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
             */
            virtual void onMediaPlayerStateUpdate(IZegoMediaPlayer* /*mediaPlayer*/, ZegoMediaPlayerState /*state*/, int /*errorCode*/) {

            }

            /**
             * The callback triggered when the network status of the media player changes.
             *
             * @param mediaPlayer Callback player object
             * @param networkEvent Network status event
             */
            virtual void onMediaPlayerNetworkEvent(IZegoMediaPlayer* /*mediaPlayer*/, ZegoMediaPlayerNetworkEvent /*networkEvent*/) {

            }

            /**
             * The callback to report the current playback progress of the media player.
             *
             * @param mediaPlayer Callback player object
             * @param millisecond Progress in milliseconds
             */
            virtual void onMediaPlayerPlayingProgress(IZegoMediaPlayer* /*mediaPlayer*/, unsigned long long /*millisecond*/) {

            }

        };


        class IZegoMediaPlayerVideoHandler
        {
        protected:

            virtual ~IZegoMediaPlayerVideoHandler() {}

        public:

            /**
             * The callback triggered when the media player throws out video frame data.
             *
             * @param mediaPlayer Callback player object
             * @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
             * @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
             * @param param video data frame param
             */
            virtual void onVideoFrame(IZegoMediaPlayer* /*mediaPlayer*/, const unsigned char** /*data*/, unsigned int* /*dataLength*/, ZegoVideoFrameParam /*param*/) {

            }

        };


        class IZegoMediaPlayerAudioHandler
        {
        protected:

            virtual ~IZegoMediaPlayerAudioHandler() {}

        public:

            /**
             * The callback triggered when the media player throws out audio frame data.
             *
             * @param mediaPlayer Callback player object
             * @param data Raw data of audio frames
             * @param dataLength Data length
             * @param param audio frame flip mode
             */
            virtual void onAudioFrame(IZegoMediaPlayer* /*mediaPlayer*/, const unsigned char* /*data*/, unsigned int /*dataLength*/, ZegoAudioFrameParam /*param*/) {

            }

        };


        class IZegoDataRecordEventHandler
        {
        protected:

            virtual ~IZegoDataRecordEventHandler() {}

        public:

            /**
             * The callback triggered when the state of data recording (to a file) changes.
             *
             * @param state File recording status, according to which you should determine the state of the file recording or the prompt of the UI.
             * @param errorCode Error code, please refer to the common error code document [https://doc-en.zego.im/en/308.html] for details
             * @param config Record config
             * @param channel Publishing stream channel
             */
            virtual void onCapturedDataRecordStateUpdate(ZegoDataRecordState /*state*/, int /*errorCode*/, ZegoDataRecordConfig /*config*/, ZegoPublishChannel /*channel*/) {

            }

            /**
             * The callback to report the current recording progress.
             *
             * @param progress File recording progress, which allows developers to hint at the UI, etc.
             * @param config Record config
             * @param channel Publishing stream channel
             */
            virtual void onCapturedDataRecordProgressUpdate(ZegoDataRecordProgress /*progress*/, ZegoDataRecordConfig /*config*/, ZegoPublishChannel /*channel*/) {

            }

        };


        class IZegoCustomVideoCaptureHandler
        {
        protected:

            virtual ~IZegoCustomVideoCaptureHandler() {}

        public:

            /**
             * The callback triggered when the SDK is ready to receive captured video data. Only those video data that are sent to the SDK after this callback is received are valid.
             *
             * @param channel Publishing stream channel
             */
            virtual void onStart(ZegoPublishChannel channel) = 0;

            /**
             * The callback triggered when SDK stops receiving captured video data.
             *
             * @param channel Publishing stream channel
             */
            virtual void onStop(ZegoPublishChannel channel) = 0;

        };


        class IZegoCustomVideoRenderHandler
        {
        protected:

            virtual ~IZegoCustomVideoRenderHandler() {}

        public:

            /**
             * The callback for obtaining the locally captured video frames (Raw Data).
             *
             * @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
             * @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
             * @param param Video frame parameters
             * @param flipMode video flip mode
             * @param channel Publishing stream channel
             */
            virtual void onCapturedVideoFrameRawData(unsigned char** /*data*/, unsigned int* /*dataLength*/, ZegoVideoFrameParam /*param*/, ZegoVideoFlipMode /*flipMode*/, ZegoPublishChannel /*channel*/) {

            }

            /**
             * The callback for obtaining the video frames (Raw Data) of the remote stream. Different streams can be identified by streamID.
             *
             * @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
             * @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
             * @param param Video frame parameters
             * @param streamID Stream ID
             */
            virtual void onRemoteVideoFrameRawData(unsigned char** /*data*/, unsigned int* /*dataLength*/, ZegoVideoFrameParam /*param*/, const std::string& /*streamID*/) {

            }

            /**
             * The callback for obtianing the video frames (Encoded Data) of the remote stream. Different streams can be identified by streamID.
             *
             * @param data Encoded data of video frames
             * @param dataLength Data length
             * @param param Video frame parameters
             * @param referenceTimeMillisecond video frame reference time, UNIX timestamp, in milliseconds.
             * @param streamID Stream ID
             */
            virtual void onRemoteVideoFrameEncodedData(const unsigned char* /*data*/, unsigned int /*dataLength*/, ZegoVideoEncodedFrameParam /*param*/, unsigned long long /*referenceTimeMillisecond*/, const std::string& /*streamID*/) {

            }

        };


        class IZegoCustomAudioProcessHandler
        {
        protected:

            virtual ~IZegoCustomAudioProcessHandler() {}

        public:

            /**
             * Custom audio processing local captured PCM audio frame callback.
             *
             * @param data Audio frame data.
             * @param dataLength Audio framw data length.
             * @param param Audio frame parameters.
             */
            virtual void onProcessCapturedAudioData(unsigned char* /*data*/, unsigned int /*dataLength*/, ZegoAudioFrameParam* /*param*/) {

            }

            /**
             * Custom audio processing remote playing stream PCM audio frame callback.
             *
             * @param data Audio frame data.
             * @param dataLength Audio frame data length.
             * @param param Audio frame parameters.
             * @param streamID Stream ID
             */
            virtual void onProcessRemoteAudioData(unsigned char* /*data*/, unsigned int /*dataLength*/, ZegoAudioFrameParam* /*param*/, const std::string& /*streamID*/) {

            }

        };


        class IZegoAudioDataHandler
        {
        protected:

            virtual ~IZegoAudioDataHandler() {}

        public:

            /**
             * The callback for obtaining the audio data captured by the local microphone.
             *
             * In non-custom audio capture mode, the SDK capture the microphone's sound, but the developer may also need to get a copy of the The audio data captured by the SDK SDK is available through this callback.
             * On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [enableAudioDataCallback] to set the mask 0x01, this callback will be triggered only when it is in the publishing stream state.
             *
             * @param data audio data of pcm format
             * @param dataLength length of data
             * @param param param of audio frame
             */
            virtual void onCapturedAudioData(const unsigned char* /*data*/, unsigned int /*dataLength*/, ZegoAudioFrameParam /*param*/) {

            }

            /**
             * The callback for obtaining the audio data of all the remote streams pulled.
             *
             * This method will callback all of the remote user's audio mix data. This callback can be used for that you needs to fetch all the playing streams to proccess.
             * On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [enableAudioDataCallback] to set the mask 0x02, this callback will be triggered only when it is in the playing stream state.
             *
             * @param data audio data of pcm format
             * @param dataLength length of data
             * @param param param of audio frame
             */
            virtual void onRemoteAudioData(const unsigned char* /*data*/, unsigned int /*dataLength*/, ZegoAudioFrameParam /*param*/) {

            }

            /**
             * The callback for obtaining the mixed audio data. Such mixed auido data are generated by the SDK by mixing the audio data of all the remote streams pulled and the auido data captured locally.
             *
             * The audio data of all playing data is mixed with the data captured by the local microphone before it is sent to the loudspeaker, and calleback out in this way.
             * On the premise of calling [setAudioDataHandler] to set the listener callback, after calling [enableAudioDataCallback] to set the mask 0x04, this callback will be triggered only when it is in the publishing stream state or playing stream state.
             *
             * @param data audio data of pcm format
             * @param dataLength length of data
             * @param param param of audio frame
             */
            virtual void onMixedAudioData(const unsigned char* /*data*/, unsigned int /*dataLength*/, ZegoAudioFrameParam /*param*/) {

            }

        };

    } //namespace EXPRESS
} //namespace ZEGO

#endif // __ZEGOEXPRESSHANDLERS_H__
