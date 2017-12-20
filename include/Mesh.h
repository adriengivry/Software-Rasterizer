#pragma once
#include "Vec3.h"
#include <vector>
#include "Vertex.h"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    Mesh();
    ~Mesh();
    static Mesh* CreateCube();
    static Mesh* CreateSphere(int latitudeCount, int longitudeCount)
};

