#include "MkdirCmd.h"
#include "Lexer.h"
#include "CreateDirVisitor.h"
#include "FileSystem.h"

namespace CommandSys
{


MkdirCmd::MkdirCmd(void)
{
}


MkdirCmd::~MkdirCmd(void)
{
}

void CommandSys::MkdirCmd::Execute( void )
{
	
	if( m_params.Count() )
	{
		m_result_output = "�����֧�ֲ���";
		return;
	}

	if( 0 == m_paths.Count() )
	{
		m_result_output = "�����﷨����ȷ";
		return;
	}

	for( int i = 0 ; i < m_paths.Count() ; i++ )
	{ 
			LexerSys::SearchPath path = m_paths.At(i);
			LexerSys::SearchPath final_path;

			//���Ҫ��Ѱ��·����Ϊ����·��
			if( !path.IsAbsolutePath() )
			{
				final_path = m_curr_path;
				final_path.Append( path ); 
			}else{

				if( 0 == path.At(0).Name().ICmp( "c:" ) )
				{
					final_path = path; 
				}else{
					m_result_output = "ϵͳ�Ҳ���ָ����·��";
					return;
				} 
			}

			FileSys::CreateDirVisitor visitor;
			visitor.SetPath( final_path );
			FileSys::FileSystem::GetInstance()->Accept( &visitor ); 
			
	}//for( int i = 0 ; i < m_paths.Count() ; i++ )
}

}//namespace CommandSys