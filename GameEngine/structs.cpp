#include "structs.hpp"

Move::Move(unsigned _x, unsigned _y, Direction _mov_dir, Direction _cap_dir){
		x = _x;
		y = _y;
		mov_dir = _mov_dir;
		cap_dir = _cap_dir;	
}

Move::Move(){
    x = OFF_BOARD;
    y = OFF_BOARD;
    mov_dir = no_dir;
    cap_dir = no_dir;
};

bool Move::equals(Move m2){
    return (x == m2.x && y == m2.y && mov_dir == m2.mov_dir && cap_dir == m2.cap_dir);
} 

bool Move::was_pass(){
    if(mov_dir == no_dir) return true;
    else return false;

}

