#ifndef GESTURING_HPP
#define GESTURING_HPP

#include <pyWrap.hpp>
#include <string>

class Gesturing :
    public pyWrap
{
    public:
        Gesturing() : pyWrap( "gesture_engine", "point_wrap", 2 ) { }
        ~Gesturing() = default;
	int operator()( std::string IP, int action)
        {
            PyObject *pValue1;
	    PyObject *pValue2;

            pValue1 = PyString_FromString(IP.c_str());
	    pValue2 = PyLong_FromLong(action);

            PyTuple_SetItem( m_pArgs, 0, pValue1 );
	    PyTuple_SetItem( m_pArgs, 1, pValue2 );

            PyObject* pResult = PyObject_CallObject( m_pFunc, m_pArgs );
            if(pResult == nullptr)
            {
                return -1;
            }
            else
            {
		return PyLong_AsLong(pResult);
            }
        }
};

#endif
