#include "FileNode.h"

namespace FileSys
{
	 
FileNode::FileNode(void):
m_binary_file(false),
m_size(0),
m_data(NULL)
{
}


FileNode::~FileNode(void)
{
	ZP_SAFE_DELETE_BUFFER( m_data );
	m_size = 0;
}

int FileSys::FileNode::Write( const void* data  , const int size  )
{   
	if( NULL == data || 0 == size )
	{
		return 0;
	}

	ZP_SAFE_NEW_BUFFER( m_data , unsigned char , size );
	memcpy( m_data , data , size );
	m_size = size;
	//�жϴ��������Ƿ�Ϊ����������
	m_binary_file = IdentifyBinaryFileData( m_data , m_size ); 
	return size;
}

int FileSys::FileNode::Read( const int offset , const int size , void* data )
{ 
	if( NULL == data ||  size <= 0 ) return 0;
	if( offset < 0 || offset >= m_size ) return 0; 
	int read_size = ( m_size - offset ) < size ? ( m_size - offset ) : size;
	memcpy( data , &m_data[offset] , sizeof( read_size ) );
	return read_size;
} 

bool FileNode::Compare( FILE* filestream , Util::String& output ) const
{
	if( 
		NULL == filestream ||
		m_data == NULL ||
		m_size == 0 
		)
	{ 
		return false;
	}
	
	Util::VectorT<unsigned char> curr_file_diff_buf;
	Util::VectorT<unsigned char> other_file_diff_buf;

	bool binary_output = IsBinaryFile();
	int ch1 = 0;
	int ch2 = 0;
	int i = 0;   

	for( i = 0 ; ( i < m_size ) && feof( filestream ) == 0 ; i++ )
	{
		 ch1 = static_cast<int>( m_data[i] );
		 ch2 = fgetc( filestream ); 
		//�����ֲ�ͬ
		if( ch1 != ch2 )
		{  
			curr_file_diff_buf.PushBack( ch1 );
			other_file_diff_buf.PushBack( ch2 );
			break;
		}
	}//for( i = 0 ; ...

	 
	

	return false;
}
 
bool FileNode::Compare( const void* data , const int size , Util::String& output ) const
{
	if( NULL == data || 0 == size )
	{
		return false;
	}



	return false;
}

bool FileNode::Compare( const Node* other_node , Util::String& output ) const
{
	if( other_node == NULL )
	{
		return false;
	}

	if( other_node == this )
	{
		output = "���ݱȽ�һ��";
		return true;
	}

	if( other_node->IsFile() )
	{ 
		unsigned char c1 = 0;
		unsigned char c2 = 0;

		//������������һ���Ƕ������ļ������ö������ļ����
		if( IsBinaryFile() || other_node->IsBinaryFile() )
		{

		}else{//�������ı������ͬ

		} 
	}//if( node->IsFile() )

	return false;
}



bool FileNode::IdentifyBinaryFileData( const void* data , const int size ) const
{
	ZP_ASSERT( NULL == data );

	for( int i = 0 ; i < size ; i++ )
	{
		if( 0 == ((unsigned char*)data)[i] )
		{
			return true;
		}
	}
	return false;
}

void FileNode::MakeDiffOutput( 
	const Util::VectorT<unsigned char>& diffbuf1 , 
	const Util::VectorT<unsigned char>& diffbuf2 , 
	Util::String& output )
{
	if( diffbuf1.Count() == 0 && diffbuf2.Count() == 0 )
	{
		output = "���ݱȽ�һ��";
		return;
	}
}


}//namespace FileSys