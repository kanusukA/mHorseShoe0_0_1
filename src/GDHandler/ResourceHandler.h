#pragma once

#include <mutex>
#include <fstream>
#include <iostream>
#include <string>

#include <filesystem>
#include <list>

#include <base/Observer.h>

using namespace std;
namespace fs = std::filesystem;


#define DEFAULT_LOC "resource_handler_def_loc.txt"
#define RENDER_MESH_LOC "Render_Mesh"
#define COLLIDER_MESH_LOC "Collider_Mesh"


// Types of resources
enum ResourceHandlerType
{
	GLOBAL,
	RENDER_MESH,
	COLLIDER_MESH
};


class ResourceHandler
{

private:
	// Multi-Thread Shit
	static ResourceHandler* pinstance_;
	static std::mutex mutex_;

	std::ofstream out_stream;
	std::ifstream in_stream;
	std::fstream f_stream;

	// default locations


	void read();
	void write();
	filesystem::path find(std::string filepath, ResourceHandlerType type);


	// Hide the constructor and destructor of the class
protected:
	ResourceHandler() {};
	~ResourceHandler() {};


public:

	// Resources
	// RenderMeshes
	// OPTIMIZE THIS !!!!!!
	//  Can be changed to an Observable state in future for regulation of use
	std::vector<string>* renderMeshes = new vector<string>();
	std::vector<string>* colliderMeshes = new vector<string>();

	// Class should not be clonable
	ResourceHandler(ResourceHandler& copy) = delete;

	// Class should not be assignable
	void operator=(const ResourceHandler&) = delete;

	void readFile(std::string filename);

	std::string getResourceFile(string fileName, ResourceHandlerType type);


	// Only way to initalize the class
	static ResourceHandler* GetInstance();

};


// Not Used in current version. can be implemented in future to regulate Resource usage
class ResourcehandlerObserver : public Observer {

};

class ResourceHandlerSubject : public Subject {

private:
	std::list<Observer*> list_observer_;
	

public:

	void Attach(Observer* obr) override {
		list_observer_.push_back(obr);
	}
	void Detach(Observer* obr) override {
		list_observer_.remove(obr);
	}

	void Notify() override {

	}

};



// Exceptions
class ResourceHandlerDefaultLocNotFound : public exception {

public:
	char* what() {
		cout << endl << "Default Resouce Location File Was Not Found.";
	}

};
class ResourceHandlerFileNotFound : public exception {

public:
	char* what() {
		cout << endl << "File does not exsist in context.";
	}

};

