#ifndef TANUKI_COMPILE_HPP_
#define TANUKI_COMPILE_HPP_
#include <string>
#include <vector>

#include "compilable_types.hpp"
#include "compile.hpp"
#include "parser.hpp"
#include "util.hpp"

std::string pref = R"""(
const puppeteer = require('puppeteer');
async function start() {
    const browser = await puppeteer.launch({headless: false});
    const page = await browser.newPage();
    async function clickXPath(xPath) {
    const [el] = await page.$x(xPath);
    await el.click();
  };

  async function clickTimes(xPath, times) {
    const [el] = await page.$x(xPath);
    await el.click({clickCount: times});
  }

  async function clickContaining(text) {
    await clickXPath(`//*[contains(text(), "${text}")]`);
  };

  async function typeXPath(xPath, text) {
      const [el] = await page.$x(xPath);
      await el.type(text);
  }

  async function waitForXPath(xPath) {
    await page.waitForXPath(xPath, {timeout: 0});
  }

  async function load(url) {
    await page.goto(url);
  }

  async function press(key) {
    await page.keyboard.press(key);
  }

  async function getText(XPath) {
    await page.waitForXPath(XPath, {timeout:0})
    const [getXpath] = await page.$x(XPath);
    return await page.evaluate(name => name.textContent, getXpath);
  }

  async function wait(milis) {
    await page.waitForTimeout(milis);
  }

  async function print(smth) {
    console.log(smth);
  }

  async function repeat(times, fun) {
    for(let i = 0; i < times; ++i) {
      fun();
    }
  }
)""";
std::string suf = "\n}\n\nexports.start = start;";

/* Compiler implementation */ 

void Compilator::compile(const Scope & scope)  {
    statements.emplace_back("{");
    statements.emplace_back("\n");
    for(auto & st : scope.statements) {
        st->compile(*this);
        statements.emplace_back("\n");
    }
    statements.emplace_back("}");
}

void Compilator::compile(const LiteralExpression & expression) {
    if(has_type<NumberToken>(expression)) {
        auto it = std::get<NumberToken>(expression);
        statements.emplace_back(std::to_string(it.repr()));
    } else {
        auto it = std::get<LiteralToken>(expression);
        statements.emplace_back("'" + it.repr() + "'");
    }
}

void Compilator::compile(const VariableExpression & expression) {
    statements.emplace_back(static_cast<const std::string &>(expression));
}

void Compilator::compile(const FunctionCall & function_call) {
    auto & name = function_call.function.get().name;
    if(name == "print") {
        statements.emplace_back("console.log(");
        function_call.args[0]->compile(*this);
        statements.emplace_back(");");
        return;
    }
    if(name == "native") {
        statements.emplace_back(std::get<LiteralToken>(dynamic_cast<LiteralExpression &>(*function_call.args[0])).repr());
        statements.emplace_back("\n");
    }
    if(name == "=" || name == "+" || name == "-" || name == "*" || name == "/" || name == "==" || name == "!=" || name == "+=" || name == "-=" || name == "*=" || name == "/=") { // TODO fix infix functions (operators)
        function_call.args[0]->compile(*this);
        statements.emplace_back(" " + name + " ");
        function_call.args[1]->compile(*this);
        // statements.emplace_back(";");
        return;
    }
    statements.emplace_back("await " + function_call.function.get().name + "(");
    function_call.args[0]->compile(*this);
    for(int i=1;i<function_call.function.get().arity;++i) {
        statements.emplace_back(", ");
        function_call.args[i]->compile(*this);
    }
    statements.emplace_back(");");
}

void Compilator::compile(const Array & array) {
    statements.emplace_back("[");
    if(!array.empty()) {
        array[0]->compile(*this);
        for_each(array.begin()+1, array.end(), [&](auto & x){statements.emplace_back(", "); x->compile(*this);});
    }
    statements.emplace_back("]");
}

void Compilator::compile(const ForEachLoop & loop) {
    statements.emplace_back("for (");
    loop.var->compile(*this);
    statements.emplace_back(" of ");
    loop.iterable->compile(*this);
    statements.emplace_back(")");
    statements.emplace_back("\n");
    loop.scope->compile(*this);
}

void Compilator::compile(const IfStatement & if_statement) {
    statements.emplace_back("if (");
    if_statement.condition->compile(*this);
    statements.emplace_back(")");
    statements.emplace_back("\n");
    if_statement.scope->compile(*this);
}

std::vector<std::string> Compilator::get_code() {
    return std::move(statements);
}

/* Compiler implementation END */

std::string get_compiled_code(Prog_AST const & prog) {
    Compilator compilator;
    compilator.compile(*prog.code);
    std::vector<std::string> comm = compilator.get_code();
    int level = 1;
    std::string res = pref;
    auto const tabulation = [&] {for(int i=0;i<level;i++) res += '\t';};
    std::for_each(comm.begin()+1,comm.end()-2,[&](auto & v) {
        if(v == "\n") {
            res += '\n';
            tabulation();
            return;
        }
        if(v == "}") {
            if(res.back() == '\t') res.pop_back(); // removing '\t'
            level--;
        }
        if(v == "{") level++;
        res += v;
    });
    return res + suf;
}

#endif /* TANUKI_COMPILE_HPP_ */