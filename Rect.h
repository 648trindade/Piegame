/*
  Piegame - C++ Game Library - A SDL wrapper based on Pygame
  Copyright (C) 2016  Rafael Gauna Trindade

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public
  License along with this library; if not, write to the Free
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Rafael Gauna Trindade
  rtrindade@inf.ufsm.br
*/
#ifndef __RECT_H__
    #define __RECT_H__
    
#include "defines.h"
#include <vector>
#include <list>

using namespace std;

class Piegame::Rect{
    protected:
        void recalculate();
    public:
        Rect(Point, Dimension);
        Rect(int, int, int, int);
        
        int x, y, w, h;
        int top, left, bottom, right;
        Point topleft, topright, bottomleft, bottomright;
        Point center, midtop, midleft, midbottom, midright;
        Dimension size;
        
        Rect copy();
        
        Rect move(Point);
        Rect move(int, int);
        void move_ip(Point);
        void move_ip(int, int);
        
        Rect inflate(Dimension);
        Rect inflate(int, int);
        void inflate_ip(Dimension);
        void inflate_ip(int, int);
        
        Rect clamp(Rect);
        void clamp_ip(Rect);
        
        Rect clip(Rect);
        
        Rect unionwith(Rect); //Renomeado por causa das unions
        void unionwith_ip(Rect);
        
        Rect unionall(Rect[], size_t);
        Rect unionall(vector<Rect>&);
        Rect unionall(list<Rect>&);
        void unionall_ip(Rect[], size_t);
        void unionall_ip(vector<Rect>&);
        void unionall_ip(list<Rect>&);
        
        Rect fit(Rect);
        
        void normalize();
        
        bool contains(Rect);
        
        bool collidepoint(Point);
        bool collidepoint(int, int);
        
        bool colliderect(Rect);
        
        int collidelist(Rect[], size_t);
        int collidelist(vector<Rect>&);
        list<Rect>::iterator collidelist(list<Rect>&);
        
        bool collidelistall(Rect[], size_t);
        bool collidelistall(vector<Rect>&);
        bool collidelistall(list<Rect>&);
        
        // collidedict
        // collidedictall
};

#endif