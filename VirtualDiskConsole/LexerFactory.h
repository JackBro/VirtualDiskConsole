#ifndef ZP_LEXERFACTORY
#define ZP_LEXERFACTORY

#include "ILexer.h"
#include "Singleton.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-����-2013 9:17:33
 */

namespace Lexer_Sys
{ 
		/**
		* @class LexerFactory
		*			������������������
		*/
		 class LexerFactory : public ZPUTIL::SingletonT<LexerFactory>
		 { 
		 public: 

			 enum LexerType
			 {
				 LEXER_TYPE_COMMAND = 1,
				 LEXER_TYPE_PATH
			 };

			  LexerFactory(){}
			  virtual ~LexerFactory(){}
	 
			/**
			 * @brief ����������ʵ��
			 * @param type
			 * @return ���ش����˵Ľ�����
			 * @retval  NULL ����ʧ�ܣ�û���ҵ������͵Ľ�����
			 */
			ILexer* CreateLexer( const LexerType type );

		};//LexerFactory

}//namespace Lexer_Sys

#endif//ZP_LEXERFACTORY