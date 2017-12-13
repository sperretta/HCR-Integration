#ifndef BOARDGRAPHICS_HPP
#define BOARDGRAPHICS_HPP

#include <simple2d.h>

#include <atomic>
#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>

using namespace std::literals::chrono_literals;
using namespace std::placeholders;

#define SCREEN_WIDTH  1680
#define SCREEN_HEIGHT 1050
#define LINE_WIDTH    5
#define WIDTH_BORDER  80
#define HEIGHT_BORDER 145
#define SQUARE_A      190
#define SQUARE_TRANS  0.8
#define INDICATOR_A   50
#define FLASH_TIME    900ms

enum class PositionState
{
    None,
    FlashRed,
    FlashGreen,
};

enum class Arrow
{
    None,
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight,
};

class BoardGraphics
{
    public:
        BoardGraphics();
        ~BoardGraphics();

        void start();
        void updateState();
        void end();

        void setActive( bool active );
        void setPosState( unsigned x, unsigned y, PositionState state, Arrow direction );
        void clearStates();

    private:
        void graphicsThread();
        void update();
        void render();

        void drawSquareAt( unsigned x, unsigned y, GLfloat r, GLfloat g, GLfloat b );
        void drawArrowAt( unsigned x, unsigned y, Arrow direction );
        void renderPieceStates();
        void drawBoard( GLfloat r, GLfloat g, GLfloat b );

        //std::vector<PositionState> m_positionStates;
        std::vector<std::pair<PositionState, Arrow>> m_positionStates;
        bool m_updatePieces;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_prevTime;
        bool m_active;

        static void updateStatic();
        static void renderStatic();

        S2D_Window *m_window;

        std::thread m_thread;
        std::atomic<bool> m_run;
};

#endif // BOARDGRAPHICS_HPP

