#include <iostream>

using namespace std;

class student{
private:
    string name, id, pwd;
    double gpa;
    int credits;
public:
    student *next;
    student(string nm, string id, string pwd, double gpa, int crd){
        this->name = nm;
        this->id = id;
        this->pwd = pwd;
        if (gpa <= 4 && gpa >= 0) this->gpa = gpa;
        else this->gpa = 0;
        this->credits = crd;
        next = NULL;
    }
    string viewid(){
        return id;
    }
    string checkpwd(){
        return pwd;
    }
    int viewgpa(){
        return gpa;
    }
    void printdata(){
        cout << "=============================="<<endl;
        cout<<"Name\t: "<<name<<endl;
        cout<<"ID\t: "<<id<<endl;
        cout<<"GPA\t: "<<gpa<<endl;
        cout<<"Credits\t: "<<credits<<endl;
        cout << "=============================="<<endl;
    }
};

class system{
private:
    int studentcount;
    student *head, *tail;
public:
    system(){
        studentcount = 0;
        head = NULL;
        tail = NULL;
    }
    void printall(){
        student *temp = head;
        if (temp != NULL){
            while (temp->next != NULL){
                temp->printdata();
                if (temp->next != NULL) temp = temp->next;
            }
            if (temp == tail) temp->printdata();
        }
        else cout << " <Console>: Error 404 not found." <<endl;
    }
    void addstudent(string nm, string id, string pwd, double gpa, int crd){
        if (head==NULL){
            head = new student(nm,id,pwd,gpa,crd);
            tail = head;
        }else{
            tail->next = new student(nm,id,pwd,gpa,crd);
            tail = tail->next;
        }

        studentcount++;
        cout<<endl;
    }
    void printspecific(string id, string pwd){
        student *temp=head;
        if(temp != NULL){
            while(temp->next != NULL){
                if (temp->viewid() == id && temp->checkpwd() == pwd) break;
                temp = temp->next;
            }
            if (temp->viewid() == id && temp->checkpwd() == pwd) temp->printdata();
            else cout << " <Console>: Error 404 not found. aCheck your id and password." <<endl;
        }
        else cout << " <Console>: Error 404 not found. bCheck your id and password." <<endl;
    }
};

//"hashing" algorithm (nor really hashing but it's an example
char translate(int x){ // fungsi yang mentranslate nilai angka menjadi huruf adfgvx
  if(x == 0) return 'a'; // jika 0 maka nilainya a
  else if(x == 1) return 'd'; // jika 1 maka nilainya d
  else if(x == 2) return 'f'; // jika 2 maka nilainya f
  else if(x == 3) return 'g'; // jika 3 maka nilainya g
  else if(x == 4) return 'v'; // jika 4 maka nilainya v
  else if(x == 5) return 'x'; // jika 5 maka nilainya x
}
string hashme(string tobehashed){ // "hashing" technique based from ADVGFX cipher. do not use this for real usage!
    char cheatsheet[6][6] = {{'8', 'p', '3', 'd', '1', 'n'}, {'l', 't', '4', 'o', 'a', 'h'}, {'7','k','b','c','5','z'}, {'j','u','6','w','g','m'}, {'x','s','v','i','r','2'}, {'9','e','y','0','f','q'}};
    string finalhash="";
    for (int i = 0; i<tobehashed.size();i++){
        for (int j = 0; j < 6; j++) { //loop untuk pengecekan baris pada cheatsheet
            for (int k = 0; k < 6; k++) { //loop untuk pengecekan kolom pada cheatsheet
                if (tobehashed.at(i) == cheatsheet[j][k]) { // seleksi kondisi bila cocok dengan cheatsheet
                    finalhash += translate(j); // memberikan nilai hasil translasi nilai j pada step1[i]
                    finalhash += translate(k); // memberikan nilai hasil translasi nilai k pada step1[i+1]
                }
            }
        }
    }
    return finalhash;
}

int main(){
    system siam;
    string nm, id, pwd;
    double gpa;
    int crd, ops;
    while(true){
        cout<<"======ACADEMICS INFORMATION SYSTEM======"<<endl;
        cout<<"0.Exit\t1. Login\t2.Create Account"<<endl;
        cout<<"<anonymous>: ";
        cin>>ops;
        if(ops == 0) break;
        else if(ops == 1){
            cout<<"\tID\t\t: ";
            cin>>id;
            cout<<"\tPassword\t: ";
            cin>>pwd;
            if(id != "root" && pwd != "root") siam.printspecific(id, hashme(pwd));
            else{
                    cout<<"<console>: root access detected, showing all data"<<endl;
                    siam.printall();
            }
        }
        else if (ops == 2){
            cout<<"\tInsert name\t: ";
            cin>>nm;
            cout<<"\tInsert ID\t: ";
            cin>>id;
            cout<<"\tInsert Password\t: ";
            cin>>pwd;
            cout<<"\tInsert GPA\t: ";
            cin>>gpa;
            cout<<"\tInsert Credits\t: ";
            cin>>crd;
            siam.addstudent(nm,id,hashme(pwd),gpa,crd);
            cout<<"<console>: account creation successful!"<<endl;
        }
        else{
            cout<<"<console>: Wrong command!"<<endl<<endl;
        }
        cout<<endl<<endl;
    }
}
