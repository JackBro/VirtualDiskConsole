#include "DelCmd.h"

namespace CommandSys
{
	 
DelCmd::DelCmd(void)
{
}


DelCmd::~DelCmd(void)
{
}

void DelCmd::Execute( void )
{
	if( m_params.Count() )
	{
		m_result_output = "�����֧�ֲ���";
		return;
	}

	if( m_paths.Count() == 0 )
	{
		m_result_output = "�����﷨����ȷ";
		return;
	}
	
	//����·����
	if( m_paths.Count() )
	{
		for( int i = 0 ; i < m_paths.Count() ; i++ )
		{ 
			FileSys::Node*  lp_search_path_node = SearchNodeByPathTokens( m_paths.At( i ) );
			if( NULL != lp_search_path_node )
			{  
				if( lp_search_path_node->IsFile() ){ 
					lp_search_path_node->Parent()->DeleteNode( lp_search_path_node->Name() );
				}else{//��Ϊ�ļ�����ɾ���ļ����������ļ�
					lp_search_path_node->DeleteNodeByType( FileSys::Node::FILE_NODE );					 
					return;
				} 
			}else{//����һ���Ƿ�·����ֱ���˳�
				m_result_output = "ϵͳ�Ҳ���ָ����·��";
				return;
			} 
		}// for( int i = 0 ; i < m_paths.Count() ; i++ )
	}//if( m_paths.Count() )
}

}//namespace CommandSys