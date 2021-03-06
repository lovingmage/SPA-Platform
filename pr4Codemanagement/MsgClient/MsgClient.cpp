/////////////////////////////////////////////////////////////////////////
// MsgClient.cpp - Demonstrates simple one-way HTTP messaging          //
//                                                                     //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016           //
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, Dell XPS 8900, Windows 10 pro      //
/////////////////////////////////////////////////////////////////////////
/*
 * This package implements a client that sends HTTP style messages and
 * files to a server that simply displays messages and stores files.
 *
 * It's purpose is to provide a very simple illustration of how to use
 * the Socket Package provided for Project #4.
 */
/*
* Required Files:
*   MsgClient.cpp, MsgServer.cpp
*   HttpMessage.h, HttpMessage.cpp
*   Cpp11-BlockingQueue.
*   Sockets.h, Sockets.cpp
*   FileSystem.h, FileSystem.cpp
*   Logger.h, Logger.cpp
*   Utilities.h, Utilities.cpp
*/
/*
 * ToDo:
 * - pull the sending parts into a new Sender class
 * - You should create a Sender like this:
 *     Sender sndr(endPoint);  // sender's EndPoint
 *     sndr.PostMessage(msg);
 *   HttpMessage msg has the sending adddress, e.g., localhost:8080.
 */
#include "../HttpMessage/HttpMessage.h"
#include "../Sockets/Sockets.h"
#include "../FileSystem/FileSystem.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include <direct.h>
#include <string>
#include <iostream>
#include <thread>

using Show = StaticLogger<1>;
using namespace Utilities;
using Utils = StringHelper;

/////////////////////////////////////////////////////////////////////
// ClientCounter creates a sequential number for each client
//
class ClientCounter
{
public:
  ClientCounter() { ++clientCount; }
  size_t count() { return clientCount; }
private:
  static size_t clientCount;
};

size_t ClientCounter::clientCount = 0;

/////////////////////////////////////////////////////////////////////
// MsgClient class
// - was created as a class so more than one instance could be 
//   run on child thread
//
class MsgClient
{
public:
  using EndPoint = std::string;
  void execute(const size_t TimeBetweenMessages, const size_t NumMessages);
  void exeCheckIn(std::string filePath);
  void multipleCheckIn(std::string filePath);
  void executeDownload(std::string packageName);
private:
  HttpMessage makeMessage(size_t n, const std::string& msgBody, const EndPoint& ep);
  void sendMessage(HttpMessage& msg, Socket& socket);
  bool sendFile(const std::string& fqname, std::string filePath, Socket& socket, std::string STATUS);
  bool downLoader(const std::string& filename, size_t fileSize, Socket& socket);
  bool downLoadwDep(const std::string& filename, size_t fileSize, Socket& socket, std::vector<std::string> depFiles);
  bool checkIn(std::string filePath, Socket& socket, std::string STATUS);


};
//----< factory for creating messages >------------------------------
/*
 * This function only creates one type of message for this demo.
 * - To do that the first argument is 1, e.g., index for the type of message to create.
 * - The body may be an empty string.
 * - EndPoints are strings of the form ip:port, e.g., localhost:8081. This argument
 *   expects the receiver EndPoint for the toAddr attribute.
 */
HttpMessage MsgClient::makeMessage(size_t n, const std::string& body, const EndPoint& ep)
{
  HttpMessage msg;
  HttpMessage::Attribute attrib;
  EndPoint myEndPoint = "localhost:8081";  // ToDo: make this a member of the sender
                                           // given to its constructor.
  switch (n)
  {
  case 1:
    msg.clear();
    msg.addAttribute(HttpMessage::attribute("POST", "Message"));
    msg.addAttribute(HttpMessage::Attribute("mode", "oneway"));
    msg.addAttribute(HttpMessage::parseAttribute("toAddr:" + ep));
    msg.addAttribute(HttpMessage::parseAttribute("fromAddr:" + myEndPoint));

    msg.addBody(body);
    if (body.size() > 0)
    {
      attrib = HttpMessage::attribute("content-length", Converter<size_t>::toString(body.size()));
      msg.addAttribute(attrib);
    }
    break;
  default:
    msg.clear();
    msg.addAttribute(HttpMessage::attribute("Error", "unknown message type"));
  }
  return msg;
}
//----< send message using socket >----------------------------------

