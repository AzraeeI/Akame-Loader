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
	printf("-h -> Help page \t\t-i -> Info page\n-s -> Show file informations\t-v -> Save informations as txt\n-X -> Pack with XOR [fastest]\t-A -> Pack with AES [safest]\n-t -> Test packed file");
	SetConsoleTextAttribute(hConsole, 6);
	// Options
	printf("\n\nOptions:\n");
	SetConsoleTextAttribute(hConsole, 7);
	printf("-q \t\t-> Be quiet\n-o File.exe \t-> Write output to 'File.exe'\n-k \t\t-> Keep backup file\nfile.exe \t-> Executable to crypt\n");
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

	// Help page
	if (argc == 1 || (string)argv[1]=="-h" || (string)argv[1]=="--help") {
		Help();
		return 0;
	}

	// Info Page
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
	string filepath = (string)argv[argc-1], fullcommand;
	struct stat fileInfo;
	bool quiet = false;

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
	for (unsigned int i = 1; i < argc; i++) {
		fullcommand += argv[i] + string(" ");
	}

	if (fullcommand.find("-q ") != string::npos) {
		cout << "Quiet mode, pretty buggy\n";
		quiet = true;
	}

	// Setup
	if (fullcommand.find("-s ") != string::npos || fullcommand.find("-v ") != string::npos) {
		if (stat(argv[argc - 1], &fileInfo) != 0) {
			printf("\n!Error: ");
			SetConsoleTextAttribute(hConsole, 12);
			printf("Can't read file informations!");
			SetConsoleTextAttribute(hConsole, 7);
			Help();
			return 0;
		}
	}

	// File information (-s)
	if (fullcommand.find("-s ") != string::npos){ 
		if(!quiet)
			cout << "\nFile Information ->\nFile Name		- " << filepath << "\nI-Node Number		- "	<< (long)fileInfo.st_ino << "\nFile Size		- "	<< fileInfo.st_size << " bytes || " << fileInfo.st_size/1024 << " kilobytes" << "\nDevice			- "	<< (char)(fileInfo.st_dev + 'A') << ":/\nMode			- "	<< (unsigned long)fileInfo.st_mode << "\nLink Count		- "	<< (long)fileInfo.st_nlink << "\nOwnership		- UID=" << (long)fileInfo.st_uid << " GID=" << (long)fileInfo.st_gid << "\nLast Status Change	- "	<< ctime(&fileInfo.st_ctime) << "Last Access		- "	<< ctime(&fileInfo.st_atime) << "Last Modification	- "	<< ctime(&fileInfo.st_mtime);
	}

	// Save file informations as txt (-v)
	if (fullcommand.find("-v ") != string::npos) {
		ofstream fileinfo("FileInformations.txt");
		fileinfo << "File Information ->\nFile Name		- " << filepath << "\nI-Node Number		- " << (long)fileInfo.st_ino << "\nFile Size		- " << fileInfo.st_size << " bytes || " << fileInfo.st_size / 1024 << " kilobytes" << "\nDevice			- " << (char)(fileInfo.st_dev + 'A') << ":/\nMode			- " << (unsigned long)fileInfo.st_mode << "\nLink Count		- " << (long)fileInfo.st_nlink << "\nOwnership		- UID=" << (long)fileInfo.st_uid << " GID=" << (long)fileInfo.st_gid << "\nLast Status Change	- " << ctime(&fileInfo.st_ctime) << "Last Access		- " << ctime(&fileInfo.st_atime) << "Last Modification	- " << ctime(&fileInfo.st_mtime);
		fileinfo.close();
	}

	// Backup file
	if (fullcommand.find("-k ") != string::npos) {
		system("mkdir Backup");
		string copycommand = string(R"(copy ")") + filepath + string(R"(" Backup)");
		cout << "\nBackup -> ";
		system(copycommand.c_str());
	}

	return 0;
}
