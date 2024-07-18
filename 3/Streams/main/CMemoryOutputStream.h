#pragma once
#include "IOutputDataStream.h"
#include <vector>

class CMemoryOutputStream : public IOutputDataStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t>& memory)
		: m_stream(memory)
		, m_isOpen(true)
	{}

	void WriteByte(uint8_t data) override
	{
		if (!m_isOpen)
			throw std::logic_error("File already closed");
		m_stream.push_back(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (!m_isOpen)
			throw std::logic_error("File already closed");
		const uint8_t* buf = static_cast<const uint8_t*>(srcData);
		for (size_t i = 0; i < size; i++)
		{
			m_stream.push_back(buf[i]);
		}
		
	}

	void Close() override
	{
		m_isOpen = false;
	}
private:
	std::vector<uint8_t>& m_stream;
	bool m_isOpen;
};