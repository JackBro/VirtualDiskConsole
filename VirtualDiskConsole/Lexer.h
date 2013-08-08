#ifndef ZP_LEXER
#define ZP_LEXER

#include "ZPDependency.h"
#include "Token.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-����-2013 9:17:33
 */

namespace LexerSys
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
			virtual void SetString(  const Util::String& str ); 
			
			/**
			* @brief �������ͷ
			* @return ����ͷ����
			*/
			virtual Token& GetCommandToken( void )  { return m_cmd_head; }

			/**
			* @brief �������ѡ��
			* @return ����ѡ���б�
			*/
			virtual Util::LinkListT<Token>& GetCommandOptions( void )  { return m_options; }

			/**
			* @brief �������·���б�
			* @return �������·���б�
			*/
			virtual Util::LinkListT<Util::LinkListT<Token>>& GetCommandPaths( void )  { return m_paths; }

			/**
			 * @brief ���������õ��ַ��������з���������token
			 */
			virtual void Analysis( void );

			/**
			 * @brief ��ս��������ݹ��´��ٴη���
			 */
			virtual void Clear( void );


#	if defined( ZP_DEBUG )
			/**
			* @brief ��ʾDebug��Ϣ
			*/
			void ShowDebugMessage( void );
#endif

		 protected:
			 
			 /**
			 * @brief ��Ҫ�������ַ�������ȡ����ͷ
			 * @remark �����ڲ����ú���
			 */
			 Util::String AnalysisCmdHead( const Util::String& str );

			 /**
			 * @brief ��Ҫ�������ַ�������ȡ����ѡ��
			 * @remark �����ڲ����ú���
			 */
			 Util::String  AnalysisCmdOptions( const Util::String& str );

			 /**
			 * @brief ��Ҫ�������ַ�������ȡ����·��
			 * @remark �����ڲ����ú���
			 */
			 Util::String  AnalysisCmdPaths( const Util::String& str );
			  
		 private: 

			 LexerState m_state;												///>������״̬
			 Util::String m_str_buf;											///>�������ַ���
			 Token m_cmd_head;											///>����ͷ
			 Util::LinkListT<Token> m_options;						///>����ѡ��
			 Util::LinkListT< Util::LinkListT<Token> > m_paths;  ///>·�����б�

		};//class Lexer 

		/**
		* @brief ��·�����з��������Ų����봫��ķ���������
		* @param str ������·����
		* @param tokens �������ķ���
		*/
		 extern void AnalysisPath( const Util::String& str , Util::LinkListT<Token>& tokens );

		 /**
		* @brief ������ǰ·���Ƿ�Ϊ����·��
		* @param toks ������·�������б�
		* @return �����Ƿ�Ϊ����·��
		*/
		 extern bool IsAbsolutePath( const Util::LinkListT<Token>& toks );

}//namespace Lexer_Sys
 
#endif//ZP_LEXER