#include "memento_writer.h"

using namespace wmdf;


void XMLMementoWriter::ProcessMemento(Memento *pm, TiXmlElement *pNode, TiXmlDocument& doc)
{

	// 1.����(��)���
	TiXmlElement *NodeElement = new TiXmlElement(pm->GetName().c_str());
	
	if (pNode==NULL)//��Ӹ��ڵ�
	{
		doc.LinkEndChild(NodeElement);
	}
	else
	{
		pNode->LinkEndChild(NodeElement);
	}
	//
	//if (RootElement)
	//{
	//	RootElement->LinkEndChild(NodeElement);
	//}else
	//{
	//	doc.LinkEndChild(NodeElement);
	//}

	// 2.ѭ������������Ϣ
	int i = 0;
	for(i = 0; i< pm->GetAttributeCount(); i++)
	{
		string str = pm->GetAttributeName(i);
		NodeElement->SetAttribute(pm->GetAttributeName(i).c_str(),pm->GetAttributeValue(i).c_str());
	}

	// 3.�ݹ����ChildMemento����
	for(i = 0; i< pm->GetChildCount(); i++)
	{
		Memento *pChildMemento = pm->GetChild(i);
		ProcessMemento(pChildMemento,NodeElement,doc);
	}
}
void XMLMementoWriter::Write(Memento *pm, char *path)
{
	TiXmlDocument doc;
	Write(pm,doc);
	doc.SaveFile(path);
}

char* XMLMementoWriter::WriteToBuf(Memento *pm) 
{
	TiXmlDocument doc;
	Write(pm,doc);
  string s ;
  s << doc;
  return (char*)s.c_str();
}

void XMLMementoWriter::Write(Memento *pm, TiXmlDocument& doc)
{
	ProcessMemento(pm,NULL,doc);
}

std::string wmdf::XMLMementoWriter::WriteToString( Memento *pm )
{
  TiXmlDocument doc;
  Write(pm,doc);
  string s ;
  s << doc;
  return s;
}
