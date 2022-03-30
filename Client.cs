 using UnityEngine;                        // These are the librarys being used
 using System.Collections;
 using System;
 using System.IO;
 using System.Net.Sockets;   

public class Client : MonoBehaviour
{
    bool socketReady = false;                // global variables are setup here
     TcpClient mySocket;
     public NetworkStream theStream;
     StreamWriter theWriter;
     StreamReader theReader;
     public String Host = "192.168.137.180";
     public Int32 Port = 80; 
     
     //Read string [0,1,2,3,4]
     public String Ax, Ay, Az, Gx, Gy, Gz;
     public String buffer;
     String[] sValue;
     
 
     void Start() {
         setupSocket ();                        // setup the server connection when the program starts
     }
     
     // Update is called once per frame
     
     void FixedUpdate(){
         
         while (theStream.DataAvailable) {                  // if new data is recieved from Arduino
             buffer = readSocket();
             sValue = buffer.Split(' ');
             Ax = sValue[0];
             Ay = sValue[1];
             Az = sValue[2];
             Gx = sValue[3];
             Gy = sValue[4];
             Gz = sValue[5];
             }
         
     }
     
     public void setupSocket() {                            // Socket setup here
         try {                
             mySocket = new TcpClient(Host, Port);
             theStream = mySocket.GetStream();
             theWriter = new StreamWriter(theStream);
             theReader = new StreamReader(theStream);
             socketReady = true;
         }
         catch (Exception e) {
             Debug.Log("Socket error:" + e);                // catch any exceptions
         }
     }
     
     public String readSocket() {                        // function to read data in
         if (theStream.DataAvailable)
             return theReader.ReadLine();
         return ""; 
     }
     
     public void closeSocket() {                            // function to close the socket
         if (!socketReady)
             return;
         theWriter.Close();
         theReader.Close();
         mySocket.Close();
         socketReady = false;
     }
     
     public void maintainConnection(){                    // function to maintain the connection (not sure why! but Im sure it will become a solution to a problem at somestage)
         if(!theStream.CanRead) {
             setupSocket();
         }
     }
}