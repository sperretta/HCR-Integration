#ifndef MOVEHEAD_HPP
#define MOVEHEAD_HPP

#include <pyWrap.hpp>
#include <string>

class MoveHead :
    public pyWrap
{
    public:
        MoveHead() : pyWrap( "gesture_engine", "move_head_random", 2 ) { }
        ~MoveHead() = default;
	void operator()( std::string IP, int distance)
        {
            PyObject *pValue1;
            PyObject *pValue2;

            pValue1 = PyString_FromString(IP.c_str());
            pValue2 = PyLong_FromLong(distance);

            PyTuple_SetItem( m_pArgs, 0, pValue1 );
            PyTuple_SetItem( m_pArgs, 1, pValue2 );

            PyObject_CallObject( m_pFunc, m_pArgs );
        }
};

#endif
