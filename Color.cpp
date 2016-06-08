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

// License for hsva, hsva, i1i2i3 and correct_gamma  color functions
/*
  pygame - Python Game Library
  Copyright (C) 2008 Marcus von Appen

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

*/

#include "Color.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace Piegame;

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}

Color::Color(int hex){
    r = (hex & 0xFF000000) >> 24;
    g = (hex & 0x00FF0000) >> 16;
    b = (hex & 0x0000FF00) >> 8;
    a = hex & 0x000000FF;
}

double* Color::cmy(){
    double* v = new double[4];
    v[0] = 1 - r/255.0;
    v[1] = 1 - g/255.0;
    v[2] = 1 - b/255.0;
    return v;
}

double* Color::hsva(){
    double* hsv = new double[4];
    hsv[0] = hsv[1] = hsv[2] = hsv[3] = 0;
    double* frgb;
    double minv, maxv, diff;

    /* Normalize */
    frgb = normalize();

    maxv = std::max (std::max (frgb[0], frgb[1]), frgb[2]);
    minv = std::min (std::min (frgb[0], frgb[1]), frgb[2]);
    diff = maxv - minv;

    /* Calculate V */
    hsv[2] = 100. * maxv;

    if (maxv == minv){
        hsv[0] = 0;
        hsv[1] = 0;
        hsv[3] = frgb[3] * 100;
        delete frgb;
        return hsv;
    }
    /* Calculate S */
    hsv[1] = 100. * (maxv - minv) / maxv;

    /* Calculate H */
    if (maxv == frgb[0])
        hsv[0] = fmod ((60 * ((frgb[1] - frgb[2]) / diff)), 360.f);
    else if (maxv == frgb[1])
        hsv[0] = (60 * ((frgb[2] - frgb[0]) / diff)) + 120.f;
    else
        hsv[0] = (60 * ((frgb[0] - frgb[1]) / diff)) + 240.f;

    if (hsv[0] < 0)
        hsv[0] += 360.f;
    
    /* H,S,V,A */
    hsv[3] = frgb[3] * 100;
    delete frgb;
    return hsv;
}

double* Color::hsla(){
    double* hsl = new double[4];
    hsl[0] = hsl[1] = hsl[2] = hsl[3] = 0;
    double* frgb;
    double minv, maxv, diff;
    
    /* Normalize */
    frgb = normalize();

    maxv = std::max (std::max (frgb[0], frgb[1]), frgb[2]);
    minv = std::min (std::min (frgb[0], frgb[1]), frgb[2]);

    diff = maxv - minv;

    /* Calculate L */
    hsl[2] = 50.f * (maxv + minv); /* 1/2 (max + min) */

    if (maxv == minv){
        hsl[1] = 0;
        hsl[0] = 0;
        hsl[3] = frgb[3] * 100;
        delete frgb;
        return hsl;
    }

    /* Calculate S */
    if (hsl[2] <= 50)
        hsl[1] = diff / (maxv + minv);
    else
        hsl[1] = diff / (2 - maxv - minv);
    hsl[1] *= 100.f;

    /* Calculate H */
    if (maxv == frgb[0])
        hsl[0] = fmod ((60 * ((frgb[1] - frgb[2]) / diff)), 360.f);
    else if (maxv == frgb[1])
        hsl[0] = (60 * ((frgb[2] - frgb[0]) / diff)) + 120.f;
    else
        hsl[0] = (60 * ((frgb[0] - frgb[1]) / diff)) + 240.f;
    if (hsl[0] < 0)
        hsl[0] += 360.f;

    /* H,S,L,A */
    hsl[3] = frgb[3] * 100;
    delete frgb;
    return hsl;
}

double* Color::i1i2i3(){
    double* v = new double[3];
    double* frgb;

    /* Normalize */
    frgb = normalize();

    v[0] = (frgb[0] + frgb[1] + frgb[2]) / 3.0f;
    v[1] = (frgb[0] - frgb[2]) / 2.0f;
    v[2] = (2 * frgb[1] - frgb[0] - frgb[2]) / 4.0f;
    
    delete frgb;
    return v;
}

double* Color::normalize(){
    double* rgba = new double[4];
    rgba[0] = r/255.0;
    rgba[1] = g/255.0;
    rgba[2] = b/255.0;
    rgba[3] = a/255.0;
    return rgba;
}

Color Color::correct_gamma(double gamma){
    double frgba[4];
    Uint8 rgba[4];

    frgba[0] = pow (r / 255.0, gamma);
    frgba[1] = pow (g / 255.0, gamma);
    frgba[2] = pow (b / 255.0, gamma);
    frgba[3] = pow (a / 255.0, gamma);

    /* visual studio doesn't have a round func, so doing it with +.5 and
     * truncaction */
    rgba[0] = (frgba[0] > 1.0) ? 255 : ((frgba[0] < 0.0) ? 0 :
        (Uint8) (frgba[0] * 255 + .5));
    rgba[1] = (frgba[1] > 1.0) ? 255 : ((frgba[1] < 0.0) ? 0 :
        (Uint8) (frgba[1] * 255 + .5));
    rgba[2] = (frgba[2] > 1.0) ? 255 : ((frgba[2] < 0.0) ? 0 :
        (Uint8) (frgba[2] * 255 + .5));
    rgba[3] = (frgba[3] > 1.0) ? 255 : ((frgba[3] < 0.0) ? 0 :
        (Uint8) (frgba[3] * 255 + .5));
    
    return Color(rgba[0], rgba[1], rgba[2], rgba[3]);
}