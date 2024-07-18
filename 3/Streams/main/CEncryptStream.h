#pragma once
#include "COutputStreamDecorator.h"
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

class CEncryptStream : public COutputStreamDecorator
{
public:
	CEncryptStream(std::unique_ptr<IOutputDataStream>&& stream, unsigned seed)
		: COutputStreamDecorator(move(stream))
	{
		m_table.resize(256);
		std::iota(m_table.begin(), m_table.end(), 0);
		std::mt19937 rnd(seed);
		std::shuffle(m_table.begin(), m_table.end(), rnd);
	}

	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(m_table[data]);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* buf = static_cast<const uint8_t*>(srcData);
		for (size_t i = 0; i < size; i++)
		{
			WriteByte(*buf);
			buf++;
		}
	}

	void Close() override
	{
		m_stream->Close();
	}
private:
	std::vector<uint8_t> m_table;
};