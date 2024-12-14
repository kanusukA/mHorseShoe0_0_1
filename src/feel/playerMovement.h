#pragma once

#include <Ogre.h>
#include <feel/KeyHandler.h>

#include <base/Observer.h>

class PlayerSubject;

void updatePosition(IKEYS* inputKeys, float deltaTime, PlayerSubject* playerSub);

void updateRotation(MOUSEIN* mInput, float deltaTime, PlayerSubject* playerSub);


// Observer class to subscribe to player variables
class PlayerObserver;

class PlayerSubject {

private:
	std::list<PlayerObserver*> list_observer_;
	Ogre::Vector3* pPosition = new Ogre::Vector3();
	Ogre::Quaternion* pRotation = new Ogre::Quaternion();

	Ogre::SceneNode* _playerNode;

public:

	PlayerSubject(Ogre::SceneNode* playerNode) {
		this->_playerNode = playerNode;
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

	void Attach(PlayerObserver* obr) {
		list_observer_.push_back(obr);
	}
	void Detach(PlayerObserver* obr) {
		list_observer_.remove(obr);
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

class PlayerObserver  {

private:

	PlayerSubject& _subject;
	Ogre::Vector3* pPosition;
	Ogre::Quaternion* pRotation;

public:

	PlayerObserver(PlayerSubject& subject) : _subject(subject) {
		this->_subject = subject;
		subject.Attach(this);
	}

	void update(Ogre::Vector3* pos, Ogre::Quaternion* rot)  {
		this->pPosition = pos;
		this->pRotation = rot;
	}

};