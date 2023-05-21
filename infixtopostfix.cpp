#include "infixtopostfix.h"

#define PI 3.141592654
#define E 2.718281828


std::unordered_map<std::string, int> basePrecedence{
    {"+", 1}, {"-", 1},{"*", 2}, {"/", 2},
    {"mod",2}
};
//其他运算符,前面跟数字或右括号隐式添加乘号
std::unordered_map<std::string, int> precedence {
    {"sin",3},{"cos",3},{"tan",3},
    {"cot",3},{"sec",3},{"csc",3},{"arcsin",3},
    {"arccos",3},{"arctan",3},{"sinh",3},{"cosh",3},
    {"tanh",3},{"ln",3},{"log",3},{"abs",3}
};
//判断运算符等级
std::unordered_map<std::string, int> precedenceGrade{
    {"+", 1}, {"-", 1},{"*", 2}, {"/", 2},
    {"%", 3}, {"^", 3},{"mod",2},
    {"sin",3},{"cos",3},{"tan",3},{"cot",3},
    {"sec",3},{"csc",3},{"arcsin",3},{"arccos",3},
    {"arctan",3},{"sinh",3},{"cosh",3},{"tanh",3},
    {"!",3},{"ln",3},{"log",3},{"abs",3}
};
std::unordered_map<std::string,std::string> downDigitsToDigits{
                                                                {"₀","0"},{"₁","1"},{"₂","2"},{"₃","3"},
                                                                {"₄","4"},{"₅","5"},{"₆","6"},{"₇","7"},
                                                                {"₈","8"},{"₉","9"},
                                                                };