void MsgClient::sendMessage(HttpMessage& msg, Socket& socket)
{
  std::string msgString = msg.toString();
  socket.send(msgString.size(), (Socket::byte*)msgString.c_str());
}
//----< send file using socket >-------------------------------------
/*
 * - Sends a message to tell receiver a file is coming.
 * - Then sends a stream of bytes until the entire file
 *   has been sent.
 * - Sends in binary mode which works for either text or binary.
 */
bool MsgClient::sendFile(const std::string& filename, std::string filePath, Socket& socket, std::string STATUS)
{
  // assumes that socket is connected

  std::string fqname = filePath + filename;
  FileSystem::FileInfo fi(fqname);
  size_t fileSize = fi.size();
  std::string sizeString = Converter<size_t>::toString(fileSize);
  FileSystem::File file(fqname);
  file.open(FileSystem::File::in, FileSystem::File::binary);
  if (!file.isGood())
    return false;
  
  HttpMessage msg = makeMessage(1, "", "localhost::8080");
  msg.addAttribute(HttpMessage::Attribute("file", filename));
  msg.addAttribute(HttpMessage::Attribute("content-length", sizeString));
  msg.addAttribute(HttpMessage::Attribute("status", STATUS));
  sendMessage(msg, socket);
  const size_t BlockSize = 2048;
  Socket::byte buffer[BlockSize];
  while (true)
  {
    FileSystem::Block blk = file.getBlock(BlockSize);
    if (blk.size() == 0)
      break;
    for (size_t i = 0; i < blk.size(); ++i)
      buffer[i] = blk[i];
    socket.send(blk.size(), buffer);
    if (!file.isGood())
      break;
  }
  file.close();
  return true;
}
//----< this defines the downloader of client>-----------------------

bool MsgClient::downLoader(const std::string & filename, size_t fileSize, Socket & socket)
{

	HttpMessage msg = makeMessage(1, "", "localhost::8080");
	msg.addAttribute(HttpMessage::Attribute("packagename", filename));
	sendMessage(msg, socket);
	
	
	return false;
}
//-----<Download packages with dependenpency files>
bool MsgClient::downLoadwDep(const std::string & filename, size_t fileSize, Socket & socket, std::vector<std::string> depFiles)
{
	HttpMessage msg = makeMessage(1, "", "localhost::8080");
	msg.addAttribute(HttpMessage::Attribute("packagename", filename));
	sendMessage(msg, socket);
	return false;
}

bool MsgClient::checkIn(std::string filePath, Socket & socket, std::string STATUS)
{
	std::vector<std::string> files = FileSystem::Directory::getFiles(filePath, "*.cpp");
	std::vector<std::string> hfiles = FileSystem::Directory::getFiles(filePath, "*.h");
	std::vector<std::string> dfiles = FileSystem::Directory::getFiles(filePath, "*.conf");
	for (size_t i = 0; i < files.size(); ++i)
	{
		Show::write("\n\n  sending file " + files[i]);
		sendFile(files[i], filePath, socket, "open");
		sendFile(hfiles[i], filePath, socket, "open");
		sendFile(dfiles[i], filePath, socket, STATUS);
	}

	return false;
}



