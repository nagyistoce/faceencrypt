#include "../StdAfx.h"
#include<memory.h>
#include<string.h>
#include <time.h>
#define Decode    0
#define Encode    1
#define ENCRYLEN  8
#define MaxFilenameLen 128
typedef void (*EncryInfo)(CString,int,CListBox*);
//bool Sub_Key[16][48];

#ifndef  DESENCRYPT_CLASS
#define  DESENCRYPT_CLASS

class DesEncrypt{
	//������
    private:
		bool Sub_Key[16][48];
		EncryInfo   _printInfo;
	    CListBox     *listCtrl;
  //������
   protected:
		void Generate_SubKey(bool*,bool*);
		void Rotate_Key(bool *,int);
		void Initial_Exchange(char *, bool*,bool* );
		void Exchange_Key(char *, bool*);
		void Expand_Right(bool*, bool*);
		void S_function(bool* ,bool* );
		void P_function(bool * );
		void Final_Exchange(bool* , bool*,char*);
		void BitToByte(char *Out, const bool *In, int bits);
   public:
	    DesEncrypt();
        void DES(char*,char *,int);
	    void Key_Process(char *);
		BOOL EncryFile(CString srcfile,CString psw);   //�����ļ���
		BOOL UncryFile(CString srcfile,CString psw);   //�����ļ�
		BOOL EncryDir(CString _fileName,CString _pwd); //�����ļ���
		BOOL UncryDir(CString _fileName,CString _pwd); //�����ļ���
		void SetPrintInfo(EncryInfo crIn,CListBox *_listCtrl); //��ʾ����״̬��Ϣ
        void printInfo(CString info,int errMod);
};
#endif