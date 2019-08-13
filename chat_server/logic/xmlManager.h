
#ifndef _XML_MGR_H
#define _XML_MGR_H

#include "../tinyxml/tinyxml.h"
#include "../define.h"
using namespace std;

class XmlManager
{
	DECLARE_SINGLETON(XmlManager);

	public:
	void getResPath(const char*, char *);//获取配置地址
	TiXmlDocument load(const char*);//加载xml文件
	TiXmlElement* getElements(TiXmlDocument,const char*);//获取节点所有属性
	TiXmlElement* getElementValue(TiXmlElement*, const char*);
	int getAttributeToInt(TiXmlElement*, const char*);
	const char* getAttributeToStr(TiXmlElement*, const char*);
	double getAttributeToDouble(TiXmlElement*, const char*);

};

#define XML_MANAGER XmlManager::instance() 

#endif
