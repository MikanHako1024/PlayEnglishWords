/*
Declare Function PlaySound Lib "winmm.dll" Alias "PlaySoundA" (ByVal lpszName As String, ByVal hModule As Long, ByVal dwFlags As Long) As Long 
*/

//Declare Function PlaySound Lib "winmm.dll" Alias "PlaySoundA" 
//(ByVal lpszName As String, ByVal hModule As Long, ByVal dwFlags As Long) As Long 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define WAVPATH "D:\\wav\\wav\\"
//#define WAVPATH ""
//#define WAVPATH "wav\\"
#define WAVtzm ".wav"





int MyUsePlaySound(char *music_NAME) 
{
	return PlaySound(music_NAME, NULL, SND_FILENAME | SND_SYNC); // 调用播放 wav 文件的 API
		// ? 函数内自带大小写兼容
}






int MakeNameAndPlay(char *word, int len)
{
	if( len<=0 || len>100 )return 0;
	
	//int MyUsePlaySound(char *music_NAME); 
		// ? 用预处理声明

	char name[150]=WAVPATH, name_end[]=WAVtzm;
	int ind=0, ind_end=0, z;
	

	// ( 已添加路径 ) 找到末尾下标
	while(name[ind]!='\0')
		ind++;
	
	// 添加引索文件夹名
	name[ind++]= (*word);
	name[ind++]= '\\'; // 不是添加两个 '\' ( '\\' 是一个字符 : \ )


	// 添加单词名
	for(z=0; z<len; z++)
		name[ind++]= *(word++);

	// 添加拓展名和'\0'
	while(name_end[ind_end]!='\0')
		name[ind++]=name_end[ind_end++];
	name[ind++]='\0';
	
	//printf("%s\n", name);

	return MyUsePlaySound(name);
}





int MyPlayWord(char *str)
{
	if( *str=='\0' )return 0;
	return MakeNameAndPlay( str, strlen(str) );
}




int _MyPlayAWord(char *str, int len)
{
	if(len<=0)return 0;
	return MakeNameAndPlay(str, len);
}

int MyPlayWords(char *str)
{
	int sum=0, ind=0, tlen=0;
	char *tp=str;
	
	tp=str+ind;
	tlen=0;
	while( str[ind]!='\n' )
	{
		/*
		if(str[ind]==' ')
		{
			sum++;
			_MyPlayAWord(tp, tlen);
			tlen=0;
		}
		else
		{
			tlen++;
		}
		*/

		switch( str[ind] )
		{
			case ' ':
			case ',':
			case '.':
			case '\n':
				{
					sum+=_MyPlayAWord(tp, tlen);
					tp=tp+tlen;
					tlen=0;
					break;
				}
			//case '\0':
				//return sum;
			default:
				tlen++;
		}
	}
	
	return sum;
}






int main(int argc, char *argv[])
{	
	// argv[0] : 自身路径
	// argv[i] : 其他路径

	
	char str[100]="word";
	
	/*
	while(1)
	{
		scanf("%s", str);
		if( strcmp(str, "endit")==0 )break;
		MyPlayWord(str);
	}
	*/

	gets(str);
	//printf("%s\n", str);
	printf("\n%d\n", MyPlayWords(str));
	
	//system("pause"); // getchar();
	return 0;
}

