#include "BoardGraphics.hpp"

BoardGraphics *pThis = nullptr;

BoardGraphics::BoardGraphics() : m_positionStates( 45, PositionState::None ), m_updatePieces{ false }, m_prevTime{ std::chrono::high_resolution_clock::now() }
{
    pThis = this;
}

BoardGraphics::~BoardGraphics() = default;

void BoardGraphics::start()
{
    m_run = true;
    m_thread = std::thread{ &BoardGraphics::graphicsThread, this };
}

// TODO: Finish this
void BoardGraphics::updateState()
{

}

void BoardGraphics::end()
{
    m_run = false;
    m_thread.join();
    S2D_FreeWindow( m_window );
}

void BoardGraphics::graphicsThread()
{
    m_window = S2D_CreateWindow( "GameBoard", SCREEN_WIDTH, SCREEN_HEIGHT, &BoardGraphics::updateStatic, &BoardGraphics::renderStatic, S2D_FULLSCREEN );
    m_window->background.r = 1;
    m_window->background.g = 1;
    m_window->background.b = 1;
    m_window->background.a = 1;

    S2D_Show( m_window );
}

void BoardGraphics::update()
{
    if( !m_run )
    {
        S2D_Close( m_window );
    }
}

void BoardGraphics::render()
{
    drawBoard( 0, 1, 0 );
    renderPieceStates();
}

void BoardGraphics::updateStatic()
{
    pThis->update();
}

void BoardGraphics::renderStatic()
{
    pThis->render();
}

void BoardGraphics::setPosState( unsigned x, unsigned y, PositionState state )
{
    unsigned offset = x + ( 9 * y );
    m_positionStates.at( offset ) = state;
}

void BoardGraphics::drawSquareAt( unsigned x, unsigned y, GLfloat r, GLfloat g, GLfloat b )
{
    GLfloat x1 = WIDTH_BORDER + ( x * SQUARE_A ) - INDICATOR_A;
    GLfloat x2 = WIDTH_BORDER + ( x * SQUARE_A ) + INDICATOR_A;
    GLfloat x3 = WIDTH_BORDER + ( x * SQUARE_A ) + INDICATOR_A;
    GLfloat x4 = WIDTH_BORDER + ( x * SQUARE_A ) - INDICATOR_A;

    GLfloat y1 = HEIGHT_BORDER + ( y * SQUARE_A ) - INDICATOR_A;
    GLfloat y2 = HEIGHT_BORDER + ( y * SQUARE_A ) - INDICATOR_A;
    GLfloat y3 = HEIGHT_BORDER + ( y * SQUARE_A ) + INDICATOR_A;
    GLfloat y4 = HEIGHT_BORDER + ( y * SQUARE_A ) + INDICATOR_A;

    S2D_DrawQuad(x1, y1, r, g, b, SQUARE_TRANS,
                 x2, y2, r, g, b, SQUARE_TRANS,
                 x3, y3, r, g, b, SQUARE_TRANS,
                 x4, y4, r, g, b, SQUARE_TRANS);
}

void BoardGraphics::renderPieceStates()
{
    auto nowTime = std::chrono::high_resolution_clock::now();
    if( ( nowTime - m_prevTime ) >= FLASH_TIME )
    {
        m_updatePieces = !m_updatePieces;
        m_prevTime = nowTime;
    }

    for( unsigned x = 0; x < 9; ++x )
    {
        for( unsigned y = 0; y < 5; ++y )
        {
            if( m_updatePieces )
            {
                unsigned offset = x + ( 9 * y );

                if( m_positionStates[offset] == PositionState::FlashRed )
                {
                    drawSquareAt( x, y, 1, 0, 0 );
                }
                else if( m_positionStates[offset] == PositionState::FlashGreen )
                {
                    drawSquareAt( x, y, 0, 1, 0 );
                }
            }
        }
    }
}

void BoardGraphics::drawBoard( GLfloat r, GLfloat g, GLfloat b )
{
    // Surrounding border
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER, WIDTH_BORDER, SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, SCREEN_HEIGHT - HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );

    // Horizontal lines
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 1 * SQUARE_A ), SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 1 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 2 * SQUARE_A ), SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 2 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 3 * SQUARE_A ), SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 3 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );

    // Vertical lines
    S2D_DrawLine( WIDTH_BORDER + ( 1 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 1 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 2 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 2 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 3 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 3 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 4 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 4 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 5 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 5 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 6 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 6 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 7 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 7 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );

    // Diagonal lines
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 1 * SQUARE_A ), WIDTH_BORDER + ( 1 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 2 * SQUARE_A ), WIDTH_BORDER + ( 2 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 3 * SQUARE_A ), WIDTH_BORDER + ( 3 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 4 * SQUARE_A ), WIDTH_BORDER + ( 4 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );

    S2D_DrawLine( WIDTH_BORDER + ( 1 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, WIDTH_BORDER + ( 5 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 2 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, WIDTH_BORDER + ( 6 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 3 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, WIDTH_BORDER + ( 7 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 4 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, WIDTH_BORDER + ( 8 * SQUARE_A ), HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );

    S2D_DrawLine( WIDTH_BORDER + ( 5 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 1 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 6 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 2 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 7 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 3 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );


    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 3 * SQUARE_A ), WIDTH_BORDER + ( 1 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 2 * SQUARE_A ), WIDTH_BORDER + ( 2 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 1 * SQUARE_A ), WIDTH_BORDER + ( 3 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER, HEIGHT_BORDER + ( 0 * SQUARE_A ), WIDTH_BORDER + ( 4 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );

    S2D_DrawLine( WIDTH_BORDER + ( 1 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 5 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 2 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 6 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 3 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 7 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 4 * SQUARE_A ), HEIGHT_BORDER, WIDTH_BORDER + ( 8 * SQUARE_A ), SCREEN_HEIGHT - HEIGHT_BORDER, LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );

    S2D_DrawLine( WIDTH_BORDER + ( 5 * SQUARE_A ), HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 3 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 6 * SQUARE_A ), HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 2 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
    S2D_DrawLine( WIDTH_BORDER + ( 7 * SQUARE_A ), HEIGHT_BORDER, SCREEN_WIDTH - WIDTH_BORDER, HEIGHT_BORDER + ( 1 * SQUARE_A ), LINE_WIDTH, r, g, b, 1, r, g, b, 1, r, g, b, 1, r, g, b, 1 );
}

