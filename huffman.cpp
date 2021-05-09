#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Huffman_Codes{
 private:
 int r_=0;
 vector<double> probabilities;
 vector<vector<string>> result;

 struct Node{
    double probability;
    int parent;
    int place; 
    int* link; 
 };

struct Tree{
   int n,r,s,u,num,root; 
   Node* node;
};

int read_data(){
    double x;
    ifstream fin;
    
    fin.open("dat.txt");
    while (fin >> x) {
	    probabilities.push_back(x);
    }

    fin.close();

    x=0;
    for (size_t i=0;i<probabilities.size();i++){
      x=x+probabilities[i];
    }

    if (x!=1.0){
      return -1;
    }

    return 0;
  }

void sorting(Tree* tree, int m, int* psp){
   int i=0,j=0,num=0; 
   int n=tree->n+1;
   int* node;
   node=new int(n);

   for(i=0;i<n;i++){ 
       node[i]=-1;
   }
 
   for(i=0;i<n;i++){
      while(j<tree->num && (tree->node[j].probability==-1.0 || tree->node[j].parent!=-1)){
        j++;
      }
      
      node[i]=j; 
      j=j+1;
      
      if(j==(tree->num+1)){
         node[i]=-1;  
         break;
      }
   }
    
    while(node[num]!=-1){
        num++; 
    }
    
    for(i=0;i<m;i++){ 
        int noswap=1;
        int i1,i2,temp;

        for(j=0;j<num-i-1;j++){
            i1=node[j]; 
            i2=node[j+1];
            if(tree->node[i1].probability<tree->node[i2].probability){
                temp=i1;
                node[j]=i2;
                node[j+1]=temp;
                noswap=0;
            }
        }

        if(noswap==1){ 
            break;
        }
    }
        
    for (i=0;i<m;i++){
        psp[i]=node[num-m+i];
    } 
}

void HuffmanCode(Tree* tree){
   int i,n,m,u;
   int* psp;
   vector<string> temp;
   u=tree->u+1; 
   string s;
   
   for(i=0;i<tree->n;i++){
      int j,k=0;
      psp=new int(u);
      for(j=0;j<u;j++){
          psp[j]=-1;
      }
    
      temp.push_back(to_string(tree->node[i].probability));
      n=i;
      m=tree->node[n].parent;

      while(m!=-1){
         psp[k]=tree->node[n].place;
         n=m;
         m=tree->node[n].parent;
         k++;
      }
 
      for(k=u-1;k>-1;k--){
         if(psp[k]!=-1){
             s=s+to_string(psp[k]);
         }
      }
      
      temp.push_back(s);
      result.push_back(temp);
      temp.clear();
      s.clear();
   }
}

int solver_not_opt(int n,int r){
    int s,num,root,j,u;
    int i=0;
    Tree* tree;
    s=n%(r-1);

    if(r==2){ 
      s=2;
    } 
    else { 
      if(s==0){ 
        s=r-1;
      } 
      else {
        if(s==1){
          s=r;
        } 
        else {
          s=s;
        }
      }
    }

    u=(n-s)/(r-1);
    num=n+u+1; 
    
    tree=new Tree;
    tree->node=new Node[num];
    tree->n=n; 
    tree->r=r; 
    tree->root=-1; 
    tree->num=num; 
    tree->u=u; 
    tree->s=s;
   
    for(i=0;i<num;i++){
      tree->node[i].link=new int(r);  
      for(j=0;j<r;j++){
          tree->node[i].link[j]=-1;
      }
        
      tree->node[i].parent=-1;
      tree->node[i].place=-1;
        
      if(i<n){
        tree->node[i].probability=probabilities[i];
      } 
      else {
        tree->node[i].probability=-1;
      }
}
 
for(i=0;i<num-n;i++){
    int* psp;
    if(i==0){ 
        int l=0,pl=0;
        double sum=0;
        psp=new int(s);
        sorting(tree,s,psp);
        for(l=0;l<s;l++){
            pl=psp[l]; 
            tree->node[i+n].link[l]=pl;
            sum=sum+tree->node[pl].probability;
            tree->node[pl].parent=i+n;
            tree->node[pl].place=l;
        }
        tree->node[i+n].probability=sum;
        delete psp;
    }
    else{ 
        int l=0,pl=0;
        double sum=0;
        psp=new int(r);
        sorting(tree,r,psp);
        for(l=0;l<r;l++){
            pl=psp[l];
            tree->node[i+n].link[l]=pl;
            sum=sum+tree->node[pl].probability;
            tree->node[pl].parent=i+n;
            tree->node[pl].place=l;
        }
        tree->node[i+n].probability=sum;
        delete psp;
    }
}

tree->root=num-1;
HuffmanCode(tree);
return 0;
}

