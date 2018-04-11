
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Start {

 
    public Start()
    {
        
        App app = App.GetInstance();
        
        app.Init();
        app.Run();
        app.Exit();
    }

   
    public void Main() {
        // TODO implement here
    }

}