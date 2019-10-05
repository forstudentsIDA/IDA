#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int m = 14;
int n = 178;
//int mm = 10;

/*double myrandom(double lb, double ub)
{

}*/

double dist(double *x, double *y, int m)
{
    double sum = 0.0;
    for(int i=1; i<m; i++)
    {
        sum += pow((x[i] - y[i]), 2.0);
    }
    return sum;
}

int main()
{
    srand(0);
    double **mas = new double*[n];
    for(int i=0; i<n; i++)
        mas[i] = new double[m];

    ifstream in("data.txt");

    while (!in.eof())
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                in >> mas[i][j];
    }

    double max_f[13], min_f[13];

    for(int j=1; j<m; j++)
    {
        max_f[j] = mas[0][j];
        min_f[j] = mas[0][j];
        for(int i=1; i<n; i++)
        {
            if(mas[i][j] < min_f[j])
                min_f[j] = mas[i][j];
            if(mas[i][j] > max_f[j])
                max_f[j] = mas[i][j];
        }
    }

    for(int j=1; j<m; j++)
        for(int i=0; i<n; i++)
            mas[i][j] = (max_f[j] - mas[i][j])/(max_f[j] - min_f[j]);

    for (size_t i=0; i<n; i++)
        std::swap(mas[i],mas[rand()%n]);

    int n_train = 0.7*n;
    double **train = new double*[n_train];
    for(int i=0; i<n_train; i++)
        train[i] = new double[m];

    int n_test = 178 - n_train;
    double **test = new double*[n_test];
    for(int i=0; i<n_test; i++)
        test[i] = new double[m];
    double *class_test = new double[n_test];
    for(int i=0; i<n_test; i++)
        class_test[i] = -1;

    for(int i=0; i<n_train; i++)
        for(int j=0; j<m; j++)
        train[i][j] = mas[i][j];
    for(int i=0; i<n_test; i++)
        for(int j=0; j<m; j++)
        test[i][j] = mas[i+n_train][j];

    double error = 0.0;
    for(int i=0; i<n_test; i++)
    {
        double tmp1 = dist(test[i], train[0], m);
        int close_i = 0;
        for(int j=1; j<n_train; j++)
        {
            double tmp2 = dist(test[i], train[j], m);
            if(tmp2 < tmp1)
            {
                tmp1 = tmp2;
                close_i = j;
            }
        }
        class_test[i] = train[close_i][0];
        if(class_test[i] != test[i][0])
            error++;
    }
    error /= n_test;

    cout << "Classification error is " << error << endl;

    ofstream out("out.txt");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            out << mas[i][j] << "\t";
        out << endl;
    }

 /*   double x = myrandom(0, 100);
    cout << x << endl;*/
}
