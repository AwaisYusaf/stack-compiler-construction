#include <iostream>
#include<string>
#include <fstream>
using namespace std;
class Node{
public:
    string value;
    Node *next;
    Node *prev;
};

//LAST IN FIRST OUT APPROACH
class Stack{
private:
    Node *top;
    Node *bottom;
public:
    Stack(){
        top=NULL;
        bottom=NULL;
    }
    void push(string data){
        Node *node=new Node;
        node->value=data;
        node->next=NULL;
        node->prev=NULL;
        if (top==NULL){
            top=node;
            bottom=node;
        }
        else{
            node->next=top;
            top->prev=node;
            top=node;
        }
    }
    bool isEmpty(){
        if (top==NULL){
            return true;
        }
        return false;
    }
    string pop(){
        if(!isEmpty()){
            Node *temp=top;
            top=top->next;
            top->prev=NULL;
            string str=temp->value;
            delete temp;
            return str;
        }
        else{
            return "";
        }
    }
    void display(){
        if(!isEmpty()){
            Node *head=top;
            while (head!=NULL){
                cout<<head->value<<" ";
                head=head->next;
            }
        }
    }
    string getTop(){
        if (top!=NULL){
            return top->value;
        }
        return NULL;
    }
}stack;

string check(string line){
    string temp="";


    if (line=="begin"||line=="end"||line=="endif"||line=="endfor"||line=="endwhile"||line=="else") {
        if (line == "begin") {
            stack.push(line);
            return "started";
        }
        if (line == "end") {
            if (stack.getTop() == "begin") {
                stack.pop();
            } else {
                return "* Error : Unexpected End ";
            }
        }

        if (line == "endif") {
            if (stack.getTop() == "else") {
                stack.pop();
                if (stack.getTop() == "if") {
                    stack.pop();
                } else if (stack.getTop() == "elseif") {
                    stack.pop();
                    stack.pop();
                }
            }
        }
        if (line=="endfor"){

        }
        if (line=="endwhile"){

        }
        if (line=="else"){

        }
    }

    else {

        for (int i = 0; i < line.length(); i++) {
            if (line[i] != ' ') {
                temp += line[i];
                if (temp == "begin") {
                    stack.push(temp);
                    return "started";
                } else if (temp == "end") {
                    if (stack.getTop() == "begin") {
                        stack.pop();
                    }
                } else if (temp == "if") {
                    stack.push("if");
                } else if (temp == "elseif") {
                    if (stack.getTop() == "if") {
                        stack.push("elseif");
                    } else {
                        return "* Error : Using eliseif without if statement at line : ";
                    }
                } else if (temp == "else") {
                    if (stack.getTop() == "elseif" || stack.getTop() == "if") {
                        stack.push("else");
                    } else {
                        return "* Error : Using else without if statement";
                    }
                } else if (temp == "endif") {
                    if (stack.getTop() == "else") {
                        stack.pop();
                        if (stack.getTop() == "if") {
                            stack.pop();
                        } else if (stack.getTop() == "elseif") {
                            stack.pop();
                            stack.pop();
                        }
                    } else if (stack.getTop() == "if") {
                        stack.pop();
                    } else {
                        return "* Error: Using endif without if statement ";
                    }
                } else if (temp == "for") {
                    stack.push("for");
                } else if (temp == "endfor") {
                    if (stack.getTop() == "for") {
                        stack.pop();
                    } else {
                        return "* Error: Using endfor without for ";
                    }
                } else if (temp == "while") {
                    stack.push("while");
                } else if (temp == "endwhile") {
                    if (stack.getTop() == "while") {
                        stack.pop();
                    } else {
                        return "* Error: Using endwhile without while ";
                    }
                } else if (line[i] == '{') {
                    stack.push("{");
                } else if (line[i] = '}') {
                    if (stack.getTop() == "{") {
                        stack.pop();
                    } else {
                        return "* Error : '{' Missing ";
                    }
                } else if (line[i] == '(') {
                    stack.push("(");
                    temp = "";
                } else if (line[i] == ')') {
                    if (stack.getTop() == ")") {
                        stack.pop();
                    } else {
                        return "* Error : '(' Missing ";
                    }
                } else if (line[i] == '[') {
                    stack.push("[");
                    temp = "";
                } else if (line[i] == ']') {
                    if (stack.getTop() == "[") {
                        stack.pop();
                    } else {
                        return "* Error : '[' Missing ";
                    }
                }
            } else {
                temp = "";
            }

        }
    }

}

int main(){
    bool isStarted=false;
    string line;
    ifstream myfile;
    myfile.open("new_file_write.txt");
    int counter=1;
    if (myfile.is_open()){
        while (getline(myfile,line)){
            string reply=check(line);
            if (reply=="started"){
                isStarted=true;
            }
            else if(reply[0]=='*'){
                cout<<reply<<" at line : " <<counter<<endl;
                break;
            }
            counter+=1;
        }
        myfile.close();
    }
}
