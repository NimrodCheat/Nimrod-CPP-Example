#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "skStr.h"
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

using namespace Nimrod;

std::string name = ""; 
std::string ownerid = ""; 
std::string secret = ""; 
std::string version = "1.0"; 
std::string url = "https://auth.nimrodcheat.com/api/1.1/"; 
std::string sslPin = "ssl pin key (optional)";


api NimrodApp(name, ownerid, secret, version, url, sslPin);

int main()
{
	SetConsoleTitleA(skCrypt("Loader"));
	std::cout << skCrypt("\n\n Connecting..");
	NimrodApp.init();
	if (!NimrodApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << NimrodApp.data.message;
		Sleep(1500);
		exit(0);
	}

	std::cout << skCrypt("\n\n App data:");
	std::cout << skCrypt("\n Number of users: ") << NimrodApp.data.numUsers;
	std::cout << skCrypt("\n Number of online users: ") << NimrodApp.data.numOnlineUsers;
	std::cout << skCrypt("\n Number of keys: ") << NimrodApp.data.numKeys;
	std::cout << skCrypt("\n Application Version: ") << NimrodApp.data.version;
	std::cout << skCrypt("\n Customer panel link: ") << NimrodApp.data.customerPanelLink;
	std::cout << skCrypt("\n Checking session validation status (remove this if causing your loader to be slow)");
	NimrodApp.check();
	std::cout << skCrypt("\n Current Session Validation Status: ") << NimrodApp.data.message;

	std::cout << skCrypt("\n\n [1] Login\n [2] Register\n [3] Upgrade\n [4] License key only\n\n Choose option: ");

	int option;
	std::string username;
	std::string password;
	std::string key;

	std::cin >> option;
	switch (option)
	{
	case 1:
		std::cout << skCrypt("\n\n Enter username: ");
		std::cin >> username;
		std::cout << skCrypt("\n Enter password: ");
		std::cin >> password;
		NimrodApp.login(username, password);
		break;
	case 2:
		std::cout << skCrypt("\n\n Enter username: ");
		std::cin >> username;
		std::cout << skCrypt("\n Enter password: ");
		std::cin >> password;
		std::cout << skCrypt("\n Enter license: ");
		std::cin >> key;
		NimrodApp.regstr(username, password, key);
		break;
	case 3:
		std::cout << skCrypt("\n\n Enter username: ");
		std::cin >> username;
		std::cout << skCrypt("\n Enter license: ");
		std::cin >> key;
		NimrodApp.upgrade(username, key);
		break;
	case 4:
		std::cout << skCrypt("\n Enter license: ");
		std::cin >> key;
		NimrodApp.license(key);
		break;
	default:
		std::cout << skCrypt("\n\n Status: Failure: Invalid Selection");
		Sleep(3000);
		exit(0);
	}

	if (!NimrodApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << NimrodApp.data.message;
		Sleep(1500);
		exit(0);
	}

	std::cout << skCrypt("\n User data:");
	std::cout << skCrypt("\n Username: ") << NimrodApp.data.username;
	std::cout << skCrypt("\n IP address: ") << NimrodApp.data.ip;
	std::cout << skCrypt("\n Hardware-Id: ") << NimrodApp.data.hwid;
	std::cout << skCrypt("\n Create date: ") << tm_to_readable_time(timet_to_tm(string_to_timet(NimrodApp.data.createdate)));
	std::cout << skCrypt("\n Last login: ") << tm_to_readable_time(timet_to_tm(string_to_timet(NimrodApp.data.lastlogin)));
	std::cout << skCrypt("\n Subscription name(s): ");
	std::string subs;
	for (std::string value : NimrodApp.data.subscriptions)subs += value + " ";
	std::cout << subs;
	std::cout << skCrypt("\n Subscription expiry: ") << tm_to_readable_time(timet_to_tm(string_to_timet(NimrodApp.data.expiry)));
	std::cout << skCrypt("\n Checking session validation status (remove this if causing your loader to be slow)");
	NimrodApp.check();
	std::cout << skCrypt("\n Current Session Validation Status: ") << NimrodApp.data.message;
	


	std::cout << skCrypt("\n\n Closing in ten seconds...");
	Sleep(10000);
	exit(0);
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
