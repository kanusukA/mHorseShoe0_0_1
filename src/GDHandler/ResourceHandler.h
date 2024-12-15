#pragma once

#include <mutex>
#include <fstream>
#include <iostream>
#include <string>

#include <filesystem>
#include <list>

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

// Integrate it into gdhandler with Ogre 

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
	std::filesystem::path find(std::string filepath, ResourceHandlerType type);


	// Hide the constructor and destructor of the class
protected:
	ResourceHandler() {};
	~ResourceHandler() {};


public:

	// Resources
	// RenderMeshes
	// OPTIMIZE THIS !!!!!!
	//  Can be changed to an Observable state in future for regulation of use
	std::vector<std::string>* renderMeshes = new std::vector<std::string>();
	std::vector<std::string>* colliderMeshes = new std::vector<std::string>();

	// Class should not be clonable
	ResourceHandler(ResourceHandler& copy) = delete;

	// Class should not be assignable
	void operator=(const ResourceHandler&) = delete;

	void readFile(std::string filename);

	std::string getResourceFile(std::string fileName, ResourceHandlerType type);


	// Only way to initalize the class
	static ResourceHandler* GetInstance();

};






// Exceptions
class ResourceHandlerDefaultLocNotFound : public std::exception {

public:
	char* what() {
		std::cout << std::endl << "Default Resouce Location File Was Not Found.";
	}

};
class ResourceHandlerFileNotFound : public std::exception {

public:
	char* what() {
		std::cout << std::endl << "File does not exsist in context.";
	}

};

