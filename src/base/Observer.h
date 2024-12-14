#pragma once



class Observer{
public:
	virtual ~Observer();
	virtual void update();
};


class Subject {
public:
	virtual ~Subject();
	virtual void Attach(Observer* obr);
	virtual void Detach(Observer* obr);
	virtual void Notify();
};



