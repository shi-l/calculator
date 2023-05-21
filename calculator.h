#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>
#include <string>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>

class calculator : public QObject
{
    Q_OBJECT
public:
    explicit calculator(QObject *parent = nullptr);
    Q_INVOKABLE QString do_calculator(QString str);
    Q_INVOKABLE QString get_postfix(QString str);
signals:

};

#endif // CALCULATOR_H
