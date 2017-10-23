#ifndef BTGFX_IO_HH
#define BTGFX_IO_HH

#include <iostream>

/// Open a text file and return it's contents.
/// @param path A text file.
/// @returns The contents of the file.
std::string read_file( const std::string& path );

#endif // BTGFX_IO_HH
