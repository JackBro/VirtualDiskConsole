#ifndef ZP_NODEVISITOR
#define ZP_NODEVISITOR

#include "ZPDependency.h"
#include "Token.h"
#include "SearchPath.h"

namespace FileSys
{
	class Node;

	class NodeVisitor
	{
	public:
	 
		NodeVisitor( void );
		virtual ~NodeVisitor( void ); 

		/**
		* @brief ��������·��
		* @param path ����·��
		*/
		virtual void SetPath( const LexerSys::SearchPath& path );

		/**
		* @brief �������·���ĵ�ǰ����
		* @return ����·���ĵ�ǰ����
		*/
		virtual LexerSys::Token GetCurrPathToken( void ) const;

		/**
		* @brief �Ƿ�����һ������
		*/
		virtual bool HasNextToken( void ) const;

		/**
		* @brief �ƶ�������·������һ������
		*/
		virtual void MoveToNextToken( void );

		/**
		* @brief ����������Ľڵ�
		*/
		virtual Node* GetSearchNode(void);

		/**
		* @brief ����������������ַ���
		*/
		virtual Util::String GetResultOutputString(void) const;

		/**
		* @brief ���ʽڵ�
		* @param node �����ʽڵ�
		*/
		virtual void Visit( Node* node ){ }; 

	protected:
		typedef Util::LinkListT<LexerSys::Token> PathToks;
		LexerSys::SearchPath m_path;		///>����·��
		Node* m_lp_final_search_node;		///>��ǰ�ڵ�
		Util::String m_result_output_str;	///>��÷��ʽ���ַ���
	};

}//namespace FileSys

#endif //ZP_NODEVISITOR