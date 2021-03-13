#ifndef USD_UTILITY_H
#define USD_UTILITY_H

#include <string>

// #include <pxr/usd/usd/attribute.h>
// #include <pxr/usd/usd/common.h>
#include <pxr/usd/sdf/path.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/stage.h>

// #include <pxr/usd/usdGeom/camera.h>
// #include <pxr/usd/usdGeom/mesh.h>
// #include <pxr/usd/usdGeom/xformCache.h>

// #include <pxr/base/vt/array.h>

// #include <pxr/base/gf/matrix3f.h>
// #include <pxr/base/gf/matrix3d.h>
// #include <pxr/base/gf/matrix4f.h>
// #include <pxr/base/gf/matrix4d.h>

// #include <pxr/usdImaging/usdImagingGL/engine.h>
// #include <pxr/usdImaging/usdImagingGL/renderParams.h>

// #include <pxr/imaging/glf/simpleLight.h>


inline void GetPrimsFromType(const std::string &prim_type,
    const pxr::UsdStageRefPtr &stage,
    const pxr::SdfPath &prim_path,
    std::vector<pxr::UsdPrim> &prim_vector)
{
    pxr::UsdPrim base_prim;
    base_prim = stage->GetPrimAtPath(prim_path);

    for(const pxr::UsdPrim &prim: base_prim.GetChildren())
    {
        if (prim.GetTypeName() == prim_type)
        {
            prim_vector.push_back(prim);
        }

        if (prim.GetChildren())
        {
            GetPrimsFromType(prim_type, stage, prim.GetPath(), prim_vector);
        }
    }
}

// /* Reimplementation of some USD's Hd API functions to triangulate/quadriangulate meshes,
//     so they can be used outside of the Hd API. */
// inline bool DoFanTriangulation(
//     pxr::GfVec3i &triangulated_indices,
//     const pxr::VtArray<int> &mesh_vertex_indices,
//     int mesh_vertex_indices_offset,
//     int mesh_vertex_indices_idx,
//     int mesh_indices_count,
//     bool flip_winding_order)
// {
//     // We check the topology.
//     if (mesh_vertex_indices_offset + mesh_vertex_indices_idx + 2 >= mesh_indices_count)
//     {
//         triangulated_indices = pxr::GfVec3i(0, 0, 0);

//         return false;
//     }

//     if (flip_winding_order)
//     {
//         triangulated_indices = pxr::GfVec3i(mesh_vertex_indices[mesh_vertex_indices_offset],
//         mesh_vertex_indices[mesh_vertex_indices_offset + mesh_vertex_indices_idx + 2],
//         mesh_vertex_indices[mesh_vertex_indices_offset + mesh_vertex_indices_idx + 1]);
//     }
//     else
//     {
//         triangulated_indices = pxr::GfVec3i(mesh_vertex_indices[mesh_vertex_indices_offset],
//         mesh_vertex_indices[mesh_vertex_indices_offset + mesh_vertex_indices_idx + 1],
//         mesh_vertex_indices[mesh_vertex_indices_offset + mesh_vertex_indices_idx + 2]);
//     }

//     return true;
// }

// inline pxr::VtVec3iArray TriangulateMeshIndices(
//     pxr::VtArray<int> &mesh_vertex_counts,
//     const pxr::VtArray<int> &mesh_vertex_indices,
//     const pxr::VtArray<int> &mesh_hole_indices,
//     const pxr::TfToken &mesh_orientation)
// {
//     pxr::VtVec3iArray mesh_triangulated_indices;

//     int mesh_faces_count = mesh_vertex_counts.size();
//     int mesh_indices_count = mesh_vertex_indices.size();
//     int mesh_hole_indices_count = mesh_hole_indices.size();
//     int mesh_triangles_count = 0;
//     int mesh_hole_idx = 0;
//     bool flip_winding_order = (mesh_orientation != pxr::TfToken("rightHanded"));
//     bool invalid_topology = false;

//     for (int face_idx = 0; face_idx < mesh_faces_count; ++face_idx)
//     {
//         int triangles_per_face = mesh_vertex_counts[face_idx] - 2;

//         // We skip the broken faces
//         if (triangles_per_face < 1)
//         {
//             invalid_topology = true;
//         }
//         // We skip the hole faces
//         else if (mesh_hole_idx < mesh_hole_indices_count & &mesh_hole_indices[mesh_hole_idx] == face_idx)
//         {
//             ++mesh_hole_idx;
//         }
//         else
//         {
//             mesh_triangles_count += triangles_per_face;
//         }
//     }

//     if (invalid_topology)
//     {
//         std::cout << std::string("WARNING - Broken faces have been found.") << std::endl;
//         invalid_topology = false;
//     }

//     mesh_triangulated_indices.resize(mesh_triangles_count);
//     mesh_hole_idx = 0;

//     for (int face_idx = 0, triangle_face_idx = 0, face_vertex_idx = 0; face_idx < mesh_faces_count; ++face_idx)
//     {
//         int face_vertex_count = mesh_vertex_counts[face_idx];

//         if (face_vertex_count < 3)
//         {
//             // We skip the invalid triangle faces.
//         }
//         else if (mesh_hole_idx < mesh_hole_indices_count & &mesh_hole_indices[mesh_hole_idx] == face_idx)
//         {
//             // We skip the hole faces.
//             ++mesh_hole_idx;
//         }
//         else
//         {
//             for (int face_vertex_count_idx = 0; face_vertex_count_idx < face_vertex_count - 2; ++face_vertex_count_idx)
//             {
//                 mesh_triangulated_indices[triangle_face_idx] = pxr::GfVec3i(0, 0, 0);

//                 if (!DoFanTriangulation(
//                     mesh_triangulated_indices[triangle_face_idx],
//                     mesh_vertex_indices,
//                     face_vertex_idx,
//                     face_vertex_count_idx,
//                     mesh_indices_count,
//                     flip_winding_order))
//                 {
//                     invalid_topology = true;
//                 }

//                 if (face_vertex_count > 3)
//                 {
//                     if (face_vertex_count_idx == 0)
//                     {
//                         if (flip_winding_order)
//                         {
//                             pxr::GfVec3i &triangulated_indices = mesh_triangulated_indices[triangle_face_idx];

//                             triangulated_indices.Set(
//                                 triangulated_indices[1],
//                                 triangulated_indices[2],
//                                 triangulated_indices[0]);
//                         }
//                     }
//                     else if (face_vertex_count_idx == face_vertex_count - 3)
//                     {
//                         if (flip_winding_order)
//                         {
//                             pxr::GfVec3i &triangulated_indices = mesh_triangulated_indices[triangle_face_idx];

//                             triangulated_indices.Set(
//                                 triangulated_indices[2],
//                                 triangulated_indices[0],
//                                 triangulated_indices[1]);
//                         }
//                     }
//                 }

//                 ++triangle_face_idx;
//             }
//         }

//         face_vertex_idx += face_vertex_count;
//     }

//     if (invalid_topology)
//     {
//         std::cout << std::string("WARNING - An inconsistency between the mesh faceVertexCounts and faceVertexIndices "
//             "has been found.") << std::endl;
//     }

//     return mesh_triangulated_indices;
// }

#endif // USD_UTILITY_H
