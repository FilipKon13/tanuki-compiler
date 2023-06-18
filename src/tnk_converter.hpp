#ifndef TANUKI_TNK_CONVERTER_HPP_
#define TANUKI_TNK_CONVERTER_HPP_

#include <string>
#include <tao/json.hpp>

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


#endif /* TANUKI_TNK_CONVERTER_HPP_ */