#include <iostream>
#include "compile.hpp"

int main(int argc, char * argv[]) {
    using namespace std;
    ifstream input(argv[1]);
    string s = read_input(input);
    cerr << s << '\n';
    // cout << Parser(Tokenizer(s).tokenize()).parse() << '\n';
    auto tree = Parser(Tokenizer(s).tokenize()).parse();
    cerr << tree << '\n';
    cout << get_compiled_code(tree) << '\n';
    return 0;
}

