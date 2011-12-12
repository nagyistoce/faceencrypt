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
	//数据项
    private:
		bool Sub_Key[16][48];
		EncryInfo   _printInfo;
	    CListBox     *listCtrl;
  //函数：
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
		BOOL EncryFile(CString srcfile,CString psw);   //加密文件，
		BOOL UncryFile(CString srcfile,CString psw);   //解密文件
		BOOL EncryDir(CString _fileName,CString _pwd); //加密文件夹
		BOOL UncryDir(CString _fileName,CString _pwd); //解密文件夹
		void SetPrintInfo(EncryInfo crIn,CListBox *_listCtrl); //显示加密状态信息
        void printInfo(CString info,int errMod);
};
#endif