#pragma once
#include "CInputStreamDecorator.h"

class CDecompressStream : public CInputStreamDecorator
{
public:
	CDecompressStream(std::unique_ptr<IInputDataStream>&& stream)
		: CInputStreamDecorator(move(stream))
	{}

	uint8_t ReadByte() override
	{
		ReadPair();
		m_pairValueAndCount.second--;
		return m_pairValueAndCount.first;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		uint8_t* buf = static_cast<uint8_t*>(dstBuffer);
		//std::streamsize readSize = m_stream->ReadBlock(buf, size);
		for (size_t i = 0; i < size; i++)
		{
			//В случае исключения вернуть то что считалось
			ReadPair();
			*buf = m_pairValueAndCount.first;
			m_pairValueAndCount.second--;
			buf++;
		}
		return size;
	}
private:
	void ReadPair()
	{
		if (m_pairValueAndCount.second == 0)
		{
			m_pairValueAndCount.first = m_stream->ReadByte();
			m_pairValueAndCount.second = m_stream->ReadByte();
		}
	}

	std::pair<uint8_t, uint8_t> m_pairValueAndCount = { 0, 0 };
};