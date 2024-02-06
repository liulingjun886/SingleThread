#pragma once

struct CEmptyClass
{
};

#define TEMPCLASSBEGIN(classname) template <typename T = CEmptyClass> class classname : public T \
{ \

#define TEMPCLASSEND };
	

