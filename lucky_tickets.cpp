#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <vector>

using namespace std;

class lucky_tickets{
  private:
  
  template<typename T>
  void myswap (T& a, T& b){ 
    T temp = a;
    a = b;
    b = temp;
  }

  void reverseStr(string& str) { 
    int n = str.length(); 
    for (int i = 0; i < n / 2; i++){ 
        myswap(str[i], str[n - i - 1]);
    }   
  }

    int convert_to_decimal(string number,int base){
      int ans= 0;
     
      for(int i=0; i<number.length(); i++){
          if(number[i]>='A'){
              ans += (number[i]-'A'+10)*pow(base,number.length()-i-1);
          } 
          else {
              ans += (number[i]-'0') *pow(base,number.length()-i-1);
          }
      }
      return ans;
  }

  bool compare_summ_half(string s,int d){
    string temp_str;
    int s1=0;
    int s2=0;

    for (int i=0;i<s.length();i++){
          if (i<int(s.length()/2)){
            temp_str.push_back(s[i]);
            s1+= convert_to_decimal(temp_str,d);
			      temp_str.clear();
          } else {
            temp_str.push_back(s[i]);
            s2+= convert_to_decimal(temp_str,d);
			      temp_str.clear();
          }
      }

      if (s1==s2){
        return true;
      } else {
        return false;
      }
  }

  string decimal_to_another(int inputNum,int base) { 
   char str[254];
   int i;
   for (i = 0;inputNum > 0; ++i ){
        str[ i ] = inputNum % base + ( ( inputNum % base <= 9 ) ? '0' : '7' );
        inputNum /= base;
    }
    str[ i ] = '\0';

    string res=string(str);
    reverseStr(res);
    return res;
  } 

  int solver_function(int n,int d){
    int a=0;
    int counter=0;
    string s;
    string a_="1";
  
    for (int i=0;i<2*n-1;i++){
      a_=a_+"0";
    }

    a=convert_to_decimal(a_,d);
   
    //наборы с нуля
    for (int i=0;i<a;i++){
      s=decimal_to_another(i,d);
      if (s.length()<2*n){
        while (s.length()!=2*n){
          s="0"+s;
        }
      }

      bool v=compare_summ_half(s,d);
      if (v==true){
          cout << s << endl;
          counter=counter+1;
      }
    }
 

    while (true){
      s=decimal_to_another(a,d);
   
      if (s.length()>(2*n)){
        break;
      }

      if (s.length()%2==0){
        bool v=compare_summ_half(s,d);
        if (v==true){
          cout << s << endl;
          counter=counter+1;
        }
    }

    a=a+1;
  }

  return counter;
}

  public:
    void solver(int n, int d){
      int cn=solver_function(n,d);
      cout << "Count of lucky tickets is " << cn;
    }
};


int main(){
  int n=2;
  int d=4;

  lucky_tickets A;
  A.solver(n,d);
  return 0;
}