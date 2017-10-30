//
// Created by Eddie Hoyle on 30/10/17.
//

#ifndef OPENGL_EXAMPLES_STRING_HH
#define OPENGL_EXAMPLES_STRING_HH


#include <string>

namespace common {

class SimpleString {

public:
    explicit SimpleString( const std::string& string );
    bool startswith( const std::string& prefix );

private:
    std::string m_string;
};

} // namespace common

#endif //OPENGL_EXAMPLES_STRING_HH
