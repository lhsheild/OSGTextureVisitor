#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <qdir.h>
#include <qdebug.h>
#include <qtextstream.h>

class OSGSelectFiles
{
public:
	QFileInfoList GetFileList(QString path);
	QStringList SelectFileList(QFileInfoList file_info_list,QString LOD);
	QStringList _osgbFileList;
	QFileInfoList _selectedOSGBFileInfo;
};

