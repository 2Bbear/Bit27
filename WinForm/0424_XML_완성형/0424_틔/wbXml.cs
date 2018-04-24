using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _0424_틔
{
    public class Item
    {
        public string Title { get; private set; }
        public string Link { get; private set; }
        public string Date { get; private set; }
        public string Author { get; private set; }
        public string Description { get; private set; }
       
        public static Item MakeItem(XmlReader xr) 
        {
            string title = string.Empty;
            string link = string.Empty;
            string Date = string.Empty;
            string Author = string.Empty;
            string Description = string.Empty;
            

            xr.ReadToDescendant("title"); 
            title = xr.ReadElementString("title");

            xr.ReadToNextSibling("link");
            link = xr.ReadElementString("link");

            xr.ReadToNextSibling("description");
            Description = xr.ReadElementString("description");

            xr.ReadToNextSibling("author");
            Author = xr.ReadElementString("author");

            xr.ReadToNextSibling("pubDate");
            Date = xr.ReadElementString("pubDate");

            

            return new Item(title, link, Date, Author, Description); 
        }   

        public Item(string title, string link, string date, string author, string desc)
        {
            Title = title;
            Link = link;
            Date = date;
            Author = author;

            string[] filter = desc.Split('"');
            

            bool a = false;
            for (int i = 0; i < filter.Length; i++)
            {
                if (filter[i].Contains("jpg"))
                {
                    a = true;
                }
            }

            if (a == true)           //사진경로에 jpg가 있으면 (경로가있으면)
            {
                Description = filter[1];
            }
            else
            {
                //경로가 없으면

                Description = "C:\\Users\\user\\Desktop\\zwi.jpg";
            }
        }
        public override string ToString()
        {
            return Title;
        }
    }

    class NodeType
    {
        public XmlNodeType NodeType2
        {
            get;
            set;
        }
        public string Name
        {
            get;
            set;
        }
        public string Value
        {
            get;
            set;
        }

        public NodeType(XmlNodeType nodetype, string name, string value)
        {
            NodeType2 = nodetype;
            Name = name;
            Value = value;
        }

        public override string ToString()
        {
            return NodeType2 + "," + Name + "," + Value;
        }
    }

    class wbXml
    {
        public static void Writer(string pathname)
        {
            XmlWriterSettings settings = new XmlWriterSettings(); 
            settings.Indent = true; 
            XmlWriter writer = XmlWriter.Create("data.xml", settings);

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
            writer.WriteElementString("title","ADO.NET");//title 요소와 값 쓰기     
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
            XmlWriter xwriter = XmlWriter.Create(br);
            //XmlWriter xwriter = XmlWriter.Create(Console.Out); //콘솔 출력 스트림으로 XmlWriter 개체 생성       
            xwriter.WriteNode(xreader, false); //xreader 개체로 읽어온 데이터를 xwriter 개체에 복사      
            xwriter.Close();      
            xreader.Close();

            return br;
        }

        public static void Writer2(string pathname)
        {
            XmlWriterSettings settings = new XmlWriterSettings(); 
            settings.Indent = true; 
            XmlWriter writer = XmlWriter.Create("data2.xml", settings); 
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

         public static StringBuilder Reader2(string pathname)
        {
            XmlReader xreader = XmlReader.Create(pathname); //XmlReader 개체 생성 
            StringBuilder br = new StringBuilder();
            XmlWriter xwriter = XmlWriter.Create(br);
            //XmlWriter xwriter = XmlWriter.Create(Console.Out,settings); //XmlWriter 개체 생성     
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
         public static StringBuilder RssReader(string path)
         {
            //==========================================
            XmlUrlResolver resolver = new XmlUrlResolver(); 
            resolver.Credentials = System.Net.CredentialCache.DefaultCredentials;

            XmlReaderSettings settings = new XmlReaderSettings(); 
            settings.XmlResolver = resolver;

            XmlReader reader = XmlReader.Create(path, settings); 
            //==========================================
            StringBuilder br = new StringBuilder();
            XmlWriter xwriter = XmlWriter.Create(br);
            xwriter.WriteNode(reader, false);
            xwriter.Close();
            //=============================================
            reader.Close();
            
             return br;
         }

         public static List<NodeType> LoadInfo(string path)
         {
             //==========================================
             XmlUrlResolver resolver = new XmlUrlResolver();
             resolver.Credentials = System.Net.CredentialCache.DefaultCredentials;

             XmlReaderSettings settings = new XmlReaderSettings();
             settings.XmlResolver = resolver;

             XmlReader reader = XmlReader.Create(path, settings);
             //==========================================
             reader.MoveToContent();
             List<NodeType> nodeinfos = new List<NodeType>();
 
            while (reader.Read())     
            {
                NodeType info = new NodeType(reader.NodeType, reader.Name, reader.Value);
                nodeinfos.Add(info);
            } 
             reader.Close();
             return nodeinfos;
         }

         public static List<Item> NodeElementParse(string path) //가장 important함
         {
             //==========================================
             XmlUrlResolver resolver = new XmlUrlResolver();
             resolver.Credentials = System.Net.CredentialCache.DefaultCredentials;

             XmlReaderSettings settings = new XmlReaderSettings();
             settings.XmlResolver = resolver;

             XmlReader reader = XmlReader.Create(path, settings);
             //==========================================
             //reader.MoveToContent();
             List<Item> items = new List<Item>();

             while (reader.Read())
             {
                 if(reader.IsStartElement("item"))
                 {
                     Item info = Item.MakeItem(reader);
                     
                     if (info != null)
                         items.Add(info);
                 }
             }

             reader.Close();
             return items;
         }


    }
}
