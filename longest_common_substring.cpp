#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

class longest_common_substring{
  private:
    string s1;
    string s2;
    string res;

    //Через суффиксальный автомат https://cp-algorithms.com/string/suffix-automaton.html#toc-tgt-0
    struct state {
      int len, link;
      map<char, int> next;
    };

  void sa_extend(char c,vector<state> &st,int &sz,int &last) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

string lcs () {
    int sz=0;
    int last=0;
    vector<state> st;
    st.resize(2*(s1.length()+s2.length()));

    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
	
    for (int i = 0; i < s1.size(); i++){
        sa_extend(s1[i],st,sz,last);
    }

    int v = 0, l = 0, best = 0, bestpos = 0;
    for (int i = 0; i < s2.size(); i++) {
        while (v && !st[v].next.count(s2[i])) {
            v = st[v].link;
            l = st[v].len;
        }
        if (st[v].next.count(s2[i])) {
            v = st [v].next[s2[i]];
            l++;
        }
        if (l > best) {
            best = l;
            bestpos = i;
        }
    }
    return s2.substr(bestpos - best + 1, best);
} 
  
    //Через КНУТА-МОРРИСА-ПРАТТА
    int kmp(string s1,string s2){
        int N = s1.length();
        int M = s2.length();
        vector<int> lps;
        lps.resize(M+1);

        lps[0] = -1;
        int i = 1;
        int j = 0; 
  
      while (i < M){
          if (s2[j] == s2[i]){
              lps[i] = lps[j];
              i++;
              j++;
          }
        
        else {
          lps[i] = j;
          j = lps[j];
      
          while (j >= 0 && s2[j] != s2[i]){
            j = lps[j];
          }

          i++;
          j++;
        }
      }

    lps[i] = j;
    i = 0;
    j = 0; 
    
  while (i < N){
    if (s2[j] == s1[i]){
      i++;
      j++;
      if (j == M){
        return (i-j);
        j = lps[j];
      }
    }
    else {
      j = lps[j];
      if (j < 0){
        i++;
        j++;
      }
    }
  }
  
   lps.clear(); 
   return -1;
}

void lcs_kmp(string s1,string s2){
    int n=s2.length();
    string s3;
    int longest=0;
    string longest_str;

    for (int i = 1; i <= n; i++){    
        for (int j = 0; j <= n - i; j++) {
            int k = j + i - 1;            
            for (int m = j; m <= k; m++){ 
                s3=s3+s2[m];
            }
            
            int v=kmp(s1,s3);
            if (v>=0){
                if (s3.length()>longest){
                    longest=s3.length();
                    longest_str=s3;
                }
            }

            s3.clear();
        }
    }

    cout << longest_str << endl;
}

void solve_one(){
        vector<vector<int>> mat;
        vector<int> tmp;
        int maxlen = 0;
	      int endingindex = s1.length();
        
        for (int i=0;i<s2.length()+1;i++){
            tmp.push_back(0);
        }

        for (int i=0;i<s1.length()+1;i++){
            mat.push_back(tmp);
        }

      for (int i = 1; i <= s1.length(); i++) {
        for (int j = 1; j <= s2.length(); j++) {
            if (s1[i - 1] == s2[j - 1]){
               mat[i][j]=mat[i-1][j-1]+1;
               if (mat[i][j]>maxlen){
                 maxlen=mat[i][j];
                 endingindex=i;
               }
            }
        }
      }

    cout << s1.substr(endingindex-maxlen,maxlen)<<endl;     
}

void solve_two(){
  lcs_kmp(s1,s2);
}

  public:
    longest_common_substring(string &str1,string &str2){
      s1=str1;
      s2=str2;
    }

    void run(){
      cout << "Knuth-Morris-Pratt " << endl;
      solve_one();
      cout << "Using matrix " << endl;
      solve_two();
      cout << "Using suffix automata" << endl;
      cout << lcs() << endl;
    }
};

class test{
  private:
    string create_test_string(int n){
      string temp;
      char c; 

      srand((unsigned)time(NULL));

      for (int i=0; i<n; i++){  
          int r = rand() % 26;
          c='a' + r;
          temp=temp+string(1,c);
      }

      return temp;  
    }

  public:
    void main(int n1,int n2){
        ofstream fout;
        string test_string_one=create_test_string(n1);
        string test_string_two=create_test_string(n2);

        fout.open("in.txt");
        fout << test_string_one << " " << test_string_two;
        fout.close();

        longest_common_substring A(test_string_one,test_string_two);
        A.run();
    }
};

int main(){
  string s1;
  string s2;
  ifstream fin;

  //test T;
  //T.main(10,10);

  fin.open("in.txt");
  fin >> s1 >> s2;
  cout << s1 << endl;
  cout << s2 << endl;
  fin.close();
  longest_common_substring A(s1,s2);
  A.run();

  return 0;
}
