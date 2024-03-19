#include <iostream>
#include <fstream>


struct task
{
    int id;
	int time;				//czas trwania
	int weight;				//ważność zadania
	int deadline;			//do kiedy ma się wykonać
};


int main()
{
	task tab[100];
	std::ifstream input("data.txt");
	int n;
    int c;
	std::string temp;
	std::string s[11] = {"data.10:", "data.11:","data.12:","data.13:","data.14:","data.15:","data.16:","data.17:","data.18:","data.19:","data.20:"};
	for(int i = 0; i < 11; i++){		//petla przejezdza po wszystkich zbiorach danych
		while(temp != s[i])			    //szukanie odpowiedniego zbioru danych
			input >> temp;
		
        std::cout << "****************" << std::endl;
		std::cout << "Zestaw danych -> " << temp << std::endl;
		input >> n;	
        				                    //wczytanie ilosci zadan
		for(int i = 0; i < n; i++){		//wczytanie parametrow kolejnych zadan
            tab[i].id = i + 1;
			input >> tab[i].time >> tab[i].weight >> tab[i].deadline;
            //std::cout << tab[i].id << " " << tab[i].time << " " << tab[i].weight << " "  << tab[i].deadline << std::endl;
		}
		
		int N = 1 << n;
		int* F = new int[N]; //tworze tablice F, n to liczba zadan
		F[0] = 0;

		for(int set = 1; set < N; set++){
			c = 0;
			for(int i = 0, b = 1; i < n; i++, b *= 2){
				if(set & b){
					c += tab[i].time;
				}
			}
			F[set] = 999999; //reprezentuje minimalna wage zadan osiagalna dla danego podzbioru zadan
			for(int k = 0, b = 1; k < n; k++, b *= 2){
				if(set & b){
					F[set] = std::min(F[set], F[set - b] + tab[k].weight * std::max(c - tab[k].deadline, 0)); //dla kazdego niepustego podzbioru set oblicza F[set], uwzgledniając wszystkie mozliwe zadania w tym podzbiorze.
				}
			}
		}
		std::cout << "Rozwiazanie optymalne: " << F[N-1] << std::endl; //Ostateczna odpowiedz F[N - 1], gdzie N = 2^n. Ta wartosc reprezentuje minimalna sume wazona osiagalna przez wykonanie podzbioru zadan w ich terminach.
        delete[] F;
    }
		

	input.close();
	
}
