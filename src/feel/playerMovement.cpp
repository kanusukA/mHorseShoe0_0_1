#include "playerMovement.h"

const int MOUSESENS = 200;

const float MOUSEROLLNUM = 0.9975;

const float PLAYERSPEED = 1;

double mouseX = 0.0f;
double mouseY = 0.0f;

// Rotation
double xRotW = 1.0f;
double xRotY = 0.0f;

double yRotW = 1.0f;
double yRotX = 0.0f;

Ogre::Quaternion verQ;
Ogre::Quaternion horQ;

Ogre::Math mathunDa = Ogre::Math();

void updatePosition(IKEYS* inputKeys, float deltaTime , PlayerSubject* playerSub)
{
	
	Ogre::Radian Yaxis = playerSub->getPlayerRotation().getYaw();

	double Zcos = (mathunDa.Cos(Yaxis) / PLAYERSPEED) * deltaTime;
	double XSin = (mathunDa.Sin(Yaxis) / PLAYERSPEED) * deltaTime;

	// PICASSO !!!!!!!!!!!!
	double Pitch = ((playerSub->getPlayerRotation().yAxis().x * mathunDa.Sin(Yaxis)) + (playerSub->getPlayerRotation().yAxis().z * mathunDa.Cos(Yaxis))) / PLAYERSPEED * deltaTime;


	if (inputKeys->Up_KEY) {
		playerSub->setPlayerPosition(
			playerSub->getPlayerPosition() + Ogre::Vector3(-XSin, Pitch, -Zcos)
		);
	}

	else if (inputKeys->Down_KEY) {
		playerSub->setPlayerPosition(
			playerSub->getPlayerPosition() + Ogre::Vector3(XSin, -Pitch, Zcos)
		);
	}

	if (inputKeys->Left_KEY) {
		playerSub->setPlayerPosition(
			playerSub->getPlayerPosition() + Ogre::Vector3(Zcos, 0, -XSin)
		);
	}

	else if (inputKeys->Right_KEY) {
		playerSub->setPlayerPosition(
			playerSub->getPlayerPosition() + Ogre::Vector3(-Zcos, 0, XSin)
		);
	}

}

void updateRotation(MOUSEIN* mInput, float deltaTime, PlayerSubject* playerSub)
{

	if (mInput->MouseXrel != 0 || mInput->MouseYrel != 0) {

		mouseX -= (mInput->MouseXrel / MOUSESENS) * deltaTime;
		mouseY -= (mInput->MouseYrel / MOUSESENS) * deltaTime;

		//RollOver
		if (mouseX <= -1) {
			mouseX = MOUSEROLLNUM;
		}
		else if (mouseX >= 1) {
			mouseX = -MOUSEROLLNUM;
		}

		if (mouseY <= -1) {
			mouseY = MOUSEROLLNUM;
		}

		else if (mouseY >= 1) {
			mouseY = -MOUSEROLLNUM;
		}


		if (mouseX > 0) {
			xRotW = 1 - ((mouseX) * 2);
		}
		else {
			xRotW = -(1 + ((mouseX) * 2));
		}

		if (mouseY > 0) {
			yRotW = 1 - ((mouseY) * 2);
		}
		else {
			yRotW = -(1 + ((mouseY) * 2));
		}

		xRotY = 1 - Ogre::Math::Abs(xRotW);
		yRotX = 1 - Ogre::Math::Abs(yRotW);

		verQ = Ogre::Quaternion(yRotW, yRotX, 0, 0);
		horQ = Ogre::Quaternion(xRotW, 0, xRotY, 0);

		verQ.normalise();
		horQ.normalise();

		playerSub->setPlayerRotation(horQ * verQ);

	}
}
