#include "StdAfx.h"
#include "encrypt.h"
//全局变量
unsigned char Initial [] =
{
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
};

//最终置换
unsigned char Final[] =
{
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

//S-盒置换
unsigned char S_Box[8][64] =
{
    /* S1 */
{ 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7, 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0, 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},

    /* S2 */
{ 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5, 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15, 13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},

    /* S3 */
{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},

    /* S4 */
{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9, 10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},

    /* S5 */
{2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},

    /* S6 */
{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11, 10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,  9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},

    /* S7 */
{4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1, 13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,  6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},

    /* S8 */
{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2, 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,  2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
};

unsigned char Key_Exchange[56] =
{
 57, 49, 41, 33, 25, 17,  9,
  1, 58, 50, 42, 34, 26, 18,
 10,  2, 59, 51, 43, 35, 27,
 19, 11,  3, 60, 52, 44, 36,
 63, 55, 47, 39, 31, 23, 15,
  7, 62, 54, 46, 38, 30, 22,
 14,  6, 61, 53, 45, 37, 29,
 21, 13,  5, 28, 20, 12,  4
};
//压缩变换
unsigned char Compression[] =
{
    14, 17, 11, 24,  1,  5, 3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8, 16, 7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

//扩展变换
unsigned char Expansion[] =
{
32,  1,  2,  3,  4,  5,
  4,  5,  6,  7,  8,  9,
  8,  9, 10, 11, 12, 13,
 12, 13, 14, 15, 16, 17,
 16, 17, 18, 19, 20, 21,
 20, 21, 22, 23, 24, 25,
 24, 25, 26, 27, 28, 29,
 28, 29, 30, 31, 32,  1
};

//P_盒置换
unsigned char P_Box[]=
{
    16, 7, 20, 21, 29, 12, 28, 17,
 1, 15, 23, 26, 5, 18, 31, 10,
 2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

//密钥置换
unsigned char Key[]=
{
    57, 49, 41, 33, 25, 17,  9, 1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

//
unsigned char Key_Move[]=
{
 1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1
};

//构造函数
DesEncrypt::DesEncrypt(){
}
/****************************************************************
 * //FUNC：加密文件函数
 * 1、参数：srcfile：待加密文件，dstfile：加密输出文件，psw:密码
 * 2、采用DES算法
*****************************************************************/
BOOL DesEncrypt::EncryFile(CString srcfile,CString psw){
	//ASSERT(psw.GetLength()==8);
	//文件类型判断，不能为当前文件类型，后缀为.znl,否则会尝试对刚创建的加密后的文件再次加密
	if(srcfile.Right(3)=="znl")
		return FALSE;
	//输入密码合法性判断
	if(psw.GetLength()>8){
		AfxMessageBox("请输入8位以内的密码，谢谢！");
		return FALSE;
	}
	//密码不足8位的补齐8位
	if(psw.GetLength()<8)
		for(int m=psw.GetLength();m<8;m++)
		psw.Insert(m,'0');
	//显示加密状态信息
	CString prInfo = "正在处理 ";
	prInfo += srcfile;
	printInfo(prInfo + "...",1);
	//构造目标文件名
	CString dstfile="";
	int dotIndex=srcfile.Find('.');
	dstfile=srcfile.Left(dotIndex+1)+"znl";
	//AfxMessageBox(dstfile);
	char Final_Result[12]={0};
	char * Message=0;
	Message=new char(12);
	//打开文件 用于输入
    CStdioFile input; CStdioFile out;
	try
	{
		if(!input.Open(srcfile,CStdioFile::modeReadWrite|CStdioFile::typeBinary))
		{
				prInfo = "打开文件 " + srcfile + " 错误";
				printInfo(prInfo,2);
				AfxMessageBox(prInfo);
				return FALSE;
		}
		input.SeekToBegin();
		if(!out.Open(dstfile, CStdioFile::modeCreate|CStdioFile::modeReadWrite|CStdioFile::typeBinary))
		{
			prInfo = "打开文件 " + dstfile + " 错误";
			printInfo(prInfo,2);
			AfxMessageBox(prInfo);
			return FALSE;
		}
		//文件无有效数据情况处理
		int dwFilelen = input.GetLength();
		if(dwFilelen == 0)
		{
			input.Close();
			prInfo = "文件 " + srcfile + " 长度为0";
			printInfo(prInfo,4);
			return FALSE;
		}
		//首先将源文件名和经过处理后的密码存入目标文件
		//文件名最长为MaxFilenameLen，太短的需要用特殊符号‘#’补齐
		out.SeekToBegin();
		if(srcfile.GetLength()<MaxFilenameLen)
		  for(int m=srcfile.GetLength();m<MaxFilenameLen;m++)
			  srcfile.Insert(m,'#');
		out.Write(srcfile,MaxFilenameLen);
		//把密码信息存入
		out.Write(psw,ENCRYLEN);
	    unsigned 	int n=0;
	    Key_Process(psw.GetBuffer(psw.GetLength()));
		n=input.Read(Message,8);
	    while(n){
			//不足8的字节的字符串需要补齐
		    if(n<8)
			for(int i=n;i<8;i++)
				Message[i]='\0';
		    DES(Message,Final_Result,Encode);
	    	Final_Result[8]=0;
		    out.Write(Final_Result,8);
		    memset(Message,0,8);
		    //重新读入
		    n=input.Read(Message,8);
		}
		input.Close();
		out.Close();
	}catch(CException e){
		//删除已经创建但加密未成功写入的目标文件
		CStdioFile::Remove(dstfile);
		prInfo = "加密文件 ";
		prInfo += srcfile + " 发生异常!";
		printInfo(prInfo,3);
		AfxMessageBox("加密文件<---"+srcfile+"--->失败，请重试！");
		input.Close();
		out.Close();
	}
	//AfxMessageBox(srcfile);
    //删除原文件
    CStdioFile::Remove(srcfile.Left(srcfile.Find('#')));
    return  TRUE;
}
/*********************************************************************
 * //FUNC：解密文件函数
 * 1、参数：srcfile：待加密文件，dstfile：加密输出文件，psw:密码
 * 2、采用DES算法
*********************************************************************/;
BOOL DesEncrypt::UncryFile(CString srcfile,CString psw){
	//ASSERT(psw.GetLength()==8);
	//文件类型判断，不能为当前文件类型，后缀为.znl,否则会尝试对刚创建的解密后的文件再次解密
	if(srcfile.Right(3)!="znl")
		return FALSE;
	//显示加密状态信息
	CString prInfo = "正在处理 ";
	        prInfo += srcfile;
	        printInfo(prInfo + "...",1);
	if(psw.GetLength()>8){
		AfxMessageBox("请输入8位以内的密码，谢谢！");
		return FALSE;
	}
	//密码不足8位的补齐8位
    if(psw.GetLength()<8)
	  for(int m=psw.GetLength();m<8;m++)
		psw.Insert(m,'0');
	char Final_Result[12]={0};
	char * Message=0;
   	       Message=new char(12);
	CString dstfile="";//输出文件名
	//打开文件 用于输入/出
    CStdioFile input; 	CStdioFile out;
	try
	{
		if(!input.Open(srcfile,CStdioFile::modeReadWrite|CStdioFile::typeBinary)){
				prInfo = "打开文件 " + srcfile + " 错误";
				printInfo(prInfo,2);
				AfxMessageBox(prInfo);
				return FALSE;
		}
		///首先读取原来的的文件名称，并打开此文件以还原解密数据
		TCHAR *data1=0;
		data1=new TCHAR[MaxFilenameLen];
		input.Read(data1,MaxFilenameLen);
		dstfile=CString(data1);
		int nameEndIndex=dstfile.Find('#');
		dstfile=dstfile.Left(nameEndIndex);
		/**********打开新文件**********************/
		if(!out.Open(dstfile, CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary)){
			prInfo = "打开文件 " + dstfile + " 错误";
			printInfo(prInfo,2);
			AfxMessageBox(prInfo);
			return FALSE;
		}
		///其次验证密码是否正确，来决定是否解密
		CString pswFromFile="";
		TCHAR *data2=new TCHAR[ENCRYLEN];
		      input.Read(data2, ENCRYLEN);
		      pswFromFile=CString(data2);
		//重要，读取时后面可能含若干空格
		      pswFromFile=pswFromFile.Left(ENCRYLEN);
		// AfxMessageBox("pswfromfile="+pswFromFile);
		// AfxMessageBox("psw="+psw);
		if(pswFromFile!=psw){
			AfxMessageBox("您的密码有误，不能解密文件<--"+srcfile+"-->！");
			prInfo = "解密文件 ";
			prInfo += srcfile + " 发生异常!原因是：   密码不正确";
		    printInfo(prInfo,4);
			input.Close();
			out.Close();
			CStdioFile::Remove(dstfile);//删除已创建但未成功写入解密数据的文件
			return FALSE;
		}
		//设置文件指针到文件数据的开始部分；
		out.SeekToBegin();
	    int n=0;
		//int  tempLen=0;  //获取当前指针位置
		     n=input.Read(Message,8);
		Key_Process(psw.GetBuffer(psw.GetLength()));
	    while(n)
		{
			//不足64位的字符串需要补齐
		    if(n<8)
			for(int i=n;i<8;i++)
				Message[i]=0;
		    DES(Message,Final_Result,Decode);
		    Final_Result[8]=0;
		    out.Write(Final_Result,8);
		    memset(Message,0,8);
		    //重新读入
		    n=input.Read(Message,8);
		}
		input.Close();
		out.Close();
	}catch(CException e){
		prInfo = "解密文件 ";
		prInfo += srcfile + " 发生异常!";
		printInfo(prInfo,3);
		AfxMessageBox("解密文件<---"+dstfile+"--->失败，请重试！");
	    CStdioFile::Remove(dstfile);//删除已创建但未成功写入解密数据的文件
		input.Close();
		out.Close();
	}
	//删除原文件
    CStdioFile::Remove(srcfile);
    return  TRUE;
}

/************************************************************************/
/* FUNC:加密文件夹 
/*     参数：加密路径和密码                                                                    */
/************************************************************************/
BOOL DesEncrypt::EncryDir(CString _fileName,CString _pwd)
{
	//DWORD dwFilelen = 0;
	CFileFind tempFind;
	TCHAR tempFileFind[MAX_PATH] = {0};
	CString tempFile = _fileName;
	tempFile.TrimRight();
	if(tempFile.Right(1) != "\\")
	{
		tempFile += "\\";
	}
	sprintf(tempFileFind,"%s*.*",tempFile);
	BOOL IsFinded = (BOOL)tempFind.FindFile(tempFileFind);
	while(IsFinded)
	{
		IsFinded = (BOOL)tempFind.FindNextFile();
		if(!tempFind.IsDots())
		{
			TCHAR foundFileName[MAX_PATH] = {0};
			strncpy(foundFileName,tempFind.GetFilePath().GetBuffer(0),MAX_PATH);
			if(tempFind.IsDirectory())
			{
				CString subDir(_T(""));
				subDir.Format("%s",foundFileName);
				EncryDir(subDir,_pwd);
			}
			else
			{
				EncryFile(foundFileName,_pwd);
			}
		}
	}
	return TRUE;
}
/************************************************************************/
/*   FUNC:解密文件夹 
/*     参数：解密路径和密码                                                                    */
/************************************************************************/
BOOL DesEncrypt::UncryDir(CString _fileName,CString _pwd)
{
	//DWORD dwFilelen = 0;
	CFileFind tempFind;
	TCHAR tempFileFind[MAX_PATH] = {0};
	CString tempFile = _fileName;
	tempFile.TrimRight();
	if(tempFile.Right(1) != "\\")
	{
		tempFile += "\\";
	}
	sprintf(tempFileFind,"%s*.*",tempFile);
	BOOL IsFinded = (BOOL)tempFind.FindFile(tempFileFind);
	while(IsFinded)
	{
		IsFinded = (BOOL)tempFind.FindNextFile();
		if(!tempFind.IsDots())
		{
			TCHAR foundFileName[MAX_PATH] = {0};
			strncpy(foundFileName,tempFind.GetFilePath().GetBuffer(0),MAX_PATH);
			if(tempFind.IsDirectory())
			{
				CString subDir(_T(""));
				subDir.Format("%s",foundFileName);
				UncryDir(subDir,_pwd);
			}
			else
			{
			//	CString  fileName=foundFileName.
				UncryFile(foundFileName,_pwd);
			}
		}
	}
	return TRUE;
}
void DesEncrypt:: Key_Process(char *S_Key)
{
    int round ;
    bool Bit_Key[56];//56bits
   Exchange_Key(S_Key,Bit_Key);

 for(round = 0 ;round<16;round++)
 {
  //KL->消息左28位，KR->消息右28位
     bool*KL = &Bit_Key[0], *KR = &Bit_Key[28];
  //循环左移
     Rotate_Key(KL,Key_Move[round]);
     Rotate_Key(KR,Key_Move[round]);
  //产生子密钥
     Generate_SubKey(Bit_Key,Sub_Key[round]);
    }
}
void DesEncrypt::Exchange_Key(char *Key , bool* New_Key)
{
    int i ,j;
 bool Bit_Key[64];

 //Transform the initial key to bool type
 for(i = 0 ;i<8;i++)
  for(j=0;j<8;j++)
  {
   Bit_Key[i*8+j] = (Key[i]>>j)&0x01;
  }

    for(i=0;i<56;i++)
        New_Key[i]=Bit_Key[Key_Exchange[i]-1];
}

void DesEncrypt::Rotate_Key(bool*Key ,int round)
{
    bool temp[64];   
 //void *memcpy( void *to, const void *from, size_t count );
    //函数从from中复制count 个字符到to中，并返回to指针
    memcpy(temp, Key, round);  
    memcpy(Key, Key+round, 28-round); 
    memcpy(Key+28-round, temp, round); 
}
void DesEncrypt::Generate_SubKey(bool*Input, bool* Output)
{
 for(int i=0;i<48;i++ )
 {
     Output[i]=Input[Compression[i]-1];
    }
}

//DES函数
void DesEncrypt::DES( char*Message,char *Final_Result,int type)
{
    bool Right[32];//32bits
    bool Left[32];//32bits
    bool Expanded_Right[48];//扩展后的右消息
    bool flag[32];//用于左右消息交换
    bool Result1[48];//48bits
    bool Result2[32];//32bits
    int round ,i;

    Initial_Exchange(Message,Left,Right);
 
 //加密算法
    if(type == Encode)
	{
      for(  round = 0 ; round < 16 ; round++ )
	  {
      memcpy(flag,Right,32);

      Expand_Right(Right,Expanded_Right);

      for( i = 0 ; i<48 ; i++ )
       Result1[i]=Expanded_Right[i]^Sub_Key[round][i];

      S_function(Result1,Result2);

      P_function(Result2);

     for( i = 0 ; i<32 ; i++)
       Right[i] = Result2[i]^Left[i];
      memcpy(Left,flag,32);
  }
 }
 //解密算法
 else if(type == Decode)
 {

  for(  round = 15 ; round >=0 ; round-- )
  {
   memcpy(flag,Left,32);

   Expand_Right(Left,Expanded_Right);

   for( i = 0 ; i<48 ; i++ )
    Result1[i]=Expanded_Right[i]^Sub_Key[round][i];

   S_function(Result1,Result2);

   P_function(Result2);

   for( i = 0 ; i<32 ; i++)
    Left[i] = Result2[i]^Right[i];

    memcpy(Right,flag,32);
  }
 }
    Final_Exchange( Left , Right , Final_Result) ;

}

void DesEncrypt::Initial_Exchange(char *Message , bool*Left,bool*Right)
{
    bool temp[64];
    int i,j;
 //把 Message 转化成 bit形式
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            temp[i*8+j]= (Message[i]>>j)&0x01;
    for(i=0;i<32;i++)
        Left[i]=temp[Initial[i]-1];
    for(;i<64;i++)
        Right[i-32]=temp[Initial[i]-1];
}



void DesEncrypt::Expand_Right(bool*Input , bool*Output)
{
    for(int i =0;i<48;i++)
    Output[i]=Input[Expansion[i]-1];
}
void DesEncrypt::S_function(bool* Input,bool*Output)
{
    unsigned int x,y;
    char z;
    bool* in=Input;
    bool* out=Output;

    for(int j=0; j<8; j++,in+=6,out+=4)
    {
  //第1位和第6位
        x = (in[0]<<1) + in[5];
  //2-4位
        y = (in[1]<<3) + (in[2]<<2) + (in[3]<<1) + in[4];
  //由x y 确定的数z
        z = S_Box[j][x*16+y];
  //z用4个bit表示
        for(int i=0; i<4; i++)
        {
            out[i] = (z>>i) & 1;
        }
    }
}

void DesEncrypt::P_function(bool* a)
{
    bool temp[32];
    memcpy(temp,a,32);
    for(int i = 0 ;i<32;i++)
        a[i]=temp[P_Box[i]-1];
}


void DesEncrypt::Final_Exchange(bool*left , bool*right ,char*result )
{
    memset(result,0,8);
    bool temp1[64];
 //left 和 right 组合成 temp1
    memcpy(temp1,left,32);
    memcpy(temp1+32,right,32);
    bool temp2[64];
    for(int i=0;i<64;i++)
    {
  //由末置换得到temp2
        temp2[i]=temp1[Final[i]-1];
  //将temp2转化成char型
        result[i/8] |= temp2[i]<<(i%8);
    }
}
//显示加密信息
void DesEncrypt::SetPrintInfo(EncryInfo crIn,CListBox *_listCtrl)
{
	_printInfo = crIn;
	listCtrl = _listCtrl;
}
void DesEncrypt::printInfo(CString info,int errMod)
{
	if(_printInfo)
	{
		_printInfo(info,errMod,listCtrl);
	}
}