#ifndef ZP_TOKENLIST
#define ZP_TOKENLIST

#include "ZPDependency.h"
#include "Token.h"

namespace LexerSys
{ 
	class TokenList
	{
	public:
		TokenList(void);
		~TokenList(void);

		/**
		* @brief �ڷ����б�β���һ������
		* @param token Ҫ��ӵķ���
		*/
		void AppendToken( const Token& token );

		/**
		* @brief ���б������λ��i����ӷ���token 
		* @param token Ҫ��ӵķ���
		*/
		void InsertToken( const int i , const Token& token );

		/**
		* @brief ɾ���б�λ��i���ķ���
		* @param i Ҫɾ�����ŵ�λ��
		*/
		void DeleteToken( const int i );

		/**
		* @brief ��շ����б� 
		*/
		void Clear( void );

		/**
		* @brief �Ƿ�����һ������
		*/
		bool HasNext( void ) const; 
		void MoveFirst( void ); 
		void MoveNext( void );

		/**
		* @brief ��õ�ǰ����
		*/
		Token& CurrToken( void );
		const Token& CurrToken( void ) const;
		 
	private:
		Util::LinkListT<Token>::Iterator m_curr_token;	 //��ǰ����
		Util::LinkListT<Token> m_token_list;				 //�����б�
	};

}//namespace Lexer_Sys

#endif//ZP_TOKENLIST