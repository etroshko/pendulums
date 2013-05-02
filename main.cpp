#include <iostream>
#include <cmath>
#include <string>

using namespace std;

const double eps = 1e-14;

class Pendulum
{
public:
    Pendulum(const string &name);
    virtual ~Pendulum() {};
    virtual double get_oscillation_period()const=0;
    virtual double get_cyclic_frequency()const=0;
    string get_name();
private:
    string class_name;
};

Pendulum::Pendulum(const string &name):
    class_name(name)
{}

string Pendulum::get_name()
{
    return class_name;
}

//==========================================================================================//

class Electric_oscillating_circuit: public Pendulum
{
public:
    Electric_oscillating_circuit(double inductance, double capacitance, const string &name);
    double get_oscillation_period()const;
    double get_cyclic_frequency()const;
private:
    double class_inductance;
    double class_capacitance;
};

Electric_oscillating_circuit::Electric_oscillating_circuit(double inductance, double capacitance, const string &name):
    Pendulum(string("Electric oscillating circuit ")+name), class_inductance(inductance), class_capacitance(capacitance)
{}

double Electric_oscillating_circuit::get_cyclic_frequency()const
{
    return 1/sqrt(class_inductance*class_capacitance);
}

double Electric_oscillating_circuit::get_oscillation_period()const
{
    return 2*M_PI*sqrt(class_inductance*class_capacitance);
}

//===================================================================================//

class Mathematical_pendulum: public Pendulum
{
public:
    Mathematical_pendulum(double length, const string &name);
    double get_oscillation_period()const;
    double get_cyclic_frequency()const;
private:
    double class_length;
};

Mathematical_pendulum::Mathematical_pendulum(double length, const string &name):
    Pendulum(string("Mathematical pendulum ")+name), class_length(length)
{}

double Mathematical_pendulum::get_cyclic_frequency()const
{
    return sqrt(9.8/class_length);
}

double Mathematical_pendulum::get_oscillation_period()const
{
    return 2*M_PI*sqrt(class_length/9.8);
}

//===========================================================================================//

class Spring_pendulum: public Pendulum
{
public:
    Spring_pendulum(double weight, const string &name);
    double get_oscillation_period()const;
    double get_cyclic_frequency()const;
private:
    double class_weight;
};

Spring_pendulum::Spring_pendulum(double weight, const string &name):
    Pendulum(string("Spring pendulum ")+name), class_weight(weight)
{}

double Spring_pendulum::get_cyclic_frequency()const
{
    return sqrt(9.8/class_weight);
}

double Spring_pendulum::get_oscillation_period()const
{
    return 2*M_PI*sqrt(class_weight/9.8);
}

//===================================================================================//

class Compound_pendulum: public Pendulum
{
public:
    Compound_pendulum(double inertia_moment, double weight, double length, const string &name);
    double get_oscillation_period()const;
    double get_cyclic_frequency()const;
private:
    double class_inertia_moment;
    double class_weight;
    double class_length;
};

Compound_pendulum::Compound_pendulum(double inertia_moment, double weight, double length, const string &name):
    Pendulum(string("Compound pendulum ")+name), class_inertia_moment(inertia_moment), class_weight(weight), class_length(length)
{}

double Compound_pendulum::get_cyclic_frequency()const
{
    return sqrt(class_weight*class_length*9.8/class_inertia_moment);
}

double Compound_pendulum::get_oscillation_period()const
{
    return 2*M_PI*sqrt(class_inertia_moment/(class_weight*class_length*9.8));
}

//=======================================================================================//

void input(Pendulum **array,int count);
void output(Pendulum **array,int count);
double ratio(const Pendulum &pendulum);

void input(Pendulum **array,int count)
{
    for(int i=0; i<count; ++i)
    {
        int n;
        do
        {
            cout<<"Select the type of a pendulum:"<<endl;
            cout<<"1 - Electric oscillating circuit\n2 - Mathematical pendulum\n3 - Spring pendulum\n4 - Compound pendulum\n";
            cin>>n;
            string name;
            double inductance, capacitance, length, weight, inertia_moment;
            switch(n)
            {
            case 1:
                cout<<"Enter the name of the electric oscillating circuit:\n";
                cin>>name;
                cout<<"Enter the inductance of the electric oscillating circuit (henry):\n";
                cin>>inductance;
                cout<<"Enter the capacitance of the electric oscillating circuit (farad):\n";
                cin>>capacitance;
                array[i] = new Electric_oscillating_circuit(inductance,capacitance,name);
                break;
            case 2:
                cout<<"Enter the name of the mathematical pendulum:\n";
                cin>>name;
                cout<<"Enter the length of the mathematical pendulum (metre):\n";
                cin>>length;
                array[i] = new Mathematical_pendulum(length,name);
                break;
            case 3:
                cout<<"Enter the name of the spring pendulum:\n";
                cin>>name;
                cout<<"Enter the weight of the spring pendulum (kilogram):\n";
                cin>>weight;
                array[i] = new Spring_pendulum(weight,name);
                break;
            case 4:
                cout<<"Enter the name of the compound pendulum:\n";
                cin>>name;
                cout<<"Enter the inertia moment of the compound pendulum (kilogram*metre^2):\n";
                cin>>inertia_moment;
                cout<<"Enter the weight of the compound pendulum (kilogram)\n";
                cin>>weight;
                cout<<"Enter the length of the compound pendulum (metre)\n";
                cin>>length;
                array[i] = new Compound_pendulum(inertia_moment, weight, length, name);
                break;
            default:
                cerr<<"try again\n";
                break;
            }
        }
        while(n < 1 || n > 4);
    }
}

void output(Pendulum **array, int count)
{
    for(int i = 0; i < count; ++i)
    {
        cout<<"The "<<i+1<<" is the "<<array[i]->get_name()<<".\n";
        cout<<"It has cyclic frequency "<<array[i]->get_cyclic_frequency()<<".\n";
        cout<<"It has square oscillation period "<<array[i]->get_oscillation_period()<<".\n";
        cout<<"The (oscillation period)/(cyclic frequency) ratio is "<<ratio(*array[i])<<".\n";
        cout<<endl<<endl;
    }
}

double ratio(const Pendulum &pendulum)
{
    if(fabs(pendulum.get_cyclic_frequency())>eps)
        return pendulum.get_oscillation_period()/pendulum.get_cyclic_frequency();
    else
        return 0.0;
}

int main()
{
    Pendulum **array = 0;
    int count;
    cout<<"Enter number of pendulums:\n";
    cin>>count;
    array = new Pendulum*[count];
    for(int i = 0; i < count; ++i)
        array[i] = 0;
    input(array, count);
    output(array, count);
    for(int i = 0; i < count; ++i)
        delete array[i];
    delete [] array;
    return 0;
}

