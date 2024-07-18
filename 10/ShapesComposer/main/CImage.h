#pragma once
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(const std::string& id, const std::filesystem::path& path,
		Rect rect)
		: m_id(id)
		, m_path(path)
		, m_frame(rect)
	{}

	std::string GetId() const  override
	{
		return m_id;
	}
	Rect GetFrame() const override
	{
		return m_frame;
	}

	void SetFrame(const Rect& frame) override
	{
		m_frame = frame;
	}

	Point GetPosition() const override
	{
		return m_frame.leftTop;
	}


	void SetPosition(Point leftTop) override
	{
		m_frame.leftTop = leftTop;
	}

	std::filesystem::path GetPath() const override
	{
		return m_path;
	}

protected:

	Rect GetChangedData() const override
	{
		return m_frame;
	}

private:
	std::string m_id;
	std::filesystem::path m_path;
	Rect m_frame;
};