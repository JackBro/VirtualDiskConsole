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
			Util::String path = m_paths.At(i).Path();
			FileSys::Node*  lp_search_path_node = SearchNodeByPath( path );
			if( NULL != lp_search_path_node )
			{  
				if( lp_search_path_node->IsFile() ){ 
					lp_search_path_node->Parent()->DeleteNode( lp_search_path_node->Name() );
				}else{//��Ϊ�ļ�����ɾ���ļ����������ļ�
					lp_search_path_node->DeleteNodeByType( FileSys::Node::FILE_NODE );					 
					return;
				} 
			}else{//���Ҳ�����ָ���ļ� 

				int last_back_slash_i = path.FindLastOf('\\');
				Util::String parent_path = path.SubString( 0 , 
					path.Length() - ( path.Length() - last_back_slash_i ) );
				
				Util::String filename = path.SubString( last_back_slash_i+1 , path.Length() - last_back_slash_i-1);

				 lp_search_path_node = SearchNodeByPath( parent_path );

				 if( NULL != lp_search_path_node )
				 {
						FileSys::Node* lp_del_node = NULL;
						while( NULL != 
							( lp_del_node = lp_search_path_node->FindFileNodeBySpec( filename ) ) )
						{
							lp_search_path_node->DeleteNode( lp_del_node->Name() );
						}

				 }else{
					 m_result_output = "ϵͳ�Ҳ���ָ����·��";
					 return; 
				 }
			} 
		}// for( int i = 0 ; i < m_paths.Count() ; i++ )
	}//if( m_paths.Count() )
}

}//namespace CommandSys