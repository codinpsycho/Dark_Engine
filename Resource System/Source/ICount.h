//.....................................................
//		Dark Engine :: Refernce Counting Base Class
//		Coded by Ishkaran Singh
//		27/3/12
//		I Game hard, I Code Harder
//.....................................................


#pragma once

class ICount
{

public:
	//If 0, no one wants u, u piece of s#!T, get out of my heap
	void Release()	{ if(DecreaseRef() == 0) delete this;	}
	//Don't forget to implement this u #$@%
	virtual ICount& Clone()	{ return *this;	}
	//But everyone can destroy u >:D
	virtual ~ICount(void) {}
// 	void fun()	{std::cout<<"ish";	}


protected:
	//No one can create u >:)
	ICount(void) : m_count(1) {}

	void AddRef()	{ ++ m_count; }
	int DecreaseRef() { return(--m_count);}

private:

	//Reference count
	int m_count;

};
