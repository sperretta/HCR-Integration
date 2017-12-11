#include "pyWrap.hpp"

pyWrap::pyWrap( const std::string& moduleName,
                const std::string& functionName,
                unsigned int numArgs
                ) :
    m_pName{ nullptr }, m_pModule{ nullptr }, m_pDict{ nullptr }, m_pFunc{ nullptr }, m_pArgs{ nullptr }, m_numArgs{ numArgs }
{
	m_pName = PyString_FromString( moduleName.c_str() );
	m_pModule = PyImport_Import( m_pName );

	m_pDict = PyModule_GetDict( m_pModule );
	m_pFunc = PyDict_GetItemString( m_pDict, functionName.c_str() );

	m_pArgs = PyTuple_New( m_numArgs );
}

// TODO: Clean up member pointers?
pyWrap::~pyWrap() = default;