infixToPostfix::infixToPostfix()
{

}

    int isOperator(std::string ch) {
        for (int i = ch.length(); i > 0; --i) {
            if(precedence.count(ch.substr(0,i)) > 0){

                return i;
            }

        }
        return 0;
    }
    int isBaseOperator(std::string ch) {
        for (int i = ch.length(); i > 0; --i) {
            if(basePrecedence.count(ch.substr(0,i)) > 0){

                return i;
            }

        }
        return 0;
    }


    int lenOfDigits(std::string expression,int begin){
        int n = 0;
        bool dpoint = false;
        for(int i = begin;i < expression.length();++i){
            char c = expression[i];
            if(std::isdigit(c)){
                n++;
            }else if(c == '.'){
                if(dpoint){
                    return -1;
                }
                dpoint = true;
                n++;
            }else{
                break;
            }
        }
        return n;
    }

    std::string downDigits(std::string expression,int begin,std::vector<std::string> &result){
        std::string downDigits;

        for (int var = begin; var < expression.length(); var = var + strlen("₀")) {
            std::string s = expression.substr(var,strlen("₀"));
            if(downDigitsToDigits.count(s) > 0){
                downDigits.append(downDigitsToDigits[s]);
            }else{
                break;
            }
        }
        return downDigits;
    }
    inline void insertOrAppend(std::string &expression,int n,std::string str){
        if(expression.length() < n){
            expression.append(str);
        }else {
            expression.insert(n,str);
        }
    }
    void stackPush(std::stack<std::string> &opStack,std::vector<std::string> &result,std::string calOperator){
        while (!opStack.empty() && opStack.top() != "("
               && (precedenceGrade[calOperator] == 0 ? 3 : precedenceGrade[calOperator])
                    <= (precedenceGrade[opStack.top()] == 0 ? 3 : precedenceGrade[opStack.top()])) {
            result.push_back( opStack.top()); // 将栈顶操作符输出
            opStack.pop();
        }
        opStack.push(calOperator); // 将新操作符入栈
    }
    void rightBracketsHandle(std::stack<std::string> &opStack,std::vector<std::string> &result){
        while (!opStack.empty() && opStack.top() != "(") {
            result.push_back( opStack.top());
            opStack.pop();
        }
        opStack.pop(); // 弹出左括号
    }
    void leftBracketsHandle(std::stack<std::string> &opStack,std::vector<std::string> &result,std::string &expression,int &n,int &prec){
        if(prec == 1 || prec == 3){
            expression.insert(n,"*");

            n = n - 1;
            return;
        }
        opStack.push("(");
        if(expression.length() > n + 1 && expression[n + 1] == '-'){
            result.push_back("-1");
            opStack.push("*");
            n = n + 1;
        }
    }
    int addParentheses(std::string &expression,int begin){
        expression.insert(begin,"(");
        int n = 0;
        int leftParentthesis = 0;
        for (int var = begin + 1; var < expression.length(); ++var) {
            char c = expression[var];
            if(c == '('){
                leftParentthesis++;
            }else if(c == ')'){
                leftParentthesis--;
                if(leftParentthesis == 0){
                    insertOrAppend(expression,var + 1,")");
                    n = var + 1 - begin;
                    break;
                }
            }
            else if(leftParentthesis == 0 && c != ' '){
                if(std::isdigit(c)){
                    int tmp = lenOfDigits(expression,var);
                    insertOrAppend(expression,var + tmp,")");
                    n = var + tmp + 1 - begin;
                    break;
                }else if(c == 'e'){
                    insertOrAppend(expression,var + 1,")");
                    n = var + 1 - begin;
                    break;
                }else if(expression.length() > var + strlen("π") - 1 && expression.substr(var,strlen("π")) == "π"){
                    insertOrAppend(expression,var + strlen("π"),")");
                    n = var + strlen("π") - begin;
                    break;
                }
            }
        }
        return n;
    }
    void convertSqrt(std::string &expression,int begin){

        expression.replace(begin,strlen("√"),"(");
        int leftParentthesis = 0;

        for (int var = begin + 1; var < expression.length(); ++var) {
            char c = expression[var];
            if(c == '('){
                leftParentthesis++;
            }else if(c == ')'){
                leftParentthesis--;
                if(leftParentthesis == 0){
                    insertOrAppend(expression,var + 1,")^0.5");

                    break;
                }
            }else if(std::isdigit(c) && leftParentthesis == 0){
                int tmp = lenOfDigits(expression,var);
                insertOrAppend(expression,var + tmp,")^0.5");
                break;
            }
        }

    }
    void convertTrigonometric(std::string &expression,int begin){

    }

    std::vector<std::string> infixToPostfix(std::string expression) {
        std::stack<std::string> opStack;
        std::vector<std::string> result;

        int n = -1;

        //前一个项是哪种类型(0:起步位置,1:数字,2:运算符,3:右括号)
        int prec = 0;

        while (++n < expression.length()) {
//            std::cout << expression <<std::endl;
            char ch = expression[n];
            if(ch == ' '){}
            //区分负数,当起步区域后为'-'时为负数其他为减号
            else if(prec == 0 && ch == '-'){
                result.push_back("-1");
                opStack.push("*");
            }else if(expression.substr(n,strlen("√")) == "√" && prec != 3){
                //隐式添加乘号
                if(prec == 1){
                    expression.insert(n,"*");
                    n = n - 1;
                    continue;
                }
                n = n + strlen("√");
                int tmp = addParentheses(expression,n);
                insertOrAppend(expression,n + tmp,"^0.5");
                n = n - 1;
                prec = 2;
            }else if(ch == '^' && prec != 0 && prec != 2){
                stackPush(opStack,result,"^");
                addParentheses(expression,n + 1);
                prec = 2;
            }
            //符号替换为数字并重新检查
            else if(ch == 'e' && prec != 3){
                std::stringstream ss;
                ss.precision(std::numeric_limits<double>::digits10);
                ss << E;
                if(prec == 1){
                    expression.replace(n,1,"*" + ss.str() + " ");
                    prec = 1;
                }else {
                    expression.replace(n,1,ss.str() + " ");
                }
                n = n - 1;
            }else if(expression.substr(n,strlen("π")) == "π" && prec != 3){
                std::stringstream ss;
                ss.precision(std::numeric_limits<double>::digits10);
                ss << PI;
                if(prec == 1){
                    expression.replace(n,strlen("π"),"*" + ss.str() + " ");
                        prec = 1;
                }else {
                        expression.replace(n,strlen("π"),ss.str() + " ");
                }
                n = n - 1;
            }
            else if (std::isdigit(ch) && prec != 1 && prec != 3) { // 如果是数字则直接输出
                int tmp = lenOfDigits(expression,n+1);
                if(tmp == -1){
                    std::vector<std::string> errResult;
                    return errResult;
                }
                result.push_back(expression.substr(n,tmp + 1));
                n = n + tmp;
                prec = 1;
            }else if(ch == '!' && prec != 0 ){
                std::string s = "!";
                stackPush(opStack,result,s);
                prec = 3;
            }else if(ch == '%' && prec != 0){
                std::string s = "%";
                stackPush(opStack,result,s);
                prec = 3;
            }
            //基本运算符前不能是其他运算符或起步位置;
            else if(isBaseOperator((expression.length() - n)>=3?expression.substr(n,3):expression.substr(n,expression.length() - n)) > 0 && prec != 2 && prec != 0){
                int nbit = isBaseOperator((expression.length() - n)>=3?expression.substr(n,3):expression.substr(n,expression.length() - n));
                std::string calOperator = expression.substr(n,nbit);
                stackPush(opStack,result,calOperator);
                n = n + nbit - 1;
                prec = 2;
            }
            //检测六位(目前最长操作符为六位)(或位置n到末尾)是否是操作符,运算符均添加括号,所以运算符后可以接其他运算符
            else if (isOperator((expression.length() - n)>=6?expression.substr(n,6):expression.substr(n,expression.length() - n)) > 0 && prec != 3) { // 如果是操作符
                if(prec == 1){
                    expression.insert(n,"*");
                    n = n - 1;
                    continue;
                }
                int nbit = isOperator((expression.length() - n)>=6?expression.substr(n,6):expression.substr(n,expression.length() - n));
                std::string calOperator = expression.substr(n,nbit);
                if(calOperator == "log"){
                    std::string digits = downDigits(expression,n + nbit,result);
                    n = n + digits.length() * strlen("₀");
                    calOperator = calOperator + (digits.length() == 0 ? "10" : digits);
                }
                stackPush(opStack,result,calOperator);
                addParentheses(expression,n + nbit);
                n = n + nbit - 1;
                prec = 2;
            }
            else if (ch == '(') { // 如果是左括号，则直接入栈
                if(prec == 1 || prec == 3){
                    expression.insert(n,"*");
                    n = n - 1;
                    continue;
                }
                opStack.push("(");
                prec = 0;
            } else if (ch == ')' && prec != 0) { // 如果是右括号，则将栈中的操作符输出，直到遇到左括号
                rightBracketsHandle(opStack,result);
                prec = 3;
            }else{
                //未检查到关键字,返回格式错误
                std::vector<std::string> errResult;
                return errResult;
            }
        }
        while (!opStack.empty()) { // 将栈中剩余的操作符全部输出
            result.push_back(opStack.top());
            opStack.pop();
        }
        return result;
    }


