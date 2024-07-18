#pragma once
#include "CInputStreamDecorator.h"
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

class CDecryptStream : public CInputStreamDecorator
{
public:
	CDecryptStream(std::unique_ptr<IInputDataStream>&& stream, unsigned seed)
		: CInputStreamDecorator(move(stream))
	{
		m_table.resize(256);
		std::iota(m_table.begin(), m_table.end(), 0);
		std::mt19937 rnd(seed);
		std::shuffle(m_table.begin(), m_table.end(), rnd);
	}

	uint8_t ReadByte() override
	{
		uint8_t byte = m_stream->ReadByte();
		auto it = std::find(m_table.begin(), m_table.end(), byte);
		auto result = static_cast<uint8_t>(std::distance(m_table.begin(), it));
		return result;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		uint8_t* buf = static_cast<uint8_t*>(dstBuffer);
		std::streamsize readSize = m_stream->ReadBlock(buf, size);
		for (size_t i = 0; i < readSize; i++)
		{
			*buf = m_table[*buf];
			buf++;
		}
		return readSize;
	}
private:
	std::vector<uint8_t> m_table;
};