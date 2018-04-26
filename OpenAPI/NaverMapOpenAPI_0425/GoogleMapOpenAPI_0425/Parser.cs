using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace GoogleMapOpenAPI_0425
{
    class Item
    {
        public static List<Item> itemlist = new List<Item>();

        public String address;
        public double x;
        public double y;

        public Item(string address, double x, double y)
        {
            this.address = address;
            this.x = x;
            this.y = y;
        }
    }
    class Parser
    {
        //public static List<Item> itemlist=new List<Item>();
        static XmlDocument currentdoc = new XmlDocument();

        #region Method
        //Save Xml
        public static void SaveXml(String path, String xmlStrData)
        {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(xmlStrData);
            doc.Save(path);

        }
        //Load Xml
        public static void LoadXml(String path)
        {
            XmlDocument doc = new XmlDocument();
            currentdoc.Load(path);

        }
        //GetPosition
        public static double[] GetPosition()
        {
            double x=0;
            double y=0;
            XmlNodeList posi = currentdoc.GetElementsByTagName("point");
            x = double.Parse(posi[0].Value);


            return new double[] {x,y };
        }
        //Make Item List
        public static void MakeItemList()
        {
            Item.itemlist.Clear();
            string resutl=string.Empty;
            String _address=String.Empty;
            double _x = 0;
            double _y = 0;

            XmlNodeList tem = currentdoc.GetElementsByTagName("items");
            XmlNode items = tem.Item(0);

            //Item들 할당
            foreach (XmlNode t in items.ChildNodes)
            {
                //Address 할당
                _address = t.FirstChild.FirstChild.Value;
                //position 할당
                _x = double.Parse(t.LastChild.FirstChild.InnerText);
                _y = double.Parse(t.LastChild.LastChild.InnerText);

                Item.itemlist.Add(new Item(_address, _y,_x));
            }
           
        }
        //Get Item List
        public static double [] GetItemXYt(XmlDocument taget)
        {

            double _x;
            double _y;

            XmlNodeList tem = taget.GetElementsByTagName("items");
            XmlNode items = tem.Item(0);
            _x = double.Parse(items.FirstChild.LastChild.FirstChild.InnerText);
            _y = double.Parse(items.FirstChild.LastChild.LastChild.InnerText);

            return new double[] { _x, _y };

        }
        public static void MakeItemList2()
        {
            Item.itemlist.Clear();
            string resutl = string.Empty;
            String _address = String.Empty;
            double _x = 0;
            double _y = 0;

            XmlNodeList tem = currentdoc.GetElementsByTagName("channel");
            XmlNode channel = tem.Item(0);
            String d;
            //Item들 할당
            foreach (XmlNode t in channel.ChildNodes)
            {
                //Address 할당
               if(t.Name.Equals("item")==true)
                {
                   d= t.ChildNodes[6].InnerText;
                    String xmlstr=APIExamTranslate.Start(d);
                    XmlDocument tempxml = new XmlDocument();
                    tempxml.LoadXml(xmlstr);
                    tempxml.Save("GlobalLocalPosition.xml");
                    tempxml.Load("GlobalLocalPosition.xml");
                    _x=GetItemXYt(tempxml)[0];
                    _y = GetItemXYt(tempxml)[1];

                    Item.itemlist.Add(new Item(_address, _y, _x));
                }
                //position 할당

               
            }

        }
        //xml수정


        #endregion
    }
}
