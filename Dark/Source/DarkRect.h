#ifndef DARK_RECT_H_
#define DARK_RECT_H_

class DarkRect;

inline bool IntersectInY(DarkRect& rect1, DarkRect& rect2);		//Checks for both way collision
inline bool IntersectInX(DarkRect& rect1, DarkRect& rect2);		//Checks for both way collision

class DarkRect
{
	int x,y;
	int m_depth;
	int m_width, m_height;
public:
	DarkRect(void);
	DarkRect(int x_, int y_, int width_, int height_, int depth_ = 0);
	
	int GetTop()		{ return y;				}
	int GetLeft()		{ return x;				}
	int GetRight()		{ return x + m_width;	}
	int GetBottom()		{ return y + m_height;	}
	int GetWidth()		{ return m_width;		}
	int GetHeight()		{ return m_height;		}
	int GetDepth()		{ return m_depth;		}
	bool  Intersect(DarkRect& rect)	{ if(IntersectInX( rect,*this ) && IntersectInY( rect,*this ) )return true; else return false;}
	virtual ~DarkRect(void);
};


inline bool IntersectInX(DarkRect& rect1, DarkRect& rect2)				
{
	if((rect2.GetLeft() >= rect1.GetLeft() && rect2.GetLeft() <= rect1.GetRight()) || (rect2.GetRight() <= rect1.GetRight() && rect2.GetRight() >= rect1.GetLeft()))
		return true;
	else if((rect1.GetLeft() >= rect2.GetLeft() && rect1.GetLeft() <= rect2.GetRight()) || (rect1.GetRight() <= rect2.GetRight() && rect1.GetRight() >= rect2.GetLeft()))
		return true;
	else
		return false;

}

inline  bool IntersectInY(DarkRect& rect1, DarkRect& rect2)				
{
	if((rect2.GetTop() >= rect1.GetTop() && rect2.GetTop() <= rect1.GetBottom()) || (rect2.GetBottom() <= rect1.GetBottom() && rect2.GetBottom() >= rect1.GetTop()))
		return true;
	else if((rect1.GetTop() >= rect2.GetTop() && rect1.GetTop() <= rect2.GetBottom()) || (rect1.GetBottom() <= rect2.GetBottom() && rect1.GetBottom() >= rect2.GetTop()))
		return true;
	else
		return false;

}

#endif