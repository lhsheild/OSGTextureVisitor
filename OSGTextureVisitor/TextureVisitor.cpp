#include"TextureVisitor.h"

using namespace osg;

TextureVisitor::TextureVisitor() :osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {

}

void TextureVisitor::apply(osg::Node& node) {
	if (node.getStateSet())
	{
		apply(node.getStateSet());
	}
	traverse(node);
}

void TextureVisitor::apply(osg::Geode& geode) {
	if (geode.getStateSet())
	{
		apply(geode.getStateSet());
	}
	int cnt = geode.getNumDrawables();
	for (int i = 0; i < cnt; i++)
	{
		apply(geode.getDrawable(i)->getStateSet());
	}
	traverse(geode);
}

void TextureVisitor::apply(osg::StateSet* state)
{
	osg::StateSet::TextureAttributeList& texAttribList = state->getTextureAttributeList();
	for (int i = 0; i < texAttribList.size(); i++)
	{
		osg::Texture2D* tex2D = NULL;
		if (tex2D = dynamic_cast<osg::Texture2D*>(state->getTextureAttribute(i,osg::StateAttribute::TEXTURE)))
		{
			if (tex2D->getImage())
			{
				_imageList.insert(std::make_pair(tex2D->getImage()->getFileName(),tex2D->getImage()));
			}
		}
	}
}

std::map<std::string, osg::Image*>& TextureVisitor::getImages(void)
{
	return _imageList;
}
