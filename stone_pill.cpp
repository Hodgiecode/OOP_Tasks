#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <algorithm>

using namespace std;

/*Вывод на экран содержимого двумерного вектора */
void print_vector_vector(vector<vector<double>> &vector_vector){
    for (size_t i=0;i<vector_vector.size();i++){
        for (size_t j=0;j<vector_vector[i].size();j++){
            cout << vector_vector[i][j] << " ";
        }

        cout << endl;
    }
}

/*Чтение входных данных из файла in. Множество положим в data_vector. l в l*/
void read_file(string in,vector<double> &data_vector,double &l){
    ifstream fin;
    fin.open(in);
    fin >> l;
    string temp;

    while (fin >> temp){
      data_vector.push_back(stoi(temp));
    }

    fin.close();
}

/*Запись в файл результата работы программы */
void write_to_file(string out,vector<vector<double>> &result_vector){
    ofstream fout;
    fout.open(out);
    for (size_t i=0;i<result_vector.size();i++){
        for (size_t j=0;j<result_vector[i].size();j++){
            fout<<result_vector[i][j] << " ";
        }

        fout << "\n";
    }

    fout.close();
}


class stone_piles{
    private:
        double l=0;
        double max_capacity=0;
        double weight_size=0;

        int candidate_for_minimal_k=-1;
        int opt_size=INT_MAX;
        double general_difference_for_set=INT_MAX;
        
        vector<double> weights_vector={0};
        vector<vector<double>> result_vector;
        vector<vector<vector<double>>> vector_for_partitions;

        double calc_sum(vector<double> &myvec){
            double sum=0;
            for (size_t i=0;i<myvec.size();i++){
                sum=sum+myvec[i];
             }

        return sum; 
    }

    public:
         void create_partitions(){
            int counter=-1;
            int i=0;
            int index=0;
            bool flag=true;

            vector<vector<double>> lists;
            vector<int> indexes;
            
            indexes.resize(weight_size);
            lists.push_back(vector<double>());
            lists[0].insert(lists[0].end(),weights_vector.begin(), weights_vector.end());

            while (true){
                counter=counter+1;
                vector_for_partitions.push_back(lists);
                i=indexes.size()-1;
                index=0;
                flag=false;

                while (true){
                     if (i<=0){
                        flag=true;
                        break;
                    }
            
                    index=indexes[i];
                    lists[index].erase(lists[index].begin()+lists[index].size()-1);

                    if (lists[index].size()>0){
                        break;
                    }

                    lists.erase(lists.begin()+index);
                    --i;
                }

                if (flag==true){
                    break;
                }
       
                ++index;

                if (index>=lists.size()){
                    lists.push_back(vector<double>());
                }

                while (i<indexes.size()){
                    indexes[i]=index;
                    lists[index].push_back(weights_vector[i]);
                    index=0;
                    ++i;
                }
            }
    }

    void find_partition(){
            int sum=0;
            int mode=1;
            double difference=0;

            for (size_t k=0;k<vector_for_partitions.size();k++){
                mode=1;
                difference=0;
                
                for (size_t i=0;i<vector_for_partitions[k].size();i++){
                    if (calc_sum(vector_for_partitions[k][i])>l){
                        mode=0;
                        break;
                    } else {
                        difference=difference+(l-calc_sum(vector_for_partitions[k][i]));
                    }
                }

                if (mode==1){
                    if (vector_for_partitions[k].size()<=opt_size){
                        if (vector_for_partitions[k].size()==opt_size && difference<general_difference_for_set){
                            general_difference_for_set=difference;
                            candidate_for_minimal_k=k;
                        }

                        if (vector_for_partitions[k].size()<opt_size){
                            opt_size=vector_for_partitions[k].size();
                            general_difference_for_set=difference;
                            candidate_for_minimal_k=k;
                        }
                    }
            }
        }
    }

    public:
        stone_piles(vector<double> &w,double k){
            weights_vector=w;
            weight_size=w.size();
            l=k;
        }

        vector<vector<double>> solver(){
            create_partitions();
            /*for (size_t i=0;i<vector_for_partitions.size();i++){
                print_vector_vector(vector_for_partitions[i]);
                cout << endl;
            }*/

            find_partition();

            //cout << candidate_for_minimal_k << " " << general_difference_for_set << " " << opt_size << endl;

            //print_vector_vector(vector_for_partitions[candidate_for_minimal_k]);

            if (candidate_for_minimal_k!=-1){
                return vector_for_partitions[candidate_for_minimal_k];
            } else {
                return vector<vector<double>>();
            }
        }

         ~stone_piles(){
            l=0;
            weights_vector.clear();
         }
};

class test_class {
    private:
        vector<double> test_set_vector;
        vector<vector<double>> rv;
        int num=0;
        double l=0;
    public:
        test_class(int number){
            num=number;
            for (int i=0;i<num;i++){
                test_set_vector.push_back(i+1);
            }
        }
    
    int test_one(){
         double se=0;
         for (size_t i=0;i<test_set_vector.size();i++){
             se=se+test_set_vector[i]+1;
         }

         stone_piles A(test_set_vector,se);
         rv=A.solver();
         if (rv.size()==1 && rv[0]==test_set_vector){
            return 1;
        } else {
            return 0;
        }
    }

    int test_two(){
        double me=*std::min_element(test_set_vector.begin(),test_set_vector.end());
        stone_piles A(test_set_vector,me);
        rv=A.solver();  
        if (rv.size()==0){
            return 1;
        } else {
            return 0;
        }
    }

    void main(){
        int v1=test_one();//l равно сумме всех элементов. Ожидаемый ответ множество состоящее из всех элементов
        int v2=test_two();//l меньше или равно минимальному элементу тестового множества. Ответ пустое множество.

        if (v1==1){
            cout << "Test 0 is passed" << endl;
        }

        if (v2==1){
            cout << "Test 1 is passed" << endl;
        }
    }

     ~test_class(){
        test_set_vector.clear();
    }
};



int main(){
    vector<vector<double>> rv;
    vector<double> dv;
    double l=0;
    
    string in="in.txt";
    string out="out.txt";

    //int limit=42; // l для теста
    int n=6;//число элементов в тестовом множестве
    test_class B(n);
    B.main();
    
    read_file(in,dv,l);
    stone_piles A(dv,l); //создаем класс для решения задачи
    rv=A.solver(); //решаем задачу
    write_to_file(out,rv);
   
    return 0;
}