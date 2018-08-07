#include <QtCore/QCoreApplication>
#include "TextureVisitor.h"
#include "VertexVisitor.h"
#include "OSGSelectFiles.h"

#include <osgDB/readfile>
#include <osgDB/writefile>
#include <osgViewer/Viewer>
#include <osgUtil/Optimizer>

#include <fstream>
#include<iostream>
#include <io.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//设置工作空间
	QTextStream qin(stdin);
	QTextStream qout(stdout);
	QString path; QString savePath; QString LOD; QString saveName;

	qout << "Please input the filepath of Data" << endl;
	qin >> path;
	/*qout << path << endl;*/

	qout << "Please input the filepath of Saving OBJ data" << endl;
	qin >> savePath;
	//qout << savePath << endl;

	qout << "Please input the level of details you want" << endl;
	qin >> LOD;
	//qout << LOD << endl;

	qout << "Please input the savename of Saving OBJ data" << endl;
	qin >> saveName;

	//获取所需文件
	OSGSelectFiles osgSelect;
	//获取目录文件信息
	QFileInfoList osgbFileInfo = osgSelect.GetFileList(path);
	QStringList selectedOSGBFiles = osgSelect.SelectFileList(osgbFileInfo, LOD);
	QFileInfoList selectedOSGBFileInfo = osgSelect._selectedOSGBFileInfo;
	//实例化Viewer
    osg::ref_ptr<osgViewer::Viewer> view = new osgViewer::Viewer();
	//创建根节点
	osg::ref_ptr<osg::Group> root = new osg::Group();
	
	
	//载入模型
	for each (QString filename in selectedOSGBFiles)
	{
		std::string qxfilename = filename.toStdString();
		/*std::cout << qxfilename << endl;*/
		root->addChild(osgDB::readNodeFile(qxfilename));
	}

	//创建纹理、顶点访问器并启动访问器
	TextureVisitor tv; VertexVisitor vv;
	root->accept(tv); root->accept(vv);
	//申请输出流
	std::fstream vvfout("vv.txt");
	std::fstream tvfout("tv.txt");
	//获取顶点数
	int size_t = vv.extracted_verts->size();
	//初始化顶点迭代器
	std::vector<osg::Vec3>::iterator vviter = vv.extracted_verts->begin();
	//写入顶点文件
	for (int i = 0; i < size_t; i++)
	{
		vvfout << vviter->x() << "	" << vviter->y() << "	" << vviter->z() << std::endl;
		vviter++;
	}

	//贴图映射表
	std::map<std::string, osg::Image*>imageList = tv.getImages();
	//贴图映射表迭代器
	std::map<std::string, osg::Image*>::iterator iter = imageList.begin();
	unsigned int cnt = 0; char* buffer = new char[2000];
	
	for (int i=0;iter != imageList.end(); iter++)
	{
		//std::string stringName= selectedOSGBFiles.at(i).toStdString();
		QByteArray cpath = selectedOSGBFileInfo.at(i).fileName().toLocal8Bit();
		char* charName = cpath.data();

		//QString textureName = QString::fromStdString(iter->first);
		//sprintf(buffer, "Tile_+122_-045_L19%d.jpg", cnt++);
		osgDB::writeImageFile(*(iter->second), savePath.toStdString() +iter->first);
		i++;
		//sprintf(buffer, charName, cnt++);
		//osgDB::writeImageFile(*(iter->second), selectedOSGBFiles.at(i).toStdString());
		tvfout << iter->second << std::endl;		
	}

	osgDB::writeNodeFile(*root.get(), savePath.toStdString()+saveName.toStdString());

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	//view->setSceneData(root.get());
	view->setSceneData(osgDB::readNodeFile(savePath.toStdString() + saveName.toStdString()));
	view->setUpViewInWindow(800, 300, 1920, 1080);
	view->realize();
	view->run();
	return a.exec();
}
