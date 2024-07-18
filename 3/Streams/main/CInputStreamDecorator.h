#pragma once
#include "IInputDataStream.h"
#include <memory>

class CInputStreamDecorator : public IInputDataStream
{
public:
	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}
protected:
	CInputStreamDecorator(std::unique_ptr<IInputDataStream>&& stream)
		: m_stream(move(stream))
	{}
	std::unique_ptr<IInputDataStream> m_stream;
};