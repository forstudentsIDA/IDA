#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int m = 11;
int n = 699;
int mm = 10;

double dist(double *x, double *y, int m)
{
    double sum = 0.0;
    for(int i=0; i<m-1; i++)
        sum += pow((x[i]-y[i]), 2.0);
    return sum;
}

int main()
{
    srand(0);
    double **mas_tmp = new double*[n];
    for(int i=0; i<n; i++)
        mas_tmp[i] = new double[m];

    double **mas = new double*[n];
    for(int i=0; i<n; i++)
        mas[i] = new double[mm];

    ifstream in("breast-cancer-wisconsin.txt");

    while (!in.eof())
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            in >> mas_tmp[i][j];
    }

    for(int i=0; i<n; i++)
        for(int j=1; j<m; j++)
        mas[i][j-1] = mas_tmp[i][j];

    double max_f[9], min_f[9];

    for(int j=0; j<mm-1; j++)
    {
        max_f[j] = mas[0][j];
        min_f[j] = mas[0][j];
        for(int i=0; i<n; i++)
        {
            if(mas[i][j] < min_f[j])
                min_f[j] = mas[i][j];
            if(mas[i][j] > max_f[j])
                max_f[j] = mas[i][j];
        }
    }

    for(int j=0; j<mm-1; j++)
        for(int i=0; i<n; i++)
            mas[i][j] = (max_f[j] - mas[i][j])/(max_f[j] - min_f[j]);

    for(size_t i=0; i<n; i++)
        std::swap(mas[i],mas[rand()%n]);

    int n_train = 0.7*n;
    int n_test = n - n_train;
    double **train = new double*[n_train];
    for(int i=0; i<n_train; i++)
        train[i] = new double [mm];
    double **test = new double*[n_test];
    for(int i=0; i<n_test; i++)
        train[i] = new double {mm};

    double *class_test = new double{n_test};
    for(int i=0; i<n_test; i++)
        class_test[i] = 0;

    double error = 0.0;

    for(int i=0; i<n_test; i++)
    {
        double tmpl = dist(test[i], train[0], mm);
        int close_i = 0;
        for(int j=1; j<n_train; j++)
        {
            double tmp2 = dist(test[i], train[j], mm);
            if(tmp2 < tmpl)
            {
                tmpl = tmp2;
                close_i = j;
            }
        }
    class_test[i] = train[close_i][mm-1];
    if(class_test[i] != test[i][mm-1])
        error++;
    }

    cout << error << endl;
    error /= n_test;

    cout << n_test << endl;

    cout << "CLassification error is " << error << endl;

    ofstream out("out.txt");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<mm; j++)
            out << mas[i][j] << "\t";
        out << endl;
    }
}
