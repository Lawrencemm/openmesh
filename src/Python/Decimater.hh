#ifndef OPENMESH_PYTHON_DECIMATER_HH
#define OPENMESH_PYTHON_DECIMATER_HH

#include "Python/Bindings.hh"
#include "OpenMesh/Tools/Decimater/ModBaseT.hh"
#include "OpenMesh/Tools/Decimater/ModAspectRatioT.hh"
#include "OpenMesh/Tools/Decimater/ModEdgeLengthT.hh"
#include "OpenMesh/Tools/Decimater/ModHausdorffT.hh"
#include "OpenMesh/Tools/Decimater/ModIndependentSetsT.hh"
#include "OpenMesh/Tools/Decimater/ModNormalDeviationT.hh"
#include "OpenMesh/Tools/Decimater/ModNormalFlippingT.hh"
#include "OpenMesh/Tools/Decimater/ModProgMeshT.hh"
#include "OpenMesh/Tools/Decimater/ModQuadricT.hh"
#include "OpenMesh/Tools/Decimater/ModRoundnessT.hh"
#include "OpenMesh/Tools/Decimater/DecimaterT.hh"

#include <cstdio>

namespace OpenMesh {
namespace Python {

#define INIT_MESH_REF init<Mesh&>()[with_custodian_and_ward<1,2>()]

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(decimate_overloads, decimate, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(decimate_to_faces_overloads, decimate_to_faces, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_max_err_overloads, set_max_err, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_min_roundness_overloads, set_min_roundness, 1, 2)


template <class Handle>
void expose_module_handle(const char *_name) {
	class_<Handle, boost::noncopyable>(_name)
		.def("is_valid", &Handle::is_valid)
		;
}

template <class Module>
list infolist(Module& _self) {
	const typename Module::InfoList& infos = _self.infolist();
	list res;
	for (size_t i = 0; i < infos.size(); ++i) {
		res.append(infos[i]);
	}
	return res;
}

template <class Mesh>
void expose_decimater(const char *_name) {

	typedef Decimater::ModBaseT<Mesh> ModBase;
	typedef Decimater::ModAspectRatioT<Mesh> ModAspectRatio;
	typedef Decimater::ModEdgeLengthT<Mesh> ModEdgeLength;
	typedef Decimater::ModHausdorffT<Mesh> ModHausdorff;
	typedef Decimater::ModIndependentSetsT<Mesh> ModIndependentSets;
	typedef Decimater::ModNormalDeviationT<Mesh> ModNormalDeviation;
	typedef Decimater::ModNormalFlippingT<Mesh> ModNormalFlipping;
	typedef Decimater::ModProgMeshT<Mesh> ModProgMesh;
	typedef Decimater::ModQuadricT<Mesh> ModQuadric;
	typedef Decimater::ModRoundnessT<Mesh> ModRoundness;

	typedef Decimater::ModHandleT<ModAspectRatio> ModAspectRatioHandle;
	typedef Decimater::ModHandleT<ModEdgeLength> ModEdgeLengthHandle;
	typedef Decimater::ModHandleT<ModHausdorff> ModHausdorffHandle;
	typedef Decimater::ModHandleT<ModIndependentSets> ModIndependentSetsHandle;
	typedef Decimater::ModHandleT<ModNormalDeviation> ModNormalDeviationHandle;
	typedef Decimater::ModHandleT<ModNormalFlipping> ModNormalFlippingHandle;
	typedef Decimater::ModHandleT<ModProgMesh> ModProgMeshHandle;
	typedef Decimater::ModHandleT<ModQuadric> ModQuadricHandle;
	typedef Decimater::ModHandleT<ModRoundness> ModRoundnessHandle;

	typedef Decimater::BaseDecimaterT<Mesh> BaseDecimater;
	typedef Decimater::DecimaterT<Mesh> Decimater;

	typedef typename ModProgMesh::Info Info;
	typedef std::vector<Info> InfoList;

	bool (BaseDecimater::*add1)(ModAspectRatioHandle&) = &Decimater::add;
	bool (BaseDecimater::*add2)(ModEdgeLengthHandle&) = &Decimater::add;
	bool (BaseDecimater::*add3)(ModHausdorffHandle&) = &Decimater::add;
	bool (BaseDecimater::*add4)(ModIndependentSetsHandle&) = &Decimater::add;
	bool (BaseDecimater::*add5)(ModNormalDeviationHandle&) = &Decimater::add;
	bool (BaseDecimater::*add6)(ModNormalFlippingHandle&) = &Decimater::add;
	bool (BaseDecimater::*add7)(ModProgMeshHandle&) = &Decimater::add;
	bool (BaseDecimater::*add8)(ModQuadricHandle&) = &Decimater::add;
	bool (BaseDecimater::*add9)(ModRoundnessHandle&) = &Decimater::add;

	bool (BaseDecimater::*remove1)(ModAspectRatioHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove2)(ModEdgeLengthHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove3)(ModHausdorffHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove4)(ModIndependentSetsHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove5)(ModNormalDeviationHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove6)(ModNormalFlippingHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove7)(ModProgMeshHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove8)(ModQuadricHandle&) = &Decimater::remove;
	bool (BaseDecimater::*remove9)(ModRoundnessHandle&) = &Decimater::remove;

	ModAspectRatio& (BaseDecimater::*module1)(ModAspectRatioHandle&) = &Decimater::module;
	ModEdgeLength& (BaseDecimater::*module2)(ModEdgeLengthHandle&) = &Decimater::module;
	ModHausdorff& (BaseDecimater::*module3)(ModHausdorffHandle&) = &Decimater::module;
	ModIndependentSets& (BaseDecimater::*module4)(ModIndependentSetsHandle&) = &Decimater::module;
	ModNormalDeviation& (BaseDecimater::*module5)(ModNormalDeviationHandle&) = &Decimater::module;
	ModNormalFlipping& (BaseDecimater::*module6)(ModNormalFlippingHandle&) = &Decimater::module;
	ModProgMesh& (BaseDecimater::*module7)(ModProgMeshHandle&) = &Decimater::module;
	ModQuadric& (BaseDecimater::*module8)(ModQuadricHandle&) = &Decimater::module;
	ModRoundness& (BaseDecimater::*module9)(ModRoundnessHandle&) = &Decimater::module;

	// Decimater
	// ----------------------------------------

	char buffer[64];
	snprintf(buffer, sizeof buffer, "%s%s", _name, "Decimater");

	class_<Decimater, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("decimate", &Decimater::decimate, decimate_overloads())
		.def("decimate_to", &Decimater::decimate_to)
		.def("decimate_to_faces", &Decimater::decimate_to_faces, decimate_to_faces_overloads())

		.def("initialize", &Decimater::initialize)
		.def("is_initialized", &Decimater::is_initialized)

		.def("add", add1)
		.def("add", add2)
		.def("add", add3)
		.def("add", add4)
		.def("add", add5)
		.def("add", add6)
		.def("add", add7)
		.def("add", add8)
		.def("add", add9)

		.def("remove", remove1)
		.def("remove", remove2)
		.def("remove", remove3)
		.def("remove", remove4)
		.def("remove", remove5)
		.def("remove", remove6)
		.def("remove", remove7)
		.def("remove", remove8)
		.def("remove", remove9)

		.def("module", module1, return_value_policy<reference_existing_object>())
		.def("module", module2, return_value_policy<reference_existing_object>())
		.def("module", module3, return_value_policy<reference_existing_object>())
		.def("module", module4, return_value_policy<reference_existing_object>())
		.def("module", module5, return_value_policy<reference_existing_object>())
		.def("module", module6, return_value_policy<reference_existing_object>())
		.def("module", module7, return_value_policy<reference_existing_object>())
		.def("module", module8, return_value_policy<reference_existing_object>())
		.def("module", module9, return_value_policy<reference_existing_object>())
		;

	// ModBase
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModBase");

	class_<ModBase, boost::noncopyable>(buffer, no_init)
		.def("name", &ModBase::name, OPENMESH_PYTHON_DEFAULT_POLICY)
		.def("is_binary", &ModBase::is_binary)
		.def("set_binary", &ModBase::set_binary)
		.def("initialize", &ModBase::initialize) // TODO VIRTUAL
		.def("collapse_priority", &ModBase::collapse_priority) // TODO VIRTUAL
		.def("preprocess_collapse", &ModBase::preprocess_collapse) // TODO VIRTUAL
		.def("postprocess_collapse", &ModBase::postprocess_collapse) // TODO VIRTUAL
		.def("set_error_tolerance_factor", &ModBase::set_error_tolerance_factor) // TODO VIRTUAL
		;

	// ModAspectRatio
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModAspectRatio");

	class_<ModAspectRatio, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("aspect_ratio", &ModAspectRatio::aspect_ratio)
		.def("set_aspect_ratio", &ModAspectRatio::set_aspect_ratio)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModAspectRatioHandle");
	expose_module_handle<ModAspectRatioHandle>(buffer);

	// ModEdgeLength
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModEdgeLength");

	class_<ModEdgeLength, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("edge_length", &ModEdgeLength::edge_length)
		.def("set_edge_length", &ModEdgeLength::set_edge_length)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModEdgeLengthHandle");
	expose_module_handle<ModEdgeLengthHandle>(buffer);

	// ModHausdorff
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModHausdorff");

	class_<ModHausdorff, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("tolerance", &ModHausdorff::tolerance)
		.def("set_tolerance", &ModHausdorff::set_tolerance)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModHausdorffHandle");
	expose_module_handle<ModHausdorffHandle>(buffer);

	// ModIndependentSets
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModIndependentSets");

	class_<ModIndependentSets, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF);

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModIndependentSetsHandle");
	expose_module_handle<ModIndependentSetsHandle>(buffer);

	// ModNormalDeviation
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModNormalDeviation");

	class_<ModNormalDeviation, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("normal_deviation", &ModNormalDeviation::normal_deviation)
		.def("set_normal_deviation", &ModNormalDeviation::set_normal_deviation)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModNormalDeviationHandle");
	expose_module_handle<ModNormalDeviationHandle>(buffer);

	// ModNormalFlipping
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModNormalFlipping");

	class_<ModNormalFlipping, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("max_normal_deviation", &ModNormalFlipping::max_normal_deviation)
		.def("set_max_normal_deviation", &ModNormalFlipping::set_max_normal_deviation)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModNormalFlippingHandle");
	expose_module_handle<ModNormalFlippingHandle>(buffer);

	// ModProgMesh
	// ----------------------------------------

	class_<Info>("Info", no_init)
		.def_readwrite("v0", &Info::v0)
		.def_readwrite("v1", &Info::v1)
		.def_readwrite("vl", &Info::vl)
		.def_readwrite("vr", &Info::vr)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModProgMesh");

	class_<ModProgMesh, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("pmi", &infolist<ModProgMesh>)
		.def("infolist", &infolist<ModProgMesh>)
		.def("write", &ModProgMesh::write)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModProgMeshHandle");
	expose_module_handle<ModProgMeshHandle>(buffer);

	// ModQuadric
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModQuadric");

	class_<ModQuadric, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("set_max_err", &ModQuadric::set_max_err, set_max_err_overloads())
		.def("unset_max_err", &ModQuadric::unset_max_err)
		.def("max_err", &ModQuadric::max_err)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModQuadricHandle");
	expose_module_handle<ModQuadricHandle>(buffer);

	// ModRoundness
	// ----------------------------------------

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModRoundness");

	class_<ModRoundness, bases<ModBase>, boost::noncopyable>(buffer, INIT_MESH_REF)
		.def("set_min_angle", &ModRoundness::set_min_angle)
		.def("set_min_roundness", &ModRoundness::set_min_roundness, set_min_roundness_overloads())
		.def("unset_min_roundness", &ModRoundness::unset_min_roundness)
		.def("roundness", &ModRoundness::roundness)
		;

	snprintf(buffer, sizeof buffer, "%s%s", _name, "ModRoundnessHandle");
	expose_module_handle<ModRoundnessHandle>(buffer);
}

} // namespace OpenMesh
} // namespace Python

#endif
