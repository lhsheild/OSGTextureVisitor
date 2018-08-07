#pragma once

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

class FindNodeVisitor :public osg::NodeVisitor {
public:
	FindNodeVisitor(const std::string &searchName);

	virtual void apply(osg::Node &searchNode);
	virtual void apply(osg::Geode &geode);
	virtual void apply(osg::Transform &searchNode);

	void setNameToFind(const std::string &searchNode);
	osg::Node* getFirst();
	typedef std::vector<osg::Node*> nodeListType;
	nodeListType& getNodeList() {
		return foundNodeList;
	}
private:
	std::string searchForName;
	nodeListType foundNodeList;
};