#ifndef ZP_TOKEN
#define ZP_TOKEN

#include "ZPDependency.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-����-2013 9:17:33
 */
namespace LexerSys
{ 
	class Token {
	public:  

		enum TokenType
		{
			UNKNOWN_TOKEN = 0,
			CMD_TOKEN,
			OPTION_TOKEN,
			PATH_NODE_TOKEN
		};

		enum TokenSubType
		{ 
			NULL_TOKEN,
			FOLDER_NODE_TOKEN,
			FILE_NODE_TOKEN,
			WILDCARD_TOKEN,
			DRIVE_TOKEN
		};

		/**
		* @brief Ĭ�Ϲ��캯��
		*/
		 Token():m_type(UNKNOWN_TOKEN),m_subtype(NULL_TOKEN),m_legal(true){}

		 /**
		 * @brief �������캯��
		 */
		 Token( const Token& token ):
		 m_type( token.m_type ),m_subtype( token.m_subtype ),m_name( token.m_name ),m_legal( token.m_legal ){}

		 /**
		 * @brief ��������
		 */
		 virtual ~Token(){}

		/**
		 * @brief	 ��ȡ��������
		 * @return ���������ַ���
		 */
		Util::String Name( void ) const { return m_name; }

		/**
		 * @brief	 ���÷�������
		 * @param Ҫ���õķ�������
		 * @return void
		 */
		void Name( const Util::String& name ){ m_name = name; }
		  
		/**
		 *@brief  ���ط�������
		 */
		TokenType Type( void ) const { return m_type; }
		 

		/**
		* @brief ���ñ������
		*/
		void Type( const TokenType type ){ m_type = type; } 

		/**
		* @brief ��ȡ���������
		*/
		TokenSubType SubType( void ) const { return m_subtype; }

		/**
		* @brief ���ñ������
		*/
		void SubType( const TokenSubType subtype ){ m_subtype = subtype; }

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
		void Append( const Util::String::XCHAR c  );

		/**
		* @brief �ڱ�ǽ�β�����һ���ַ���
		* @param str Ҫ���ӵ��ַ���
		*/
		void Append( const Util::String& str );

		/**
		* @brief ���÷������
		*/
		void Clear(void);

		/**
		* @brief �ӵ�ǰ��������ȡ�ļ���
		* @remark �˺���ֻ���ڡ�ͨ�������"�ļ���"���ͷ���������
		*/
		Util::String ExtractFileName( void ) const;

		/**
		* @brief �ӵ�ǰ��������ȡ��չ��
		* @remark �˺���ֻ���ڡ�ͨ�������"�ļ���"���ͷ���������
		*/ 
		Util::String ExtractFileExtName( void ) const;
		
		/**
		* @breif ������ǰ�����Ǻ�������
		*/
		void Analysis(void);

		/**
		* @brief ��ֵ���������
		*/
		Token& operator=( const Token& rhs );
  
	private:

		TokenType      m_type;			///>��������
		TokenSubType m_subtype;   ///>����������
		bool				   m_legal;			///>�÷����Ƿ�Ϸ�
		Util::String m_name;		///>���������ַ���

	}; //class Token

	 
	 
}//namespace Lexer_Sys
#endif //ZP_TOKEN
