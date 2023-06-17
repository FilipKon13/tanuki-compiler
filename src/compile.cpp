#include <iostream>
#include "compile.hpp"

int main() {
    using namespace std;
    string s = read_input();
    // cout << Parser(Tokenizer(s).tokenize()).parse() << '\n';
    auto tree = Parser(Tokenizer(s).tokenize()).parse();
    cerr << tree << '\n';
    cout << get_compiled_code(tree) << '\n';
    return 0;
}

