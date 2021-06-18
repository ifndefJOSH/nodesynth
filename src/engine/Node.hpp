/**
 * Node class for each node in the backend.
 * */
#ifndef NODE_CPP_
#define NODE_CPP_

#include <string>
#include <iostream>

class Node {
public:
	virtual Node(std::string name);
	virtual ~Node();
	/**
	 * Sets the name of the Node
	 * 
	 * @param name The name to set
	 * */
	void setName(std::string name) {
		this->name = name;
	}
	/**
	 * Gets the name for the Node
	 * 
	 * @return The name of the node.
	 * */
	std::string getName() {
		return this->name;
	}
protected:
	
private:
	std::string name;
}


#endif /* NODE_CPP_ */
