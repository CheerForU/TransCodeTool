#pragma once
#include "StdAfx.h"
#include "fileOper.h"
#include <atlconv.h>
#include "myLog.h"


fileOper::fileOper()
{
	//���ô洢����Ϊ1M
	m_bufferSize=1024*1024;
	m_lastPos = m_bufferSize-1;
	m_bytesRead = 0;
	m_bytesWrite = 0;
	m_bufferRead = 0;
	m_bufferWrite = 0;
	m_len = 0;
	m_fileLen = 0;

	m_buffer =  new byte[m_bufferSize];
	memset(m_buffer,0,m_bufferSize);
}

fileOper:: ~fileOper()
{
	delete[] m_buffer;
}

void fileOper::setLastErrInfo(string lastErrInfo) {
	m_lastErrInfo = lastErrInfo;
}

string fileOper::getLastErrInfo() {
	return m_lastErrInfo;
}

bool fileOper::openFile(string srcPath)
{
	m_handle = CreateFile(srcPath.c_str(),GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);

	if(m_handle==INVALID_HANDLE_VALUE)
	{		 
		DWORD e = GetLastError();
		setLastErrInfo("�ļ���ʧ��,����ԭ��"+e);
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		CloseHandle(m_handle);
		return false;
	}
	return true;
}

bool fileOper::closeFile()
{
	if(m_handle!=NULL){
		if(!CloseHandle(m_handle))
		{
			DWORD e = GetLastError();
			setLastErrInfo("�ļ��ر�ʧ��,����ԭ��"+e);
			LOG4CPLUS_ERROR(logger,m_lastErrInfo);
			return false;
		}
		return true;
	}else
	{
		setLastErrInfo("�ļ����Ϊ��");
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return false;
	}

}


DWORD fileOper::ReadBufFile(DWORD bufOffSet)
{
	DWORD m_readLen;
	if (m_fileLen - m_bufferRead > m_bufferSize)
	{
		//�������һ��buffer
		m_readLen = m_bufferSize - bufOffSet;
		
	}else
	{
		//���һ��buffer
		m_readLen = m_fileLen - m_bufferRead;
	}
	if(ReadFile(m_handle, m_buffer + bufOffSet , m_readLen, &m_bytesRead, NULL) <= 0)
	{
		DWORD e = GetLastError();
		setLastErrInfo("���ļ�ʧ��,����ԭ��"+e);
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return 0;
	}
	m_bufferRead += m_readLen;
	return m_readLen;

}

DWORD fileOper::ReadStringFile(byte* line,DWORD linesize)
{
	DWORD lineSize = 0;
	DWORD i = 0;	
	DWORD readLen = 0;
	DWORD bufOffSet = 0;
	m_fileLen = GetFileSize(m_handle ,NULL);
	m_myLen = m_fileLen;
	memset(line,0,linesize);
	do
	{
		if (m_lastPos == m_bufferSize - 1)
		{
			//buffer��һ��
			readLen = ReadBufFile(bufOffSet);
			m_len = bufOffSet + readLen;
			i = 0;
		}else
		{
			//buffer������
			i = m_lastPos + 1;
		}
		for(;i < m_len; i++)
		{
			if (ifEnd(m_buffer,i,m_len))
			{
				i= i + m_flagLen;
				if (m_lastPos == m_bufferSize-1)
				{
					//��һ��
					m_lastPos = 0;
					lineSize = i - m_lastPos+1;
					if (lineSize>linesize)
					{
						setLastErrInfo("һ�г��ȳ���10K");
						LOG4CPLUS_ERROR(logger,m_lastErrInfo);
						return -1;
					}
					memcpy(line, m_buffer + m_lastPos, lineSize);
				}else
				{
					//������
					lineSize = i - m_lastPos ;
					if (lineSize>linesize)
					{
						setLastErrInfo("һ�г��ȳ���10K");
						LOG4CPLUS_ERROR(logger,m_lastErrInfo);
						return -1;
					}
					memcpy(line, m_buffer + m_lastPos + 1, lineSize);
				}
				m_lastPos = i;
				m_bufferWrite += lineSize;
				return lineSize;
			}
		}
		
		//δ�����н���
		if (m_bytesRead == m_fileLen||m_bufferSize+m_bytesRead == m_fileLen)
		{
			if (m_lastPos == m_bufferSize-1){
				lineSize = m_fileLen - m_bufferWrite;
				if (lineSize>linesize)
				{
					setLastErrInfo("һ�г��ȳ���10K");
					LOG4CPLUS_ERROR(logger,m_lastErrInfo);
					return -1;
				}
				memcpy(line, m_buffer , lineSize);
			}
			else
			{
				lineSize = m_fileLen - m_bufferWrite;
				if (lineSize>linesize)
				{
					setLastErrInfo("һ�г��ȳ���10K");
					LOG4CPLUS_ERROR(logger,m_lastErrInfo);
					return -1;
				}
				memcpy(line, m_buffer + m_lastPos+1 , lineSize);
			}
			m_lastPos = i;
			m_bufferWrite += lineSize;
			return lineSize;
		}
		bufOffSet = m_bufferSize - m_lastPos - 1;
		memmove(m_buffer, m_buffer + m_lastPos + 1, bufOffSet);
		m_lastPos = m_bufferSize-1 ;
		
	} while (m_bufferWrite != m_fileLen);
	return -1;
}

int fileOper::WriteStringFile(byte* buf, DWORD bufSize)
{
	if(!WriteFile(m_handle,buf,bufSize,&m_bytesWrite,NULL))
	{
		DWORD e = GetLastError();
		setLastErrInfo("д�ļ�ʧ��,����ԭ��"+e);
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return -1;
	}
	return 0;
}
