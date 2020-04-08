#ifndef PARADEF_H_
#define PARADEF_H_


typedef enum {
	conn_type_usb = 1,
	conn_type_tcpip = 2,
	conn_type_ble = 3,
	conn_type_android_com = 4,
	conn_type_andoird_usb = 5,
	conn_type_voice_base = 6,
	conn_type_nfc = 7, //读音基站读卡器连接
	conn_type_end
}ConnectType;

typedef enum {
	BaseStation_RFPower = 1,				//基站功率
	BaseStation_Channel = 2,				// ,  基站主信道
	BaseStation_CommunicationChannels = 3,	//通讯通道：是否中继，通道数，通道1，通道2，通道3，通道4
	BaseStation_IP = 4,						//IP
	BaseStation_MAC = 5,					//mac地址
	BaseStation_SubnetMask = 6,				//子网掩码
	BaseStation_Gateway = 7,				//网关
	BaseStation_Title = 8,					//基站名称
	BaseStation_ID = 9,						//基站编号
	BaseStation_SN = 10,						//硬件序列号（ 只读）
	BaseStation_Version = 11,				//硬件版本
	BaseStation_PairCode = 12,				//配对码
	BaseStation_MatchCode = 12,				//配对码

	SoftwareDongle_VerifyPWD = 13,			//验证密码
	SoftwareDongle_A_PWD = 14,				//软件狗密码
	SoftwareDongle_A_Zone = 15,				//软件狗读写A区
	SoftwareDongle_B_Zone = 16,

	Keypad_Config = 17,						//键盘设置  ReportMode, offtime, SubmisMode, Buzzer, LCD,Vib, Lang

	Keypad_WorkingMode = 18,				//键盘连接模式（固定配对、自由配对、免配对）
	Keypad_IdentificationMode = 19,			//键盘识别模式（是否SN号模式）

Keypad_ID = 20,							//键盘编号
Keypad_UserID = 21,						//用户编号
Keypad_SN = 22,							//键盘出厂序列号
Keypad_Version = 23,					//键盘版本信息
Keypad_MatchCode = 24,					//配对码




WiFi_SSID = 25,							//组合 baseMode,ssid
WiFi_WorkMode = 26,
WiFi_Password = 27,

Background_SignIn = 28,
Keypad_AuthorizeByID = 29,
Keypad_AuthorizeBySN = 30,

BaseStation_ChannelInterference = 31,
BaseStation_AutoChangeChannel = 32,

BaseStation_Model = 33,
Keypad_Model = 34,
Keypad_UserName = 35,					//用户姓名

Keypad_MonitorEnable = 36,           // 键盘定时监听投票信标
Keypad_KeepPowerOn = 37,        //键盘不关机，用于测试和生产
Keypad_SignalFrequence = 38,   //考勤信号每秒次数
Keypad_SignalPower = 39,    //键盘发送考勤信号功率
BaseStation_MatchPassword = 40, //自由模式下基站的密码
BaseStation_Time = 41,          //考勤基站时间
BaseStation_AttendanceRepeatFilter = 42,   //基站去重配置

SoftwareDongle_C_Zone = 43,
SoftwareDongle_D_Zone = 44,
BaseStation_UID = 45, //基站唯一硬件编号UID
BaseStation_OEM = 46,  //基站OEM硬件信息
Keypad_OEM = 47,

BaseStation_WhiteList = 48,


Device_FirmUpdateMode = 50,//
Device_FirmSendProgress = 51,
Device_firmUpdateError = 52,
Device_FirmUpdateProgress = 53,

Keypad_FirmUpdateMode = 54,//
Keypad_FirmUpdateProgress = 55,
Keypad_firmUpdateError = 56,

Keypad_Shareholder = 57,
Keypad_Shares = 58,
Keypad_SharesShow = 59,

Keypad_DataDownloadMode = 60,
Keypad_DataDownloadProgress = 61,

Keypad_HomeworkEnable = 62,

BaseStation_FreeMatchSnModeConfig = 63,//免配对SN号模式基站设置

BaseStation_WhiteListAdd = 64,
BaseStation_WhiteListRemove = 65,
BaseStation_WhiteListCheck = 66,    //not support
BaseStation_WhiteListClear = 67,    //not support

VoiceKeypad_UserInfo = 68,

Keypad_Gold = 80,

Keypad_DisplayBigID = 81,
Keypad_DisplayFlash = 82,
Keypad_FeedBackConfig = 83, //即时反馈设置
Keypad_FeedBackKeyInfo = 84,//即时反馈按键提示自定义等级

Keypad_BTMAC = 85,//定制键盘的蓝牙MAC地址

BaseStation_LowPowerMatch = 86, //低功率快速配对

Keypad_UserNameDelete = 87,//清空姓名

Keypad_Bind = 88, //语音基站遥控绑定和解绑 1绑定，2解绑
VoiceBaseStation_HardwareInfo = 89, //语音基站硬件信息
VoiceBaseStation_HardwareConfig = 90, //震动，蜂鸣，指示灯，状态报告设置
VoiceBaseStation_BackgroudEnable = 91,

BaseStation_AskApply = 101,//请教申请
Keypad_AutoPowerOffLevel = 102, //   4档键盘自动关机时间 :00 - 30秒 01-2分钟 10-10分钟 11-45分钟
Keypad_DisplayMessage = 103, //键盘显示自定义文字


ExamConfigInfoFile = 104,//下发多题测验题型，答案或打分

BaseStation_FreeMatchModeSetBaseOnLine = 105,
BaseUploadHomeworkStart = 106,
BaseUploadHomeworkStop = 107,
Keypad_CallEnable = 108,

BaseStation_CustomVoteTitle = 109,//预设键盘自定义标题

Keypad_HeartBeatEnable = 110,// 键盘心跳开关 


    BaseStation_BootLoaderMode = 201,
    KeyPad_PowerOff = 222,
    
    
    param_End
} ParamType;


