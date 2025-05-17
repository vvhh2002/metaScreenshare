//
// Copyright (c) 2019-2025 yanggaofeng
//

#ifndef INCLUDE_YANGRTC_YANGPEERCONNECTION8_H_
#define INCLUDE_YANGRTC_YANGPEERCONNECTION8_H_
#include <stdint.h>

#include <yangrtc/yangrtcinfo.h>

#ifdef __cplusplus

class YangCallbackReceive {
public:
	YangCallbackReceive(){};
	virtual ~YangCallbackReceive(){};
	virtual void receiveAudio(YangFrame* audioFrame)=0;
	//frametype:YANG_Frametype_I YANG_Frametype_P
	virtual void receiveVideo(YangFrame* videoFrame)=0;
	virtual void receiveMsg(YangFrame* msgFrame)=0;
};

class YangCallbackIce{
public:
	YangCallbackIce(){};
	virtual ~YangCallbackIce(){};
	virtual void onIceStateChange(int32_t  uid,YangIceCandidateState iceState)=0;
	virtual void onConnectionStateChange(int32_t  uid,YangRtcConnectionState connectionState)=0;
	virtual void onIceCandidate(int32_t  uid,char* sdp)=0;
	virtual void onIceGatheringState(int32_t  uid,YangIceGatheringState gatherState)=0;
};

class YangCallbackRtc{
public:
	YangCallbackRtc(){};
	virtual ~YangCallbackRtc(){};
	virtual void setMediaConfig(int32_t  uid,YangAudioParam* audio,YangVideoParam* video)=0;
	virtual void sendRequest(int32_t  uid,uint32_t  ssrc,YangRequestType req)=0;
};

class YangCallbackSslAlert{
public:
	YangCallbackSslAlert() {};
	virtual ~YangCallbackSslAlert() {};
	virtual void sslCloseAlert(int32_t  uid)=0;
};


class YangPeerConnection8 {
public:
	YangPeerConnection8(){};
	virtual ~YangPeerConnection8(){};
	YangPeer m_peer;
	virtual int32_t  addAudioTrack(YangAudioCodec codec)=0;
	virtual int32_t  addVideoTrack(YangVideoCodec codec)=0;

	virtual int32_t  addTransceiver(YangMediaTrack media,YangRtcDirection direction)=0;

	virtual int32_t  createOffer( char **psdp)=0;
	virtual int32_t  createAnswer(char* answer)=0;

	virtual int32_t  createDataChannel()=0;

	virtual int32_t  generateCertificate()=0;

	virtual int32_t  setLocalDescription(char* sdp)=0;
	virtual int32_t  setRemoteDescription(char* sdp)=0;

	virtual int32_t  close()=0;

	virtual yangbool  isAlive()=0;
	virtual yangbool  isConnected()=0;

	virtual int32_t  on_audio(YangPushData* audioData)=0;
	virtual int32_t  on_video(YangPushData* videoData)=0;
	virtual int32_t  on_message(YangFrame* msgFrame)=0;

	virtual int32_t  addIceCandidate(char* candidateStr)=0;
	virtual int32_t  sendRequestPli()=0;

};

extern "C"{
YANG_EXPORT_API YangPeerConnection8* yang_create_peerConnection8(YangPeerInfo* peerInfo,YangCallbackReceive* receive,YangCallbackIce* ice,YangCallbackRtc* rtc,YangCallbackSslAlert* sslAlert);


#else

typedef struct YangPeerConnection8 {
	YangPeer peer;
	int32_t  (*addAudioTrack)(YangPeer* peer,YangAudioCodec codec);
	int32_t  (*addVideoTrack)(YangPeer* peer,YangVideoCodec codec);
	int32_t  (*addTransceiver)(YangPeer* peer,YangMediaTrack media,YangRtcDirection direction);

	int32_t  (*createOffer)(YangPeer* peer, char **psdp);
	int32_t  (*createAnswer)(YangPeer* peer,char* answer);
	int32_t  (*createDataChannel)(YangPeer* peer);

	int32_t  (*generateCertificate)(YangPeer* peer);
	int32_t  (*setCertificateFile)(YangPeer* peer,char* pkeyfile,char* certfile);

	int32_t  (*setLocalDescription)(YangPeer* peer,char* sdp);
	int32_t  (*setRemoteDescription)(YangPeer* peer,char* sdp);

	int32_t  (*close)(YangPeer* peer);

	yangbool (*isAlive)(YangPeer* peer);
	yangbool (*isConnected)(YangPeer* peer);

	int32_t  (*on_audio)(YangPeer* peer,YangPushData *audioData);
	int32_t  (*on_video)(YangPeer* peer,YangPushData *videoData);
	int32_t  (*on_message)(YangPeer* peer,YangFrame* msgFrame);

	int32_t  (*addIceCandidate)(YangPeer* peer,char* candidateStr);
	int32_t  (*sendRequestPli)(YangPeer* peer);

	YangRtcConnectionState (*getConnectionState)(YangPeer* peer);
	YangIceCandidateType (*getIceCandidateType)(YangPeer* peer);
}YangPeerConnection8;

YANG_EXPORT_API int32_t yang_create_peerConnection8(YangPeerConnection8* conn);
YANG_EXPORT_API int32_t yang_destroy_peerConnection8(YangPeerConnection8* conn);

#endif

YANG_EXPORT_API void yang_init_peerParam(YangPeerInfo* peerInfo);


#ifdef __cplusplus
}
#endif
#endif /* INCLUDE_YANGRTC_YANGPEERCONNECTION8_H_ */
