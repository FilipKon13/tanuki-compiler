#include <iostream>
#include "tnk_converter.hpp"

int main(int argc, char * argv[]) {
    const JSON json = tao::json::from_file( argv[1] );
    // tao::json::to_stream( std::cout, json , 4);
    TNKConverter converter;
    converter.compile(json);
    std::cout << converter.get_result() << '\n';
    return 0;
}