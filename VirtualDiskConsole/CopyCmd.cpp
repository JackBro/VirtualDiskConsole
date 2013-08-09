#include "CopyCmd.h"


namespace CommandSys
{
	 
CopyCmd::CopyCmd( void )
{

}
 
CopyCmd::~CopyCmd( void )
{

}

void CommandSys::CopyCmd::Execute( void )
{
	if( m_params.Count() > 0 )
	{
		m_result_output = "���֧�ֲ���";
		return;
	}

	if( m_paths.Count() == 0 )
	{
		m_result_output = "�����﷨����ȷ";
		return;
	}

	if( m_paths.Count() != 2 )
	{
		m_result_output = "�����﷨����ȷ";
		return;
	}
	 
	LexerSys::SearchPath src_path = m_paths.At(0);
	LexerSys::SearchPath dst_path = m_paths.At(1);

	//����Ŀ��·���Ƿ���һ���ļ���
	BOOL src_path_is_folder = PathIsDirectory( src_path.Path().Ptr() ); 
	Util::String src_path_origin = src_path.Path();
	Util::String src_path_without_filespec = src_path_origin;

	FileSys::Node* lp_search_node = SearchNodeByPathTokens( dst_path );

	if( TRUE == src_path_is_folder )
	{
		//δ�ҵ�Ŀ��ڵ�
		if( lp_search_node == NULL )
		{
			m_result_output = "������Ŀ���ļ��в�����";
			return;
		}else{
			//�ҵ�Ŀ��ڵ㵫����һ���ļ�
			if( lp_search_node->IsFile() )
			{
				m_result_output = "���ڿ���Դ·��ָ���ļ��У�����Ŀ��·���������ļ���";
				return;
			} 
		}
		//�ص������ļ���
		src_path_without_filespec = src_path_origin.SubString( 0 , 
			src_path_origin.Length() - ( src_path_origin.Length() -src_path_origin.FindLastOf('\\') ) );

	}//if( TRUE == src_path_is_folder )
	 

	WIN32_FIND_DATA find_data;
	memset( &find_data , 0 , sizeof(find_data) );
	HANDLE handle_findfile = FindFirstFile( src_path.Path().Ptr() , &find_data );
	if( INVALID_HANDLE_VALUE == handle_findfile )
	{
		m_result_output = "���ش���·����������";
		return;
	}  

	//���ұ��ش��̵�·����ָ�����ļ������ļ�������
	Util::QueueT<Util::String>  copy_filenames; 
	do{
		if( find_data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE )
		{
			copy_filenames.Enqueue( find_data.cFileName );  
		}
	} while( FindNextFile( handle_findfile , &find_data ));
	  
	FindClose( handle_findfile );
	handle_findfile = NULL;
	   

	m_result_output = Util::StringFormat( "�ܹ�������%d���ļ�\n", 
													copy_filenames.Size() ); 
	while( copy_filenames.Size() )
	{
		m_result_output.Append( copy_filenames.Front() );
		m_result_output.Append('\n'); 
		copy_filenames.Dequeue();
	}



}


}//namespace CommandSys