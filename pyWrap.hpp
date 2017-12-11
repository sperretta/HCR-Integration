#ifndef PYWRAP_HPP
#define PYWRAP_HPP

#include <python2.7/Python.h>

#include <string>

class pyWrap
{
    public:
        pyWrap( const std::string& moduleName,
                const std::string& functionName,
                unsigned int numArgs
                );
        virtual ~pyWrap();

    protected:
        PyObject *m_pName,
                 *m_pModule,
                 *m_pDict,
                 *m_pFunc,
                 *m_pArgs;

        unsigned int m_numArgs;
};

#endif // PYWRAP_HPP
