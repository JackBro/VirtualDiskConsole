#ifndef ZP_STRING_UTIL
#define ZP_STRING_UTIL

#include "ZPDependency.h"

#		ifdef ZP_UNICODE
#			define String  StringW
#		else
#			define String  StringA
#		endif 

	namespace ZPUTIL
	{
		 const int INIT_STRING_LENGTH = 16;	 
		 const int STRING_LEN_INC = 1;

		 /**
			@brief �����ַ���str�ַ�����
			@return �����ַ�������
		 */
		 template<typename T>
		inline int StrLenT( const T* str )
		 {
			 if( NULL == str )
			 {
				 return 0;
			 }

			 const T* p = str;
			 int str_len = 0;
			 while( 0 != (*p) )
			 { 
				 str_len++; 
				 p++; 
			 }
			 return str_len;
		 }

		 /**
			@brief ��ָ���ַ��Ƿ�Ϊ�հ��ַ�
			@param c ��Ҫ�����ַ�
			@return �����Ƿ�Ϊ�հ��ַ�
			@retval true �ǿհ��ַ�
			@retval false ���ǿհ��ַ�
		 */
		 template<typename T>
		 inline bool IsWhiteChar( const T c )
		 {
			 if(  c == 0x09 
				 || c == 0x0A
				 || c == 0x0D
				 || c == 0x20
				 )
			 {
				 return true;
			 }
			 return false;
		 }

		 /**
			@brief ��ָ���ַ��Ƿ�ΪӢ���ַ�
			@param c ��Ҫ�����ַ�
			@return �����Ƿ�ΪӢ���ַ�
			@retval true ��Ӣ���ַ�
			@retval false ����Ӣ���ַ�
		 */
		 template<typename T>
		 inline bool IsAlpha( const T c )
		 {
			 if(  
				  ( c >= 'A' && c <= 'Z' ) ||
				  ( c >= 'a' && c <= 'z' )
				 )
			 {
				 return true;
			 }
			 return false;
		 }

		template<typename T>
		class StringT
		{
		public:

			typedef T XCHAR;

			/**
				@brief Ĭ�Ϲ��캯��
			*/
			StringT():
			  m_str_buf(NULL),
			  m_len(0),
			  m_capacity(0)
			{
				Assign( INIT_STRING_LENGTH );
			}
			
			
			StringT( const T* str ):
				m_str_buf(NULL),
				m_len(0),
				m_capacity(0)
			{
				this->operator=( str );
			}
			  
			/**
				@brief �������캯��
			*/
			StringT( const StringT& str ):
			m_str_buf(NULL),
			m_len(0),
			m_capacity(0)
			{
				this->operator=( str );
			}

			/**
				@brief ��������
			*/
			~StringT()
			{
				this->Destroy();
			}

			/**
				@brief ���������ַ������ȵ�����������С
				@param len Ҫ������ַ����ռ��С���˺�������������С�ٶ����һ���ֿռ��Ա���Ƶ��������
				@return void
			*/
			inline void Assign( const int len )
			{
				//����������ַ������ȿռ�Ƿ���
				//���볤�Ȼ�������С�Ѿ�������ֱ��
				//����
				if(  len < m_capacity )
				{
					return;
				}
				
				T* lp_old_buf = m_str_buf;
				if( len >= m_capacity )
				{
					m_str_buf = NULL;
					m_capacity = len+STRING_LEN_INC; 
					ZP_SAFE_NEW_BUFFER( m_str_buf , T , m_capacity );
					memset( m_str_buf , 0 , sizeof(T)*m_capacity );
				}

				if( NULL != lp_old_buf )
				{
					memcpy( m_str_buf , lp_old_buf , sizeof(T)*m_len );
					ZP_SAFE_DELETE_BUFFER( lp_old_buf );
				}
			}

			/**
				@brief �����ַ�������
				@return �����ַ�������
			*/
			inline int Length(void) const { return m_len; }
			/**
				@brief �����ַ����������������ɵ��ַ���
				@return �����ַ����������������ɵ��ַ���
			*/
			inline int Capacity(void) const { return m_capacity; }

			/**
				@brief ���ص�ǰ�ַ����Ƿ�Ϊ��
				@return bool
				@retval false ���ַ�����Ϊ��ʱ
				@retval true ���ַ���Ϊ��ʱ
			*/
			inline bool IsEmpty(void) const { return ( 0 == m_len ); }

			/**
				@brief �������������ַ�
				@param i ����ֵ( ������ 0 �� Length() ֮�� )
				@return T& 
			*/
			inline T& At( const int i ) 
			{
				ZP_ASSERT( i >= 0 && i < Length() );
				return m_str_buf[i];
			}

			/**
				@brief �������������ַ�
				@param i ����ֵ( ������ 0 �� Length() ֮�� )
				@return const T& 
			*/
			inline const T& At( const int i ) const 
			{
				ZP_ASSERT( i >= 0 && i < Length() );
				return m_str_buf[i];
			}
			 

			/**
				@brief ɾ���ַ�����ָ����Χ�ڵ����ַ���
				@param i ����ֵָ����ʲô�ط���ʼɾ�� ( ������ 0 <= i < Length() ֮�� )
				@param len �� i �����������i���ֽ�ɾ���೤���ַ���
				@return int ����ɾ������´����ַ���
			*/
			inline int Delete( const int i , const int len )
			{
				if( i < 0 || i >= Length() )
				{
					return Length();
				}

				if( len <= 0 )
				{
					return Length();
				}

				if( len <= Length() - i )
				{
					T* p = &m_str_buf[i];
					T* q = &m_str_buf[i+len];
					while( *(p++) = *(q++) ){} 
					m_len -= len;
				} 
				return Length();
			}

			/**
				@brief �� i ��֮ǰ���� str �ַ���
				@param str Ҫ������ַ���
				@param i ����ֵ( ������ 0 <= i <= Length() ֮�� ) 
				@return StringT& ���ز������ַ���
			*/
			inline StringT& Insert( const StringT& str , const int i )
			{
				if( i < 0 || i > Length() )
				{
					return *this;
				}

				if( str.IsEmpty() )
				{
					return *this;
				} 

				Assign( Length() + str.Length() );
				
				int pos = Length();
				int offset = str.Length();
				
				while( pos > i-1 )
				{
					m_str_buf[pos+offset] = m_str_buf[pos];
					pos--;
				}

				memcpy( &m_str_buf[i] , str.m_str_buf , sizeof(T)*str.Length() );
				m_len += str.Length();
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief �����ַ����뵱ǰ�ַ����Ƚ�
				@param str �����ַ���
				@param lowercast �Ƿ�ת����Сд�Ƚ�(������ΪtrueʱΪ��Сд������Ĭ��Ϊfalse)
				@return �ȽϽ��
				@retval -1 ��ǰ�ַ���С�ڴ����ַ���
				@retval 0   ��ǰ�ַ������ڴ����ַ���
				@retval 1   ��ǰ�ַ������ڴ����ַ���
			*/
			inline int Compare( const StringT& str , const bool lowercast = false ) const
			{
				//�������ַ�����Ϊ�� ���ж������ַ������
				if( this->IsEmpty() && str.IsEmpty() )
					return 0;
				//һ��Ϊ��һ����Ϊ������
				if( this->IsEmpty() )
				{
					return -1;
				}else if( str.IsEmpty() ){
					return 1;
				}

				//�������ַ�������Ϊ��
				const T* p = m_str_buf;
				const T* q = str.m_str_buf;
				int ret = 0;
				while( 1 )
				{
					T c1 = *p;
					T c2 = *q;

					//�Ƿ�ִ�д�Сд�����бȽ�
					if( lowercast )
					{ //���ַ�Ϊ��д��ת��ΪСд�ٽ��бȽ�
							if( (*p) >= 'A' && (*p) <= 'Z' )
							{
								c1 += 0x20;
							}
							if( (*q) >= 'A' && (*q) <= 'Z' )
							{
								c2 += 0x20;
							} 
					}

					if( ( ret = ( c1 - c2 ) ) || !c2 )
					{
						break;
					}

					p++;
					q++;
				}

				if( ret < 0 ) 
				{
					return -1;
				}else if( ret > 0 ){
					return 1;
				}
				return ret;
			}

			/**
				@brief �����ַ����뵱ǰ�ַ����Ƚϣ����Դ�Сд��
				@param str �����ַ��� 
				@return �ȽϽ��
				@retval -1 ��ǰ�ַ���С�ڴ����ַ���
				@retval 0   ��ǰ�ַ������ڴ����ַ���
				@retval 1   ��ǰ�ַ������ڴ����ַ���
			*/
			inline int ICmp( const StringT& str ) const
			{
				return Compare( str , true );
			}

			/**
				@brief �ҵ����ַ����� start_posλ�ô���ʼ��һ�γ���c�ַ���λ��
				@param c Ҫ���ҵ��ַ�
				@param start_pos ��ʼ���ҵ�λ�ã���0��ʼ������ֵ��
				@return int
				@retval -1 δ�ҵ���ָ���ַ���
				@retval 0 ~ Length()-1 ���ַ����к���c�����ص�һ���ַ���λ��
			*/
			inline int Find( const T c , const int start_pos )
			{ 
				//start_pos λ��Խ�磬��ֱ�ӷ��ز���ʧ��
				if( start_pos < 0 || start_pos >= Length() )
				{
					return -1;
				}

				int pos = start_pos; 
				while( 1 <= ( this->Length() - pos ) )
				{ 
					if( c == At( pos ) )
					{
						return pos;
					}
					pos++;
				}//while

				return -1;
			}


			/**
				@brief �ҵ����ַ����� start_posλ�ô���ʼ��һ�γ���str��λ��
				@param str Ҫ���ҵ��ַ���
				@param start_pos ��ʼ���ҵ�λ�ã���0��ʼ������ֵ��
				@return int
				@retval -1 δ�ҵ���ָ���ַ���
				@retval 0 ~ Length()-1 ���ַ����к���str�����ص�һ���ַ���λ��
			*/
			inline int Find( const StringT& str , const int start_pos )
			{
				//���ַ���Ϊ����ֱ�ӷ���
				if( str.IsEmpty() )
				{
					return -1;
				} 

				//start_pos λ��Խ�磬��ֱ�ӷ��ز���ʧ��
				if( start_pos < 0 || start_pos >= Length() )
				{
					return -1;
				}

				int pos = start_pos;

				while( str.Length() <= ( this->Length() - pos ) )
				{
					int pos_copy = pos;
					int find_str_offset = 0;

					while( 
						find_str_offset < str.Length() 
						&& ( str.At(find_str_offset) == At(pos) ) 
						)
					{
						find_str_offset++;
						pos++;
					}
					
					if( find_str_offset < str.Length() )
					{
						pos = pos_copy+1;
					}else{ //���ڵ�ǰ�ַ������ҵ���ָ���ַ���
						pos = pos_copy;
						return pos;
					} 
				}// while

				//δ�ҵ�Ҫ�ҵ��ַ���
				return -1;
			} 


			/**
				@brief �ҵ����ַ����� start_posλ�ô���ʼ��һ�γ���str��λ��
				@param str Ҫ���ҵ��ַ���
				@param start_pos ��ʼ���ҵ�λ�ã���0��ʼ������ֵ��
				@return int
				@retval -1 δ�ҵ���ָ���ַ���
				@retval 0 ~ Length()-1 ���ַ����к���str�����ص�һ���ַ���λ��
			*/
			inline int Find( const T* str , const int start_pos  )
			{
				return this->Find( StringT( str ) , start_pos );
			} 

			/**
				@brief ���ر��ַ��� �ӵ�i���ַ���ʼ�ĳ���len�����ַ���
				@param i �Ӵ��ڵ�ǰ�ַ�������ʼλ��( ��0��ʼ������ )
				@param len  Ҫ��ȡ���Ӵ�����
				@return StringT ���ַ��� 
				@retval �մ�				  ����ȡ�Ӵ�ʧ��ʱ����
				@retval �������ַ���  ��ȡ�Ӵ��ɹ�ʱ����
			*/
			inline StringT SubString( const int i , const int len ) const
			{
				StringT ret;

				//���Ȳ��������򷵻ؿմ�
				if( len <= 0 )
				{
					return ret;
				}

				//����ʼλ�÷�Χ�����򷵻ؿմ�
				if( i < 0 || i >= Length() )
				{
					return ret;
				}

				//�Ӵ���ȡ������Χ�򷵻ؿմ�
				if( i + len > Length() )
				{
					return ret;
				}

				ret.Assign( len );
				memcpy( 
					reinterpret_cast<void*>( ret.m_str_buf ) , 
					reinterpret_cast<void*>( &m_str_buf[i] ) , 
					sizeof(T)*len 
					); 
				ret.m_str_buf[len] = 0;
				ret.m_len = len;

				return ret;
			}

			/**
				@brief �����ַ���������ָ��
			*/
			inline T* Ptr(void){ return m_str_buf; }
			/**
				@brief �����ַ���������ָ��
			*/
			inline const T* Ptr(void) const { return m_str_buf; }
			 

			/**
				@brief ����ַ���
				@return void 
			*/
			inline void Empty(void) 
			{ 
				m_len = 0;
				if( NULL != m_str_buf )
				{
					m_str_buf[0] = 0;
				}
			}

			/**
			* @brief ���ַ����Ӵ�дת��ΪСд
			* @return void
			*/
			inline void ConvertToLowercast( void )
			{
				//��Ϊ����ֱ�ӷ���
				if( IsEmpty() )
				{
					return;
				}

				for( int i = 0 ; i < m_len ; i++ )
				{
					if( ( m_str_buf[i] >= 'A' && m_str_buf[i] <= 'Z' ) )
					{
						m_str_buf[i] += 0x20;
					}
				}  
			}


			/**
				@brief ���ַ���β�������ַ���
				@param str Ҫ�����ڵ�ǰ�ַ���ĩβ���ַ���
				@return String& ���Ӻ���ַ�������
			*/
			inline StringT& Append( const StringT& str  )
			{
				if( str.IsEmpty() )
				{
					return *this;
				}

				Assign( Length() + str.Length() ); 
				memcpy( 
								reinterpret_cast<void*>( &m_str_buf[m_len] ) , 
								reinterpret_cast<void*>( str.m_str_buf ) ,
								sizeof(T)*str.Length() 
							);
				m_len += str.Length();
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief ���ַ���β�������ַ�
				@param c Ҫ�����ڵ�ǰ�ַ���ĩβ���ַ�
				@return String&	���Ӻ���ַ�������
			*/
			inline StringT& Append( const T c  )
			{ 
				Assign( Length() + 1 ); 
				m_str_buf[m_len] = c; 
				m_str_buf[m_len+1] = 0;
				m_len ++; 
				return *this;
			} 

			/**
				@brief ���������Ҳ�����пհ��ַ� 
				@return String&	�����ĵ�ǰ�ַ���
			*/
			inline StringT& Trim(void)
			{
				return TrimLeft().TrimRight();
			}

			/**
				@brief ���������пո� 
				@return String&	�����ĵ�ǰ�ַ���
			*/
			inline StringT& TrimLeft(void)
			{
				if( IsEmpty() )
				{
					return *this;
				}

				int start_pos = 0;
				int len = 0;
				while( 
					IsWhiteChar( m_str_buf[len] )
					)
				{
					len++;
				}

				if( len > 0 )
				{
					Delete( start_pos , len );
				}
				return *this;
			}

			/**
				@brief ����Ҳ����пո� 
				@return String&	�����������ַ���
			*/
			inline StringT& TrimRight(void)
			{
				if( IsEmpty() )
				{
					return *this;
				}

				int start_pos = Length()-1;
				int len = 0;

				while(  
					IsWhiteChar( m_str_buf[start_pos] ) 
					)
				{
					start_pos--;
					len++;
				}

				if( len > 0 )
				{
					Delete( start_pos+1 , len );
				}
				return *this;
			} 

			/**
				@brief ����ַ����е����пհ��ַ�
				@return String&	�����ĵ�ǰ�ַ���
			*/
			inline StringT& ClearAllWhiteChars(void)
			{
				if( IsEmpty() )
				{
					return *this;
				}

				int final_pos = 0;  
				for( int pos = 0 ; pos < Length() ; pos++ )
				{
					 if(  !IsWhiteChar( m_str_buf[pos] )  )
					 {
						 m_str_buf[final_pos++] = m_str_buf[pos]; 
					 }
				}

				m_str_buf[final_pos] = 0;
				m_len = final_pos;
				return *this;
			}
			
			/**
				@brief �滻�ַ����е���start_pos ��ʼ���������е�str�ַ����������滻Ϊreplace_str
				@param str Ҫ�����滻���ַ���
				@param replace_str �滻���ַ���
				@param start_pos ������
				@return String& �����滻��ɵ��ַ���
			*/
			inline StringT& Replace( const StringT& str , const StringT& replace_str , const int start_pos )
			{
				if( IsEmpty() )
				{
					return *this;
				}

				if( str.IsEmpty() )
				{
					return *this;
				}

				int pos = start_pos; 
				while( -1 != ( pos = Find( str , pos ) ) )
				{
					 Delete( pos , str.Length() );
					 Insert( replace_str , pos );
					 pos += replace_str.Length();
				}

				return *this;
			}

			/**
				@brief �����ַ���  
			*/
			inline void Destroy(void)
			{
				ZP_SAFE_DELETE_BUFFER( m_str_buf );
				m_len = 0;
				m_capacity = 0;
			}
			 
			/**
				@brief �ж�������������
			*/
			inline bool operator==( const StringT& rhs ) const
			{
				return ( this->Compare( rhs ) == 0 );
			} 

			/**
				@brief �жϲ�������������
			*/
			inline bool operator!=( const StringT& rhs ) const
			{
				return !( this->operator==( rhs ) );
			}

			/**
				@brief +=��������أ��ڵ�ǰ�ַ���ĩβ�����ַ���
			*/
			inline StringT& operator+=( const StringT& rhs )
			{
				return this->Append( rhs );
			} 

			/**
				@brief +=��������أ��ڵ�ǰ�ַ���ĩβ�����ַ���
			*/
			inline StringT& operator+=( const T* rhs )
			{
				return this->Append( StringT( rhs ) );
			}

			/**
				@brief +=��������أ��ڵ�ǰ�ַ���ĩβ�����ַ�
			*/
			inline StringT& operator+=( const T c )
			{
				return this->Append( c );
			}

			/**
				@brief ���ظ�ֵ�����
			*/
			inline StringT& operator=( const StringT& rhs )
			{
				if( rhs.IsEmpty() )
				{
					this->Destroy();
					return *this;
				}

				Assign( rhs.Length() );
				memcpy( m_str_buf , rhs.m_str_buf , sizeof(T)*rhs.Length() );
				m_len = rhs.Length();
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief ���ظ�ֵ�����
			*/
			inline StringT& operator=( const T* rhs )
			{
				if( NULL == rhs )
				{
					return *this;
				}
				 
				int str_len = StrLenT( rhs ); 
				if( str_len == 0 )
				{ 
					this->Destroy();
					return *this;
				}

				Assign( str_len );
				memcpy( m_str_buf , rhs , sizeof(T)*str_len );
				m_len = str_len;
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief �ӷ����������
			*/
			inline StringT operator+( const StringT& rhs ) const 
			{
				StringT rs = *this;
				rs += rhs;
				return rs;
			}

		private:
			T* m_str_buf;	///>�ַ���������
			int m_len;			///>�ַ������ȣ����ַ���Ϊ��λ��
			int m_capacity;	///>�ַ������������������ַ���Ϊ��λ��
		}; 

		template<typename T>
		std::ostream& operator<<( std::ostream& o , const StringT<T>& str )
		{
			if( NULL != str.Ptr() )
			{
				o<<str.Ptr();
			}
			return o;
		}

		typedef StringT<char> StringA;	///>		���ַ����ַ���
		typedef StringT<wchar_t> StringW;	///> ���ַ����ַ���



	}//namespace ZPUTIL

#endif //ZP_STRING_UTIL

