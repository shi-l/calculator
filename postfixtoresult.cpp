#include "postfixtoresult.h"

postfixToResult::postfixToResult()
{

}

double cAdd(double a,double b){

    return a + b;
}

double cSubtract(double a,double b){
    return a - b;
}

double cMultiply(double a,double b){
    return a * b;
}

double cDivide(double a,double b){
    return a / b;
}

int cMod(int a,int b){

    return a % b;
}

double cAbs(double a){
    return std::abs(a);
}

double cPrecent(double a){
    return 0.01 * a;
}

double cPower(double a,double b){

    return std::pow(a,b);
}

double cSqrt(double a){
    return std::sqrt(a);
}

double cCos(double a){
    return std::cos(a);
}

double cSin(double a){
    return std::sin(a);
}

double cTan(double a){
    return std::tan(a);
}

double cSec(double a){
    return 1/std::cos(a);
}

double cCsc(double a){
    return 1/std::sin(a);
}

double cCot(double a){
    return 1/std::tan(a);
}

double cArccos(double a){
    return std::acos(a);
}

double cArcsin(double a){
    return std::asin(a);
}

double cArctan(double a){
    return std::atan(a);
}

double cCosh(double a){
    return std::cosh(a);
}

double cSinh(double a){
    return std::sinh(a);
}

double cTanh(double a){
    return std::tanh(a);
}

double cLn(double a){
    return std::log(a);
}

double cLog(double a,double b){
    return std::log(b) / std::log(a);
}

double cGamma(double a){
    return std::tgamma(a + 1);
}

bool isInteger(double a){
    int aFloor = std::floor(a);
    int aCeil = std::ceil(a);
    if(a - aFloor < 1e-9 || aCeil - a < 1e-9){
        return true;
    }
    return false;
}

std::string opreatorHandle(std::vector<std::string> postfix){
    std::string result = "未知错误!";
    std::stack<double> dStack;
    for (int i = 0; i < postfix.size(); ++i) {
        std::string str = postfix.at(i);
        if((str[0] == '-' && str.length() > 1) || std::isdigit(str[0])){
            double d = std::stod(str);
            dStack.push(d);
        }else{
            if(dStack.empty()){
                return "格式错误";
            }
            double a = dStack.top();
            dStack.pop();
            if(str == "+"){
                double b = dStack.top();
                dStack.pop();
                double c = cAdd(a,b);
                dStack.push(c);
            }else if(str == "-"){
                double b = dStack.top();
                dStack.pop();
                double c = cSubtract(b,a);
                dStack.push(c);
            }else if(str == "*"){
                double b = dStack.top();
                dStack.pop();
                double c = cMultiply(a,b);
                dStack.push(c);
            }else if(str == "/"){
                double b = dStack.top();
                dStack.pop();
                double c = cDivide(b,a);
                dStack.push(c);
            }else if(str == "mod"){
                double b = dStack.top();
                dStack.pop();
                if(!(isInteger(a) && isInteger(b))){
                    return "取模运算仅对整数有意义";
                }
                double c = cMod(b,a);
                dStack.push(c);
            }else if(str == "^"){
                double b = dStack.top();
                dStack.pop();
                double c = cPower(b,a);
                dStack.push(c);
            }else if(str == "%"){
                double c = cPrecent(a);
                dStack.push(c);
            }else if(str == "abs"){
                double c = cAbs(a);
                dStack.push(c);
            }else if(str == "sqrt"){
                double c = cSqrt(a);
                dStack.push(c);
            }
            else if(str == "cos"){
                double c = cCos(a);
                dStack.push(c);
            }
            else if(str == "sin"){
                double c = cSin(a);
                dStack.push(c);
            }
            else if(str == "tan"){
                double c = cTan(a);
                dStack.push(c);
            }
            else if(str == "sec"){
                double c = cSec(a);
                dStack.push(c);
            }
            else if(str == "csc"){
                double c = cCsc(a);
                dStack.push(c);
            }
            else if(str == "cot"){
                double c = cCot(a);
                dStack.push(c);
            }
            else if(str == "arcsin"){
                if(a > 1 || a < -1){
                    return "反正弦函数在 [-1，1] 范围之外无意义";
                }
                double c = cArcsin(a);
                dStack.push(c);
            }
            else if(str == "arccos"){
                if(a > 1 || a < -1){
                    return "反余弦函数在 [-1，1] 范围之外无意义";
                }
                double c = cArcsin(a);
                dStack.push(c);
            }
            else if(str == "arctan"){
                double c = cArctan(a);
                dStack.push(c);
            }
            else if(str == "sinh"){
                double c = cSinh(a);
                dStack.push(c);
            }
            else if(str == "cosh"){
                double c = cCosh(a);
                dStack.push(c);
            }
            else if(str == "tanh"){
                double c = cTanh(a);
                dStack.push(c);
            }else if(str == "ln"){
                double c = cLn(a);
                dStack.push(c);
            }else if(str == "!"){
                double c = cGamma(a);
                dStack.push(c);
            }else if(str.substr(0,3) == "log"){
                double b = std::stod(str.substr(3));
                double c = cLog(b,a);
                dStack.push(c);
            }
        }
    }
    std::stringstream ss;
    ss.precision(10);
    ss << dStack.top();

    return ss.str();
}
