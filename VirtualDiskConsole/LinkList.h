#ifndef ZP_LINKLIST
#define ZP_LINKLIST

namespace Util
{
	 
	template<typename T>
	class LinkListT
	{
	public:
		 
			class LinkNode
			{
			protected:
				LinkNode(void):
					 m_lp_parent_list( NULL),
					 m_data(),
				     m_lp_prev( NULL ),
				     m_lp_next( NULL )
					 {
						 m_lp_prev = this;
						 m_lp_next = this;
					 }
			public:

				friend class LinkListT;

				/**
					@brief �������Ĺ��캯��
					@param lp_parent ��������
				*/
				LinkNode( LinkListT* lp_parent ):
				  m_lp_parent_list( lp_parent ),
					  m_data(),
					  m_lp_prev( NULL ),
					  m_lp_next( NULL )
				  {
					  m_lp_prev = this;
					  m_lp_next = this;
				  }

				 /**
					@brief �������Ĺ��캯��
					@param lp_parent ��������
					@param data �������
				*/
				LinkNode( LinkListT* lp_parent , const T& data ):
				m_lp_parent_list( lp_parent ),
				m_data( data ),
				m_lp_prev( NULL ),
				m_lp_next( NULL )
				{
					m_lp_prev = this;
					m_lp_next = this;
				}

				~LinkNode(){} 

				inline LinkListT* ParentList(void)  { return m_lp_parent_list; }
				inline const LinkListT* ParentList(void) const { return m_lp_parent_list; }
				inline T& Data(void) { return m_data; }
				inline const T& Data(void) const { return m_data; }
				inline LinkNode* Prev(void) { return m_lp_prev; }
				inline LinkNode* Next(void) { return m_lp_next; }
				inline const LinkNode* Prev(void) const { return m_lp_prev; }
				inline const LinkNode* Next(void) const { return m_lp_next; }
	
				/**
					@brief �ӵ�ǰ���ǰ����һ�����
					@param insert_node ָ��Ҫ����Ľ��
					@return ���ص�ǰ���
				*/
				inline LinkNode* InsertFront( LinkNode* insert_node )
				{ 
					insert_node->m_lp_parent_list = this->ParentList();
					insert_node->m_lp_prev = Prev(); 
					insert_node->m_lp_next = this; 
					Prev()->m_lp_next = insert_node;
					m_lp_prev = insert_node;
					return this;
				}

				/**
					@brief �ӵ�ǰ�������һ�����
					@param insert_node ָ��Ҫ����Ľ��
					@return ���ص�ǰ���
				*/
				inline LinkNode* InsertBack( LinkNode* insert_node )
				{
					insert_node->m_lp_parent_list = this->ParentList();
					insert_node->m_lp_prev = this;
					insert_node->m_lp_next = Next();
					Next()->m_lp_prev = insert_node;
					m_lp_next = insert_node;
					return this;
				}

				/**
					@brief ���˽���������ժ�� 
					@return ���ص�ǰ���
				*/
				inline LinkNode* Remove(void)
				{
					m_lp_parent_list = NULL;
					Prev()->m_lp_next = Next();
					Next()->m_lp_prev = Prev();
					m_lp_prev = this;
					m_lp_next = this;
					return this;
				}

				/**
					@brief �������  
				*/
				inline void DeleteThis(void)
				{
					delete this;
				}

			private:
				LinkListT* m_lp_parent_list;  ///>��������
				T m_data;							  ///>����
				LinkNode* m_lp_prev;      ///>ָ��ǰһ������ָ��
				LinkNode* m_lp_next;      ///>ָ���һ������ָ��
			};// LinkNode

	public: 

		/**
			@brief Ĭ�Ϲ��캯��
		*/
		LinkListT():
		  m_lp_head(NULL),
		  m_count(0)
		{
		} 

		 /**
			@brief �������캯��
		 */
		LinkListT( const LinkListT& list ):
			m_lp_head(NULL),
			m_count(0)
		{
			this->Clone( list );
		}

		 /**
			@brief ��������
		 */
		~LinkListT()
		{
			this->Clear();
		}

