/*
 * File:   B00130829_Part1.cpp
 * Author: Rakul R Sampath
 *
 * Created on 20 December 2019, 19:13
 *
 * Event Driven Programming Task
 */

#include <iostream>
#include <windows.h>

using namespace std;

class machineProgram
{
	class State* current;
public:
	machineProgram();
	void setCurrent(State* s)
	{
		current = s;
	}
	void idle();
	void sensing();
	void processing();
};

class State
{
public:
	virtual void idle(machineProgram* m)
	{
		cout << "nodes in idle state" << endl;
	}
	virtual void sensing(machineProgram* m)
	{
		cout << "sensing the nodes" << endl;
	}
	virtual void processing(machineProgram* m)
	{
		cout << "processing the nodes" << endl;
	}

};

void machineProgram::idle()
{
	current->idle(this);
}

void machineProgram::sensing()
{
	current->sensing(this);
}

void machineProgram::processing()
{
	current->processing(this);
}

class Idle : public State
{
public:
	Idle()
	{
		cout << "Constructor in idle state" << endl;
	};
	~Idle()
	{
		cout << "Destructor in idle state" << endl;
	};
	void sensing(machineProgram* m);

};

class Sensing : public State
{
public:
	Sensing()
	{
		cout << "Constructor in sensing state" << endl;
	};
	~Sensing()
	{
		cout << "Destructor in sensing state" << endl;
	};
	void processing(machineProgram* m);

};

class Processing : public State
{
public:
	Processing()
	{
		cout << "Constructor in processing state" << endl;
	};
	~Processing()
	{
		cout << "Destructor in processing state" << endl;
	};

	void idle(machineProgram* m);

};

void Idle::sensing(machineProgram* m)
{
	cout << "Idle Condition to Sensing Condition" << endl;
	m->setCurrent(new Sensing());
	delete this;
	cout << "Reading the sensor values!!!" << endl;
	Sleep(500);
	cout << "Getting data from the humidity sensor" << endl;
	int a = 0;
	while (a++ < 8)
	{
		int humidity = (rand() % (100 - 21 + 7)) + 25;
		cout << "The Humidity Sensor Values are: " << humidity << endl;
		Sleep(250);
	}

	Sleep(500);
	cout << "Getting data from the temperature sensor" << endl;
	int b = 0;
	while (b++ < 8)
	{
		int temp = (rand() % (100 - 15 + 9)) + 26;
		cout << "The Temperature Sensor Values are: " << temp << endl;
		Sleep(250);
	}
	Sleep(500);
	cout << "Values are ready for the processing!" << endl;
	m->processing();
}

void Sensing::processing(machineProgram* m)
{
	cout << "Sensing Condition to Processing Condition" << endl;
	m->setCurrent(new Processing());
	delete this;
	cout << "Processing the sensor data!" << endl;
	Sleep(500);
	cout << "Processing the humidity data" << endl;
	Sleep(500);
	cout << "Processing the temperature data" << endl;
	Sleep(500);
	cout << "Going back to Idle state Condition!" << endl;
	Sleep(500);
	m->idle();
}

void Processing::idle(machineProgram* m)
{
	cout << "Processing Condition to Idle Condition!" << endl;
	m->setCurrent(new Idle());
	delete this;
}

machineProgram::machineProgram()
{
	current = new Idle();
	cout << '\n';
}

int main()
{
	machineProgram FSM;
	char userPreference;
	for (int i = 0; i < 8; i++)
	{
		cout << "System is in idle condition. Do you want to begin Sensing Condition (y/n): ";
		cin >> userPreference;
		if (char(toupper(userPreference)) == 'Y')
		{
			FSM.sensing();
			Sleep(500);
		}
		else if (char(toupper(userPreference)) == 'N')
		{
			continue;
		}
		else
		{
			cout << "Given Invalid Character!!!" << endl;
		}
	}
	return 0;
}
