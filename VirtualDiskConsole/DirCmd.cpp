#include "DirCmd.h"

namespace CommandSys
{ 

DirCmd::DirCmd(void)
{
}


DirCmd::~DirCmd(void)
{
}

void DirCmd::Execute( void )
{
	FileSys::Node* lp_curr_path_node =	SearchCurrPathNode(); 

	bool folder_only = false;
	bool recursive = false;

	//��������
	if( m_params.Count() )
	{
		for( int i = 0 ; i < m_params.Count() ; i++ )
		{
			LexerSys::Token param_tok = m_params.At( i );

			if( 0 == param_tok.Name().ICmp("ad") )
			{
				folder_only = true;
			}else if( 0 == param_tok.Name().ICmp("s") ){
				recursive = true;
			}else{//�Ƿ�ѡ��
				m_result_output = Util::StringFormat("������ʽ����ȷ-\"%s\"" , param_tok.Name().Ptr() );
				return;
			} 
		}//for( int i = 0 ; i < m_params.Count() ; i++ )
	}//if( m_params.Count() )

	//����·����
	if( m_paths.Count() )
	{
		for( int i = 0 ; i < m_paths.Count() ; i++ )
		{
			FileSys::Node*  lp_search_path_node = SearchNodeByPath( m_paths.At( i ) );
			if( NULL != lp_search_path_node )
			{ 
				lp_search_path_node->GetFileListOutputString( m_result_output , recursive , folder_only );
				
			}else{//����һ���Ƿ�·��
				m_result_output = "ϵͳ�Ҳ���ָ����·��";
				return;
			}
		}// for( int i = 0 ; i < m_paths.Count() ; i++ )
	}else{
		lp_curr_path_node->GetFileListOutputString( m_result_output , recursive , folder_only );
	}

}

}//namespace CommandSys