typedef enum{
	KeyPad_Config = 17,             //deprecated ,use Keypad_Config
    KeyPad_ConnectionMode = 18,		//deprecated, use Keypad_WorkingMode
    KeyPad_IdentificationMode = 19,	//deprecated, use Keypad_IdentificationMode
    KeyPad_ID = 20,					//deprecated, use Keypad_ID
    KeyPad_UserID = 21,				//deprecated, use Keypad_UserID
    KeyPad_SN = 22,					//deprecated, use Keypad_SN
    KeyPad_Version = 23,			//deprecated, use Keypad_Version
    KeyPad_PairCode = 24,			//deprecated, use Keypad_MatchCode
	KeyPad_UserName = 35,           //deprecated, use Keypad_UserName
}deprecatedType;

typedef enum {
    VoteType_Free = 0,						//空闲模式(停止)
    VoteType_Signin = 1,					//签到
    VoteType_Vote = 2,						//表决
    
    VoteType_Number = 4,					//数值 （单项评分模式）
    VoteType_TrueFalse = 5,					//判断
    VoteType_KeyPadTest = 9	,				//模拟测试
    VoteType_Choice = 10,					//选择
    VoteType_Sequence = 11,					//排序
    VoteType_FillBlanks = 12,				//填空
    VoteType_Quiz = 13,						//抢答
    
    VoteType_Examination = 14,				//测验
    VoteType_Homework = 15,					//作业
	VoteType_Voice = 16,					//语音答题
	VoteType_GroupPK = 17,					//分组PK
    VoteType_Election = 22,                 //选举
    VoteType_KeyPadMatch = 40,				//配对
    VoteType_Continue = 100,
    VoteType_SubmitAndContinue = 101,
    
    VoteType_End
} VoteType;


typedef enum {
	KeyResult_info = 1,						//结果
	KeyResult_status = 2,					//状态
	KeyResult_loginInfo = 3,				//登录信息
	KeyResult_remoteControl = 4,            //表决器遥控指令应答
	KeyResult_match = 5,                    //配对信息
	KeyResult_attendance = 6,               //考勤定位
	KeyResult_keyCode = 7,                  //键值
	KeyResult_voice = 8,
	KeyResult_voice_speed = 9,
	KeyResult_wav_file = 10,
	KeyResult_voice_stream = 11,			//语音流

	KeyResult_nfc = 12,						//读到卡时返回
	KeyResult_uncommited = 13,			   //课后练习未提交的数目
	KeyResult_nfc_data = 14,			   //读写NFC卡数据时返回
	
    KeyResult_end
} KeypadResultType;


 
#define	T1_KEY_CODE_A 1
#define	T1_KEY_CODE_B 2
#define	T1_KEY_CODE_C 3
#define	T1_KEY_CODE_D 4
#define	T1_KEY_CODE_L 13
#define	T1_KEY_CODE_R 14
#define	T1_KEY_CODE_CENTER 16

	 
 

#endif
