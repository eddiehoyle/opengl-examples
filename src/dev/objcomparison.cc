////
//// Created by Eddie Hoyle on 3/11/17.
////
//
//#include <iostream>
//#include <cassert>
//#include "../common/obj/tiny_obj_loader.hh"
//#include "../common/obj/parser.hh"
//#include "../common/resources.hh"
//
//void external( const std::string& path, tinyobj::shape_t& shape ) {
//
//    std::vector< tinyobj::shape_t > shapes;
//    tinyobj::LoadObj( shapes, path.c_str() );
//
//    if ( !shapes.empty() ) {
//        shape = shapes.back();
//
//        std::cerr << __func__ << " :"
//                  << " shapes=" << shapes.size()
//                  << ", positions=" << shape.mesh.vertices.size()
//                  << ", normals=" << shape.mesh.normals.size()
//                  << ", texcoords=" << shape.mesh.texcoords.size()
//                  << ", indices=" << shape.mesh.indices.size()
//                  << std::endl;
//
//    }
//}
//
//void internal( const std::string& resource, common::Shape& shape ) {
//
//    common::load_obj( resource, shape );
//    std::cerr << __func__ << " :"
//              << " shapes=" << "NA"
//              << ", positions=" << shape.mesh.vertices.size()
//              << ", normals=" << shape.mesh.normals.size()
//              << ", texcoords=" << shape.mesh.texcoords.size()
//              << ", indices=" << shape.mesh.indices.size()
//              << std::endl;
//}
//
//int main( void ) {
//
//    bool result;
//    const std::string path = common::getResource( "dragon.obj", result );
//
//
//    tinyobj::shape_t external_shape;
//    external( path, external_shape );
//
//    common::Shape internal_shape;
//    internal( path, internal_shape );
//
//    assert( internal_shape.mesh.vertices.size() == external_shape.mesh.vertices.size() );
//    assert( internal_shape.mesh.texcoords.size() == external_shape.mesh.texcoords.size() );
//    assert( internal_shape.mesh.normals.size() == external_shape.mesh.normals.size() );
//    assert( internal_shape.mesh.indices.size() == external_shape.mesh.indices.size() );
//
//    for ( std::size_t i = 0; i < internal_shape.mesh.vertices.size(); ++i ) {
//        float internal_position = internal_shape.mesh.vertices[ i ];
//        float external_position = external_shape.mesh.vertices[ i ];
//        if ( internal_position  != external_position ) {
//            std::cerr << "Position error! " << internal_position << " != " << external_position << std::endl;
//        }
//        assert( internal_position == external_position );
//    }
//    std::cerr << "Positions match!" << std::endl;
//    for ( std::size_t i = 0; i < internal_shape.mesh.texcoords.size(); ++i ) {
//        float internal_texcoords = internal_shape.mesh.texcoords[ i ];
//        float external_texcoords = external_shape.mesh.texcoords[ i ];
//        if ( internal_texcoords  != external_texcoords ) {
//            std::cerr << "Texcoords error! " << internal_texcoords << " != " << external_texcoords << std::endl;
//        }
//        assert( internal_texcoords == external_texcoords );
//    }
//    std::cerr << "Texcoords match!" << std::endl;
//    for ( std::size_t i = 0; i < internal_shape.mesh.normals.size(); ++i ) {
//        float internal_normals = internal_shape.mesh.normals[ i ];
//        float external_normals = external_shape.mesh.normals[ i ];
//        if ( internal_normals  != external_normals ) {
//            std::cerr << "Normals error! " << internal_normals << " != " << external_normals << std::endl;
//        }
//        assert( internal_normals == external_normals );
//    }
//    std::cerr << "Normals match!" << std::endl;
//    for ( std::size_t i = 0; i < internal_shape.mesh.indices.size(); ++i ) {
//        float internal_indices = internal_shape.mesh.indices[ i ];
//        float external_indices = external_shape.mesh.indices[ i ];
//        if ( internal_indices  != external_indices ) {
//            std::cerr << "Indices error! " << internal_indices << " != " << external_indices << std::endl;
//        }
//        assert( internal_indices == external_indices );
//    }
//    std::cerr << "Indices match!" << std::endl;
//
//    return 0;
//}