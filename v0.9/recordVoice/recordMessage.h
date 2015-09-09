#ifndef RECORDMESSAGE_H
#define RECORDMESSAGE_H

/** *********************************************************
    ˵��:
    ���ļ�Ϊ��v0.9���recordvoice��recordMessage.h���õ��ļ�
    GuiRecordNotifyC ��Ա����˵����
    command: 1:��ʼ 0:ֹͣ
    flag: ��Ӧ clientMain.h�к궨��� m_flag
        UploadRecord : �Ὣ¼����¼�����ݿ�
        SaveRecord,  : ֻ�Ǳ����� nand��
        TestRecord   : GUI���Թ��ܣ��򱣴���nand��test.wav�ļ�
    sample: 0 1 2 3
    time: ¼��ʱ�䳤�ȣ��Ϊ10���� 10*60=600����GUI����ʱӦָ��
    Ϊ0���Ա����ֹͣ¼���ܼ�ʱ��Ч�������������һֱ¼��ָ��ʱ�䳤��

    [zhenyubin 2014/12/30]
************************************************************/

#include "dbusMessage.h"

#define NOTF_ID_GUI_RECORD  1177
#define REQ_ID_GUI_RECORD   1177
#define REP_ID_GUI_RECORD   1177

//¼��֪ͨ,��Ϣ,�ظ� [zhenyubin 2014/12/30]
enum enuRecordCommand
{
    StopRecord=0,
    StartRecord
};

/** ***********************************************************
    �洢��־
    ��Ӧ clientMain.h�к궨��
    �� m_flag
    #define UPLOAD 0
    #define SAVE 1
    #define TEST 2 //Gui¼�����Թ��� [zhenyubin 2014/12/30]
**************************************************************/
enum enuRecordFlag
{
    UploadRecord =0,
    SaveRecord,
    TestRecord
};
class GuiRecordNotifyC:public DBusNotifyC
{
    DBUS_NOTIFY_OBJECT(GuiRecordNotifyC)

public:
    GuiRecordNotifyC():DBusNotifyC(NOTF_ID_GUI_RECORD){}
    ~GuiRecordNotifyC(){}

    enuRecordCommand command; //1: ��ʼ 0��ֹͣ
    enuRecordFlag flag; //���滹�ǲ���
    int sample; //������ 0: 8000 1: 11000; 2: 23000; 3: 32000;
    int time; //¼��ʱ�� Gui����Ӧ��ָ��Ϊ0 �����ܼ�ʱ����ֹͣ����
};
class GuiReqRecordC:public DBusRequestC
{
    DBUS_REQUEST_OBJECT(GuiReqRecordC)

public:
    GuiReqRecordC():DBusRequestC(REQ_ID_GUI_RECORD){}
    char filePath[256]; //¼���ļ���
};
class GuiRepRecordC:public DBusReplyC
{
    DBUS_REPLY_OBJECT(GuiRepRecordC)

public:
    GuiRepRecordC():DBusReplyC(REP_ID_GUI_RECORD){}
    bool received;
};

#endif // RECORDMESSAGE_H
