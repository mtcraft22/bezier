/*
    Copyright (C) 2024 mtcraft22(Marc Tort Pascual) 
    This file is part of Bezier.

    Bezier is free software: 
    you can redistribute it and/or modify it under the terms 
    of the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.
    Bezier is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along with Bezier. If not, see <https://www.gnu.org/licenses/>. 
*/
#pragma once
#include <mtcad/Node.hpp>
#include <mtcad/circle.hpp>
#include <mtcad/curve.hpp>
#include <mtcad/line.hpp>
#include <mtcad/Rectangle.hpp>
#include <mtcad/Shape.hpp>
#include <mtcad/Triangle.hpp>

const std::string mt_cad::Circle::material = "circle";
const int mt_cad::Circle::max_nodes = 2;
const std::string mt_cad::Curve::material = "curve";
const int mt_cad::Curve::max_nodes = 3;
const std::string mt_cad::Line::material = "line";
const int mt_cad::Line::max_nodes = 2;
const std::string mt_cad::Rectangle::material = "rectangle";
const int mt_cad::Rectangle::max_nodes = 2;
const std::string mt_cad::Triangle::material = "triangle";
const int mt_cad::Triangle::max_nodes = 3;