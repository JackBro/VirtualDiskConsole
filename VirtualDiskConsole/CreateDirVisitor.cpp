#include "CreateDirVisitor.h"
#include "Node.h"

namespace FileSys
{

	CreateDirVisitor::CreateDirVisitor(void)
	{
	}


	CreateDirVisitor::~CreateDirVisitor(void)
	{
	}

	void CreateDirVisitor::Visit( Node* node )
	{
		ZP_ASSERT( NULL != node ); 

		if( NULL != node )
		{
			if( HasNextToken() )
			{
				LexerSys::Token curr_tok = GetCurrPathToken();
				MoveToNextToken();

				if( 
					curr_tok.Type() == LexerSys::Token::DRIVE_TOKEN ||
					curr_tok.Type() == LexerSys::Token::WILDCARD_TOKEN 
					)
				{
					m_result_output_str = "�ļ�����Ŀ¼�������﷨����ȷ";
					return;
				}

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
					}else{
						node = node->CreateNode( curr_tok.Name() , Node::FOLDER_NODE );
						if( NULL != node )
						{
							node->Accept( this );
							return;
						}
					}

				} //if( node->IsFolder() )
			}//if( HasNextToken() )
		}//if( NULL != node ) 

	} 

}//namespace FileSys

