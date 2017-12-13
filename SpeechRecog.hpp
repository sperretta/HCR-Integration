#ifndef SPEECHRECOG_HPP
#define SPEECHRECOG_HPP

#include <pyWrap.hpp>
#include <string>

class SpeechRecog :
    public pyWrap
{
    public:
        SpeechRecog() : pyWrap( "SpeechRec", "get_command", 2 ) { }
        ~SpeechRecog() = default;
	std::string operator()( float timeout, float distance)
        {
            PyObject *pValue1;
	    PyObject *pValue2;

            pValue1 = PyFloat_FromDouble(timeout);
	    pValue2 = PyFloat_FromDouble(distance);

            PyTuple_SetItem( m_pArgs, 0, pValue1 );
	    PyTuple_SetItem( m_pArgs, 1, pValue2 );

            PyObject* pResult = PyObject_CallObject( m_pFunc, m_pArgs );
            if(pResult == nullptr)
            {
                return std::string("");
            }
            else
            {
		std::string returnString(PyString_AsString(pResult));
		if(returnString.length() == 0)
		{
		    return std::string("");
		}
		return returnString;
            }
        }
};

#endif
