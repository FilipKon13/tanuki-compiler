#include <string>
#include <iostream>
#include <tao/json.hpp>
#include "compile.hpp"
using JSON = tao::json::value;


class TNKConverter {
    std::string result;
public:
    void compile(JSON const & v);
    void compileScriptLine(JSON const & v);
    void compileScriptStart(JSON const & v);
    std::string get_result();
};

void TNKConverter::compile(JSON const & v) {
    for(auto & x : v.get_array()) {
        auto & o = x.get_object();
        auto & type = o.at("type").get_string();
        if(type == "scriptStart")       compileScriptStart(o);
        else if(type == "scriptLine")   compileScriptLine(o);
        else throw std::string("Unknown node type");
    }
}

void TNKConverter::compileScriptLine(JSON const & v) {
    result += v.get_object().at("data").get_object().at("line").get_string() + '\n';
}

void TNKConverter::compileScriptStart(JSON const & v) {}

std::string TNKConverter::get_result() {
    return result;
}

int main(int argc, char * argv[]) {
    const JSON json = tao::json::from_file( argv[1] );
    // tao::json::to_stream( std::cout, json , 4);
    TNKConverter converter;
    converter.compile(json);
    std::cout << get_compiled_code(Parser(Tokenizer(converter.get_result()).tokenize()).parse()) << '\n';
    return 0;
}