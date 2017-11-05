//
// Created by Eddie Hoyle on 4/11/17.
//

#ifndef OPENGL_EXAMPLES_PARSER_HH
#define OPENGL_EXAMPLES_PARSER_HH

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <map>

namespace common {

/// TODO
struct Material {
    glm::vec3 ambient[3];
    glm::vec3 diffuse[3];
    glm::vec3 specular[3];
    glm::vec3 transmittance[3];
    glm::vec3 emission[3];
    float shininess;

    std::string ambient_name;
    std::string diffuse_texname;
    std::string specular_texname;
    std::string normal_texname;
    std::map< std::string, std::string > unknown_parameter;
};

/// TODO
struct Mesh {
    std::vector< float >          vertices;
    std::vector< float >          texcoords;
    std::vector< float >          normals;
    std::vector< unsigned int >   indices;
};

/// TODO
struct Shape {
    Material material;
    Mesh mesh;
};

void load_obj( const std::string& path, Shape& shape );

}

#endif //OPENGL_EXAMPLES_PARSER_HH
