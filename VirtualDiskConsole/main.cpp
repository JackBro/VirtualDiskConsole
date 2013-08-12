
#include <iostream>
#include "String.h"
#include "LinkList.h"
#include "Stack.h"
#include "Queue.h" 
#include "Lexer.h"
#include <atlstr.h>
#include "VirtualDiskConsole.h"
#include <conio.h>
#include "FileSystem.h"
 
#pragma warning(disable:4786)

 

void PrintWelcomeHead(void)
{
	for( int i = 0 ; i < 70 ; i++ )
	{
		std::cout<<"*";
	} 
	std::cout<<std::endl; 
	std::cout<<"*"<<std::endl; 
	std::cout<<"*"<<"          "<<"�������ϵͳ"<<std::endl; 
	std::cout<<"*"<<std::endl;  
	for( int i = 0 ; i < 70 ; i++ )
	{
		std::cout<<"*";
	}
	std::cout<<std::endl;
}

void PrintBackspace( const int times = 1)
{
	for( int i = 0 ; i < times ; i++ )
	{
		std::cout<<'\b';
		std::cout<<' ';
		std::cout<<'\b';
	}
}
int main(void)
{ 
	using namespace Util;
	using namespace std;
	using namespace LexerSys;

	setlocale(LC_ALL,"");

	PrintWelcomeHead();

	VirtualDiskConsole::CreateInstance();
	VirtualDiskConsole::GetInstance()->Init();

	StackT<Util::String> cmd_history;

	{//Ԥ��������
	/*	VirtualDiskConsole::GetInstance()->AddCommand("copy C:\\drivers\\win\\camera\\* drivers");
		VirtualDiskConsole::GetInstance()->AddCommand("cd drivers");*/
	}
	 
	char *pmb = (char *)malloc( MB_CUR_MAX );

	while( 1 )
	{
		Util::String cmd_str;
		wint_t input_c = 0;
		bool direction_button_press = false;  

		VirtualDiskConsole::GetInstance()->ExecuteCommandQueue();
		VirtualDiskConsole::GetInstance()->PrintPrompt(); 
		 

		//ֻҪ�û�û�а��س���
		while( ( input_c=  _getwch() ) != VK_RETURN )
		{  
			if( direction_button_press )
			{
				//���������ϼ�
				if( input_c == 72 )
				{ 
					//����������ʷ
					if( cmd_history.Size() )
					{
						Util::String prev_cmd = cmd_history.Front();
						cmd_history.Pop();
						PrintBackspace( cmd_str.Length() );
						cmd_str = prev_cmd;
						std::cout<<cmd_str;
					}
				}
				direction_button_press = false;
				continue;
			}

			if( input_c == 224 )
			{
				direction_button_press = true;
				continue;
			}

			//��Ϊ�˸��
			if( input_c == VK_BACK )
			{
				if( cmd_str.Length() )
				{  
						unsigned char byte_del = static_cast<unsigned char>( cmd_str.PopBack() );
						PrintBackspace();  
						if( byte_del > 127 )
						{
							cmd_str.PopBack();
							PrintBackspace();
						}
				}
			}else{    
				_putwch( input_c );  
				int size_convert = 0;
				wctomb_s( &size_convert , pmb , MB_CUR_MAX , input_c );
 
				for( int i = 0 ; i < size_convert ; i++ )
				{
					cmd_str.Append( pmb[i] );  
				}
			} 
		}
		std::cout<<std::endl;

		if( cmd_str.Length() == 0 )
		{
			continue;;
		} 

		Util::String special_cmd = cmd_str;

		special_cmd.ClearAllWhiteChars();
		special_cmd.ConvertToLowercast();

		//�˳�ϵͳ����
		if( special_cmd == "exit" )
		{
			std::cout<<"�˳�ϵͳ!"<<std::endl;
			break; 
		}else if( special_cmd == "show_volume"){//��ʾ��������

			double used_size_bytes = static_cast<double>( FileSys::FileSystem::GetInstance()->TotalSize() ) / ( 1024.0f*1024.0f );
			double virtualdisk_capacity =  static_cast<double>( FileSys::FileSystem::GetInstance()->Capacity() ) / ( 1024.0f*1024.0f );

			std::cout<<"��ʹ�ÿռ䣺"<<used_size_bytes<<"MB"<<endl;
			std::cout<<"�ܿռ䣺"<<virtualdisk_capacity<<"MB"<<endl;
			std::cout<<"��ʹ���ˣ�"<<( used_size_bytes/virtualdisk_capacity)*100.0f<<"%"<<endl;
			continue;
		}

		VirtualDiskConsole::GetInstance()->ExecuteCommand( cmd_str );
		VirtualDiskConsole::GetInstance()->PrintResult();

		//��ִ������������������ʷ��
		cmd_history.Push( cmd_str );
	}
	
	free( pmb );
	pmb = NULL;

	VirtualDiskConsole::GetInstance()->Destroy();
	VirtualDiskConsole::DestroyInstance(); 
	 
}