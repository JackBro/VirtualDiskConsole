#include "PathSearchVisitor.h"
#include "Node.h"
#include "Token.h"

namespace FileSys
{
	 
PathSearchVisitor::PathSearchVisitor(void)
{
}


PathSearchVisitor::~PathSearchVisitor(void)
{
}

void PathSearchVisitor::Visit( Node* node )
{
	ZP_ASSERT( NULL != node ); 

	if( NULL != node )
	{
		if( HasNextToken() )
		{
			LexerSys::Token curr_tok = GetCurrPathToken();
			MoveToNextToken();

			if( curr_tok.Name() == "." )
			{ 
				node->Accept( this );
				return; 
			}else if( curr_tok.Name() == ".." ){

				//����ǰ�ڵ㲻Ϊ���ڵ�
				if( !node->IsRoot() )
				{
					node->Parent()->Accept( this );
					return;
				}else{
					node->Accept( this );
					return;
				}
			}

			//�������Ľڵ�Ϊ�ļ���
			if( node->IsFolder() )
			{ 
				Node* lp_next_node = node->FindNode( curr_tok.Name() );
				if( NULL != lp_next_node )
				{ 
					lp_next_node->Accept( this );
					return;
				}
			} 

		}else{//�ҵ�Ҫ�ҽڵ�
			m_lp_final_search_node = node;
			return;
		}

	}//if( NULL != node ) 
	m_lp_final_search_node = NULL;
}
 
}//namespace FileSys