public:

Huffman_Codes(int r){
  r_=r;
}
void main(){
    int v=read_data();
    if (v==0){
        solver_not_opt(int(probabilities.size()),r_);
        
        double l=0;
        for (size_t i=0;i<result.size();i++){
            l=l+result[i][1].length()*probabilities[i];
            cout << result[i][0] << " : " << result[i][1] << " : " << result[i][1].length()*probabilities[i] << endl;
         }

         cout << "l=" << l << endl;
    } else {
        cout << "Problem with input data !" << endl;
    }
  }

  ~Huffman_Codes(){
    r_=0;
  }
};


class Test{
  private:
  double uniform_distribution(double M, double N){
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
 }

  double poisson_distribution(int k, double mean) { 
    double p = std::exp(-mean);
    double f = 1;
    for (int i=0 ;i<k;i++){
      f *= mean/(i+1); 
    }    
    return p*f;
  }
  
  double binomial_distribution(int n,int k,double p){
    double w = 1; 
    
    if (k > n){
      return 1;
    }

    if (p > 1 || p < 0){
      return 1;
    }

    for (int i = n - k + 1; i <= n; ++i){
      w = w * i;
    }

    for (int i = 1; i <= k; ++i){
      w = w / i;
    }

    w = w * pow(p, k) * pow(1.0 - p, n - k);
    return w;
}

void write_to_file(int mode,int n,double p){
    ofstream fin;
    int k=0;
    double x=0;
    double y=0;
    double eps=0;
    double num = fabs(p);
    
    num = p - int(p);
    while (num != 0){
      num = num * 10;
      k = k + 1;
      num = num - int(num);
    }

    eps=pow(0.1,k);    
    fin.open("dat.txt");
    
    for (int i=0;i<n;i++){
      if (mode==0){
        x=uniform_distribution(0,1);
      }

      if (mode==1){
        x=poisson_distribution(i,p);
      }

      if (mode==2){
        x=binomial_distribution(n,i,p);
      }

      x=round(x*pow(10.0,k))/pow(10.0,k);
      
      if (x>eps){
        if (1.000-y-x<eps*10){
          fin << std::fixed << std::setprecision(k) << 1.000-y << " ";
          break;
        } 
        
        else {
          fin << std::fixed << std::setprecision(k) << x << " ";
        }
      }

      y=y+x;
  }

    fin.close();
  }

public:
  //Test();
  void main(int mode,int n,double p,int r){
    write_to_file(mode,n,p);
    Huffman_Codes hc(r);
    hc.main();
  }

  //~Test();
};


 int main(){
  //первоисточник https://www.programmersought.com/article/46614802995/

  double p=0.0025;
  int mode=1; //0-равномерное распределение от 0 до 1; 1-распределение Пуассона; 2 - биномиальное; 
  int n=10;
  int r=4;//кодируем буквами от 0 до r-1 
  
  Test T;//пока просто пишет данные в файл и запускает хаффмана
  T.main(mode,n,p,r);
 
  //Huffman_Codes hc(r);
  //hc.main();
  return 0;
}