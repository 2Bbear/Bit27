using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _0424_XML
{
    class NodeTypeInfo
    {
        public XmlNodeType NodeType { get; set; }
        public string Name { get; set; }
        public string Value { get; set; }
        

        public NodeTypeInfo(XmlNodeType nodetype, string name, string value)
        {
            NodeType = nodetype;
            Name = name;
            Value = value;
        }

        public override string ToString()
        {
            return NodeType + ", " + Name + ", " + Value;
        }
    }
    
    class Item
    {
        public string Title { get; private set; }

        public string link { get; private set; }

        public Item(string _title, string _link)
        {
            Title = _title;
            link = _link;
        }
        public static Item MakeItem(XmlReader xr)
        {
            string title = string.Empty;
            string link = string.Empty;

            xr.ReadToDescendant("title");
            title = xr.ReadElementString("title");


            //xr.ReadToNextSibling("link");
            //xr.ReadStartElement("link");
            //link = xr.Value;

            //xr.ReadToNextSibling("description");
            //xr.ReadStartElement("description");
            //string[] str = xr.ToString().Split('"');

            //link = str[1];

            xr.ReadToNextSibling("description");
            //xr.ReadStartElement("description");
            string ssr = xr.ReadElementString("description");

            string [] ssr2=ssr.Split('"');
            link = ssr2[1];
            return new Item(title, link);
        }

        public override string ToString()
        {
            return Title;
        }
    }

    class wbXml
    {
        public static void Writer(string pathname)
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            XmlWriter writer = XmlWriter.Create(pathname, settings);
            writer.WriteComment("XmlWriter 개체로 요소 쓰기");
            writer.WriteStartElement("books"); //루트 요소 쓰기
            writer.WriteStartElement("book");//book 요소 쓰기
            writer.WriteStartElement("title");//title 요소 쓰기
            writer.WriteName("XML.NET");
            writer.WriteEndElement();//title 요소 닫기
            writer.WriteStartElement("가격");//가격 요소 쓰기
            writer.WriteValue(12000);
            writer.WriteEndElement();//가격 요소 닫기
            writer.WriteEndElement();//book 요소 닫기
            writer.WriteStartElement("book");//book 요소 쓰기
            writer.WriteElementString("title", "ADO.NET");//title 요소와 값 쓰기
            writer.WriteStartElement("가격");//가격 요소 쓰기
            writer.WriteValue(15000);
            writer.WriteEndElement();//가격 요소 닫기
            writer.WriteEndElement();//book 요소 닫기
            writer.WriteEndElement();//루트 요소 닫기
            writer.Close();
        }

        public static StringBuilder Reader(string pathname)
        {
            XmlReader xreader = XmlReader.Create(pathname); //XmlReader 개체 생성
            StringBuilder br = new StringBuilder();
            XmlWriter xwriter = XmlWriter.Create(br); //콘솔 출력 스트림으로 XmlWriter 개체 생성
            xwriter.WriteNode(xreader, false); //xreader 개체로 읽어온 데이터를 xwriter 개체에 복사
            xwriter.Close();
            xreader.Close();

            return br;
        }

        public static void WriterAttribute(string pathname)
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            XmlWriter writer = XmlWriter.Create(pathname, settings);
            writer.WriteComment("XmlWriter 개체로 특성 쓰기");
            writer.WriteStartElement("books"); //루트 요소 쓰기
            writer.WriteStartElement("book");//book 요소 쓰기
            writer.WriteStartAttribute("title"); //title 특성 쓰기
            writer.WriteString("XML.NET"); //title 특성 값 쓰기
            writer.WriteEndAttribute(); //title 특성 닫기
            writer.WriteStartAttribute("가격");//가격 특성 쓰기

            writer.WriteValue(12000); //가격 특성 값 쓰기
            writer.WriteEndAttribute(); //가격 특성 닫기
            writer.WriteEndElement(); //book 요소 닫기
            writer.WriteStartElement("book");//book 요소 쓰기
            writer.WriteAttributeString("title", "ADO.NET");//title 특성과 값 쓰기
            writer.WriteStartAttribute("가격");//가격 특성 쓰기
            writer.WriteValue(15000);//가격 특성 값 쓰기
            writer.WriteEndAttribute();//가격 특성 닫기
            writer.WriteEndElement();//book 요소 닫기
            writer.WriteEndElement();//루트 요소 닫기
            writer.Close();
        }

        public static StringBuilder ReaderAttribute(string pathname)
        {
            XmlReader xreader = XmlReader.Create(pathname); //XmlReader 개체 생성
            StringBuilder br = new StringBuilder();
            XmlWriter xwriter = XmlWriter.Create(br); //XmlWriter 개체 생성
            while (xreader.Read())
            {
                if (xreader.NodeType == XmlNodeType.Element)
                {
                    xwriter.WriteStartElement(xreader.Name);
                    xwriter.WriteAttributes(xreader, false); //xreader의 현재 특성을 쓰기
                    if (xreader.IsEmptyElement)
                    {
                        xwriter.WriteEndElement();
                    }
                }
                else if (xreader.NodeType == XmlNodeType.EndElement)
                {
                    xwriter.WriteEndElement();
                }
            }
            xwriter.Close();
            xreader.Close();

            return br;
        }

        public static StringBuilder RssReader(string pathname)
        {
            XmlUrlResolver resolver = new XmlUrlResolver();
            resolver.Credentials = System.Net.CredentialCache.DefaultCredentials;
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.XmlResolver = resolver;
            XmlReader reader = XmlReader.Create(pathname, settings);
            //=====================================
            StringBuilder br = new StringBuilder();
            XmlWriter xwriter = XmlWriter.Create(br);
            xwriter.WriteNode(reader, false);
            xwriter.Close();
            //=====================================
            reader.Close();
            return br;
        }

        public static List<NodeTypeInfo> NodeInfo(string pathname)
        {
            XmlUrlResolver resolver = new XmlUrlResolver();
            resolver.Credentials = System.Net.CredentialCache.DefaultCredentials;
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.XmlResolver = resolver;
            XmlReader reader = XmlReader.Create(pathname, settings);
            //=====================================
            List<NodeTypeInfo> nodeinfos = new List<NodeTypeInfo>();

            while (reader.Read())
            {
                NodeTypeInfo info = new NodeTypeInfo(reader.NodeType, reader.Name, reader.Value);
                nodeinfos.Add(info);
            }
            //=====================================
            reader.Close();
            return nodeinfos;
        }

        public static List<Item> NodeElementParse(string pathname)
        {
            XmlUrlResolver resolver = new XmlUrlResolver();
            resolver.Credentials = System.Net.CredentialCache.DefaultCredentials;
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.XmlResolver = resolver;
            XmlReader reader = XmlReader.Create(pathname, settings);
            //=====================================
            List<Item> items = new List<Item>();

            while (reader.Read())
            {
                if (reader.IsStartElement("item"))
                {
                    Item item = Item.MakeItem(reader);
                    if (item != null) { items.Add(item); }
                }
            }
            //=====================================
            reader.Close();
            return items;
        }
    }
}
