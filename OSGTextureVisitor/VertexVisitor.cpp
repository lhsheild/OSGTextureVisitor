#include "VertexVisitor.h"

VertexVisitor::VertexVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
	//顶点数据
	extracted_verts = new osg::Vec3Array();
}

void VertexVisitor::apply(osg::Geode& geode) {
	//遍历所有drawable
	for (int i = 0; i < geode.getNumDrawables(); i++)
	{
		//获取几何体
		osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));
		if (!geom)
		{
			std::cout << "几何体错误" << std::endl;

			continue;
		}
		//获取顶点数组
		osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
		if (!verts)
		{
			std::cout << "顶点数组错误" << std::endl;

			continue;
		}
		//保存数组
		extracted_verts->insert(extracted_verts->end(), verts->begin(), verts->end());
	}
}