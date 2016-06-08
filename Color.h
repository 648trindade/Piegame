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

#ifndef __COLOR_H__
    #define __COLOR_H__
    
#include "defines.h"

class Piegame::Color{
    public:
        Color(Uint8, Uint8, Uint8, Uint8);
        Color(int);
        
        Uint8 r, g, b, a;
        
        double* cmy();
        double* hsva();
        double* hsla();
        double* i1i2i3();
        double* normalize();
        Color correct_gamma(double);
        // set_length
};

#endif