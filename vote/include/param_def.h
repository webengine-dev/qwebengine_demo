#ifndef PARADEF_H_
#define PARADEF_H_


typedef enum {
	conn_type_usb = 1,
	conn_type_tcpip = 2,
	conn_type_ble = 3,
	conn_type_android_com = 4,
	conn_type_andoird_usb = 5,
	conn_type_voice_base = 6,
	conn_type_nfc = 7, //������վ����������
	conn_type_end
}ConnectType;

typedef enum {
	BaseStation_RFPower = 1,				//��վ����
	BaseStation_Channel = 2,				// ,  ��վ���ŵ�
	BaseStation_CommunicationChannels = 3,	//ͨѶͨ�����Ƿ��м̣�ͨ������ͨ��1��ͨ��2��ͨ��3��ͨ��4
	BaseStation_IP = 4,						//IP
	BaseStation_MAC = 5,					//mac��ַ
	BaseStation_SubnetMask = 6,				//��������
	BaseStation_Gateway = 7,				//����
	BaseStation_Title = 8,					//��վ����
	BaseStation_ID = 9,						//��վ���
	BaseStation_SN = 10,						//Ӳ�����кţ� ֻ����
	BaseStation_Version = 11,				//Ӳ���汾
	BaseStation_PairCode = 12,				//�����
	BaseStation_MatchCode = 12,				//�����

	SoftwareDongle_VerifyPWD = 13,			//��֤����
	SoftwareDongle_A_PWD = 14,				//���������
	SoftwareDongle_A_Zone = 15,				//�������дA��
	SoftwareDongle_B_Zone = 16,

	Keypad_Config = 17,						//��������  ReportMode, offtime, SubmisMode, Buzzer, LCD,Vib, Lang

	Keypad_WorkingMode = 18,				//��������ģʽ���̶���ԡ�������ԡ�����ԣ�
	Keypad_IdentificationMode = 19,			//����ʶ��ģʽ���Ƿ�SN��ģʽ��

Keypad_ID = 20,							//���̱��
Keypad_UserID = 21,						//�û����
Keypad_SN = 22,							//���̳������к�
Keypad_Version = 23,					//���̰汾��Ϣ
Keypad_MatchCode = 24,					//�����




WiFi_SSID = 25,							//��� baseMode,ssid
WiFi_WorkMode = 26,
WiFi_Password = 27,

Background_SignIn = 28,
Keypad_AuthorizeByID = 29,
Keypad_AuthorizeBySN = 30,

BaseStation_ChannelInterference = 31,
BaseStation_AutoChangeChannel = 32,

BaseStation_Model = 33,
Keypad_Model = 34,
Keypad_UserName = 35,					//�û�����

Keypad_MonitorEnable = 36,           // ���̶�ʱ����ͶƱ�ű�
Keypad_KeepPowerOn = 37,        //���̲��ػ������ڲ��Ժ�����
Keypad_SignalFrequence = 38,   //�����ź�ÿ�����
Keypad_SignalPower = 39,    //���̷��Ϳ����źŹ���
BaseStation_MatchPassword = 40, //����ģʽ�»�վ������
BaseStation_Time = 41,          //���ڻ�վʱ��
BaseStation_AttendanceRepeatFilter = 42,   //��վȥ������

SoftwareDongle_C_Zone = 43,
SoftwareDongle_D_Zone = 44,
BaseStation_UID = 45, //��վΨһӲ�����UID
BaseStation_OEM = 46,  //��վOEMӲ����Ϣ
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

BaseStation_FreeMatchSnModeConfig = 63,//�����SN��ģʽ��վ����

BaseStation_WhiteListAdd = 64,
BaseStation_WhiteListRemove = 65,
BaseStation_WhiteListCheck = 66,    //not support
BaseStation_WhiteListClear = 67,    //not support

VoiceKeypad_UserInfo = 68,

Keypad_Gold = 80,

Keypad_DisplayBigID = 81,
Keypad_DisplayFlash = 82,
Keypad_FeedBackConfig = 83, //��ʱ��������
Keypad_FeedBackKeyInfo = 84,//��ʱ����������ʾ�Զ���ȼ�

Keypad_BTMAC = 85,//���Ƽ��̵�����MAC��ַ

BaseStation_LowPowerMatch = 86, //�͹��ʿ������

Keypad_UserNameDelete = 87,//�������

Keypad_Bind = 88, //������վң�ذ󶨺ͽ�� 1�󶨣�2���
VoiceBaseStation_HardwareInfo = 89, //������վӲ����Ϣ
VoiceBaseStation_HardwareConfig = 90, //�𶯣�������ָʾ�ƣ�״̬��������
VoiceBaseStation_BackgroudEnable = 91,

BaseStation_AskApply = 101,//�������
Keypad_AutoPowerOffLevel = 102, //   4�������Զ��ػ�ʱ�� :00 - 30�� 01-2���� 10-10���� 11-45����
Keypad_DisplayMessage = 103, //������ʾ�Զ�������


ExamConfigInfoFile = 104,//�·�����������ͣ��𰸻���

BaseStation_FreeMatchModeSetBaseOnLine = 105,
BaseUploadHomeworkStart = 106,
BaseUploadHomeworkStop = 107,
Keypad_CallEnable = 108,

BaseStation_CustomVoteTitle = 109,//Ԥ������Զ������

Keypad_HeartBeatEnable = 110,// ������������ 


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
    VoteType_Free = 0,						//����ģʽ(ֹͣ)
    VoteType_Signin = 1,					//ǩ��
    VoteType_Vote = 2,						//���
    
    VoteType_Number = 4,					//��ֵ ����������ģʽ��
    VoteType_TrueFalse = 5,					//�ж�
    VoteType_KeyPadTest = 9	,				//ģ�����
    VoteType_Choice = 10,					//ѡ��
    VoteType_Sequence = 11,					//����
    VoteType_FillBlanks = 12,				//���
    VoteType_Quiz = 13,						//����
    
    VoteType_Examination = 14,				//����
    VoteType_Homework = 15,					//��ҵ
	VoteType_Voice = 16,					//��������
	VoteType_GroupPK = 17,					//����PK
    VoteType_Election = 22,                 //ѡ��
    VoteType_KeyPadMatch = 40,				//���
    VoteType_Continue = 100,
    VoteType_SubmitAndContinue = 101,
    
    VoteType_End
} VoteType;


typedef enum {
	KeyResult_info = 1,						//���
	KeyResult_status = 2,					//״̬
	KeyResult_loginInfo = 3,				//��¼��Ϣ
	KeyResult_remoteControl = 4,            //�����ң��ָ��Ӧ��
	KeyResult_match = 5,                    //�����Ϣ
	KeyResult_attendance = 6,               //���ڶ�λ
	KeyResult_keyCode = 7,                  //��ֵ
	KeyResult_voice = 8,
	KeyResult_voice_speed = 9,
	KeyResult_wav_file = 10,
	KeyResult_voice_stream = 11,			//������

	KeyResult_nfc = 12,						//������ʱ����
	KeyResult_uncommited = 13,			   //�κ���ϰδ�ύ����Ŀ
	KeyResult_nfc_data = 14,			   //��дNFC������ʱ����
	
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
