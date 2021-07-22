//+
SetFactory("OpenCASCADE");

Box(1) = {0, 0, 0, 1, 1, 1};
//+
Physical Volume("volume", 1) = {1};
//+
//+
Physical Surface("plane", 2) = {6, 1, 3, 5, 4, 2};
