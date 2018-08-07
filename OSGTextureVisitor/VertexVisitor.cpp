#include "VertexVisitor.h"

VertexVisitor::VertexVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
	//��������
	extracted_verts = new osg::Vec3Array();
}

void VertexVisitor::apply(osg::Geode& geode) {
	//��������drawable
	for (int i = 0; i < geode.getNumDrawables(); i++)
	{
		//��ȡ������
		osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));
		if (!geom)
		{
			std::cout << "���������" << std::endl;

			continue;
		}
		//��ȡ��������
		osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
		if (!verts)
		{
			std::cout << "�����������" << std::endl;

			continue;
		}
		//��������
		extracted_verts->insert(extracted_verts->end(), verts->begin(), verts->end());
	}
}