#ifndef ZP_VECTOR
#define ZP_VECTOR

namespace Util
{
	const int INIT_VECTOR_ELEM_COUNT = 32;
	const int VECTOR_ELEM_COUNT_INC = 16;

	template<typename T>
	class VectorT
	{
	public:
		VectorT();
		VectorT( const VectorT& v );
		~VectorT();

		/**
		* @brief Ϊ��Ҫ���Ԫ�ص�������ռ�
		* @param elem_count ��Ҫ�����Ԫ��
		*/
		void Assign( const int elem_count );
		
		/**
		* @brief ������β������Ԫ�� elem 
		* @param elem Ҫ���ӵ�Ԫ��
		*/
		void PushBack( const T elem );

		/**
		* @brief ������ͷ������Ԫ�� elem 
		* @param elem Ҫ���ӵ�Ԫ��
		*/
		void PushFront( const T elem );

		/**
		* @brief ������λ��i������Ԫ��elem
		* @param i Ҫ���������
		* @param elem Ҫ�����Ԫ��
		*/
		void Insert( const int i , const T elem );

		/**
		* @brief ɾ��i����Ԫ��
		* @param i Ҫɾ��Ԫ�ص�����
		*/
		void DeleteAt( const int i );

		/**
		* @brief ��ȡi����Ԫ��
		* @param i ����
		*/
		T& At( const int i );

		/**
		* @brief ��ȡi����Ԫ��
		* @param i ����
		*/
		const T& At( const int i ) const;

		/**
		* @brief ��������е�����
		*/
		void Clear(void);

		/**
		* @brief �����д�ŵ�Ԫ����
		* @return ����������ŵ�Ԫ����
		*/
		int Count(void) const;

		/**
		* @brief �������������ɵ�Ԫ����
		* @return �������������ɵ�Ԫ����
		*/
		int Capacity(void) const;

		/**
		* @brief ��ֵ���������
		*/
		VectorT& operator=( const VectorT& rhs );
		 
	private:

		T* m_buf;			///>���������ݻ�����
		int m_count;		///>�����е�Ԫ����
		int m_capacity;	///>�����еĿռ������ɶ���Ԫ�� 
	};

	 
	  
	template<typename T>
	Util::VectorT<T>::VectorT():
	m_buf(NULL),
	m_count(0),
	m_capacity(0)
	{
		Assign( INIT_VECTOR_ELEM_COUNT );
	}

	template<typename T>
	Util::VectorT<T>::VectorT( const VectorT& v ):
	m_buf(NULL),
	m_count(0),
	m_capacity(0)
	{
		this->operator=( v );
	}

	template<typename T>
	Util::VectorT<T>::~VectorT()
	{
		ZP_SAFE_DELETE_BUFFER( m_buf );
		m_count = 0;
		m_capacity = 0;
	}
	
	template<typename T>
	void Util::VectorT<T>::Assign( const int elem_count )
	{
		//�������ڵ�Ԫ������������Ҫ���򲻷���
		if( elem_count <= 0 || 
			elem_count <= m_capacity )
		{
			return;
		}

		//������������
		const int final_capacity = elem_count + VECTOR_ELEM_COUNT_INC;
		T* new_buf = NULL;
		ZP_SAFE_NEW_BUFFER( new_buf , T , final_capacity );
		ZP_ASSERT( NULL != new_buf );

		if( NULL != m_buf )
		{
			for( int i = 0 ; i < m_count ; i++ )
			{
				new_buf[i] = m_buf[i];
			}
			ZP_SAFE_DELETE_BUFFER( m_buf );
		}

		m_buf = new_buf;
		m_capacity = final_capacity;
	}

	template<typename T>
	void Util::VectorT<T>::PushFront( const T elem )
	{
		Assign( Count() + 1 );

		for( int i = m_count ; i > 0 ; i-- )
		{
			m_buf[i] = m_buf[i-1];
		}
		m_buf[0] = elem;
		m_count++;
	}

	template<typename T>
	void Util::VectorT<T>::PushBack( const T elem )
	{
		Assign( Count() + 1 );
		m_buf[ m_count++ ] = elem; 
	}

	template<typename T>
	void Util::VectorT<T>::DeleteAt( const int i )
	{
		if( i < 0 || i >= Count() )
		{
			return;
		}

		for( int j =  i ; j < Count()-1 ; j++ )
		{
			m_buf[j] = m_buf[j+1];
		}
		m_count--;
	}

	template<typename T>
	void Util::VectorT<T>::Insert( const int i , const T elem )
	{
		if( i < 0 || i > Count() )
		{
			return;
		}
		Assign( Count() + 1 );
		for( int j = m_count ; j > i ; j-- )
		{
			m_buf[j] = m_buf[j-1];
		}
		m_buf[i] = elem;
		m_count++;
	}


	template<typename T>
	T& Util::VectorT<T>::At( const int i )
	{
		ZP_ASSERT( i < 0 || i >= m_count );
		return m_buf[i];
	}

	template<typename T>
	const T& Util::VectorT<T>::At( const int i ) const
	{
		ZP_ASSERT( i < 0 || i >= m_count );
		return m_buf[i];
	}


	template<typename T>
	void Util::VectorT<T>::Clear( void )
	{
		m_count = 0;
	}

	template<typename T>
	int Util::VectorT<T>::Capacity( void ) const
	{
		return m_capacity;
	}

	template<typename T>
	int Util::VectorT<T>::Count( void ) const
	{
		return m_count;
	}


	template<typename T>
	VectorT<T>& Util::VectorT<T>::operator=( const VectorT<T>& rhs )
	{
		Assign( rhs.Count() );

		for( int i = 0 ; i < rhs.Count() ; i++ )
		{
			m_buf[i] = rhs.m_buf[i];
		}
		m_count = rhs.m_count;

		return *this;
	}


}//namespace ZPUTIL

#endif //ZP_VECTOR