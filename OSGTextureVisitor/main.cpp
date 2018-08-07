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

	//���ù����ռ�
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

	//��ȡ�����ļ�
	OSGSelectFiles osgSelect;
	//��ȡĿ¼�ļ���Ϣ
	QFileInfoList osgbFileInfo = osgSelect.GetFileList(path);
	QStringList selectedOSGBFiles = osgSelect.SelectFileList(osgbFileInfo, LOD);
	QFileInfoList selectedOSGBFileInfo = osgSelect._selectedOSGBFileInfo;
	//ʵ����Viewer
    osg::ref_ptr<osgViewer::Viewer> view = new osgViewer::Viewer();
	//�������ڵ�
	osg::ref_ptr<osg::Group> root = new osg::Group();
	
	
	//����ģ��
	for each (QString filename in selectedOSGBFiles)
	{
		std::string qxfilename = filename.toStdString();
		/*std::cout << qxfilename << endl;*/
		root->addChild(osgDB::readNodeFile(qxfilename));
	}

	//�����������������������������
	TextureVisitor tv; VertexVisitor vv;
	root->accept(tv); root->accept(vv);
	//���������
	std::fstream vvfout("vv.txt");
	std::fstream tvfout("tv.txt");
	//��ȡ������
	int size_t = vv.extracted_verts->size();
	//��ʼ�����������
	std::vector<osg::Vec3>::iterator vviter = vv.extracted_verts->begin();
	//д�붥���ļ�
	for (int i = 0; i < size_t; i++)
	{
		vvfout << vviter->x() << "	" << vviter->y() << "	" << vviter->z() << std::endl;
		vviter++;
	}

	//��ͼӳ���
	std::map<std::string, osg::Image*>imageList = tv.getImages();
	//��ͼӳ��������
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

	//�Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	//view->setSceneData(root.get());
	view->setSceneData(osgDB::readNodeFile(savePath.toStdString() + saveName.toStdString()));
	view->setUpViewInWindow(800, 300, 1920, 1080);
	view->realize();
	view->run();
	return a.exec();
}
