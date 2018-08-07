#pragma once
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/NodeVisitor>
#include<osgDB/ReadFile>
#include<osgDB/WriteFile>
#include <fstream>
#include <iostream>

class VertexVisitor :public osg::NodeVisitor {
public:
	osg::ref_ptr<osg::Vec3Array> extracted_verts;
	VertexVisitor();
	virtual void apply(osg::Geode& geode);
};