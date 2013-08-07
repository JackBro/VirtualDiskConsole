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
			NULL_TOKEN,
			CMD_TOKEN,
			OPTION_TOKEN,
			PATH_NODE_TOKEN,
			WILDCARD_TOKEN
		};

		/**
		* @brief Ĭ�Ϲ��캯��
		*/
		 Token():m_type(NULL_TOKEN),m_legal(true){}

		 /**
		 * @brief �������캯��
		 */
		 Token( const Token& token ):m_type( token.m_type ),m_name( token.m_name ),m_legal( token.m_legal ){}

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
		* @brief ���ص�ǰ�����Ƿ�Ϊ��
		* @return ��ǰ�����Ƿ�Ϊ��
		* @retval true Ϊ��
		* @retval false ��Ϊ��
		*/
		bool IsEmpty( void ) const { return m_name.IsEmpty(); }

		/**
		* @brief ���÷��Ŷ����Ƿ�Ϸ�
		* @param �Ϸ����
		*/
		void SetLegal( const bool legal ){ m_legal = legal; }

		/**
		* @brief �ڱ�ǽ�β������һ���ַ�
		* @param c Ҫ���ӵ��ַ�
		*/
		void Append( const ZPUTIL::String::XCHAR c  );

		/**
		* @brief �ڱ�ǽ�β�����һ���ַ���
		* @param str Ҫ���ӵ��ַ���
		*/
		void Append( const ZPUTIL::String& str );

		/**
		* @brief ���÷������
		*/
		void Clear(void);

		/**
		* @brief ��ֵ���������
		*/
		Token& operator=( const Token& rhs );

	private:

		TokenType      m_type;			///>��������
		bool				   m_legal;			///>�÷����Ƿ�Ϸ�
		ZPUTIL::String m_name;		///>���������ַ���

	}; //class Token

/**
* @brief �鿴��ǰ����Ƿ�Ϊͨ���
*/
extern	bool IsWildCardToken( const Token& tok );

}//namespace Lexer_Sys
#endif //ZP_TOKEN
