#pragma once
#include "IInputDataStream.h"
#include <fstream>

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(const std::string& fileName)
		: m_stream(fileName, std::ios::in | std::ios::binary)
	{}

	bool IsEOF() const override
	{
		return m_stream.eof();
	}

	uint8_t ReadByte() override
	{		
		char* byte = new char;
		m_stream.read(byte, 1);
		if (IsEOF())
			throw std::ios_base::failure("The end of the file has been reached");
		uint8_t result = static_cast<uint8_t>(*byte);
		delete byte;
		//m_stream >> byte;
		return result;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (IsEOF())
			throw std::ios_base::failure("The end of the file has been reached");
		m_stream.read(static_cast<char*>(dstBuffer), size);
		if (m_stream.bad() || m_stream.fail())
			throw std::ios_base::failure("Error with read block");
		return m_stream.gcount();
	}

private:
	std::ifstream m_stream;
};