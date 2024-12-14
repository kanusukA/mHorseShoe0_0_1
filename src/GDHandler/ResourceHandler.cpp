#include "ResourceHandler.h"


// Multi-Thread shit
ResourceHandler* ResourceHandler::pinstance_{ nullptr };
std::mutex ResourceHandler::mutex_;

// Insert command  implementation to execute read , write and find requests

void ResourceHandler::read()
{

}

void ResourceHandler::write()
{
}

std::filesystem::path ResourceHandler::find(std::string fileName, ResourceHandlerType type = ResourceHandlerType::GLOBAL)
{
	std::cout << "Opening file " << fileName << std::endl;

	in_stream.open(DEFAULT_LOC);
	std::string line;
	bool inGroup = type == ResourceHandlerType::GLOBAL;

	// Searching in Current Loc

	if (in_stream.is_open()) {

		// Searching in Default Resource Loc
		while (getline(in_stream, line))
		{
			// Remove invaild lines
			if (!line.empty()) {

				cout << "Searching in - " << line << endl;

				if (!inGroup) {
					switch (type)
					{
					case ResourceHandlerType::COLLIDER_MESH:
						if (line == COLLIDER_MESH_LOC)
						{
							inGroup = true;
						}
						break;
					case ResourceHandlerType::RENDER_MESH:
						if (line == RENDER_MESH_LOC) {
							inGroup = true;
						}
						break;
					default:
						break;
					}
				}
				else {
					try {
						for (const auto& entry : fs::directory_iterator(line)) {

							if (entry.path().filename().string() == fileName) {
								cout << "File found At - " << line << endl;
								return entry.path();
							}
						}
					}
					catch (const std::exception& e) {
						if (type != ResourceHandlerType::GLOBAL) {
							throw ResourceHandlerFileNotFound();
						}
					}
				}

			}

		}
		throw ResourceHandlerFileNotFound();

	}
	else {

		throw ResourceHandlerDefaultLocNotFound();

	}


	in_stream.close();
}

string ResourceHandler::getResourceFile(string fileName, ResourceHandlerType type)
{
	filesystem::path filePath;

	try
	{
		filePath = this->find(fileName, type);
	}
	catch (const std::exception&)
	{
		cout << "Resource File Not Found !";
		return;
	}
	switch (type)
	{
	case GLOBAL:
		break;
	case RENDER_MESH:
		this->renderMeshes->push_back(filePath.string());
		break;
	case COLLIDER_MESH:
		this->colliderMeshes->push_back(filePath.string());
		break;
	default:
		break;
	}
	return filePath.string();
}




void ResourceHandler::readFile(std::string filename)
{
	this->find(filename);
}



ResourceHandler* ResourceHandler::GetInstance() {

	// locks storage 
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr) {
		pinstance_ = new ResourceHandler();
	}
	return pinstance_;

}
