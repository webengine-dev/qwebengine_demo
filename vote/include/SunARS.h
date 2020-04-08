#ifndef SUNARS_H
#define SUNARS_H

#ifndef _WIN32
#include <stdio.h>


#define __declspec(dllexport)
#endif

extern "C" __declspec(dllexport) int License(int Mode, const char* sInfo);

extern "C" __declspec(dllexport) int Connect(int iMode,const char* sParam);
extern "C" __declspec(dllexport) int Disconnect(int iBaseID);

extern "C" __declspec(dllexport) int WriteHDParam(int iBaseID,int iMode, const char* sSetting);

extern "C" __declspec(dllexport) int ReadHDParam(int iBaseID,int iMode);
extern "C" __declspec(dllexport) int ReadHDParam2(int iBaseID,int iMode ,const char* sSetting);

extern "C" __declspec(dllexport) int VoteStart(int iMode, const char* sSetting);
extern "C" __declspec(dllexport) int VoteStart2(int iBaseID,int iMode, const char* sSetting);
extern "C" __declspec(dllexport) int VoteStartExt(int iBaseID, int iMode, const char* sSetting,const char* title,const char * keySn);

extern "C" __declspec(dllexport) int VoteStop();
extern "C" __declspec(dllexport) int VoteStop2(int iBaseID);

extern "C" __declspec(dllexport) int VoteStopByMsg(char * sInfo);
extern "C" __declspec(dllexport) int VoteStopByMsg2(int iBaseID,char * sInfo);

extern "C" __declspec(dllexport) int GetMultiResultByID(const char* sKeyIDs, int resultType, int resultId);
extern "C" __declspec(dllexport) int GetMultiResultByID2(int iBaseID, const char* KeyIDs, int resultType, int resultId);

extern "C" __declspec(dllexport) int GetResultBySN(const char* sKeySn, int resultType, int resultId);
extern "C" __declspec(dllexport) int GetResultBySN2(int iBaseID, const char* keySn, int resultType, int resultId);

extern "C" __declspec(dllexport) int ExitGetResult();
extern "C" __declspec(dllexport) int ExitGetResult2(int iBaseID);

extern "C" __declspec(dllexport) int SendExamMultiAnswer(const char * sInfo);
extern "C" __declspec(dllexport) int SendExamMultiAnswer2(int iBaseID,const char * sInfo);

extern "C" __declspec(dllexport) int SendExamChoiceAnswer100(int iBaseID,const char * sInfo);

extern "C" __declspec(dllexport) int WriteHDParamBySn(const char* sKeySn,int iMode, const char* sSetting);//deprecated,use WriteKeypadParam
extern "C" __declspec(dllexport) int ReadHDParamBySn(const char* sKeySn,int iMode);//deprecated,use ReadKeypadParam

extern "C" __declspec(dllexport) int WriteKeypadParam(int iBaseID,int iKeyID,const char * sKeySn,int iMode, const char* sSetting);
extern "C" __declspec(dllexport) int ReadKeypadParam(int iBaseID,int iKeyID,const char* sKeySn,int iMode,const char* sSetting);


extern "C" __declspec(dllexport) int KeypadFirmwareUpdate(int iBaseID, const char * filePath,const char * firmwareVer, int hardwareVer, int keyMode, const char * keys);
extern "C" __declspec(dllexport) int DeviceFirmwareUpdate(int iBaseID,const char * filePath,int deviceType,const char * groups);

extern "C" __declspec(dllexport) int WriteKeypadShareholder(int iBaseID,int  iKeyID ,const char * sKeySn,int encode, const char * sName,int byteLen);

extern "C" __declspec(dllexport) int WriteKeypadShares(int iBaseID,int  iKeyID ,const char * sKeySn,int ballots,int balMode);

extern "C" __declspec(dllexport) int WriteKeypadDataTable(int iBaseID,int  iKeyID ,const char * sKeySn,int downType,int downId,const char * filePath);


extern "C" __declspec(dllexport) int StopDownload(int iBaseID);

extern "C" __declspec(dllexport) int GetStaIP();
extern "C" __declspec(dllexport) int SetDemoMode(int isEnable,const char* keyIDs,int keyInteval);
extern "C" __declspec(dllexport) int SetLogOn(int isEnable);
extern "C" __declspec(dllexport) int CheckBaseConnection();
extern "C" __declspec(dllexport) int StopTaskAndFree();

 
extern "C" __declspec(dllexport) int OpenNfcReader(int autoFindCard);
extern "C" __declspec(dllexport) int CloseNfcReader();
extern "C" __declspec(dllexport) int WriteNFCData(char * wifi_ssid, char * wifi_pwd, char * userId, char * userName, int credit);
extern "C" __declspec(dllexport) int ReadNFCData();

extern "C" __declspec(dllexport) int FirewallConfig();
extern "C" __declspec(dllexport) int AddAppToWhiteList(const char* fullPath, const char* name);


typedef void (*ConnectEventCallBack)(int iBaseID, int iMode, const char* sInfo);
typedef void (*HDParamCallBack)(int iBaseID, int iMode, const char* sInfo);
typedef void (*HDParamBySnCallBack)(const char* keySn, int iMode, const char* sInfo);//deprecated,use KeypadParamCallBack
typedef void (*KeypadParamCallBack)(int iBaseID, int iKeyID ,const char* sKeySn, int iMode, const char* sInfo);
typedef void (*VoteEventCallBack)(int iBaseID, int iMode, const char* sInfo);
typedef void (*KeyEventCallBack)(int iBaseID,int iKeyID, const char* sKeySN, int iMode, float Time, const char* sInfo);
typedef void (*StaIpEventCallBack)(const char* sInfo);
typedef void (*LogEventCallBack)(const char* sInfo);
typedef void(*VoiceStreamEventCallBack)(int keyId, const char* keySn, int sampleRate, int bitsPerSample, int channel, const char* data, int len,int recFlag);


extern "C" __declspec(dllexport) void SetConnectEventCallBack(ConnectEventCallBack cb);
extern "C" __declspec(dllexport) void SetHDParamEventCallBack(HDParamCallBack cb);
extern "C" __declspec(dllexport) void SetHDParamBySnEventCallBack(HDParamBySnCallBack cb);
extern "C" __declspec(dllexport) void SetKeypadParamEventCallBack(KeypadParamCallBack cb);
extern "C" __declspec(dllexport) void SetVoteEventCallBack(VoteEventCallBack cb);
extern "C" __declspec(dllexport) void SetKeyEventCallBack(KeyEventCallBack cb);
extern "C" __declspec(dllexport) void SetStaEventCallBack(StaIpEventCallBack cb);
extern "C" __declspec(dllexport) void SetLogEventCallBack(LogEventCallBack cb);
extern "C" __declspec(dllexport) void SetVoiceStreamEventCallBack(VoiceStreamEventCallBack cb);

#endif // SUNARS_H
