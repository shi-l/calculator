#include "calculator.h"



std::vector<std::string> infixToPostfix(std::string expression);
std::string opreatorHandle(std::vector<std::string> postfix);

    calculator::calculator(QObject *parent)
        : QObject{parent}
    {

    }
    QString calculator::do_calculator(QString str){
        std::vector<std::string> result = infixToPostfix(str.toStdString());
        if(result.size() == 0 && str.length() > 0){
                return "格式错误";
        }else if(str.length() == 0){
                return "";
        }
//        for (auto& s : result) {

//            std::cout << s << " ";
//        }
//        std::cout << std::endl;
        QString resultStr = QString::fromStdString(opreatorHandle(result));
        return resultStr;
    }

    QString calculator::get_postfix(QString str){
        std::vector<std::string> result = infixToPostfix(str.toStdString());
        if(result.size() == 0 && str.length() > 0){
                return "格式错误";
        }
        std::string postfix;
        for (auto& s : result) {
                postfix.append(s + " ");
        }
        return QString::fromStdString(postfix);
    }
