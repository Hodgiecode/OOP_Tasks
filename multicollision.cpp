#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// http://pages.cs.wisc.edu/~shuchi/courses/787-F09/scribe-notes/lec7.pdf
// https://www.cs.purdue.edu/homes/hmaji/teaching/Spring%202017/lectures/03.pdf
// https://www.cs.cmu.edu/afs/cs/academic/class/15859-f04/www/scribes/lec6.pdf
/*Случайная величина X равномерно распределена от 1, до N. Производится n независимо распределенных испытаний. 
Найти вероятность того, что Х принимает какое-то значение не менее k раз.
Т.е. мы бросаем n мячиков в N корзин. Какова вероятность, что хотя бы в одну корзину попадет не менее k мячиков.*/



class multicollision{
private:
double randMToN(double M, double N){
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
}


double power(double n,int base){
    double m=1;
    for (int i=0;i<base;++i){
        m=m*n;
    }

    return m;
}


double c_nk(int n,int k){
    //https://e-maxx.ru/algo/binomial_coeff
    double res = 1;
	for (int i=1; i<=k; ++i){
		res = res * (n-k+i) / i;
    }
	return res;
}

double solve_binomial(int balls,int bins,int k){
    double p=(double)1/bins;
    double res=0;

    for (int i=k;i<=balls;i++){
        double cnk = c_nk(balls,i);
        double p_= power((double)p,i);
        double q = power((double)(1-p),balls-i);

        res=res+cnk*p_*q;
    }

    return res;
}

double solve_montecarlo(int balls,int bins,int k,int numtrials){
    srand((unsigned)time(NULL));
    int successes=0;
    int balls_in_bin=0;
    double a=0;
    double p=(double)1/bins;

    for (int i=0;i<numtrials;i++){
        balls_in_bin=0;
        for (int j=0;j<balls;j++){
            a=randMToN(0,1);
            if (a<p){
                balls_in_bin=balls_in_bin+1;
            }
        }

        if (balls_in_bin>k-1){
            successes=successes+1;
        }
    }

    return (double)successes/numtrials;
}

public:
    void solver(int N,int n,int k,int numtrials,int amount_of_montecarlo,int montecarlo_step){
        double res1=solve_binomial(N,n,k);
        double res2=0;
        double tmp=0;
        cout << "Finish using Bernoulli." << endl;
        
        for (int i=0;i<amount_of_montecarlo;i++){ //находим среднее значение всех запусков
            tmp=solve_montecarlo(N,n,k,numtrials+i*montecarlo_step);
            cout << "- Probability using Monte Carlo after " << numtrials+i*montecarlo_step <<" trials:" << tmp << endl;
            res2=res2+tmp;
        }

        res2=res2/amount_of_montecarlo;
        cout << endl << "Probability using Bernoulli:" << res1 << " ; ";
        cout << "Probability using Monte Carlo (avg):" << res2 << endl;
    }
};

int main(){
    int bins=8;
    int balls=10;
    int k=5; 
    int numtrials=5000;
    int amount_of_montecarlo=30;//сколько раз запускать Монте Карло
    int montecarlo_step=1000;//с каким шагом запускать Монте Карло

    multicollision A;
    A.solver(balls,bins,k,numtrials,amount_of_montecarlo,montecarlo_step);
    return 0;
}