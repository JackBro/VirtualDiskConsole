#ifndef ZP_STACK
#define ZP_STACK

#include "LinkList.h"

namespace Util
{ 
	template<typename T>
	class StackT
	{
	public:
		/**
			@brief Ĭ�Ϲ��캯��
		*/
		StackT(void){}
		/**
			@brief �������캯��
		*/
		StackT( const StackT& stack ):m_stack(stack.m_stack){}
		/**
			@brief ��������
		*/
		~StackT(){}
		 
		/**
			@brief ��Ԫ��data��ջ
			@param data Ҫ��ջԪ��
		*/
		inline void Push( const T& data ){ m_stack.PushFront( data ); }
		/**
			@brief ��ջ��Ԫ�س�ջ
		*/
		inline void Pop(void){ m_stack.PopFront();  }
		/**
			@brief ����ջԪ����
			@return ջԪ����
		*/
		inline int    Size(void) const { return m_stack.Count(); }
		/**
			@brief ջ�Ƿ�Ϊ��
			@retval true ջΪ��ջ
			@retval false ջΪ�ǿ�
		*/
		inline bool  IsEmpty(void) const { return m_stack.IsEmpty(); }
		/**
			@brief ����ջ��Ԫ��
			@return ջ��Ԫ��
		*/
		inline T& Front(void){ return m_stack.Front(); }

		/**
			@brief ����ջ��Ԫ��
			@return ջ��Ԫ��
		*/
		inline const T& Front(void) const { return m_stack.Front(); }

		/**
			@brief ��ֵ��������� 
		*/
		inline StackT& operator=( const StackT& stack )
		{
			m_stack = stack.m_stack;
			return *this;
		}

	private:
		LinkListT<T> m_stack;	///>����ջ���������ݽṹ
	};

}//namespace ZPUTIL

#endif //ZP_STACK