		/**
			@brief ����ͷ���ָ��
			@retval NULL ������Ϊ��
		*/
		inline LinkNode* Head(void){ return m_lp_head; }

		/**
			@brief ����ͷ���ָ��
			@retval NULL ������Ϊ��
		*/
		inline const LinkNode* Head(void) const{ return m_lp_head; }

		/**
			@brief ����β���ָ��
			@retval NULL ������Ϊ��
		*/
		inline LinkNode* Tail(void)
		{
			if( m_lp_head )
			{
				return m_lp_head->Prev();
			}
			return m_lp_head;
		}

		/**
			@brief ����β���ָ��
			@retval NULL ������Ϊ��
		*/
		inline const LinkNode* Tail(void) const
		{
			if( m_lp_head )
			{
				return m_lp_head->Prev();
			}
			return m_lp_head;
		} 

		/**
			@brief ���������н����
			@return �����
		*/
		inline int Count(void) const { return m_count; }

		inline T& Front(void)
		{
			ZP_ASSERT( NULL != m_lp_head );
			return m_lp_head->Data();
		}

		inline const T& Front(void) const 
		{
			ZP_ASSERT( NULL != m_lp_head );
			return m_lp_head->Data();
		}

		inline T& Back(void)
		{
			ZP_ASSERT( NULL != Tail() );
			return Tail()->Data();
		}

		inline const T& Back(void) const
		{
			ZP_ASSERT( NULL != Tail() );
			return Tail()->Data();
		}

		/**
			@brief ��ǰ�˲���һ����dataΪ���ݵĽ��
			@param data Ҫ���������
		*/
		inline void PushFront( const T& data )
		{
			LinkNode* lp_new_node = new LinkNode( this , data );
			ZP_ASSERT( NULL != lp_new_node );
			
			if( m_lp_head )
			{
				m_lp_head->InsertFront( lp_new_node );
			} 
			m_lp_head = lp_new_node; 
			m_count++;
		}

		/**
			@brief �Ӻ�˲���һ����dataΪ���ݵĽ��
			@param data Ҫ���������
		*/
		inline void PushBack( const T& data )
		{
			LinkNode* lp_new_node = new LinkNode( this , data );
			ZP_ASSERT( NULL != lp_new_node );

			if( m_lp_head )
			{
				m_lp_head->InsertFront( lp_new_node );
			}else{
				m_lp_head = lp_new_node;
			}
			m_count++;
		}

		/**
			@brief ����ͷ��һ�����
		*/
		inline void PopFront( void )
		{
			if( m_lp_head )
			{
				Erase( m_lp_head );
			}
		}

		/**
			@brief ����β��һ�����
		*/
		inline void PopBack( void )
		{
			if( m_lp_head )
			{
				Erase( m_lp_head->Prev() );
			}
		}
		 

		/**
			@brief ɾ������ָ���Ľ��
			@param node Ҫɾ���Ľ��(��Ҫ�˽�����Ϊ�������ϵĽ��)
			@return ɾ��������һ�����
		*/
		inline LinkNode* Erase( LinkNode* node )
		{  
			ZP_ASSERT( NULL != node ); 
			//��������������Ϊ��ǰ������ǰ�������Ȩ�Ƴ�
			ZP_ASSERT( node->ParentList() == this );
			
			LinkNode* lp_next_node = NULL; 
			if( m_lp_head == node )
			{//��ɾ������ͷ���
				//����ǰ�����в�ֻ��һ�����
				if( m_lp_head->Next() != m_lp_head )
				{
					m_lp_head = m_lp_head->Next();
					lp_next_node = m_lp_head;
				}else{
					m_lp_head = NULL; 
				}
			}else{//��ɾ���Ĳ���ͷ��� 
				if( node != Tail() )
				{
					lp_next_node = node->Next();
				} 
			}
			 
			node->Remove()->DeleteThis();
			node = NULL;
			m_count--;

			return lp_next_node;
		}

		/**
		* @brief ��ȡ��i����Ԫ��
		*/
		inline T& At( const int i )
		{
			ZP_ASSERT( i >= 0 || i < Count() );   

			int count = 0;
			LinkNode* p = m_lp_head;
			while( count != i )
			{
				p = p->Next();
				count++;
			}

			return p->Data();
		}

