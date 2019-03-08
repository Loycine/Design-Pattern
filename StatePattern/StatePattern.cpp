#include<iostream>
#include<memory>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

class Trafic;

class TraficLight {
public:
	virtual void handle(Trafic* trafic) = 0;
};

class Trafic {
public:
	shared_ptr<TraficLight> traficLight;
public:
	Trafic(shared_ptr<TraficLight> traficLight)
	{
		this->traficLight = traficLight;
	}
	void request()
	{
		traficLight->handle(this);
	}
};

class RedTraficLight : public TraficLight {
public:
	virtual void handle(Trafic* trafic);
};

class YellowTraficLight : public TraficLight {
public:
	virtual void handle(Trafic* trafic);
};

class GreenTraficLight : public TraficLight {
public:
	virtual void handle(Trafic* trafic);
};

void RedTraficLight::handle(Trafic* trafic)
{
	cout << "Current is red Light\n";
	trafic->traficLight = make_shared<YellowTraficLight>();
}

void YellowTraficLight::handle(Trafic* trafic)
{
	cout << "Current is yellow Light\n";
	trafic->traficLight = make_shared<GreenTraficLight>();
}

void GreenTraficLight::handle(Trafic* trafic)
{
	cout << "Current is green Light\n";
	trafic->traficLight = make_shared<RedTraficLight>();
}

int main()
{
	Trafic *trafic = new Trafic(make_shared<RedTraficLight>());
	trafic->request();
	trafic->request();
	trafic->request();
	delete trafic;
	
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
	
	getchar();
}


