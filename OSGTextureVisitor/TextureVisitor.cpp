#include"TextureVisitor.h"

using namespace osg;

TextureVisitor::TextureVisitor() :osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN) {

}

void apply(osg::Node& node) {
	if (node.getStateSet())
	{
		//apply(node.getStateSet());

	}
	TextureVisitor::TextureVisitor().traverse(node);
}