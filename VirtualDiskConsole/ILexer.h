#ifndef ZP_ILEXER
#define ZP_ILEXER

#include "ZPDependency.h"
#include "Token.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-����-2013 9:17:33
 */

namespace Lexer_Sys
{ 
		 class ILexer 
		 { 
		 public:   
			 ILexer(){} 
			 virtual ~ILexer(){}

			 /**
			 * @brief ������Ҫ�������ַ��� 
			 * @param str ��Ҫ�������ַ���
			 */
			virtual void SetString(  const ZPUTIL::String& str ) = 0;

			/**
			 * @brief ���������õ��ַ��������з���������token
			 */
			virtual void Analysis( void ) = 0;

			/**
			 * @brief ��ս��������ݹ��´��ٴη���
			 */
			virtual void Clear( void ) = 0;

			/**
			 * @brief  ��÷�����Ϻ�õ��ķ����б�
			 */
			virtual const ZPUTIL::LinkListT<Token>& GetTokenList( void ) const  = 0; 


		};//class ILexer 

}//namespace Lexer_Sys
 
#endif//ZP_ILEXER