		inline const T& At( const int i ) const
		{ 
			ZP_ASSERT( i >= 0 || i < Count() );   

			int count = 0;
			LinkNode* p = m_lp_head;
			while( count != i )
			{
				p = p->Next();
				count++;
			}

			return p->Data();
		}

		/**
			@brief ��λ��i���������� data
			@param i Ҫ�����λ��
			@param data Ҫ���������
		*/
		inline void Insert( const int i , const T& data  )
		{
			ZP_ASSERT( i >= 0 || i <= Count() );   

			if( i == 0 )
			{
				PushFront( data );
				return;
			} else if ( i == Count() ) {
				PushBack( data );
				return;
			}

			int c = 0;
			LinkNode* lp_curr_node = m_lp_head;
			while( c != i )
			{
				lp_curr_node = lp_curr_node->Next();
				c++;
			}

			LinkNode* lp_new_node = new LinkNode( this , data );
			lp_curr_node->InsertFront( lp_new_node );  
			m_count++;
		}


		/**
			@brief ɾ��������ָ���Ľڵ�
			@param i ����
		*/
		inline void DeleteAt( const int i )
		{
			ZP_ASSERT( i >= 0 || i < Count() ); 

			int c = 0;
			LinkNode* lp_del_node = m_lp_head;
			while( c != i )
			{
				lp_del_node = lp_del_node->Next();
				c++;
			}  

			Erase( lp_del_node );
		}
		
		/**
			@brief ���������Ƿ�Ϊ��
			@return ���������Ƿ�Ϊ��
			@retval true Ϊ��
			@retval false Ϊ�ǿ�
		*/
		inline bool IsEmpty(void) const { return ( m_count == 0 ); }

		/**
			@brief ��������е����н��
		*/
		inline void Clear(void)
		{
			if( NULL != Head() )
			{ 
				LinkNode* p = Head();
				LinkNode* end = Head();
				do{
					LinkNode* tmp = p->Next();
					p->DeleteThis();
					p = tmp;
				}while( p != end );

				m_lp_head = NULL;
				m_count = 0; 
			}//if( NULL != Head() )
		}

		/**
			@brief ������һ������
			@param list Ҫ����������
			@return void
		*/
		inline void Clone( const LinkListT& list )
		{
			this->Clear();

			if( list.IsEmpty() )
			{
				return;
			}

			const LinkNode* p = list.Head();
			const LinkNode* end = list.Head();
			do{ 
				this->PushBack( p->Data() );
				p = p->Next();
			}while( p != end );

			m_count = list.Count();
		}

		/**
		* @brief �ڵ�ǰ��������һ������
		* @param list Ҫ���ӵ�����
		*/
		inline LinkListT& Append( const LinkListT& list )
		{
			if( list.IsEmpty() )
			{
				return *this;
			}

			const LinkNode* p = list.Head();
			const LinkNode* end = list.Head();
			do{ 
				this->PushBack( p->Data() );
				p = p->Next();
			}while( p != end );

			return *this;
		}

		/**
			@brief ������������
			@param list Ҫ����������
			@return void
		*/
		inline void Swap( LinkListT& list )
		{
			LinkNode* lp_head_copy = m_lp_head;
			int count_copy = m_count;

			m_lp_head = list.m_lp_head;
			m_count = list.m_count;

			list.m_lp_head = lp_head_copy;
			list.m_count = count_copy;
		}

		/**
			@brief ��ֵ���������
		*/
		inline LinkListT& operator=( const LinkListT& rhs )
		{
			this->Clone( rhs );
			return *this;
		}

		//��������� 
		class Iterator
		{
		public:

			friend class LinkListT;

			Iterator():
			  m_list_ref( NULL ),
			  m_lp_curr_node(NULL)
			{ 
			}

			Iterator(  LinkListT* list ):
			  m_list_ref( list ),
			  m_lp_curr_node(NULL)
			{
				m_lp_curr_node = m_list_ref->Head();
			}

			 Iterator( LinkListT* list , LinkNode* node ):
				m_list_ref( list ),
				m_lp_curr_node(node)
			{ 
			}

