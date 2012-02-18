/**
 * Copyright (c) 2011 Daniel Wiberg
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

#include "slg/Node.hpp"
#include "catch.hpp"

using namespace slg;

TEST_CASE("Allocation", "Test allocation and creation of nodes")
{
  SceneGraph graph(4);
  
  NodeRef n1 = graph.createNode(Node::Root);
  NodeRef n2 = graph.createNode(n1);
  NodeRef n3 = graph.createNode(n2);
  NodeRef n4 = graph.createNode(Node::Root);
  NodeRef nError = graph.createNode(Node::Root);
  
  CHECK(n1 != Node::Error);
  CHECK(n2 != Node::Error);
  CHECK(n3 != Node::Error);
  CHECK(n4 != Node::Error);
  CHECK(nError == Node::Error);
  
  CHECK(graph.parentOf(n1) == Node::Root);
  CHECK(graph.parentOf(n2) == n1);
  CHECK(graph.parentOf(n3) == n2);
  CHECK(graph.parentOf(n4) == Node::Root);
}
