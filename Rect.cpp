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

// License for fit rect function
/*
  pygame - Python Game Library
  Copyright (C) 2000-2001  Pete Shinners

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

  Pete Shinners
  pete@shinners.org
*/

#include "Rect.h"
using namespace Piegame;

/* ============================= Rect =============================== */

Rect::Rect(Point p, Dimension d) : Rect(p.x, p.y, d.w, d.h){}

Rect::Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h){
    recalculate();
}

void Rect::recalculate(){
    left   = (w>=0)? x : x+w;
    right  = (w>=0)? x+w : x;
    top    = (h>=0)? y : y+h;
    bottom = (h>=0)? y+h : y;
    
    topleft     = {left, top};
    topright    = {right, top};
    bottomleft  = {left, bottom};
    bottomright = {right, bottom};
    
    center = {(left+right)>>1, (top+bottom)>>1};
    midtop = {(left+right)>>1, top};
    midleft = {left, (top+bottom)>>1};
    midbottom = {(left+right)>>1, bottom};
    midright = {right, (top+bottom)>>1};
    
    size = {(right-left), (bottom-top)};
}

Rect Rect::copy(){
    return Rect(x,y,w,h);
}

Rect Rect::move(Point p){ return move(p.x, p.y); }
Rect Rect::move(int x, int y){
    Rect r = copy();
    r.move_ip(x, y);
    return r;
}
void Rect::move_ip(Point p){ move_ip(p.x, p.y); }
void Rect::move_ip(int x, int y){
    this->x += x;
    this->y += y;
    recalculate();
}

Rect Rect::inflate(Dimension d){ return inflate(d.w, d.h); }
Rect Rect::inflate(int w, int h){
    Rect r = copy();
    r.inflate_ip(w, h);
    return r;
}
void Rect::inflate_ip(Dimension d){ inflate_ip(d.w, d.h); }
void Rect::inflate_ip(int w, int h){
    this->w += w;
    this->h += h;
    x -= w>>1;
    y -= h>>1;
    recalculate();
}

Rect Rect::clamp(Rect rt){
    Rect r = copy();
    r.clamp_ip(rt);
    return r;
}
void Rect::clamp_ip(Rect r){
    if (size.w <= r.size.w && size.h <= r.size.h){
        x = (w>=0)? r.left : r.right;
        y = (h>=0)? r.top  : r.bottom;
    }
    else{
        if (w>=0) x = r.left - ((size.w - r.size.w)>>1);
        else x = r.right + ((size.w - r.size.w)>>1);
        if (h>=0) y = r.top - ((size.h - r.size.h)>>1);
        else y = r.bottom + ((size.h - r.size.h)>>1);
    }
    recalculate();
}

Rect Rect::clip(Rect r){
    if (!colliderect(r))
        return Rect(0, 0, 0, 0);
    int x = (left>r.left)? left : r.left;
    int y = (top>r.top)? top : r.top;
    int w = ((right<r.right)? right : r.right) - x;
    int h = ((bottom<r.bottom)? bottom : r.bottom) - y;
    return Rect(x, y, w, h);
}

Rect Rect::unionwith(Rect rt){
    Rect r = copy();
    r.unionwith_ip(rt);
    return r;
}
void Rect::unionwith_ip(Rect r){
    x = (left<r.left)? left : r.left;
    y = (top<r.top)? top : r.top;
    w = ((right>r.right)? right : r.right) - x;
    h = ((bottom>r.bottom)? bottom : r.bottom) - y;
    recalculate();
}

Rect Rect::unionall(Rect vr[], size_t size){
    Rect r = copy();
    unionall_ip(vr, size);
    return r;
}
Rect Rect::unionall(vector<Rect>& vr){
    Rect r = copy();
    unionall_ip(vr);
    return r;
}
Rect Rect::unionall(list<Rect>& lr){
    Rect r = copy();
    unionall_ip(lr);
    return r;
}
void Rect::unionall_ip(Rect vr[], size_t size){
    for(int i=0; i<size; i++)
        unionwith_ip(vr[i]);
}
void Rect::unionall_ip(vector<Rect>& vr){
    for(int i=0; i<vr.size(); i++)
        unionwith_ip(vr[i]);
}
void Rect::unionall_ip(list<Rect>& lr){
    for(Rect r : lr)
        unionwith_ip(r);
}

Rect Rect::fit(Rect r){
    int w, h, x, y;
    float xratio, yratio, maxratio;
    
    xratio = (float) this->w / (float) r.w;
    yratio = (float) this->h / (float) r.h;
    maxratio = (xratio > yratio) ? xratio : yratio;

    w = (int) (this->w / maxratio);
    h = (int) (this->h / maxratio);

    x = r.x + (r.w - w)>>1;
    y = r.y + (r.h - h)>>1;

    return Rect(x, y, w, h);
}

void Rect::normalize(){
    x = left;
    y = top;
    w = size.w;
    h = size.h;
    recalculate();
}

bool Rect::contains(Rect r){
    return left <= r.left && right >= r.right && top <= r.top && bottom >= r.bottom;
}

bool Rect::collidepoint(Point p){ return collidepoint(p.x, p.y); }
bool Rect::collidepoint(int x, int y){
    return left <= x && right >= x && top <= y && bottom >= y;
}

bool Rect::colliderect(Rect r){
    if (collidepoint(r.topleft)) return true;
    if (collidepoint(r.topright)) return true;
    if (collidepoint(r.bottomleft)) return true;
    if (collidepoint(r.bottomright)) return true;
    
    if (r.collidepoint(topleft)) return true;
    if (r.collidepoint(topright)) return true;
    if (r.collidepoint(bottomleft)) return true;
    if (r.collidepoint(bottomright)) return true;
    
    return false;
}

int Rect::collidelist(Rect vr[], size_t size){
    for(int i=0; i<size; i++)
        if(colliderect(vr[i]))
            return i;
    return -1;
}
int Rect::collidelist(vector<Rect>& vr){
    for(int i=0; i<vr.size(); i++)
        if(colliderect(vr[i]))
            return i;
    return -1;
}
list<Rect>::iterator Rect::collidelist(list<Rect>& lr){
    for(list<Rect>::iterator it = lr.begin(); it!=lr.end(); it++)
        if(colliderect(*it))
            return it;
    return lr.end();
}

bool Rect::collidelistall(Rect vr[], size_t size){
    for(int i=0; i<size; i++)
        if(!colliderect(vr[i]))
            return false;
    return true;
}
bool Rect::collidelistall(vector<Rect>& vr){
    for(int i=0; i<vr.size(); i++)
        if(!colliderect(vr[i]))
            return false;
    return true;
}
bool Rect::collidelistall(list<Rect>& vr){
    for(Rect r : vr)
        if(!colliderect(r))
            return false;
    return true;
}