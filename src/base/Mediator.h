#pragma once

#include <iostream>

class MediatorComponent;

class Mediator {
public:
	virtual void Notify(MediatorComponent* component, std::string event) const = 0;

};

class MediatorComponent {
protected:
	Mediator* _mediator;

public:

	MediatorComponent(Mediator* mediator = nullptr) : _mediator(mediator) {}

	void setMediator(Mediator* mediator) {
		this->_mediator = mediator;
	}

};
