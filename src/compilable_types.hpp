#ifndef TANUKI_COMPILABLE_HPP_
#define TANUKI_COMPILABLE_HPP_

class Scope;
class LiteralExpression;
class VariableExpression;
class FunctionCall;
class Array;
class ForEachLoop;


class Compilator {
    std::vector<std::string> statements;
public:
    void compile(const Scope &);
    void compile(const LiteralExpression &);
    void compile(const VariableExpression &);
    void compile(const FunctionCall &);
    void compile(const Array &);
    void compile(const ForEachLoop &);
    std::vector<std::string> get_code();
};


#endif /* TANUKI_COMPILABLE_HPP_ */
