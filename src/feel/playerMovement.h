#pragma once

#include <Ogre.h>
#include <feel/KeyHandler.h>
#include <base/Observer.h>


// Observer class to subscribe to player variables

class PlayerObserver : public Observer{

private:

	Ogre::Vector3* pPosition = nullptr;
	Ogre::Quaternion* pRotation = nullptr;

public:

	PlayerObserver(Subject& subject) {
		subject.Attach(this);
	}

	void update(Ogre::Vector3* pos, Ogre::Quaternion* rot) {
		this->pPosition = pos;
		this->pRotation = rot;
	}

	Ogre::Vector3 getPlayerPosition() {
		return *pPosition;
	}

	Ogre::Quaternion getPlayerRotation() {
		return *pRotation;
	}

};

class PlayerSubject : public Subject {

private:
	std::list<PlayerObserver*> list_observer_;
	Ogre::Vector3* pPosition = new Ogre::Vector3();
	Ogre::Quaternion* pRotation = new Ogre::Quaternion();

	Ogre::SceneNode* _playerNode;

public:

	PlayerSubject(Ogre::SceneNode* playerNode) {
		this->_playerNode = playerNode;
		*this->pPosition = playerNode->getPosition();
		*this->pRotation = playerNode->getOrientation();
	}

	Ogre::Vector3 getPlayerPosition() {
		return _playerNode->getPosition();
	}
	Ogre::Quaternion getPlayerRotation() {
		return _playerNode->getOrientation();
	}

	void setPlayerPosition(Ogre::Vector3 pos) {
		_playerNode->setPosition(pos);
		*pPosition = pos;
	}
	void setPlayerRotation(Ogre::Quaternion rot) {
		_playerNode->setOrientation(rot);
		*pRotation = rot;
	}

	void Attach(Observer* obr) override {
		list_observer_.push_back(static_cast<PlayerObserver*>(obr));
	}
	void Detach(Observer* obr) override {
		list_observer_.remove(static_cast<PlayerObserver*>(obr));
	}

	void update(Ogre::Vector3 pos, Ogre::Quaternion rot) {
		*pPosition = pos;
		*pRotation = rot;
	}

	void Notify() {
		std::list<PlayerObserver*>::iterator iterator = list_observer_.begin();
		while (iterator != list_observer_.end()) {
			(*iterator)->update(pPosition, pRotation);
			++iterator;
		}
	}

};


void updatePosition(IKEYS* inputKeys, float deltaTime, PlayerSubject* playerSub);

void updateRotation(MOUSEIN* mInput, float deltaTime, PlayerSubject* playerSub);
