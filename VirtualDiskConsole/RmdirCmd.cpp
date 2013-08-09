#include "RmdirCmd.h"

namespace CommandSys
{

RmdirCmd::RmdirCmd(void)
{
}


RmdirCmd::~RmdirCmd(void)
{
}

void CommandSys::RmdirCmd::Execute( void )
{
	bool recursive = false;

	//��������
	if( m_params.Count() )
	{
		for( int i = 0 ; i < m_params.Count() ; i++ )
		{
			LexerSys::Token param_tok = m_params.At( i );

			 if( 0 == param_tok.Name().ICmp("s") ){
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
				if( lp_search_path_node->IsFile() || lp_search_path_node->Parent()->IsRoot() )
				{
					m_result_output = "Ŀ¼����Ч";
					return;
				}

				if( lp_search_path_node->IsLeaf() || recursive ){

					FileSys::Node* lp_curr_path_node =	SearchCurrPathNode(); 
					//��ɾ���Ľڵ㲻��Ϊ��ǰ·���ڵ�����
					if( lp_search_path_node != lp_curr_path_node 
						&& !lp_curr_path_node->IsAncestor( lp_search_path_node )  )
					{
						lp_search_path_node->Parent()->DeleteNode( lp_search_path_node->Name() );
					}else{
						m_result_output = "�����ļ������ڱ�ʹ��,�޷�ɾ����Ŀ¼!";
						return;
					} 
				}else{
					m_result_output = "Ŀ¼���ǿյ�";
					return;
				} 
			}else{//����һ���Ƿ�·����ֱ���˳�
				m_result_output = "ϵͳ�Ҳ���ָ����·��";
				return;
			}
		}// for( int i = 0 ; i < m_paths.Count() ; i++ )
	} 

}

}//namespace CommandSys