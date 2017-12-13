#ifndef ENUM_HPP
#define ENUM_HPP

#define OFF_BOARD 100

enum Piece{
	none, 
	p1,
	p2
};

enum Direction{
	no_dir = 0,
	u = 1<<0,
	d = 1<<1,
	l = 1<<2,
	r = 1<<3,
	ul = 1<<4,
	ur = 1<<5,
	dl = 1<<6,
	dr = 1<<7
};

enum ErrorCode{
	success = 1,
    validMove,
    noPiece,
    wrongPiece,
    notSamePiece,
    noMove,
    pieceAdded,
    pieceMissing,
    invalidDirection,
    bothPartial,
    withdrawlPartial,
    approachPartial,
    unknownError,
    invalidMove,
};


#endif

