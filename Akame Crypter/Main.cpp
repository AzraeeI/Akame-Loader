#include "Includes.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool file_exists(string& filepath) {
	struct stat buffer;
	return (stat(filepath.c_str(), &buffer) == 0);
}

void Help() {
	// Main
	SetConsoleTextAttribute(hConsole, 2);
	printf("\nCorrect usage: ");
	SetConsoleTextAttribute(hConsole, 7);
	printf(R"("Akame Crypter.exe" [-Command] [-Option] [-o "Output File.exe"] C:/path/to/file/file.exe)");
	SetConsoleTextAttribute(hConsole, 6);
	// Commands
	printf("\n\nCommands:\n");
	SetConsoleTextAttribute(hConsole, 7);
	printf("!Use them in this order\n-h -> help page \t\t-i -> info page\n-s -> show file informations\t-v -> save informations as txt\n-X -> Pack with XOR [fastest]\t-A -> Pack with AES [safest]\n-t -> test packed file");
	SetConsoleTextAttribute(hConsole, 6);
	// Options
	printf("\n\nOptions:\n");
	SetConsoleTextAttribute(hConsole, 7);
	printf("!Use them in this order\n-q \t\t-> be quiet\n-o File.exe \t-> write output to 'File.exe'\n-k \t\t-> Keep backup file\nfile.exe \t-> DLL/Executable to crypt\n");
	// End
	SetConsoleTextAttribute(hConsole, 2);
	printf("\nAkame Crypter comes with ABSOLUTELY NO WARRANTY\nFor more details visit https://github.com/Wtf-Is-This-x1337/Akame\n");
	SetConsoleTextAttribute(hConsole, 7);
}

int main(int argc, char* argv[]) {
	printf(R"(   ___   __                    _____              __         
  / _ | / /_____ ___ _  ___   / ___/_____ _____  / /____ ____
 / __ |/  '_/ _ `/  ' \/ -_) / /__/ __/ // / _ \/ __/ -_) __/
/_/ |_/_/\_\\_,_/_/_/_/\__/  \___/_/  \_, / .__/\__/\__/_/   
                                     /___/_/                 
)");
	if (argc == 1 || (string)argv[1]=="-h" || (string)argv[1]=="--help") {
		Help();
		return 0;
	}
	if ((string)argv[1] == "-i" || (string)argv[1] == "--info") {
		// Credits
		printf("\nCreated by	-> WtfIsThis");
		// Github
		printf("\nGithub Repo	-> https://github.com/Wtf-Is-This-x1337/Akame");
		// Version
		printf("\nVersion		-> 0.1");
		// Details
		printf("\n\nDetails	-> \n* Akame is an open-source C++ Crypter. Stub && Builder coded in Visual Studio.");
		// Features
		printf("\n\nFeatures -> \n* XOR && AES Encryption\n* Virtual Env Detection\n");
		// End
		SetConsoleTextAttribute(hConsole, 2);
		printf("\nAkame Crypter comes with ABSOLUTELY NO WARRANTY\nFor more details visit https://github.com/Wtf-Is-This-x1337/Akame\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}

	// Variables
	string filepath = (string)argv[argc-1];
	struct stat fileInfo;

	// Error Handling
	if (!file_exists(filepath) || filepath.find(".exe") == string::npos) {
		printf("\n!Error: ");
		SetConsoleTextAttribute(hConsole, 12);
		printf("Incorrect file path / file extension!\n");
		SetConsoleTextAttribute(hConsole, 7);
		Help();
		return 0;
	}

	// Commands
	if ((string)argv[1] == "-s") {
		if (stat(argv[argc - 1], &fileInfo) != 0) {
			printf("\n!Error: ");
			SetConsoleTextAttribute(hConsole, 12);
			printf("Can't read file informations!");
			SetConsoleTextAttribute(hConsole, 7);
			Help();
			return 0;
		}
		cout << "\nFile Information ->";
		cout << "\nFile Name		- " << filepath;
		cout << "\nI-Node Number		- "	<< (long)fileInfo.st_ino;
		cout << "\nFile Size		- "	<< fileInfo.st_size << " bytes || " << fileInfo.st_size/1024 << " kilobytes";
		cout << "\nDevice			- "	<< (char)(fileInfo.st_dev + 'A') << ":/";
		cout << "\nMode			- "	<< (unsigned long)fileInfo.st_mode;
		cout << "\nLink Count		- "	<< (long)fileInfo.st_nlink;
		cout << "\nOwnership		- UID=" << (long)fileInfo.st_uid << " GID=" << (long)fileInfo.st_gid;
		cout << "\nLast Status Change	- "	<< ctime(&fileInfo.st_ctime);
		cout << "Last Access		- "	<< ctime(&fileInfo.st_atime);
		cout << "Last Modification	- "	<< ctime(&fileInfo.st_mtime);
	}
	return 0;
}