#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int getMin(vector <int> a) {
	int mn = a[0];
	#pragma omp parallel for  reduction(min : mn)
	for(int i = 0; i < a.size(); i++) 
		mn = (mn > a[i]) ? a[i] : mn;
	return mn;
}

int getMax(vector <int> a) {
	int mx = a[0];
	#pragma omp parallel for  reduction(max : mx)
	for(int i = 0; i < a.size(); i++) 
		mx = (mx < a[i]) ? a[i] : mx;
	return mx;
}

int getSum(vector <int> a) {
	int sum = 0;
	#pragma omp parallel for  reduction(+ : sum)
	for(int i = 0; i < a.size(); i++) 
		sum += a[i];
	return sum;
}

double getAvg(vector <int> a) {
	return (double)getSum(a) / a.size(); 
}

int main() {
	int n = 100000;
	vector <int> a(n);
	for(int i = 1; i <= n; i++) a[i-1] = i;
	double start = omp_get_wtime();
	cout << "min: " << getMin(a) << endl;
	cout << "max: " << getMax(a) << endl;
	cout << "sum: " << getSum(a) << endl;
	cout << "avg: " << getAvg(a) << endl;
	cout << omp_get_wtime() - start << endl;
}