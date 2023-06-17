#include <iostream>
#include <tao/json.hpp>

using JSON = tao::json::value;

int main() {
    const JSON v = tao::json::from_file( "src/file.json" );
    tao::json::to_stream( std::cout, v , 4);
    return 0;
}