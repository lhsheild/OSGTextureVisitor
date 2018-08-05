#include <QtCore/QCoreApplication>
#include <osgDB/readfile>
#include <osgDB/writefile>
#include <osgViewer/Viewer>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
    osg::ref_ptr<osgViewer::Viewer> view = new osgViewer::Viewer();
	view->setSceneData(osgDB::readNodeFile("cow.osg"));
	view->setUpViewInWindow(800, 300, 1920, 1080);
	view->realize();
	view->run();
	return a.exec();
}
