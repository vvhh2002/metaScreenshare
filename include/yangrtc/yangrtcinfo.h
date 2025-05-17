//
// Copyright (c) 2019-2025 yanggaofeng
//

#ifndef SRC_YANGRTCINFO8_H_
#define SRC_YANGRTCINFO8_H_
#include <stdint.h>
#if Yang_Enale_RtcInfo

#ifndef INCLUDE_YANGUTIL_YANGAVINFO_H_
#define INCLUDE_YANGUTIL_YANGAVINFO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef  uint8_t yangbool;
#define yangtrue 1
#define yangfalse 0

#define YANG_Frametype_I 1
#define YANG_Frametype_P 0

typedef enum {
	Yang_IpFamilyType_IPV4,
	Yang_IpFamilyType_IPV6
} YangIpFamilyType;

typedef enum{
	YangTransportAll,
	YangTransportRelay
}YangIceTransportPolicy;

typedef enum{
	YangIceModeFull,
	YangIceModeLite
}YangIceMode;

typedef enum {
	YangIceNew,
    YangIceSuccess,
    YangIceFail
} YangIceCandidateState;

typedef enum {
	YangIceGatherNew,
	YangIceGathering,
    YangIceGatherComplete
} YangIceGatheringState;

typedef enum {
    Yang_Conn_State_New,
    Yang_Conn_State_Connecting,
    Yang_Conn_State_Connected,
    Yang_Conn_State_Disconnected,
    Yang_Conn_State_Failed,
    Yang_Conn_State_Closed
} YangRtcConnectionState;
typedef enum YangAudioCodec{
	Yang_AED_AAC,
	Yang_AED_MP3,
	Yang_AED_SPEEX,
	Yang_AED_OPUS,
	Yang_AED_PCMA,
	Yang_AED_PCMU
}YangAudioCodec;

typedef enum{
	Yang_VED_H264,
	Yang_VED_H265
}YangVideoCodec;

typedef enum{
	YangMediaAudio,
	YangMediaVideo
}YangMediaTrack;


typedef enum{
	YangRateHold,
	YangRateIncrese,
	YangRateDecrese
}YangLostRateState;

typedef enum{
	YangSendrecv,
	YangSendonly,
	YangRecvonly,
	YangInactive
}YangRtcDirection;

typedef struct{
	int16_t mediaType;
	int16_t frametype;
	int32_t capacity;

	int32_t uid;
	int32_t nb;

	int64_t pts;
	int64_t dts;
	uint8_t* payload;
}YangFrame;

typedef struct {
	YangAudioCodec encode;
	int32_t  sample;
	int32_t  channel;
    int32_t  audioClock;
    int32_t  fec;
}YangAudioParam;

typedef struct  {
	YangVideoCodec encode;
	int32_t  videoClock;
}YangVideoParam;

typedef enum YangRequestType {
	Yang_Req_Sendkeyframe,
	Yang_Req_HighLostPacketRate,
	Yang_Req_LowLostPacketRate,
	Yang_Req_Connected,
	Yang_Req_Disconnected
}YangRequestType;

typedef struct{
	void* context;
	void (*sslAlert)(void* context,int32_t  uid,char* type,char* desc);
}YangSslCallback;

typedef struct {
	 void* context;
	 void (*receiveAudio)(void* context,YangFrame *audioFrame);
	 void (*receiveVideo)(void* context,YangFrame *videoFrame);
	 void (*receiveMsg)(void* context,YangFrame *videoFrame);
}YangReceiveCallback;

typedef struct{
	void* context;
	void (*onIceStateChange)(void* context,int32_t  uid,YangIceCandidateState iceState);
	void (*onConnectionStateChange)(void* context, int32_t  uid,YangRtcConnectionState connectionState);
	void (*onIceCandidate)(void* context, int32_t  uid,char* sdp);
	void (*onIceGatheringState)(void* context, int32_t  uid,YangIceGatheringState gatherState);
}YangIceCallback;

typedef struct{
	void* context;
	void (*estimate)(void* context,int32_t  puid,YangLostRateState  lostState,uint32_t target_bitrate);
	void (*updateRttRate)(void* context,int32_t  puid,uint32_t rtt,uint32_t ack_bitrate,float lossrate);
}YangEstimateCallback;

typedef struct{
	void* context;
	void (*setMediaConfig)(void* context,int32_t  puid,YangAudioParam* audio,YangVideoParam* video);
	void (*sendRequest)(void* context,int32_t  puid,uint32_t  ssrc,YangRequestType req);
}YangRtcCallback;

typedef struct  {
	YangSslCallback sslCallback;
	YangRtcCallback rtcCallback;
	YangIceCallback iceCallback;
	YangReceiveCallback recvCallback;
	YangEstimateCallback estCallback;
}YangPeerCallback;

typedef struct{
	void* pushData;
}YangPushData;

typedef struct{
	void* session;
	int32_t (*on_audio)(void* session,YangPushData* pushData);
	int32_t (*on_video)(void* session,YangPushData* pushData);
}YangPacerCallback;

typedef struct{
	int32_t enableAudioFec;
	int32_t sample;
	int32_t channel;

	YangAudioCodec  audioEncoderType;
}YangPushAudioInfo;

typedef struct{
	int32_t width;
	int32_t height;
	int32_t fps;
	YangVideoCodec  videoEncoderType;
}YangPushVideoInfo;



typedef enum{
	YANG_DATA_CHANNEL_DCEP = 50,
	YANG_DATA_CHANNEL_STRING = 51,
	YANG_DATA_CHANNEL_BINARY = 53,
	YANG_DATA_CHANNEL_STRING_EMPTY = 56,
	YANG_DATA_CHANNEL_BINARY_EMPTY = 57
}YangDataChannelType;


typedef struct YangRtcInfo {
	yangbool enableFec;
	yangbool enablePacer;
	yangbool isControlled;
	yangbool enableSdpCandidate;

	int32_t  sessionTimeout;
	int32_t  iceCandidateType;
	YangIceTransportPolicy iceTransportPolicy;

	int32_t  iceServerPort;

	int32_t  rtcSocketProtocol;
	int32_t  turnSocketProtocol;

	int32_t  rtcPort;
	int32_t  rtcLocalPort;

	int32_t turnReqInterval;
	int32_t maxTurnWaitTime;

	int32_t maxPacerDelayTime;
	int32_t nackPktCount;

	char iceServerIP[64];
	char iceUserName[32];
	char icePassword[64];
}YangRtcInfo;




typedef struct{
	int32_t uid;
	int32_t userId;
	int32_t remotePort;
	YangIceMode iceMode;
	YangIpFamilyType familyType;
	YangRtcDirection direction;

	YangRtcInfo rtc;
	YangPushAudioInfo pushAudio;
	YangPushVideoInfo pushVideo;
}YangPeerInfo;


typedef struct{
	void* conn;
	YangPeerInfo peerInfo;
	YangPeerCallback peerCallback;
}YangPeer;

#endif

#endif

#if _WIN32
#define YANG_EXPORT_API __declspec(dllexport)
#else
#define YANG_EXPORT_API
#endif


#endif /* SRC_YANGRTCINFO8_H_ */
