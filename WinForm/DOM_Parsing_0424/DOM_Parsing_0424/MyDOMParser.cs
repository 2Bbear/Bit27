using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
/// <summary>
/// 
/// 아직 Attirubut 수정하는 코드 만들지 못했음
/// </summary>
namespace DOM_Parsing_0424
{
    class MyDOMParser
    {

        static XmlDocument currentdoc=null;

        static MyDOMParser()
        {
            
        }
      

        #region Method
        //Make New Default XmlDocument Method
        public static void MakeXmlDocument(String path)
        {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml("<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
                        "<books>" +
                        "<book>" +
                        "<title> ADO.NET </title>" +
                        "</book>" +
                        "</books>");

            doc.Save("data.xml");
        }
        //Make New XmlDocument add Node, delete Nod Method
        public static void MakeXmlDonumentAddNodeAttribute(String path)
        {
            XmlDocument doc = new XmlDocument();
            /**
             * AppendChild(object) 는 object를 붙이겠다는 의미
             * 
             * 구조
             * Document
             * l
             * DocumentElement
             * l
             * Attributes
             * 
             * 
             */
            //header 추가
            XmlDeclaration xmldecl;
            xmldecl = doc.CreateXmlDeclaration("1.0", null, null);
            doc.InsertBefore(xmldecl, doc.DocumentElement);
            //comment 추가
            XmlComment comment;
            comment = doc.CreateComment("XML 노드 삽입 ");
            doc.AppendChild(comment); 


            //Element root 추가
            XmlElement root = doc.CreateElement("books");
            doc.AppendChild(root); // 문서 최 상단에 Element를 붙이는 메소드
            //Element Attribute 추가
            XmlElement elem = doc.CreateElement("book"); // Element 하위의 Element를 붙이는 메소드
            elem.InnerText = "XML.NET";
            doc.DocumentElement.AppendChild(elem);
            elem.SetAttribute("price", "12000");

            XmlElement elem2 = doc.CreateElement("book2"); // Element 하위의 Element를 붙이는 메소드
            elem2.InnerText = "ADD XML.NET";
            doc.DocumentElement.AppendChild(elem2);
            elem2.SetAttribute("price", "12000");

            //특성 추가
            XmlAttribute attr = doc.CreateAttribute("count");
            attr.Value = "50";
            elem.Attributes.Append(attr);
            
            //save
            doc.Save("data.xml");
            Console.WriteLine();
        }
        //Load XmlDocument
        public static void LoadXmlDocument(String path)
        {
            currentdoc = new XmlDocument();
            currentdoc.Load(path);
            
        }
        //Print XmlDcument
        public static String PrintCurrentXmlDocument()
        {
            string result = "root : " + currentdoc.DocumentElement.Name + "\r\n";
            foreach (XmlNode temp in currentdoc.DocumentElement.ChildNodes)
            {
                result += "childe : " + temp.Name;
                foreach (XmlAttribute t in temp.Attributes)
                {
                    result += " "+t.Name + " : " + t.Value+" ";
                }
                result += "\r\n";
            }

            return result;
        }

        //Add New Element Node
        public static void AddNode(String path,String nodename,String contentstr)
        {
            currentdoc = new XmlDocument();
            currentdoc.Load(path);

            if (currentdoc.DocumentElement.Name!=null)
            {
                //Element Attribute 추가
                XmlElement elem = currentdoc.CreateElement(nodename); // Element 하위의 Element를 붙이는 메소드
                elem.InnerText = contentstr;
                currentdoc.DocumentElement.AppendChild(elem);
                elem.SetAttribute("price", "12000");
                currentdoc.Save(path);
            }
            else
            {
                throw new Exception("현재 XML파일이 선택되지 않았습니다.");
            }
        }

        //Delete Element Node
        public static void DeleteNode(String path, string nodename)
        {
            currentdoc = new XmlDocument();
            currentdoc.Load(path);
            if (currentdoc.DocumentElement.Name != null)
            {
                int size = currentdoc.DocumentElement.ChildNodes.Count;
                for (int i = size - 1; i >= 0; i--)
                {
                    if(currentdoc.DocumentElement.ChildNodes[i].Name.Equals(nodename))
                    {
                        currentdoc.DocumentElement.RemoveChild(currentdoc.DocumentElement.ChildNodes[i]);
                    }
                    

                }


                //foreach (XmlNode temp in currentdoc.DocumentElement.ChildNodes)
                //{
                //    if (temp.Name.Equals(nodename))
                //    {
                //        currentdoc.DocumentElement.RemoveChild(temp);
                //    }

                //}

                currentdoc.Save(path);
            }
            else
            {
                throw new Exception("현재 XML파일이 선택되지 않았습니다.");
            }

        }
        
        //Set Node Attribute
        public static void ChangeNodeAttribute(String path, string nodename,string _value)
        {
            currentdoc = new XmlDocument();
            currentdoc.Load(path);
            if (currentdoc.DocumentElement.Name != null)
            {
                int size = currentdoc.DocumentElement.ChildNodes.Count;
                for (int i = size - 1; i >= 0; i--)
                {
                    if (currentdoc.DocumentElement.ChildNodes[i].Name.Equals(nodename))
                    {
                        //특성 값 변경
                        //currentdoc.DocumentElement.ChildNodes[i].Attributes[0].InsertAfter(currentdoc.CreateAttribute("FuckU"), currentdoc.DocumentElement.ChildNodes[i].Attributes[0]);
                       
                        currentdoc.DocumentElement.ChildNodes[i].Attributes[0].Value = _value;
                    }


                }
                currentdoc.Save(path);
            }
            else
            {
                throw new Exception("현재 XML파일이 선택되지 않았습니다.");
            }
        }
        #endregion
    }
}
