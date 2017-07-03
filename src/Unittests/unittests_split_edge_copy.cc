
#include <gtest/gtest.h>
#include <Unittests/unittests_common.hh>
#include <iostream>

namespace {

class OpenMeshSplitEdgeCopyTriangleMesh : public OpenMeshBase {

    protected:

        // This function is called before each test is run
        virtual void SetUp() {

            // Do some initial stuff with the member data here...
        }

        // This function is called after all tests are through
        virtual void TearDown() {

            // Do some final stuff with the member data here...
        }

    // Member already defined in OpenMeshBase
    //Mesh mesh_;
};

class OpenMeshSplitEdgeCopyPolyMesh : public OpenMeshBasePoly {

    protected:

        // This function is called before each test is run
        virtual void SetUp() {

            // Do some initial stuff with the member data here...
        }

        // This function is called after all tests are through
        virtual void TearDown() {

            // Do some final stuff with the member data here...
        }

    // Member already defined in OpenMeshBase
    //Mesh mesh_;
};

/*
 * ====================================================================
 * Define tests below
 * ====================================================================
 */

/* splits an edge that has a property in a triangle mesh with split_edge_copy
 * the property should be copied to the new edge
 */
TEST_F(OpenMeshSplitEdgeCopyTriangleMesh, SplitEdgeCopyTriangleMesh) {

  mesh_.clear();
  mesh_.request_edge_status();

  // Add some vertices
  Mesh::VertexHandle vhandle[4];

  vhandle[0] = mesh_.add_vertex(Mesh::Point(0, 0, 0));
  vhandle[1] = mesh_.add_vertex(Mesh::Point(0, 1, 0));
  vhandle[2] = mesh_.add_vertex(Mesh::Point(1, 1, 0));
  vhandle[3] = mesh_.add_vertex(Mesh::Point(0.25, 0.25, 0));

  // Add one face
  std::vector<Mesh::VertexHandle> face_vhandles;

  face_vhandles.push_back(vhandle[2]);
  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[0]);

  Mesh::FaceHandle fh = mesh_.add_face(face_vhandles);
  Mesh::EdgeHandle eh = *mesh_.edges_begin();

  // Test setup:
  //  1 === 2
  //  |   /
  //  |  /
  //  | /
  //  0

  // set property
  OpenMesh::EPropHandleT<int> eprop_int;
  mesh_.add_property(eprop_int);
  mesh_.property(eprop_int, eh) = 999;
  //set internal property
  mesh_.status(eh).set_tagged(true);

  // split face with new vertex
  mesh_.split_edge_copy(eh, vhandle[3]);

  // Check setup
  Mesh::EdgeHandle eh0 = mesh_.edge_handle( mesh_.next_halfedge_handle( mesh_.halfedge_handle(eh, 1) ) );
  EXPECT_EQ(999, mesh_.property(eprop_int, eh0)) << "Different Property value";
  EXPECT_TRUE(mesh_.status(eh0).tagged()) << "Different internal property value";
}

/* splits an edge that has a property in a poly mesh with split_edge_copy
 * the property should be copied to the new faces
 */
TEST_F(OpenMeshSplitEdgeCopyPolyMesh, SplitEdgeCopyPolymesh) {

  mesh_.clear();
  mesh_.request_edge_status();

  // Add some vertices
  Mesh::VertexHandle vhandle[5];

  vhandle[0] = mesh_.add_vertex(PolyMesh::Point(0, 0, 0));
  vhandle[1] = mesh_.add_vertex(PolyMesh::Point(0, 1, 0));
  vhandle[2] = mesh_.add_vertex(PolyMesh::Point(1, 1, 0));
  vhandle[3] = mesh_.add_vertex(PolyMesh::Point(1, 0, 0));
  vhandle[4] = mesh_.add_vertex(PolyMesh::Point(0.5, 0.5, 0));

  // Add face
  std::vector<Mesh::VertexHandle> face_vhandles;

  face_vhandles.push_back(vhandle[0]);
  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[2]);
  face_vhandles.push_back(vhandle[3]);

  PolyMesh::FaceHandle fh = mesh_.add_face(face_vhandles);
  PolyMesh::EdgeHandle eh = *mesh_.edges_begin();

  // Test setup:
  //  1 === 2
  //  |     |
  //  |     |
  //  |     |
  //  0 === 3

  // set property
  OpenMesh::EPropHandleT<int> eprop_int;
  mesh_.add_property(eprop_int);
  mesh_.property(eprop_int, eh) = 999;
  //set internal property
  mesh_.status(eh).set_tagged(true);


  // split face with new vertex
  mesh_.split_edge_copy(eh, vhandle[4]);


  // Check setup  
  Mesh::EdgeHandle eh0 = mesh_.edge_handle( mesh_.next_halfedge_handle( mesh_.halfedge_handle(eh, 1) ) );
  EXPECT_EQ(999, mesh_.property(eprop_int, eh0)) << "Different Property value";
  EXPECT_TRUE(mesh_.status(eh0).tagged()) << "Different internal property value";
}
}
