/////////////////////////////////////////////////////////////////////////
// MsgServer.cpp - Demonstrates simple one-way HTTP style messaging    //
//                 and file transfer                                   //
//                                                                     //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016           //
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, Dell XPS 8900, Windows 10 pro      //
/////////////////////////////////////////////////////////////////////////
/*
* This package implements a server that receives HTTP style messages and
* files from multiple concurrent clients and simply displays the messages
* and stores files.
*
* It's purpose is to provide a very simple illustration of how to use
* the Socket Package provided for Project #4.
*/
/*
* Required Files:
*   MsgClient.cpp, MsgServer.cpp
*   HttpMessage.h, HttpMessage.cpp
*   Cpp11-BlockingQueue.h
*   Sockets.h, Sockets.cpp
*   FileSystem.h, FileSystem.cpp
*   Logger.h, Logger.cpp 
*   Utilities.h, Utilities.cpp
*/
/*
 * ToDo:
 * - pull the receiving code into a Receiver class
 * - Receiver should own a BlockingQueue, exposed through a
 *   public method:
 *     HttpMessage msg = Receiver.GetMessage()
 * - You will start the Receiver instance like this:
 *     Receiver rcvr("localhost:8080");
 *     ClientHandler ch;
 *     rcvr.start(ch);
 */
#include "../HttpMessage/HttpMessage.h"
#include "../Sockets/Sockets.h"
#include "../FileSystem/FileSystem.h"
#include "../Logger/Cpp11-BlockingQueue.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../Logger/StringTime.h"
#include <string>
#include <iostream>
#include <direct.h>
#include <map>
#include <time.h>


using Show = StaticLogger<1>;
using namespace Utilities;

/////////////////////////////////////////////////////////////////////
// ClientHandler class
/////////////////////////////////////////////////////////////////////
// - instances of this class are passed by reference to a SocketListener
// - when the listener returns from Accept with a socket it creates an
//   instance of this class to manage communication with the client.
// - You need to be careful using data members of this class
//   because each client handler thread gets a reference to this 
//   instance so you may get unwanted sharing.
// - I may change the SocketListener semantics (this summer) to pass
//   instances of this class by value.
// - that would mean that all ClientHandlers would need either copy or
//   move semantics.
//
class ClientHandler
{
public:
  ClientHandler(BlockingQueue<HttpMessage>& msgQ) : msgQ_(msgQ) {}
  void operator()(Socket socket);
  const std::string currentDateTime();
  std::string relocateFile(std::string inFiles);
private:
  bool connectionClosed_;
  HttpMessage readMessage(Socket& socket);
  bool readFile(const std::string& filename, size_t fileSize, Socket& socket);
  BlockingQueue<HttpMessage>& msgQ_;
  std::map<std::string, std::string> fileMap;
};
//----< this defines processing to frame messages >------------------

HttpMessage ClientHandler::readMessage(Socket& socket)
{
  connectionClosed_ = false;
  HttpMessage msg;

  // read message attributes

  while (true)
  {
    std::string attribString = socket.recvString('\n');
    if (attribString.size() > 1)
    {
      HttpMessage::Attribute attrib = HttpMessage::parseAttribute(attribString);
      msg.addAttribute(attrib);
    }
    else
    {
      break;
    }
  }
  // If client is done, connection breaks and recvString returns empty string

  if (msg.attributes().size() == 0)
  {
    connectionClosed_ = true;
    return msg;
  }
  // read body if POST - all messages in this demo are POSTs

  if (msg.attributes()[0].first == "POST")
  {
    // is this a file message?

    std::string filename = msg.findValue("file");
    if (filename != "")
    {
      size_t contentSize;
      std::string sizeString = msg.findValue("content-length");
      if (sizeString != "")
        contentSize = Converter<size_t>::toValue(sizeString);
      else
        return msg;

      readFile(filename, contentSize, socket);
    }

    if (filename != "")
    {
      // construct message body

      msg.removeAttribute("content-length");
      std::string bodyString = "<file>" + filename + "</file>";
      std::string sizeString = Converter<size_t>::toString(bodyString.size());
      msg.addAttribute(HttpMessage::Attribute("content-length", sizeString));
      msg.addBody(bodyString);
    }
    else
    {
      // read message body

      size_t numBytes = 0;
      size_t pos = msg.findAttribute("content-length");
      if (pos < msg.attributes().size())
      {
        numBytes = Converter<size_t>::toValue(msg.attributes()[pos].second);
        Socket::byte* buffer = new Socket::byte[numBytes + 1];
        socket.recv(numBytes, buffer);
        buffer[numBytes] = '\0';
        std::string msgBody(buffer);
        msg.addBody(msgBody);
        delete[] buffer;
      }
    }
  }
  return msg;
}
//----< read a binary file from socket and save >--------------------
/*
 * This function expects the sender to have already send a file message, 
 * and when this function is running, continuosly send bytes until
 * fileSize bytes have been sent.
 */
