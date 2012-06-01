#ifndef SCOTT_CUBEWORLD_CUBE_MESH_BUILDER_H
#define SCOTT_CUBEWORLD_CUBE_MESH_BUILDER_H

#include <stdint.h>
#include <cstddef>
#include <vector>

#include "math/vector.h"
#include "graphics/cubevertex.h"

struct WorldChunkMesh
{
    WorldChunkMesh( unsigned int vbo_id, unsigned int ibo_id, size_t faceCount )
        : vbid( vbo_id ),
          ibid( ibo_id ),
          faceCount( faceCount )
    {
    }

    unsigned int vbid;
    unsigned int ibid;
    size_t faceCount;
};

class WorldChunkBuilder
{
public:
    WorldChunkBuilder();

    void addCube( const Vec3& );

    WorldChunkMesh createMesh() const;

    void addFace( const Vec3& pA, const Vec3& nA,
                  const Vec3& pB, const Vec3& nB,
                  const Vec3& pC, const Vec3& nC,
                  const Vec3& pD, const Vec3& nD );

    size_t numIndices() const;
    size_t numFaces()   const;
    size_t numVerts()   const;

private:
    std::vector<int>        faces;
    std::vector<CubeVertex> vertices;
    int m_offset;
};

#endif
