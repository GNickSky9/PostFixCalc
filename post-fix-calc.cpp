#include <iostream>
#include <stack>
#include <cstdlib>
#include <cmath>
#include <limits>

using namespace std;

bool isOperator(const string &ele)
{
    if(ele == "^" || ele == "*" || ele == "/" || ele == "+" || ele == "-" || ele == "(" || ele == ")")
        return true;
    else
        return false;
}

bool isOperand(const string &ele)
{
    if(ele >= "0" && ele <= "9")
        return true;
    else if(ele >= "a" && ele <= "z")
        return true;
    else if(ele >= "A" && ele <= "Z")
        return true;
    else
        return false;
}

bool isOpenPara(const string &ele)
{
    if(ele == "(")
        return true;
    else
        return false;
}

bool isClosePara(const string &ele)
{
    if(ele == ")")
        return true;
    else
        return false;
}

// Lower # Is Higher Priority
int priority(const string &op)
{
    if(op == "+" || op == "-")
        return 3;
    else if(op == "*" || op == "/")
        return 2;
    else if(op == "^")
        return 1;
}

// 1 = op1 Is Greater Than op2
// 2 = op2 Is Greater Than op1
// 3 = Equal
int prec(const string &op1, const string &op2)
{
    if(isOperator(op1) && isOperator(op2))
    {
        if(priority(op1) < priority(op2))
            return 1;
        else if(priority(op1) == priority(op2))
            return 2;
        else
            return 3;
    }
    else if(!isOperator(op1))
    {
        cout << "Operator 1: " << op1 << " Is Not A Valid Operator." << endl;
        throw -1;
    }
    else if(!isOperator(op2))
    {
        cout << "Operator 2: " << op2 << " Is Not A Valid Operator." << endl;
        throw -1;
    }
}

double evalPO(const string &postFix)
{
    stack<double> operands;
    stack<string> opStack;
    double result;
    string temp;
    string op;
    double first, second;

    for(unsigned int i = 0; i < postFix.size(); ++i)
    {
        temp = postFix.at(i);
        if(isOperand(temp))
        {
            operands.push(atof(temp.c_str()));
        }
        else if(isOperator(temp))
        {
            opStack.push(temp);
            if(operands.size() >= 2)
            {
                first = operands.top();
                operands.pop();
                second = operands.top();
                operands.pop();
                op = opStack.top();

                if(op == "/")
                    operands.push(second/first);
                else if(op == "*")
                    operands.push(second*first);
                else if(op == "+")
                    operands.push(second+first);
                else if(op == "-")
                    operands.push(second-first);
                else if(op == "^")
                    operands.push(pow(second,first));
            }
        }
    }
    result = operands.top();
    operands.pop();

    return result;
}

string inToPo(const string &infix)
{
    stack<string> opStack;
    string postFix("");
    string operators("+-*/^");
    string temp("");

    for(int i = 0; i < infix.size(); ++i)
    {
        temp = infix.at(i);

        if(isOperand(temp))     // Found Operand
        {
            postFix += temp;
        }
        else if(isOpenPara(temp))
        {
            opStack.push(temp);
        }
        else if(isClosePara(temp))
        {
            while(!opStack.empty() && opStack.top() != "(")
            {
                postFix += opStack.top();
                opStack.pop();
            }
            opStack.pop();
        }
        else if(isOperator(temp)) // Found Operator
        {
            while(!opStack.empty() && !isOpenPara(opStack.top()) && prec(opStack.top(),temp)==1)
            {
                postFix += opStack.top();
                opStack.pop();
            }
            while(!opStack.empty() && !isOpenPara(opStack.top()) && prec(opStack.top(),temp)==2)
            {
                postFix += opStack.top();
                opStack.pop();
            }
            opStack.push(temp);
        }
    }

    while(!opStack.empty())
    {
        postFix += opStack.top();
        opStack.pop();
    }

    return postFix;
}

int main()
{
    string equation, input;
    while(input != "3")
    {
        cout << "What Would You Like To Do?\n(1)Infix->PostFix\n(2)PostFix Evaluation\n(3)Exit\n> ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin.clear();
        while(input != "1" && input != "2" && input != "3")
        {
            cout << "Invalid, Try Again\n> ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cin.clear();
        }
        if(input == "1")
        {
            cout << "\nEnter Infix Equation: ";
            getline(cin,equation);
            cout << "Evaluated To: " << inToPo(equation) << "\n\n\n";
        }
        else if(input == "2")
        {
            cout << "\nEnter PostFix Equation: ";
            getline(cin,equation);
            cout << "Evaluated To: " << evalPO(equation) << "\n\n\n";
        }
    }

    return 0;
}
