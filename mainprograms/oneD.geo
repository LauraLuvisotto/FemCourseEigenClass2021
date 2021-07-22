// Gmsh project created on Sun Jun 20 19:58:37 2021
//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {8, 0, 0, 1.0};
//+
Line(1) = {1, 2};
//+
//+
Physical Curve("line", 1) = {1};
//+
Physical Point("left", 2) = {1};
//+
Physical Point("right", 3) = {2};
