#include <iostream>
#include <vector>
using namespace std;

class weight_task {
	private:
		int N_ = 0;
		int maximal = 500000;
		int pair_count = 0;
		int step = 0;
		vector<vector<int>> pair;
		vector<int> tmp;

		void print_result() {
			cout << "Steps amount:" << step << endl;
			cout << pair.size() << endl;
			for (size_t i = 0; i < pair.size(); i++) {
				cout << pair[i][0] << " " << pair[i][1] << endl;
			}
		}

		int find_next_prime_number(int a){
			int counter = 0;
			int result = 0;

			for (int i=a+1;i<maximal;i++){
				counter = 0;
				for (int j = 2; j <= i / 2; j++) {
					if (i%j == 0) {
						counter++;
					}

					step = step + 1;
				}

				if (counter == 0) {
					result = i;
					break;
				}

				step = step + 1;
			}

			return result;
		}

	public:
		weight_task(int N) {
			N_ = N;
		}

		~weight_task() {
			N_ = 0;
		}

		int solver_simple() {
			int cnt = 0;
			int prime = 0;
			int l = 0;
			int i = 0;

			if (N_ == 1) {
				return -1;
			}

			while (N_ > 1){
				prime = find_next_prime_number(N_);
				l=0;
				i = 1;
				
				while (true){
					if (i + N_ == prime){
						l = i;
						break;
					}

					i = i + 1;
					step = step + 1;
				}

				cnt = 0;
				for (size_t i = l; i <= (N_ + l) / 2; i++){
					tmp.push_back(i);
					tmp.push_back(N_ - cnt);
					pair.push_back(tmp);
					tmp.clear();
					cnt = cnt + 1;
				}
				
				step = step + 1;
				N_ = l - 1;
			}

			print_result();
			return 0;
		}
};



int main() {
	int N = 2;
	weight_task A(N);//структура хранения пар это двумерный вектор, что не оптимально. Также нет идеи каким образом нужно делать оптимальную версию.
	A.solver_simple();
	system("pause");
	return 0;
}