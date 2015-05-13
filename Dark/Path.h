#pragma once

class Path
{
public:
	Path(char* path_);
	Path(void);
	~Path(void);
	char* GetPath() const		{ return m_path;	}
	void SetPath(char* path_)	{ m_path = path_;	}	
private:
	char* m_path;
};