			Iterator( const Iterator& it ):
				m_list_ref( it.m_list_ref ),
				m_lp_curr_node( it.m_lp_curr_node )
			{ 
			}
            
			~Iterator(){ m_list_ref = NULL; m_lp_curr_node = NULL; }

			/**
				@brief ������������Ϊ������
			*/
			void MoveFirst( void ){ m_lp_curr_node = m_list_ref->Head(); }

			/**
			* @brief ���������ƶ������һ��Ԫ��
			*/
			void MoveLast( void ){ m_lp_curr_node = m_list_ref->Tail(); }

			/**
				@brief �Ƿ�����һ��Ԫ��
				@retval true ������һ��Ԫ��
				@retval false û����һ��Ԫ��
			*/
			bool HasNext( void ) const { return  ( NULL != m_lp_curr_node ); }

			/**
				@brief ���ص�ǰԪ�أ����ƶ�����һ��Ԫ��
				@return ��ǰԪ��ֵ
			*/
			T& Next( void )
			{
				ZP_ASSERT( m_list_ref );
				ZP_ASSERT( m_lp_curr_node );

				LinkNode* lp_ret_node = m_lp_curr_node;
				if( m_lp_curr_node->Next() == m_list_ref->Head() )
				{
					m_lp_curr_node = NULL;
				}else{
					m_lp_curr_node = m_lp_curr_node->Next();
				}
				return lp_ret_node->Data();
			}

			T& Data(void) { return m_lp_curr_node->Data(); }

			const T& Data(void) const { return m_lp_curr_node->Data(); }

			T& operator*()
			{
				ZP_ASSERT( m_list_ref );
				ZP_ASSERT( m_lp_curr_node );
				return m_lp_curr_node->Data();
			}

			const T& operator*() const
			{
				ZP_ASSERT( m_list_ref );
				ZP_ASSERT( m_lp_curr_node );
				return m_lp_curr_node->Data();
			}

			bool operator==( const Iterator& rhs )
			{
				return ( m_list_ref == rhs.m_list_ref ) 
					&& ( m_lp_curr_node == rhs.m_lp_curr_node );
			}

			bool operator != ( const Iterator& rhs )
			{
				return !( this->operator==( rhs ) );
			}

			Iterator& operator = ( const Iterator& rhs )
			{
				m_list_ref = rhs.m_list_ref;
				m_lp_curr_node = rhs.m_lp_curr_node;
				return *this;
			} 

		protected:
			
			/**
				@brief ���ص�����ָ���ĵ�ǰ���
				@return ��ǰ���ָ��
				@remark �����ڲ�����
			*/
			inline LinkNode* CurrNode(void) const { return m_lp_curr_node; }
			/**
				@brief ���õ�ǰ���������ָ��
				@param node Ҫ���õĽ��ָ��
				@return void 
				@remark �����ڲ�����
			*/
			inline void CurrNode( LinkNode* node ) { m_lp_curr_node = node; }

		private:
			LinkListT* m_list_ref;					///>ָ�����������
			LinkNode* m_lp_curr_node;		///>ָ���������ָ���ĵ�ǰ������
		};
		
		/**
			@brief ����ָ��������ʼ������
			@return ָ��������ʼ�ĵ�����
			*/
			inline Iterator Begin(void)
			{
				return Iterator( this );
			}

		/**
			@brief ����ָ�������β�ĵ�����
			@return ָ�������β�ĵ�����
		*/
		inline Iterator End(void)
		{
			Iterator it(this);
			it.CurrNode( NULL );
			return it;
		}

		/**
			@brief ɾ����������ָ����
			@param Ҫɾ���ĵ�����
			@return ɾ����ǰ��������ָ������һ�����
		*/
		inline Iterator Erase( Iterator& it )
		{
			ZP_ASSERT( this == it.m_list_ref );
			ZP_ASSERT( NULL !=  it.m_lp_curr_node );
			return Iterator( this , this->Erase( it.m_lp_curr_node ) );
		}

	private: 
		LinkNode* m_lp_head;				///> ����ͷָ��
		int m_count;								///> �����еĽ����
	};

}// namespace ZPUTIL

#endif //ZP_LINKLIST