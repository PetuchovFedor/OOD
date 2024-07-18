#pragma once
#include "IOutputDataStream.h"
#include <memory>

class COutputStreamDecorator : public IOutputDataStream
{
protected:
	COutputStreamDecorator(std::unique_ptr<IOutputDataStream>&& stream)
		: m_stream(move(stream))
	{}
	std::unique_ptr<IOutputDataStream> m_stream;
};