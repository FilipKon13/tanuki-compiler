#include <iostream>
#include <fstream>
#include <tao/json.hpp>

using JSON = tao::json::value;

JSON NODE = tao::json::from_string(R"""({
    "data": {},
    "dragging": false,
    "height": 60,
    "id": "0",
    "position": {
        "x": 0,
        "y": 0
    },
    "positionAbsolute": {
        "x": 0,
        "y": 0
    },
    "selected": false,
    "type": "scriptLine",
    "width": 167
})""");

void set_position(JSON & v, double x, double y) {
    v.get_object().at("position").get_object().at("x").set_double(x);
    v.get_object().at("position").get_object().at("y").set_double(y);
    
    v.get_object().at("positionAbsolute").get_object().at("x").set_double(x);
    v.get_object().at("positionAbsolute").get_object().at("y").set_double(y);
}

void set_type(JSON & v, std::string const & type) {
    v.get_object().at("type").set_string(type);
}

void set_id(JSON & v, int id) {
    v.get_object().at("id").set_signed(id);
}

void set_data(JSON & v, std::string const & line) {
    v.get_object().at("data").set_object({ {"line", line} });
}

JSON parse_tnk(std::ifstream & file) {
    std::string line;
    JSON result = tao::json::empty_array;
    auto &array = result.get_array();
    {
        auto start_node = NODE;
        set_type(start_node, "scriptStart");
        array.push_back(start_node);
    }
    int id = 1;
    while(std::getline(file, line)) {
        if(!line.empty() && line.back() == '\r') line.pop_back();
        auto node = NODE;
        set_position(node, 0, id * 100);
        // set_type() // already good
        set_id(node, id);
        set_data(node, line);
        array.push_back(node);
        id++;
    }
    return result;
}

int main(int argc, char * argv[]) {
    // const JSON v = tao::json::from_file( "src/file.json" );
    std::ifstream input(argv[1]);
    tao::json::to_stream( std::cout, parse_tnk(input) , 4);
    return 0;
}