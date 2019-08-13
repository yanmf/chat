
#include"xmlManager.h"

DEFINE_SINGLETON(XmlManager);

void XmlManager::getResPath(const char* path, char* res_path)
{
	memset(res_path, 0, sizeof(res_path));
	strcat(res_path,"config/");
	strcat(res_path,path);
}

TiXmlDocument XmlManager::load(const char* path)
{
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		return NULL;
	}
	return doc;
}

TiXmlElement* XmlManager::getElements(TiXmlDocument doc, const char* name)
{
	return new TiXmlElement(*doc.FirstChildElement(name));
}

TiXmlElement* XmlManager::getElementValue(TiXmlElement* ele, const char * name)
{
	TiXmlNode* node = ele->FirstChild(name);
	TiXmlElement *tiXml=new TiXmlElement(*node->ToElement()); 
	return tiXml;
}

int XmlManager::getAttributeToInt(TiXmlElement* node, const char* name)
{
	int value;
	node->QueryIntAttribute(name, &value);
	return value;
}

const char* XmlManager::getAttributeToStr(TiXmlElement* node, const char* name)
{
	return node->Attribute(name);
}

double XmlManager::getAttributeToDouble(TiXmlElement* node, const char* name)
{
	double value;
	node->QueryDoubleAttribute(name, &value);
	return value;
}
