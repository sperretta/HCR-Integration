#ifndef READBOARD_HPP
#define READBOARD_HPP

#include <GameEngine/enum.hpp>

#include <pyWrap.hpp>

class ReadBoard :
    public pyWrap
{
    public:
        ReadBoard() : pyWrap( "readBoard", "readBoard", 1 ) { }
        ~ReadBoard() = default;
        std::vector<Piece> operator()( std::string camera )
        {
            PyObject *pValue1;

            pValue1 = PyString_FromString( camera.c_str() );
            PyTuple_SetItem( m_pArgs, 0, pValue1 );

            PyObject* pResult = PyObject_CallObject( m_pFunc, m_pArgs );
            if(pResult == nullptr)
            {
                return std::vector<Piece>();
            }
            else
            {
                std::vector<Piece> state( PyList_Size( pResult ), Piece::none );
                PyObject *listItem = nullptr;

                for( unsigned i = 0; i < state.size(); ++i )
                {
                    listItem = PyList_GetItem( pResult, i );
                    switch( PyInt_AsLong( listItem ) )
                    {
                        case 2:
                            state.at( i ) = Piece::p2;
                            break;
                        case 1:
                            state.at( i ) = Piece::p1;
                            break;
                        case 0:
                        default:
                            state.at( i ) = Piece::none;
                            break;
                    }
                }

                return state;
            }
        }
};

#endif // READBOARD_HPP
