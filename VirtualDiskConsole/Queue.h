#ifndef ZP_QUEUE
#define ZP_QUEUE

#include "LinkList.h"

namespace Util
{
	template<typename T>
	class QueueT
	{
	public:
		/**
			@brief Ĭ�Ϲ��캯��
		*/
		QueueT(){}
		/**
			@brief �������캯��
		*/
		QueueT( const QueueT& q ):m_queue(q.m_queue){}
		/**
			@brief ��������
		*/
		~QueueT(){}

		/**
			@brief ��Ԫ�� data �����
			@param data Ҫѹ���Ԫ��
		*/
		inline void Enqueue( const T& data ){ m_queue.PushBack( data ); }

		/**
			@brief ��Ԫ�س�����
		*/
		inline void Dequeue( void ){ m_queue.PopFront(); }

		/**
			@brief ���ض���ͷ����Ԫ��
			@return ���صĶ���ͷ��Ԫ��
		*/
		inline T& Front(void) { return m_queue.Front(); }

		/**
			@brief ���ض���ͷ����Ԫ��
			@return ���صĶ���ͷ��Ԫ��
		*/
		inline const T& Front(void) const { return m_queue.Front(); }

		/**
			@brief ���ض��д�С
			@return ����Ԫ����
		*/
		inline int Size(void) const { return m_queue.Count(); }

		/**
			@brief ��ֵ���������
			@return ��ǰ��������
		*/
		inline QueueT& operator=( const QueueT& rhs )
		{
			m_queue = rhs.m_queue;
			return *this;
		}
	private:
		LinkListT<T> m_queue;		///>���ڶ��е��������ݽṹ
	};
	
}//namespace ZPUTIL


#endif //ZP_QUEUE