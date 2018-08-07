#include "FindNodeVisitor.h"

FindNodeVisitor::FindNodeVisitor(const std::string &searchName) :osg::NodeVisitor(TRAVERSE_ALL_CHILDREN), searchForName(searchName) {

}
