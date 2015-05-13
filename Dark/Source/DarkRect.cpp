#include "DarkRect.h"

DarkRect::DarkRect(void)
{
	x = y = m_width = m_height = m_depth = 0;
}
DarkRect::DarkRect(int x_, int y_, int width_, int height_, int depth_)
{
	x = x_;
	y = y_;
	m_width = width_;
	m_height = height_;
	m_depth = depth_;
}

DarkRect::~DarkRect(void)
{
}
