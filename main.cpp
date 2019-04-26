#include <iostream>
#include "PolyVox/Mesh.h"
#include "PolyVox/RawVolume.h"
#include "PolyVox/CubicSurfaceExtractor.h"
#include "PolyVox/MarchingCubesSurfaceExtractor.h"

void createSphereInVolume(PolyVox::RawVolume<uint8_t>& volData, float fRadius)
{
    //This vector hold the position of the center of the volume
    PolyVox::Vector3DFloat v3dVolCenter(volData.getWidth() / 2, volData.getHeight() / 2, volData.getDepth() / 2);

    //This three-level for loop iterates over every voxel in the volume
    for (int z = 0; z < volData.getDepth(); z++)
    {
        for (int y = 0; y < volData.getHeight(); y++)
        {
            for (int x = 0; x < volData.getWidth(); x++)
            {
                //Store our current position as a vector...
                PolyVox::Vector3DFloat v3dCurrentPos(x, y, z);
                //And compute how far the current position is from the center of the volume
                float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

                uint8_t uVoxelValue = 0;

                //If the current voxel is less than 'radius' units from the center then we make it solid.
                if (fDistToCenter <= fRadius)
                {
                    //Our new voxel value
                    uVoxelValue = 255;
                }

                //Wrte the voxel value into the volume
                volData.setVoxel(x, y, z, uVoxelValue);
            }
        }
    }
}

class VoxelMesh {

};

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Create an empty volume and then place a sphere in it
    PolyVox::RawVolume<uint8_t> volData(PolyVox::Region(PolyVox::Vector3DInt32(0, 0, 0), PolyVox::Vector3DInt32(63, 63, 63)));
    createSphereInVolume(volData, 30);

    // Extract the surface for the specified region of the volume. Uncomment the line for the kind of surface extraction you want to see.
//    auto mesh = PolyVox::extractCubicMesh(&volData, volData.getEnclosingRegion());
    auto mesh = PolyVox::extractMarchingCubesMesh(&volData, volData.getEnclosingRegion());

    // The surface extractor outputs the mesh in an efficient compressed format which is not directly suitable for rendering. The easiest approach is to
    // decode this on the CPU as shown below, though more advanced applications can upload the compressed mesh to the GPU and decompress in shader code.
    auto decodedMesh = PolyVox::decodeMesh(mesh);

    for (int i=0; i< decodedMesh.getNoOfIndices(); i++) {
        std::cout << decodedMesh.getIndex(i) << ';';
    }
    std::cout << std::endl;

    for (int i=0; i< decodedMesh.getNoOfVertices(); i++) {
        const auto &vertex = decodedMesh.getVertex(i);
        std::cout << vertex.position << ';';
    }
    std::cout << std::endl;

    for (int i=0; i< decodedMesh.getNoOfVertices(); i++) {
        const auto &vertex = decodedMesh.getVertex(i);
        std::cout << vertex.normal << ';';
    }
    std::cout << std::endl;


    return 0;
}