#ifndef USD_HELPER_H
#define USD_HELPER_H

#include <string>

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xformCache.h>
#include <pxr/usd/usd/attribute.h>
#include <pxr/base/vt/array.h>
#include <pxr/base/gf/matrix3f.h>
#include <pxr/base/gf/matrix3d.h>
#include <pxr/base/gf/matrix4f.h>
#include <pxr/base/gf/matrix4d.h>


inline void GetPrimFromType(const std::string& primType,
    const pxr::UsdStageRefPtr& stage,
    const pxr::SdfPath& primPath,
    std::vector<pxr::UsdPrim>& primVector)
{
    pxr::UsdPrim basePrim;
    basePrim = stage->GetPrimAtPath(primPath);

    for(const pxr::UsdPrim& prim: basePrim.GetChildren())
    {
        if (prim.GetTypeName() == primType)
        {
            primVector.push_back(prim);
        }

        if (prim.GetChildren())
        {
            GetPrimFromType(primType, stage, prim.GetPath(), primVector);
        }
    }
}

/* Reimplementation of some USD's Hd API functions to triangulate/quadriangulate meshes,
    so they can be used outside of the Hd API. */
inline bool DoFanTriangulation(pxr::GfVec3i& triangulatedIndices,
    const pxr::VtArray<int>& meshVertexIndices,
    int meshVertexIndicesOffset,
    int meshVertexIndicesIdx,
    int meshIndicesCount,
    bool flipWindingOrder)
{
    // We check the topology.
    if (meshVertexIndicesOffset + meshVertexIndicesIdx + 2 >= meshIndicesCount)
    {
        triangulatedIndices = pxr::GfVec3i(0, 0, 0);

        return false;
    }

    if (flipWindingOrder)
    {
        triangulatedIndices = pxr::GfVec3i(meshVertexIndices[meshVertexIndicesOffset],
        meshVertexIndices[meshVertexIndicesOffset + meshVertexIndicesIdx + 2],
        meshVertexIndices[meshVertexIndicesOffset + meshVertexIndicesIdx + 1]);
    }
    else
    {
        triangulatedIndices = pxr::GfVec3i(meshVertexIndices[meshVertexIndicesOffset],
        meshVertexIndices[meshVertexIndicesOffset + meshVertexIndicesIdx + 1],
        meshVertexIndices[meshVertexIndicesOffset + meshVertexIndicesIdx + 2]);
    }

    return true;
}

inline pxr::VtVec3iArray TriangulateMeshIndices(pxr::VtArray<int>& meshVertexCounts,
    const pxr::VtArray<int>& meshVertexIndices,
    const pxr::VtArray<int>& meshHoleIndices,
    const pxr::TfToken& meshOrientation)
{
    pxr::VtVec3iArray meshTriangulatedIndices;

    int meshFacesCount = meshVertexCounts.size();
    int meshIndicesCount = meshVertexIndices.size();
    int meshHoleIndicesCount = meshHoleIndices.size();
    int meshTrianglesCount = 0;
    int meshHoleIdx = 0;
    bool flipWindingOrder = (meshOrientation != pxr::TfToken("rightHanded"));
    bool invalidTopology = false;

    for (int faceIdx = 0; faceIdx < meshFacesCount; ++faceIdx)
    {
        int trianglesPerFace = meshVertexCounts[faceIdx] - 2;

        // We skip the broken faces
        if (trianglesPerFace < 1)
        {
            invalidTopology = true;
        }
        // We skip the hole faces
        else if (meshHoleIdx < meshHoleIndicesCount && meshHoleIndices[meshHoleIdx] == faceIdx)
        {
            ++meshHoleIdx;
        }
        else
        {
            meshTrianglesCount += trianglesPerFace;
        }
    }

    if (invalidTopology)
    {
        std::cout << std::string("WARNING - Broken faces have been found.") << std::endl;
        invalidTopology = false;
    }

    meshTriangulatedIndices.resize(meshTrianglesCount);
    meshHoleIdx = 0;

    for (int faceIdx = 0, triangleFaceIdx = 0, faceVertexIdx = 0; faceIdx < meshFacesCount; ++faceIdx)
    {
        int faceVertexCount = meshVertexCounts[faceIdx];
        
        if (faceVertexCount < 3)
        {
            // We skip the invalid triangle faces.
        }
        else if (meshHoleIdx < meshHoleIndicesCount && meshHoleIndices[meshHoleIdx] == faceIdx)
        {
            // We skip the hole faces.
            ++meshHoleIdx;
        }
        else
        {
            for (int faceVertexCountIdx = 0; faceVertexCountIdx < faceVertexCount - 2; ++faceVertexCountIdx)
            {
                meshTriangulatedIndices[triangleFaceIdx] = pxr::GfVec3i(0, 0, 0);

                if (!DoFanTriangulation(meshTriangulatedIndices[triangleFaceIdx],
                    meshVertexIndices,
                    faceVertexIdx,
                    faceVertexCountIdx,
                    meshIndicesCount,
                    flipWindingOrder))
                {
                    invalidTopology = true;
                }

                if (faceVertexCount > 3)
                {
                    if (faceVertexCountIdx == 0)
                    {
                        if (flipWindingOrder)
                        {
                            pxr::GfVec3i &triangulatedIndices = meshTriangulatedIndices[triangleFaceIdx];

                            triangulatedIndices.Set(triangulatedIndices[1],
                                triangulatedIndices[2],
                                triangulatedIndices[0]);
                        }
                    }
                    else if (faceVertexCountIdx == faceVertexCount - 3)
                    {
                        if (flipWindingOrder)
                        {
                            pxr::GfVec3i &triangulatedIndices = meshTriangulatedIndices[triangleFaceIdx];
                            
                            triangulatedIndices.Set(triangulatedIndices[2],
                                triangulatedIndices[0],
                                triangulatedIndices[1]);
                        }
                    }
                }

                ++triangleFaceIdx;
            }
        }

        faceVertexIdx += faceVertexCount;
    }

    if (invalidTopology)
    {
        std::cout << std::string("WARNING - An inconsistency between the mesh faceVertexCounts and faceVertexIndices "
            "has been found.") << std::endl;
    }

    return meshTriangulatedIndices;
}

#endif // USD_HELPER_H
