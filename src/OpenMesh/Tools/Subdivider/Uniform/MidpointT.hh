#pragma once

#include <OpenMesh/Core/Mesh/BaseKernel.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/SubdividerT.hh>
#include <OpenMesh/Core/Utils/PropertyManager.hh>

#include <algorithm>

namespace OpenMesh {
namespace Subdivider {
namespace Uniform {

template<typename MeshType, typename RealType = double>
class MidpointT : public SubdividerT<MeshType, RealType>
{
public:
    using real_t = RealType;
    using mesh_t = MeshType;
    using parent_t = SubdividerT<MeshType, RealType>;

    using parent_t::parent_t;

    const char* name() const { return "midpoint"; }

protected: // SubdividerT interface
    bool prepare(mesh_t& _m) override
    {
        return true;
    }

    bool subdivide(mesh_t& _m, size_t _n, const bool _update_points = true) override
    {
        auto edge_midpoint = makePropertyManagerFromNew<EPropHandleT<typename mesh_t::VertexHandle>>(_m, "edge_midpoint");
        auto is_original_vertex = makePropertyManagerFromNew<VPropHandleT<bool>>(_m, "is_original_vertex");

        for (size_t iteration = 0; iteration < _n; ++iteration) {
            is_original_vertex.set_range(_m.vertices_begin(), _m.vertices_end(), true);
            // Create vertices on edge midpoints
            for (const auto& eh : _m.edges()) {
                auto new_vh = _m.new_vertex(_m.calc_edge_midpoint(eh));
                edge_midpoint[eh] = new_vh;
                is_original_vertex[new_vh] = false;
            }
            // Create new faces from original faces
            for (const auto& fh : _m.faces()) {
                std::vector<typename mesh_t::VertexHandle> new_corners;
                for (const auto& eh : _m.fe_range(fh)) {
                    new_corners.push_back(edge_midpoint[eh]);
                }
                _m.add_face(new_corners);
            }
            // Create new faces from original vertices
            for (const auto& vh : _m.vertices()) {
                if (is_original_vertex[vh]) {
                    if (!_m.is_boundary(vh)) {
                        std::vector<typename mesh_t::VertexHandle> new_corners;
                        for (const auto& eh : _m.ve_range(vh)) {
                            new_corners.push_back(edge_midpoint[eh]);
                        }
                        std::reverse(begin(new_corners), end(new_corners));
                        _m.add_face(new_corners);
                    }
                }
            }
            for (const auto& vh : _m.vertices()) {
                if (is_original_vertex[vh]) {
                    _m.delete_vertex(vh);
                }
            }
        }
        return true;
    }

    bool cleanup(mesh_t& _m) override
    {
        return true;
    }
};

} // namespace Uniform
} // namespace Subdivider
} // namespace OpenMesh
