//
// Copyright (c) 2019-2025 yanggaofeng
//

#ifndef INCLUDE_YANGRTC_YANGRTCPACER_H_
#define INCLUDE_YANGRTC_YANGRTCPACER_H_
#include <yangrtc/YangPeerConnection8.h>
#ifdef __cplusplus
extern "C"{

	class YangCallbackPacer{
	public:
		YangCallbackPacer(){};
		virtual ~YangCallbackPacer(){};
		virtual int32_t on_audio(YangPushData* audioData)=0;
		virtual int32_t on_video(YangPushData* videoData)=0;
	};

	class YangRtcPacer {
	public:
		YangRtcPacer(){};
		virtual ~YangRtcPacer(){};
	public:
		virtual int32_t reset()=0;
		virtual int32_t process()=0;

		virtual int32_t resetAudioTime()=0;
		virtual int32_t resetVideoTime()=0;
		virtual int32_t writeAudioFrame(YangFrame* audioFrame)=0;
		//frametype:YANG_Frametype_I YANG_Frametype_P
		//not pace mode
		virtual int32_t writeVideoFrame(YangFrame* videoFrame)=0;
		virtual int32_t bufferAudioFrame(YangFrame* audioFrame)=0;
		//frametype:YANG_Frametype_I YANG_Frametype_P
		//pace mode
		virtual int32_t bufferVideoFrame(YangFrame* videoFrame)=0;
		virtual int32_t attachConnection(YangPeerConnection8* conn)=0;
	};
	YANG_EXPORT_API YangRtcPacer* yang_create_rtcPacer(YangPeerInfo* peerInfo,yangbool hasAudio,yangbool hasVideo,YangCallbackPacer* pacerCallback);
}

#else

typedef struct  {
	 void* session;
	 int32_t (*reset)(void* session);
	 int32_t (*process)(void* session);

	 int32_t (*resetAudioTime)(void* session);
	 int32_t (*resetVideoTime)(void* session);
	 int32_t (*writeAudioFrame)(void* session,YangFrame* audioFrame);
	//frametype:YANG_Frametype_I YANG_Frametype_P
	//not pace mode
	 int32_t (*writeVideoFrame)(void* session,YangFrame* videoFrame);
	 int32_t (*bufferAudioFrame)(void* session,YangFrame* audioFrame);
	//frametype:YANG_Frametype_I YANG_Frametype_P
	//pace mode
	 int32_t (*bufferVideoFrame)(void* session,YangFrame* videoFrame);
	 int32_t (*attachConnection)(void* session,YangPeerConnection8* conn);
}YangRtcPacer;

YANG_EXPORT_API int32_t yang_create_rtcPacer(YangRtcPacer* pacer,YangPeerInfo* peerInfo,yangbool hasAudio,yangbool hasVideo,YangPacerCallback* pacerCallback);
YANG_EXPORT_API int32_t yang_destroy_rtcPacer(YangRtcPacer* pacer);

#endif

#endif /* INCLUDE_YANGRTC_YANGRTCPACER_H_ */
