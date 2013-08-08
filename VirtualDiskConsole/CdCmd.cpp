#include "CdCmd.h"
#include "PathSearchVisitor.h"
#include "FileSystem.h"
#include "Node.h"
#include "Lexer.h"

namespace CommandSys
{ 

CdCmd::CdCmd(void)
{

}
 
CdCmd::~CdCmd(void)
{
}

void CdCmd::Execute( void )
{ 
	FileSys::Node* lp_curr_path_node =	SearchCurrPathNode();
	m_curr_path = lp_curr_path_node->PathName();

	if( m_params.Count() > 0 )
	{
		m_result_output = "ϵͳ�Ҳ���ָ��·��";
		return;
	}

	//���ж��·��
	if( m_paths.Count() > 1  )
	{
		m_result_output = "�ļ�����Ŀ¼�������﷨����ȷ��";
		return;
	}else if( m_paths.Count() == 0 ){ 
		m_result_output = m_curr_path; 
		return;
	}else{//��һ��·��
		if( m_paths.At(0).At(0).Name() == ".." )
		{
			//����ǰ·���ڵ㲻Ϊ��
			if( !lp_curr_path_node->IsRoot() )
			{
				lp_curr_path_node = lp_curr_path_node->Parent();
				m_curr_path = lp_curr_path_node->PathName();
				m_result_output = m_curr_path;
			}
		}else if( m_paths.At(0).At(0).Name() == "." ){
			m_result_output = m_curr_path; 
		}else{//��������·���� 
			FileSys::Node* lp_search_node = 
				SearchNodeByPathTokens( m_paths.At(0) );

			if( lp_search_node )
			{
				m_curr_path = lp_search_node->PathName();
				m_result_output.Empty();
			}else{
				m_result_output = "ϵͳ�Ҳ���ָ��·��";
			} 
		}
	}


}

}//namespace CommandSys