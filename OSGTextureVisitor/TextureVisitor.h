#pragma once

#include<osg/Node>
#include<osg/Geode>
#include<osg/Group>
#include<osg/NodeVisitor>
#include<osgDB/ReadFile>
#include<osgDB/WriteFile>
#include <osg/Texture2D>
#include <fstream>
#include <iostream>

class TextureVisitor:public osg::NodeVisitor {
public:
	TextureVisitor();
	virtual void apply(osg::Node& node);
	virtual void apply(osg::Geode& geode);
	virtual void apply(osg::StateSet* state);
	std::map<std::string, osg::Image*>& getImages(void);
protected:
	std::map<std::string, osg::Image*> _imageList;
};