bool ClientHandler::readFile(const std::string& fullname, size_t fileSize, Socket& socket)
{
	
  std::string dirname = relocateFile(fullname);
  std::string fqname;
  size_t lastindex = fullname.find_last_of(".");
  std::string shortname = fullname.substr(0, lastindex);
  std::string localTime;
  localTime = currentDateTime();

  
  if (fullname.substr(fullname.find_last_of(".") + 1) == "conf")
  {
	  fqname = dirname + shortname + ".xml";
  }
  else
  {
	  fqname = dirname + fullname + ".snt";
  }

  FileSystem::File file(fqname);
  file.open(FileSystem::File::out, FileSystem::File::binary);
  if (!file.isGood())
  {
    /*
     * This error handling is incomplete.  The client will continue
     * to send bytes, but if the file can't be opened, then the server
     * doesn't gracefully collect and dump them as it should.  That's
     * an exercise left for students.
     */
    Show::write("\n\n  can't open file " + fqname);
    return false;
  }

  const size_t BlockSize = 2048;
  Socket::byte buffer[BlockSize];

  size_t bytesToRead;
  while (true)
  {
    if (fileSize > BlockSize)
      bytesToRead = BlockSize;
    else
      bytesToRead = fileSize;

    socket.recv(bytesToRead, buffer);

    FileSystem::Block blk;
    for (size_t i = 0; i < bytesToRead; ++i)
      blk.push_back(buffer[i]);

    file.putBlock(blk);
    if (fileSize < BlockSize)
      break;
    fileSize -= BlockSize;
  }
  file.close();
  std::ofstream wofs;
  wofs.open(fqname, std::ofstream::out | std::ofstream::app);
  wofs << "<packagename>" + shortname + "</packagename>\n" << "<checkintime>" + localTime + "</checkintime>\n";
  wofs << "</Metadata>";
  return true;
}
//----< receiver functionality is defined by this function >---------

void ClientHandler::operator()(Socket socket)
{
  /*
   * There is a potential race condition due to the use of connectionClosed_.
   * If two clients are sending files at the same time they may make changes
   * to this member in ways that are incompatible with one another.  This
   * race is relatively benign in that it simply causes the readMessage to 
   * be called one extra time.
   *
   * The race is easy to fix by changing the socket listener to pass in a 
   * copy of the clienthandler to the clienthandling thread it created.  
   * I've briefly tested this and it seems to work.  However, I did not want
   * to change the socket classes this late in your project cycle so I didn't
   * attempt to fix this.
   */
  while (true)
  {
    HttpMessage msg = readMessage(socket);
    if (connectionClosed_ || msg.bodyString() == "quit")
    {
      Show::write("\n\n  clienthandler thread is terminating");
      break;
    }
    msgQ_.enQ(msg);
  }
}

const std::string ClientHandler::currentDateTime()
{
	std::string time;
	Time newTime;
	time = newTime.stringTime();
	return time;

}

std::string ClientHandler::relocateFile(std::string inFiles)
{
	std::string localTime;
	localTime = currentDateTime();
	size_t lastindex = inFiles.find_last_of(".");
	std::string filename = inFiles.substr(0, lastindex);
	std::map<std::string, std::string>::iterator it;
	std::string dirname;
	it = fileMap.find(filename);
	if ((it != fileMap.end()))
	{ 
		dirname = "../TestFiles/" + it->first + '_' + it->second + '/';
	}
	else
	{
		fileMap.insert(std::pair<std::string, std::string>(filename, localTime));
		dirname = "../TestFiles/" + filename + '_' + localTime + '/';
		_mkdir(dirname.c_str());
		/*std::string tempxml = dirname + "Metadata_" + filename + ".xml";
		std::ofstream outfile(tempxml);
		std::ofstream wofs;
		wofs.open(tempxml, std::ofstream::out | std::ofstream::app);
		wofs << "<Metadata>\n";
		wofs << "<packagename>" + filename + "</packagename>\n" << "<checkintime>" + localTime + "</checkintime>\n";
		wofs.close();*/
	}
	return dirname;
}

//----< test stub >--------------------------------------------------

int main()
{
  ::SetConsoleTitle(L"HttpMessage Server - Runs Forever");

  Show::attach(&std::cout);
  Show::start();
  Show::title("\n  HttpMessage Server started");

  BlockingQueue<HttpMessage> msgQ;

  try
  {
    SocketSystem ss;
    SocketListener sl(8080, Socket::IP6);
    ClientHandler cp(msgQ);
    sl.start(cp);
    /*
     * Since this is a server the loop below never terminates.
     * We could easily change that by sending a distinguished 
     * message for shutdown.
     */
    while (true)
    {
      HttpMessage msg = msgQ.deQ();
      Show::write("\n\n  server recvd message contents:\n" + msg.bodyString());
    }
  }
  catch (std::exception& exc)
  {
    Show::write("\n  Exeception caught: ");
    std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
    Show::write(exMsg);
  }
}