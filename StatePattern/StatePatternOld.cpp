#include <iostream>
using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class Context;
class State { // 抽象状态类，定义一个接口以封装与Context的一个特定状态相关的行为
public:
	virtual void Handle(Context* c) = 0;
	virtual ~State() {}
};

class Context { // 维护一个ConcreteState子类的实例，这个实例定义为当前状态
private:
	State * state;
public:
	Context(State* s) { state = s; }
	void Request() { // // 对请求做处理，并设置下一状态
		state->Handle(this);
	}
	void SetState(State* s) { state = s; }

	~Context()
	{
		delete state;
	}
};

// 具体状态类，每一个字类实现与Context的一个状态相关行为
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
	c->Request();  // ConcreteStateA 切换状态
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
