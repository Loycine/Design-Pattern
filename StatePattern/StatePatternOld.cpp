#include <iostream>
using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class Context;
class State { // ����״̬�࣬����һ���ӿ��Է�װ��Context��һ���ض�״̬��ص���Ϊ
public:
	virtual void Handle(Context* c) = 0;
	virtual ~State() {}
};

class Context { // ά��һ��ConcreteState�����ʵ�������ʵ������Ϊ��ǰ״̬
private:
	State * state;
public:
	Context(State* s) { state = s; }
	void Request() { // // ��������������������һ״̬
		state->Handle(this);
	}
	void SetState(State* s) { state = s; }

	~Context()
	{
		delete state;
	}
};

// ����״̬�࣬ÿһ������ʵ����Context��һ��״̬�����Ϊ
class ConcreteStateA : public State {
public:
	void Handle(Context* c);
};

class ConcreteStateB : public State {
public:
	void Handle(Context* c);
};

class ConcreteStateC : public State {
public:
	void Handle(Context* c);
};

void ConcreteStateA::Handle(Context* c) {
	cout << "ConcreteStateA" << endl;
	c->SetState(new ConcreteStateB());
	delete this;
}

void ConcreteStateB::Handle(Context* c) {
	cout << "ConcreteStateB" << endl;
	c->SetState(new ConcreteStateC());
	delete this;
}

void ConcreteStateC::Handle(Context* c) {
	cout << "ConcreteStateC" << endl;
	c->SetState(new ConcreteStateA());
	delete this;
}



int main() {
	State* s = new ConcreteStateA();
	Context* c = new Context(s);
	c->Request();  // ConcreteStateA �л�״̬
	c->Request();  // ConcreteStateB
	c->Request();  // ConcreteStateC
	delete c;
	
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

	_CrtDumpMemoryLeaks();
	
	getchar();
	return 0;
}
