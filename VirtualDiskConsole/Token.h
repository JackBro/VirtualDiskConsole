#ifndef ZP_TOKEN
#define ZP_TOKEN

#include "ZPDependency.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-����-2013 9:17:33
 */
namespace Lexer_Sys
{ 
	class Token {
	public: 

		enum TokenType
		{
			STRING_TYPE = 1,
			INT_TYPE
		};

		/**
		* @brief Ĭ�Ϲ��캯��
		*/
		 Token():m_type(STRING_TYPE),m_legal(true){}
		 /**
		 * @brief �������캯��
		 */
		 Token( const Token& token ):m_type( token.m_type ),m_legal( token.m_legal ),m_name( token.m_name ){}
		 /**
		 * @brief ��������
		 */
		 virtual ~Token(){}

		/**
		 * @brief	 ��ȡ��������
		 * @return ���������ַ���
		 */
		ZPUTIL::String Name( void ) const { return m_name; }

		/**
		 * @brief	 ���÷�������
		 * @param Ҫ���õķ�������
		 * @return void
		 */
		void Name( const ZPUTIL::String& name ){ m_name = name; }
		 

		/**
		 *@brief  ���ط�������
		 */
		TokenType Type(){ return m_type; }

		/**
		* @brief ���ñ������
		*/
		void Type( const TokenType type ){ m_type = type; } 

		/**
		* @brief ���ص�ǰ�����Ƿ�Ϊ�Ϸ�
		* @return �����Ƿ�Ϸ�
		*/
		bool IsLegal( void ) const { return m_legal; }

		/**
		* @brief ���÷��Ŷ����Ƿ�Ϸ�
		* @param �Ϸ����
		*/
		void SetLegal( const bool legal ){ m_legal = legal; }

		/**
		* @brief ��ֵ���������
		*/
		Token& operator=( const Token& rhs );

	private:

		TokenType      m_type;			///>��������
		bool				   m_legal;			///>�÷����Ƿ�Ϸ�
		ZPUTIL::String m_name;		///>���������ַ���

	}; //class Token

}//namespace Lexer_Sys
#endif //ZP_TOKEN
