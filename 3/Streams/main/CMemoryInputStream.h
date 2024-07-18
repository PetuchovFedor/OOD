#pragma once
#include "IInputDataStream.h"
#include <vector>

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& memory)
		: m_stream(memory)
	{}
	bool IsEOF() const override
	{
		return m_readPos == m_stream.size();
	}

	uint8_t ReadByte() override
	{
		if (IsEOF())
			throw std::ios_base::failure("The end of the file has been reached");
		uint8_t byte = m_stream[m_readPos];
		m_readPos++;
		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (size > (m_stream.size() - m_readPos))
			throw std::ios_base::failure("the reading size exceeds the size possible for reading");
		uint8_t* buf = static_cast<uint8_t*>(dstBuffer);
		std::copy(m_stream.begin() + m_readPos, m_stream.begin() + m_readPos + size, buf);
		m_readPos += size;
		return size;
	}

private:
	std::vector<uint8_t> m_stream;
	size_t m_readPos = 0;
};