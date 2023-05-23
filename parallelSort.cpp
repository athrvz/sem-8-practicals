
/*
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const int N = 10000;

void bubble(vector <int> & a) {
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < a.size(); j++) 
			if(a[j] > a[j + 1]) swap(a[j], a[j + 1]);
	}
	// for(int x : a) cout << x << " ";
	// cout << endl;
}

void pBubble(vector <int> & a) {
	int n = a.size();
	for(int phase = 0; phase < n; phase++) {
		if(phase % 2 == 0) {
			#pragma omp parallel for num_threads(10) default(none) shared(a, n) private(i)
			for(int i = 1; i < n; i += 2) 
				if(a[i - 1] > a[i]) swap(a[i - 1], a[i]);
		}
		else {
			#pragma omp parallel for num_threads(10) default(none) shared(a, n) private(i)
			for(int i = 1; i < n - 1; i += 2) 
				if(a[i] > a[i + 1]) swap(a[i], a[i + 1]);
		}
	}
}

int main() {
	vector <int> a(N);
	for(int i = N; i >= 1; i--) a[N - i] = i;

	double start, end;
	start = omp_get_wtime();
	bubble(a);
	// pBubble(a);
	end = omp_get_wtime();
	cout << end - start << " sec" << endl;
	// for(int x : a) cout << x << " ";
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubble(vector <int> a) {
	int n = a.size();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n - 1; j++) 
			if(a[j] > a[j + 1]) swap(a[j], a[j + 1]);
	}
	// for(int x: a) cout << x << " ";
	// cout << endl;
}

void pBubble(vector <int> a) {
	int n = a.size();
	for(int ph = 0; ph < n; ph++) {
		if(ph % 2 == 0) {
			#pragma omp parallel for num_threads(16)
			for(int i = 1; i < n; i += 2) 
				if(a[i - 1] > a[i]) swap(a[i - 1], a[i]);
		} else {
			#pragma omp parallel for num_threads(16)
			for(int i = 1; i < n - 1; i += 2)
				if(a[i] > a[i + 1]) swap(a[i], a[i + 1]);
		}
	}
	// for(int x : a) cout << x << " ";
	// cout << endl;
}

int main() {
	int n = 1e4;
	vector <int> a(n);
	for(int i = 0; i < n; i++) 
		a[i] = n - i;

	double start, end;
	start = omp_get_wtime();
	pBubble(a);
	// bubble(a);
	cout << omp_get_wtime() - start << endl;
}