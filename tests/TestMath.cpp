/**
 * Copyright (c) 2012 Daniel Wiberg
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#include "slg/Quaternion.hpp"
#include "slg/Matrix4.hpp"
#include "catch.hpp"

using namespace slg;

TEST_CASE("Quaternion construction", "Test quaternion contstructors")
{
  Quaternion n1;
  CHECK(n1.x == 0.0f);
  CHECK(n1.y == 0.0f);
  CHECK(n1.z == 0.0f);
  CHECK(n1.w == 1.0f);
  
  Quaternion n2(1.0f, 2.0f, 3.0f, 4.0f);
  CHECK(n2.x == 1.0f);
  CHECK(n2.y == 2.0f);
  CHECK(n2.z == 3.0f);
  CHECK(n2.w == 4.0f);
  
  Quaternion n3(n2);
  CHECK(n3.x == 1.0f);
  CHECK(n3.y == 2.0f);
  CHECK(n3.z == 3.0f);
  CHECK(n3.w == 4.0f);
}

TEST_CASE("Quaternion conjugate", "Test quaternion conjugate")
{
  Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
  CHECK(q1.x == 1.0f);
  CHECK(q1.y == 2.0f);
  CHECK(q1.z == 3.0f);
  CHECK(q1.w == 4.0f);
  
  Quaternion q2 = q1.conjugate();
  CHECK(q2.x == -1.0f);
  CHECK(q2.y == -2.0f);
  CHECK(q2.z == -3.0f);
  CHECK(q2.w == 4.0f);
}

TEST_CASE("Quaternion angle-axis rotation", "Test quaternion rotations")
{
  Quaternion rot(Vector3(0, 1, 0), degToRad(90.0f));
  Vector3 vec = rot * Vector3(1, 0, 0);
  
  CHECK(vec.x == 0.0f);
  CHECK(vec.y == 0.0f);
  CHECK(equal(vec.z, -1.0f));
  
  Quaternion rot2(Vector3(1, 0, 0), degToRad(90.0f));
  Vector3 vec2 = rot2 * Vector3(0, 1, 0);
  
  CHECK(vec2.x == 0.0f);
  CHECK(vec2.y == 0.0f);
  CHECK(equal(vec2.z, 1.0f));
}

TEST_CASE("Matrix multiplication", "Test matrix 4x4 multiplication")
{
  Matrix4 mat1( 1,  2,  3,  4,
                5,  6,  7,  8,
                8,  9, 10, 11,
               12, 13, 14, 15);
  Matrix4 ident;
  
  Matrix4 result1 = mat1 * mat1;
  
  CHECK(result1[0] == 83.0f);
  CHECK(result1[4] == 93.0f);
}

