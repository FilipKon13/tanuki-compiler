#include <string>
#include <iostream>
#include "tnk_converter.hpp"
#include "compile.hpp"

int main(int argc, char * argv[]) {
    const JSON json = tao::json::from_file( argv[1] );
    // tao::json::to_stream( std::cerr, json , 4);
    TNKConverter converter;
    converter.compile(json);
    std::cout << get_compiled_code(Parser(Tokenizer(converter.get_result()).tokenize()).parse()) << '\n';
    return 0;
}