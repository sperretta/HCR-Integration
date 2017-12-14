#ifndef MOVEHEAD_HPP
#define MOVEHEAD_HPP

#include <pyWrap.hpp>
#include <string>

class MoveHead :
    public pyWrap
{
    public:
        MoveHead() : pyWrap( "gesture_engine", "move_head_random", 1 ) { }
        ~MoveHead() = default;
	void operator()( std::string IP)
        {
            PyObject *pValue1;

            pValue1 = PyString_FromString(IP.c_str());

            PyTuple_SetItem( m_pArgs, 0, pValue1 );

            PyObject_CallObject( m_pFunc, m_pArgs );
        }
};

#endif
