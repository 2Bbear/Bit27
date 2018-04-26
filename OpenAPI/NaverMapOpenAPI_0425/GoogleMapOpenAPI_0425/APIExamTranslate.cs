using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Net;

using System.IO;

namespace GoogleMapOpenAPI_0425
{
    
    class APIExamTranslate
    {
        
        public static string Start(String target)
        {
            string query = target; // 검색할 주소
            //string url = "https://openapi.naver.com/v1/map/geocode?query=" + query; // 결과가 JSON 포맷
            string url = "https://openapi.naver.com/v1/map/geocode.xml?query=" + query;  // 결과가 XML 포맷
            //string url = "https://map.naver.com/?query=" + query;
            //strimg url ="https://openapi.naver.com/v1/map/staticmap.bin?query="+query // 결과가 jpg
            //string url = "https://openapi.naver.com/v1/search/local.xml?query=" + query + "&display=20&start=1";
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Headers.Add("X-Naver-Client-Id", "penrf9sjWqff0tZLTxbJ"); // 클라이언트 아이디
            request.Headers.Add("X-Naver-Client-Secret", "At5SVJCTTo");       // 클라이언트 시크릿
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            string status = response.StatusCode.ToString();
            if (status == "OK")
            {
                Stream stream = response.GetResponseStream();
                StreamReader reader = new StreamReader(stream, Encoding.UTF8);
                string text = reader.ReadToEnd();
                Parser.SaveXml("data.xml",text);
                return text;
                //Console.WriteLine(text);
            }
            else
            {
                return "Error 발생=" + status;
                //Console.WriteLine("Error 발생=" + status);
            }
        }
        public static string Start2(String target)
        {
            string query = target; // 검색할 주소
            //string url = "https://openapi.naver.com/v1/map/geocode?query=" + query; // 결과가 JSON 포맷
            //string url = "https://openapi.naver.com/v1/map/geocode.xml?query=" + query;  // 결과가 XML 포맷
            //string url = "https://map.naver.com/?query=" + query;
            String url ="https://openapi.naver.com/v1/map/staticmap.bin?query="+query; // 결과가 jpg
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Headers.Add("X-Naver-Client-Id", "penrf9sjWqff0tZLTxbJ"); // 클라이언트 아이디
            request.Headers.Add("X-Naver-Client-Secret", "At5SVJCTTo");       // 클라이언트 시크릿
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            string status = response.StatusCode.ToString();
            if (status == "OK")
            {
                Stream stream = response.GetResponseStream();
                StreamReader reader = new StreamReader(stream, Encoding.UTF8);
                string text = reader.ReadToEnd();
                return text;
                //Console.WriteLine(text);
            }
            else
            {
                return "Error 발생=" + status;
                //Console.WriteLine("Error 발생=" + status);
            }
        }
        public static string SearchStart(string target)
        {
            string query = target; // 검색할 문자열
            //string url = "https://openapi.naver.com/v1/search/blog?query=" + query; // 결과가 JSON 포맷
            string url = "http://music.naver.com/search/search.nhn?query=" + query + "&x=0&y=0";  // 결과가 XML 포맷
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Headers.Add("X-Naver-Client-Id", "zKMyiORUPqxuuPGzJge2"); // 클라이언트 아이디
            request.Headers.Add("X-Naver-Client-Secret", "07mQLmoKWk");       // 클라이언트 시크릿
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            string status = response.StatusCode.ToString();
            if (status == "OK")
            {
                Stream stream = response.GetResponseStream();
                StreamReader reader = new StreamReader(stream, Encoding.UTF8);
                string text = reader.ReadToEnd();
                return text;
                //textBox1.Text = text;
            }
            else
            {
                
                return "Error 발생=" + status;
            }
        }
        public static string SearchKeyWordMap(String target)
        {
            string query = target+"음식점"; // 검색할 문자열
            //string url = "https://openapi.naver.com/v1/search/blog?query=" + query; // 결과가 JSON 포맷
            string url = "https://openapi.naver.com/v1/search/local.xml?query=" + query;  // 결과가 XML 포맷
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Headers.Add("X-Naver-Client-Id", "ONQTxiZPzHemKitDqIpe"); // 클라이언트 아이디
            request.Headers.Add("X-Naver-Client-Secret", "3SNeTNy2Lt");       // 클라이언트 시크릿
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            string status = response.StatusCode.ToString();
            if (status == "OK")
            {
                Stream stream = response.GetResponseStream();
                StreamReader reader = new StreamReader(stream, Encoding.UTF8);
                string text = reader.ReadToEnd();
                return text;
                //Console.WriteLine(text);
            }
            else
            {
                Console.WriteLine("Error 발생=" + status);
                return "Error 발생=" + status;
            }
        }
        public static string SearchKeyWordImage(String target)
        {
            string query = target; // 검색할 문자열
            //string url = "https://openapi.naver.com/v1/search/blog?query=" + query; // 결과가 JSON 포맷
            string url = "https://openapi.naver.com/v1/search/image.xml?query=" + query;  // 결과가 XML 포맷
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Headers.Add("X-Naver-Client-Id", "ONQTxiZPzHemKitDqIpe"); // 클라이언트 아이디
            request.Headers.Add("X-Naver-Client-Secret", "3SNeTNy2Lt");       // 클라이언트 시크릿
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            string status = response.StatusCode.ToString();
            if (status == "OK")
            {
                Stream stream = response.GetResponseStream();
                StreamReader reader = new StreamReader(stream, Encoding.UTF8);
                string text = reader.ReadToEnd();
                return text;
                //Console.WriteLine(text);
            }
            else
            {
                Console.WriteLine("Error 발생=" + status);
                return "Error 발생=" + status;
            }
        }
    }
}
