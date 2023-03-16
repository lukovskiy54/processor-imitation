#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <random>
#include <cstdio>
using namespace std;
bool check(string p) {                // перевірка чи є такий регістр
    if (p == "R1," || p == "R2," || p == "R3," || p == "R4,") {
        return true;
    }
    else {
        cout << "There is no register with this name "<<endl;
        return false;
    }

}
bool check2(string p) {                // перевірка чи є такий регістр
    if (p == "R1" || p == "R2" || p == "R3" || p == "R4") {
        return true;
    }
    else {
        cout << "There is no register with this name "<<endl;
        return false;
    }

}
string to_binary(int value){
    char sign = '0';
    if(value<0){
       sign = '1';
    }
    value = abs(value);
    int rem;
    unsigned long long binary = 0;
    unsigned long long multiplicator = 1;
    while (value > 0){
        rem = value % 2;
        value /= 2;
        binary += rem * multiplicator;
        multiplicator *= 10;
    }
    string bin = to_string(binary);
    string result = "0000000000000000000000";
    int i = bin.length () - 1;
    for (int j = result.length () - 1; j > 0; j--)
    {
        result[j] = bin[i];
        if (i == 0)
            break;
        i--;
    }
    result[0] = sign;
    return result;
}
int to_decimal(string res){
    int sign = 0;
    if(res[0] == '1'){
        sign = 1;
    }
    long long n = stoll(res.erase(0,1));
    int dec = 0, i = 0, rem;
    while (n!=0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    if (sign == 1){
        dec = dec* (-1);
    }
    return dec;
}

class Processor{
    public:
    string IR; //- регістр команди (містить текстовий запис команди, яка є поточною);
    string R1 = to_binary(rand()); //- перший регістр;
    string R2 = to_binary(rand()); //- другий регістр;
    string R3 = to_binary(rand()); //- третій регістр;
    string R4 = to_binary(rand());  //- четвертий регістр;
    char RC = 'a';    // - регістр для зберігання символу
    int PS = 1; //- регістр статусу (містить знак останнього результату);
    int PC = 0; //- регістр лічильника команд;
    int TC = 1; //- регістр лічильника тактів;
    bool mov(int i) {
        if(!check(this->IR.substr(i + 1, 3))){
            cout<<"Wrong input"<<endl;
            return false;
        }
        this->PC++;
        enum StringValue { R2, R1, R3, R4 };
        static std::map<std::string, StringValue> s_mapStringValues;
        s_mapStringValues["R1"] = R1;
        s_mapStringValues["R2"] = R2;
        s_mapStringValues["R3"] = R3;
        s_mapStringValues["R4"] = R4;
        int h = ::getchar();
        if(h == '\n') {
            cout << "Command: " << this->IR << endl;
            cout << "R1 = " << this->R1 << "   " << "Ins = " << IR.substr(0, i) << "|" << this->IR.substr(i + 1, 2)
                 << "|" << to_binary(abs(stoi(this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 7)))) << endl;
            cout << "R2 = " << this->R2 << "   " << "PC = " << PC << endl;
            cout << "R3 = " << this->R3 << "   " << "TC = " << TC << endl;
            cout << "R4 = " << this->R4 << "   " << "PS = " << PS << endl;
        }
        if(stoi(this->IR.substr(this->IR.find(',') + 1,this->IR.length() - 7))<0){
            PS = -1;
        }else PS = 1;
        switch(s_mapStringValues[this->IR.substr(i + 1, 2)])
        {
            case R1:
                this->R1 = to_binary(abs(stoi(this->IR.substr(this->IR.find(',') + 1,this->IR.length() - 7))));
                TC++;
                break;
            case R2:
                this->R2 = to_binary(abs(stoi(this->IR.substr(this->IR.find(',') + 1,this->IR.length() - 7))));
                TC++;
                break;
            case R3:
                this->R3 = to_binary(abs(stoi(this->IR.substr(this->IR.find(',') + 1,this->IR.length() - 7))));
                TC++;
                break;
            case R4:
                this->R4 = to_binary(abs(stoi(this->IR.substr(this->IR.find(',') + 1,this->IR.length() - 7))));
                TC++;
                break;
        }
        int o = ::getchar();
        if(o == '\n') {
              cout<<"Command: "<<this->IR<<endl;
              cout<<"R1 = "<<this->R1<<"   "<<"Ins = "<<IR.substr(0, i)<<"|"<<this->IR.substr(i + 1, 2)<<"|"<<to_binary(abs(stoi(this->IR.substr(this->IR.find(',') + 1,this->IR.length() - 7))))<<endl;
              cout<<"R2 = "<<this->R2<<"   "<<"PC = "<<PC<<endl;
              cout<<"R3 = "<<this->R3<<"   "<<"TC = "<<TC<<endl;
              cout<<"R4 = "<<this->R4<<"   "<<"PS = "<<PS<<endl;
              TC = 1;
        }
        return true;
    }
    bool swap(int i) {
        this->PC++;
        if(!check(this->IR.substr(i + 1, 3))){
            cout<<"Wrong input"<<endl;
            return false;
        }
        if(  (this->IR.substr(this->IR.find(',') + 1, this->IR.length()-8)).length() != 2 && (this->IR.substr(this->IR.find(',') + 1, this->IR.length()-8)).length() != 4){
            cout<<"Wrong input"<<endl;
            return false;
        }
        int B = ::getchar();
        if(B == '\n') {
            cout << "Command: " << this->IR << endl;
            cout << "R1 = " << this->R1 << "   " << "Ins = " << IR.substr(0, i) << "|" << this->IR.substr(i + 1, 2)
                 << "|" << this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8) << endl;
            cout << "R2 = " << this->R2 << "   " << "PC = " << PC << endl;
            cout << "R3 = " << this->R3 << "   " << "TC = " << TC << endl;
            cout << "R4 = " << this->R4 << "   " << "PS = " << PS << endl;
        }
            if (this->IR.substr(i + 1, 2) == "R1" || this->IR.substr(i + 1, 2) == "R2" ||
                this->IR.substr(i + 1, 2) == "R3" || this->IR.substr(i + 1, 2) == "R4") {
                this->PS = 1;
                string var = this->IR.substr(this->IR.find(',') + 1, this->IR.length()-8);
                if (var.length() == 2) {
                    this->TC++;

                    if (var != "R1" && var != "R2" && var != "R3" && var != "R4") {
                    } else {
                        enum StringValue {
                            R1, R2, R3, R4
                        };
                        static std::map<std::string, StringValue> s_mapStringValues;
                        s_mapStringValues["R1"] = R1;
                        s_mapStringValues["R2"] = R2;
                        s_mapStringValues["R3"] = R3;
                        s_mapStringValues["R4"] = R4;
                        switch (s_mapStringValues[this->IR.substr(i + 1, 2)]) {
                            case R1:
                                if (var == "R1") {
                                    cout << "Wrong input" << endl;
                                }
                                if (var == "R2") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R2);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;


                                }
                                if (var == "R3") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R3);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;


                                }
                                if (var == "R4") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R4);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;


                                }
                            case R2:
                                if (var == "R1") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R1);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R2[firstNum];
                                        this->R2[firstNum] = this->R2[secondNum];
                                        this->R2[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                                if (var == "R2") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R2);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R2[firstNum];
                                        this->R2[firstNum] = this->R2[secondNum];
                                        this->R2[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                                if (var == "R3") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R3);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R2[firstNum];
                                        this->R2[firstNum] = this->R2[secondNum];
                                        this->R2[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                                if (var == "R4") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R4);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R2[firstNum];
                                        this->R2[firstNum] = this->R2[secondNum];
                                        this->R2[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                            case R3:
                                if (var == "R1") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R1);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R3[firstNum];
                                        this->R3[firstNum] = this->R3[secondNum];
                                        this->R3[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                                if (var == "R2") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R2);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R3[firstNum];
                                        this->R3[firstNum] = this->R3[secondNum];
                                        this->R3[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                                if (var == "R3") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R3);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R3[firstNum];
                                        this->R3[firstNum] = this->R3[secondNum];
                                        this->R3[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                                if (var == "R4") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R4);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R3[firstNum];
                                        this->R3[firstNum] = this->R3[secondNum];
                                        this->R3[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                            case R4:
                                if (var == "R1") {
                                    int firstNum;
                                    int secondNum;
                                    int dec = to_decimal(this->R1);
                                    string de = to_string(dec);
                                    if (de.length() == 4) {
                                        string sub1 = de.substr(0, 2);
                                        string sub2 = de.substr(2, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R1[firstNum];
                                        this->R1[firstNum] = this->R1[secondNum];
                                        this->R1[secondNum] = RC;
                                    } else if (de.length() == 3) {
                                        string sub1 = de.substr(0, 1);
                                        string sub2 = de.substr(1, 2);
                                        firstNum = stoi(sub1);
                                        secondNum = stoi(sub2);
                                        this->RC = this->R4[firstNum];
                                        this->R4[firstNum] = this->R4[secondNum];
                                        this->R4[secondNum] = RC;
                                    } else cout << "Wrong input" << endl;
                                }
                                if (var == "R2") {
                                    if (var == "R1") {
                                        int firstNum;
                                        int secondNum;
                                        int dec = to_decimal(this->R2);
                                        string de = to_string(dec);
                                        if (de.length() == 4) {
                                            string sub1 = de.substr(0, 2);
                                            string sub2 = de.substr(2, 2);
                                            firstNum = stoi(sub1);
                                            secondNum = stoi(sub2);
                                            this->RC = this->R1[firstNum];
                                            this->R1[firstNum] = this->R1[secondNum];
                                            this->R1[secondNum] = RC;
                                        } else if (de.length() == 3) {
                                            string sub1 = de.substr(0, 1);
                                            string sub2 = de.substr(1, 2);
                                            firstNum = stoi(sub1);
                                            secondNum = stoi(sub2);
                                            this->RC = this->R4[firstNum];
                                            this->R4[firstNum] = this->R4[secondNum];
                                            this->R4[secondNum] = RC;
                                        } else cout << "Wrong input" << endl;
                                    }
                                }
                                if (var == "R3") {
                                    if (var == "R1") {
                                        int firstNum;
                                        int secondNum;
                                        int dec = to_decimal(this->R3);
                                        string de = to_string(dec);
                                        if (de.length() == 4) {
                                            string sub1 = de.substr(0, 2);
                                            string sub2 = de.substr(2, 2);
                                            firstNum = stoi(sub1);
                                            secondNum = stoi(sub2);
                                            this->RC = this->R1[firstNum];
                                            this->R1[firstNum] = this->R1[secondNum];
                                            this->R1[secondNum] = RC;
                                        } else if (de.length() == 3) {
                                            string sub1 = de.substr(0, 1);
                                            string sub2 = de.substr(1, 2);
                                            firstNum = stoi(sub1);
                                            secondNum = stoi(sub2);
                                            this->RC = this->R4[firstNum];
                                            this->R4[firstNum] = this->R4[secondNum];
                                            this->R4[secondNum] = RC;
                                        } else cout << "Wrong input" << endl;
                                    }
                                }
                                if (var == "R4") {
                                    if (var == "R1") {
                                        int firstNum;
                                        int secondNum;
                                        int dec = to_decimal(this->R4);
                                        string de = to_string(dec);
                                        if (de.length() == 4) {
                                            string sub1 = de.substr(0, 2);
                                            string sub2 = de.substr(2, 2);
                                            firstNum = stoi(sub1);
                                            secondNum = stoi(sub2);
                                            this->RC = this->R1[firstNum];
                                            this->R1[firstNum] = this->R1[secondNum];
                                            this->R1[secondNum] = RC;
                                        } else if (de.length() == 3) {
                                            string sub1 = de.substr(0, 1);
                                            string sub2 = de.substr(1, 2);
                                            firstNum = stoi(sub1);
                                            secondNum = stoi(sub2);
                                            this->RC = this->R4[firstNum];
                                            this->R4[firstNum] = this->R4[secondNum];
                                            this->R4[secondNum] = RC;
                                        } else cout << "Wrong input" << endl;
                                    }
                                }
                        }
                    }
                }
                if (var.length() == 4) {
                    //this->TC++;
                    enum StringValue {
                        R1, R2, R3, R4
                    };
                    static std::map<std::string, StringValue> s_mapStringValues;
                    s_mapStringValues["R1"] = R1;
                    s_mapStringValues["R2"] = R2;
                    s_mapStringValues["R3"] = R3;
                    s_mapStringValues["R4"] = R4;
                    switch (s_mapStringValues[this->IR.substr(i + 1, 2)]) {
                        case R1 :
                            this->RC = this->R1[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0, 2))];
                            this->R1[stoi(this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0,
                                                                                                                2))] = this->R1[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))];
                            this->R1[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))] = RC;
                            TC++;
                            break;
                        case R2:
                            this->RC = this->R2[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0, 2))];
                            this->R2[stoi(this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0,
                                                                                                                2))] = this->R2[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))];
                            this->R2[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))] = RC;
                            TC++;
                            break;
                        case R3:
                            this->RC = this->R3[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0, 2))];
                            this->R3[stoi(this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0,
                                                                                                                2))] = this->R3[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))];
                            this->R3[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))] = RC;
                            TC++;
                            break;
                        case R4:
                            this->RC = this->R4[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0, 2))];
                            this->R4[stoi(this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(0,
                                                                                                                2))] = this->R4[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))];
                            this->R4[stoi(
                                    this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8).substr(2, 2))] = RC;
                            TC++;
                            break;
                    }
                }
            } else { cout << "Wrong input" << endl;}
        int m = ::getchar();
        if (m == '\n') {
            cout << "Command: " << this->IR << endl;
            cout << "R1 = " << this->R1 << "   " << "Ins = " << IR.substr(0, i) << "|" << this->IR.substr(i + 1, 2)
                 << "|" << this->IR.substr(this->IR.find(',') + 1, this->IR.length() - 8) << endl;
            cout << "R2 = " << this->R2 << "   " << "PC = " << PC << endl;
            cout << "R3 = " << this->R3 << "   " << "TC = " << TC << endl;
            cout << "R4 = " << this->R4 << "   " << "PS = " << PS << endl;
            TC = 1;
        }
        return true;
    }
    void start () {
        fstream f("input.txt", ios::in);
        if (f.is_open()) {
            while (f) {
                getline(f, this->IR);                   //записуємо команду в регістр команд
                for (int i = 0; i < this->IR.length(); ++i) {
                    if (this->IR[i] == ' ') {
                        if (IR.substr(0, i) == "swap") {
                            if(swap(i)){};
                            IR.clear();
                            break;
                        }
                        if (IR.substr(0, i) == "mov") {
                            if(mov(i)){};
                            IR.clear();
                            break;
                        }
                        else cout<<"Wrong command input"<<endl;
                    }
                }
            }
        }
    }
};
int main() {
   Processor processor;
   processor.start();
   return 0;
}
