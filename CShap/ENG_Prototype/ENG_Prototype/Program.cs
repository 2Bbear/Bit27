using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Speech.Recognition;
using System.Speech.Synthesis;

namespace ENG_Prototype
{
    class Program
    {
        static void Main(string[] args)
        {
            foreach (RecognizerInfo ri in SpeechRecognitionEngine.InstalledRecognizers())
            {
                Console.WriteLine(ri.Culture);
            }

            using (SpeechRecognitionEngine recognizer = new SpeechRecognitionEngine(new System.Globalization.CultureInfo("en-us")))
            {

                
                recognizer.LoadGrammar(new DictationGrammar());

                // Add a handler for the speech recognized event.
                recognizer.SpeechRecognized += new EventHandler<SpeechRecognizedEventArgs>(recognizer_SpeechRecognized);

                //TTS==============================================
                SpeechSynthesizer tts = new SpeechSynthesizer();
                tts.SelectVoice("Microsoft Server Speech Text to Speech Voice (ko-KR, Heami)");
                tts.SetOutputToDefaultAudioDevice();
                tts.Speak("정말?");
                Console.WriteLine("정말?");
                //================================================
                // Configure input to the speech recognizer.
                recognizer.SetInputToDefaultAudioDevice();

                // Start asynchronous, continuous speech recognition.
                recognizer.RecognizeAsync(RecognizeMode.Multiple);


                // Keep the console window open.
                while (true)
                {

                    ;
                    Console.ReadLine();
                }
            }

        }

        // Handle the SpeechRecognized event.
        static void recognizer_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            Console.WriteLine("실행");
            Console.WriteLine("Recognized text: " + e.Result.Text);
        }
    }

       
    
}
