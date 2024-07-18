#pragma once
#include "COutputStreamDecorator.h"

class CCompressStream : public COutputStreamDecorator
{
public:
	CCompressStream(std::unique_ptr<IOutputDataStream>&& stream)
		:COutputStreamDecorator(move(stream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		//if (m_pair.second == 0)
		//{
		//	UpdatePair(data);
		//	//return;
		//}
		//else if (m_pair.first == data)
		//{
		//	m_pair.second++;
		//	//return;
		//}
		//if (m_pair.first != data)
		//{
		//	WritePair();
		//	UpdatePair(data);
		//}
		if (m_pairValueAndCount.second == 0)
		{
			UpdatePair(data);
			return;
		}
		if ((m_pairValueAndCount.first != data && m_pairValueAndCount.second != 0) || m_pairValueAndCount.second == m_max)
		{
			WritePair();
			UpdatePair(data);
		}
		else if (m_pairValueAndCount.second != 0)
		{
			m_pairValueAndCount.second++;
			return;
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* buf = static_cast<const uint8_t*>(srcData);
		for (size_t i = 0; i < size; i++)
		{
			WriteByte(*buf);
			buf++;
		}
		//не надо 
		WritePair();
	}

	void Close() override
	{
		WritePair();
		m_stream->Close();
	}

private:

	void UpdatePair(uint8_t data)
	{
		m_pairValueAndCount.second = 1;
		m_pairValueAndCount.first = data;
	}

	void WritePair() const
	{
		m_stream->WriteByte(m_pairValueAndCount.first);
		m_stream->WriteByte(m_pairValueAndCount.second);
	}

	std::pair<uint8_t, uint8_t> m_pairValueAndCount = { 0, 0 };
	const uint8_t m_max = std::numeric_limits<uint8_t>::max();
};