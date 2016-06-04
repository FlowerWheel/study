#include <iostream>
#include <string>
#include <set>

using namespace std;

class Message;

class Folder{
	public:
		Folder();
		Folder(const Folder &);
		Folder & operator=(const Folder &);
		~Folder();

		addMsg(const Message &);
		removeMsg(const Message &);
	
	private:
		set<Message*> msg;
};

Folder::Folder(const Folder &fname)
{
	if (this != fname)
		msg = fname.msg;
}
Folder & Folder::operator=(const Folder &fname)
{
	if (this != fname)
		msg = fname.msg;
}
Folder::~Folder()

class Message{
	public:
		Message(const string &str = "")
			: contents(str){

			}
		Message(const Message& );
		Message & operator=(const Message& );
		~Message();

		void save(Folder &);
		void remove(Folder &);

	private:
		string contents;
		set<Folder*> folders;

		void put_msg_in_folders(const set<Folder*>&);
		void remove_msg_from_folders();
};

Message::Message(const Message &msg)
	:contents(msg.contents), folders(msg.folders)
{
	put_msg_in_folders(folders);
}
void Message::put_msg_in_folders(const set<Folder*> rhs)
{
	for (set<Folder*>::const_iterator beg = rhs.begin(), 
			beg != rhs.end(), ++beg)
		(*beg)->addMsg(this);
}
Message& Message::operator=(const Message &rhs)
{
	if (&rhs != this)
	{
		remove_msg_from_folders();
		contents = rhs.contents;
		folders = rhs.folders;
		put_msg_in_folders(rhs.folders);
	}
}
void Message::remove_msg_from_folder()
{
	for(set<Folder *>::const_iterator beg = folder.begin();
			beg != folders.end(), ++beg)
		(*beg)->removeMsg(this);
}
Message::~Message()
{
	remove_msg_from_folders();
}
