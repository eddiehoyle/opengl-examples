//
// Created by Eddie Hoyle on 30/10/17.
//

#include "string.hh"

namespace common {

SimpleString::SimpleString( const std::string& string )
        : m_string( string ) {
}

bool SimpleString::startswith( const std::string& prefix ) {
    return m_string.substr( 0, prefix.size() ) == prefix;
}

} // namespace common
