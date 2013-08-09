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
		m_result_output = m_curr_path.Path(); 
		return;
	}else{//��һ��·��
			FileSys::Node* lp_search_node = 
				SearchNodeByPath( m_paths.At(0) );
			if( lp_search_node )
			{
				if( lp_search_node->IsFolder() )
				{
					m_curr_path = lp_search_node->PathName();
					m_result_output.Empty();
				}else{
					m_result_output = "Ŀ¼����Ч";
				}
			}else{
				m_result_output = "ϵͳ�Ҳ���ָ��·��";
			} 
	} 

}

}//namespace CommandSys