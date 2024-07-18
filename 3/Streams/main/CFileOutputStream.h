#pragma once
#include "IOutputDataStream.h"
#include <fstream>

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(const std::string& fileName)
		: m_stream(fileName, std::ios::out | std::ios::binary)

	{}

	void WriteByte(uint8_t data) override
	{
		if (!m_stream.is_open())
			throw std::logic_error("File already closed");
		m_stream.write(reinterpret_cast<char*>(&data), 1);
		if (m_stream.fail() || m_stream.bad())
			throw std::ios_base::failure("Error with writing byte");
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (!m_stream.is_open())
			throw std::logic_error("File already closed");
		m_stream.write(static_cast<const char*>(srcData), size);
		if (m_stream.fail() || m_stream.bad())
			throw std::ios_base::failure("Error with writing block");
	}

	void Close() override
	{
		m_stream.close();
	}
private:
	std::ofstream m_stream;
};