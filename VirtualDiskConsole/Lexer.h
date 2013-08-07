#ifndef ZP_LEXER
#define ZP_LEXER

#include "ZPDependency.h"
#include "Token.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-����-2013 9:17:33
 */

namespace Lexer_Sys
{ 
		 class Lexer 
		 { 
		 public:   

			 enum LexerState{
				 LOADED_STATE = 1,
				 UNLOADED_STATE ,
				 ANALYSISED_STATE
			 };

			 Lexer();
			 virtual ~Lexer();

			 /**
			 * @brief ������Ҫ�������ַ��� 
			 * @param str ��Ҫ�������ַ���
			 */
			virtual void SetString(  const ZPUTIL::String& str ); 
			
			/**
			* @brief �������ͷ
			* @return ����ͷ����
			*/
			virtual Token& GetCommandToken( void )  { return m_cmd_head; }

			/**
			* @brief �������ѡ��
			* @return ����ѡ���б�
			*/
			virtual ZPUTIL::LinkListT<Token>& GetCommandOptions( void )  { return m_options; }

			/**
			* @brief �������·���б�
			* @return �������·���б�
			*/
			virtual ZPUTIL::LinkListT<ZPUTIL::LinkListT<Token>>& GetCommandPaths( void )  { return m_paths; }

			/**
			 * @brief ���������õ��ַ��������з���������token
			 */
			virtual void Analysis( void );

			/**
			 * @brief ��ս��������ݹ��´��ٴη���
			 */
			virtual void Clear( void );

		 protected:
			 
			 /**
			 * @brief ��Ҫ�������ַ�������ȡ����ͷ
			 * @remark �����ڲ����ú���
			 */
			 ZPUTIL::String AnalysisCmdHead( const ZPUTIL::String& str );

			 /**
			 * @brief ��Ҫ�������ַ�������ȡ����ѡ��
			 * @remark �����ڲ����ú���
			 */
			 ZPUTIL::String  AnalysisCmdOptions( const ZPUTIL::String& str );

			 /**
			 * @brief ��Ҫ�������ַ�������ȡ����·��
			 * @remark �����ڲ����ú���
			 */
			 ZPUTIL::String  AnalysisCmdPaths( const ZPUTIL::String& str );

			 /**
			 * @brief ��·�����з��������Ų����봫��ķ���������
			 * @param str ������·����
			 * @param tokens �������ķ���
			 */
			 void AnalysisPath( const ZPUTIL::String& str , ZPUTIL::LinkListT<Token>& tokens );

		 private: 

			 LexerState m_state;												///>������״̬
			 ZPUTIL::String m_str_buf;										///>�������ַ���
			 Token m_cmd_head;											///>����ͷ
			 ZPUTIL::LinkListT<Token> m_options;					///>����ѡ��
			 ZPUTIL::LinkListT< ZPUTIL::LinkListT<Token> > m_paths;  ///>·�����б�

		};//class Lexer 

}//namespace Lexer_Sys
 
#endif//ZP_LEXER