void MsgClient::exeCheckIn(std::string filePath)
{
	ClientCounter counter;
	size_t myCount = counter.count();
	std::string myCountString = Utilities::Converter<size_t>::toString(myCount);
	Show::attach(&std::cout);
	Show::start();

	Show::title(
		"Starting HttpMessage client" + myCountString +
		" on thread " + Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id())
		);
	try
	{
		SocketSystem ss;
		SocketConnecter si;
		while (!si.connect("localhost", 8080))
		{
			Show::write("\n client waiting to connect");
			::Sleep(100);
		}

		// send a set of messages
		HttpMessage msg;
		//checkIn Test
		checkIn(filePath, si, "open");

		// shut down server's client handler
		msg = makeMessage(1, "quit", "toAddr:localhost:8080");
		sendMessage(msg, si);
		Show::write("\n\n  client" + myCountString + " sent\n" + msg.toIndentedString());
		Show::write("\n");
		Show::write("\n  All done folks");
	}
	catch (std::exception& exc)
	{
		Show::write("\n  Exeception caught: ");
		std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
		Show::write(exMsg);
	}
}
//------< Perform multiple checkin to without flag close >---------------------------------------
void MsgClient::multipleCheckIn(std::string filePath)
{
	ClientCounter counter;
	size_t myCount = counter.count();
	std::string myCountString = Utilities::Converter<size_t>::toString(myCount);
	Show::attach(&std::cout);
	Show::start();

	Show::title(
		"Starting HttpMessage client" + myCountString +
		" on thread " + Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id())
		);
	try
	{
		SocketSystem ss;
		SocketConnecter si;
		while (!si.connect("localhost", 8080))
		{
			Show::write("\n client waiting to connect");
			::Sleep(100);
		}

		// send a set of messages
		HttpMessage msg;
		// 1st time CheckIn 
		checkIn(filePath, si, "close");
		::Sleep(1000);
		// 2nd Time CheckIn
		checkIn(filePath, si, "open");

		msg = makeMessage(1, "quit", "toAddr:localhost:8080");
		sendMessage(msg, si);
		Show::write("\n\n  client" + myCountString + " sent\n" + msg.toIndentedString());
		Show::write("\n");
		Show::write("\n  All done folks");
	}
	catch (std::exception& exc)
	{
		Show::write("\n  Exeception caught: ");
		std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
		Show::write(exMsg);
	}
}

//-----< execute The Download Process>-------------------------------
void MsgClient::executeDownload(std::string packageName)
{
	ClientCounter counter;
	size_t myCount = counter.count();
	std::string myCountString = Utilities::Converter<size_t>::toString(myCount);
	Show::attach(&std::cout);
	Show::start();

	Show::title(
		"Starting HttpMessage client" + myCountString +
		" on thread " + Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id())
		);
	try
	{
		SocketSystem ss;
		SocketConnecter si;
		while (!si.connect("localhost", 8080))
		{
			Show::write("\n client waiting to connect");
			::Sleep(100);
		}

		// send a set of messages
		HttpMessage msg;
		//checkIn Test
		checkIn("../TestFiles/Client/Sockets/", si, "open");

		downLoader(packageName, 1, si);

		// shut down server's client handler
		msg = makeMessage(1, "quit", "toAddr:localhost:8080");
		sendMessage(msg, si);
		Show::write("\n\n  client" + myCountString + " sent\n" + msg.toIndentedString());
		Show::write("\n");
		Show::write("\n  All done folks");
	}
	catch (std::exception& exc)
	{
		Show::write("\n  Exeception caught: ");
		std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
		Show::write(exMsg);
	}
}
//----< entry point - runs two clients each on its own thread >------

int main()
{
  ::SetConsoleTitle(L"Clients Running on Threads");

  Show::title("Demonstrating two HttpMessage Clients each running on a child thread");
  //MsgClient c1;
  //c1.exeCheckIn("../TestFiles/Client/Logger/");

  MsgClient c2;
  c2.multipleCheckIn("../TestFiles/Client/Logger/");


  MsgClient c3;
  c3.executeDownload("Sockets");


  return 0;

}