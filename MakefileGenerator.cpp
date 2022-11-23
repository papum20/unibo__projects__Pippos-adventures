#include <iostream>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
using namespace std;



const char *THIS_NAME_CPP = "MakefileGenerator.cpp";
const char *THIS_NAME_O = "MakefileGenerator.o";
const char *THIS_NAME_EXE = "makemake";
const char *CURRENT_DIR = ".";
const char *PARENT_DIR = "..";
const char *OUT_NAME = "Makefile";
const char *PROJECT_NAME = "main";
#define IGNORED_NAMES_N 6
const char *IGNORED_NAMES[IGNORED_NAMES_N] = {THIS_NAME_CPP, THIS_NAME_O, THIS_NAME_EXE, OUT_NAME, CURRENT_DIR, PARENT_DIR};

#define PATH_LENGTH 200
#define NAME_LENGTH 40
#define EXTENSION_LENGTH 10

#define EXTENSIONS_NUMBER 2
#define EXTENSION_CPP 0
#define EXTENSION_HPP 1
const char EXTENSIONS[EXTENSIONS_NUMBER][EXTENSION_LENGTH] = {"cpp", "hpp"};

const char *COMPILE_COMMAND = "g++";
const char *LINK_PARAMETERS = "-lncurses -o";
const char *COMPILE_PARAMETERS = "-c";
const char *CLEAN_COMMAND = "clean:\n\trm -r*.o */*.o %s %s.exe";


//// FUNCTIONS

	//returns index of dot separating from extension, -1 if has no extension
	int getFileDot(char s[PATH_LENGTH]) {
		if(strlen(s) == 0) return -1;
		else {
			int i = strlen(s) - 1;
			while(i > 0 && s[i] != '.' && s[i] != '/' && s[i] != '\\') i--;
			if(s[i] == '.') return i;
			else return -1;
		}
	}

	void getFileExtension(char s[PATH_LENGTH], char out[EXTENSION_LENGTH]) {
		int dot = getFileDot(s);
		if(dot == -1) out[0] = '\0';
		else {
			dot++;
			for(int i = 0; dot <= strlen(s); i++) {	// <= so it also copies '\0'
				out[i] = s[dot];
				dot++;
			}
		}
	}

/*
	void getFileName(char s[PATH_LENGTH], char out[NAME_LENGTH]) {
		if(strlen(s) == 0) out[0] = '\0';
		else {
			int start = strlen(s) - 1;
			while(start > 0 && s[start] != '/' && s[start] != '\\') start--;
			int end = getFileDot(s);
			if(end == -1) end = strlen(s);
			int i;
			for(i = start; i < end; i++) out[i - start] = s[i];
			out[i - start] = '\0';
		}
	}
	*/
	void getPathNoExtension(char s[PATH_LENGTH], char out[PATH_LENGTH]) {
		if(strlen(s) == 0) out[0] = '\0';
		else {
			int dot = getFileDot(s);
			int end;
			if(dot != -1) end = dot;
			else end = strlen(s);

			int i;
			for(i = 0; i < end; i++) out[i] = s[i];
			out[i] = '\0';
		}
	}
/*
	void getRawFileName(char s[PATH_LENGTH], char out[NAME_LENGTH]) {
		if(strlen(s) == 0) out[0] = '\0';
		else {
			int i = strlen(s) - 1, j;
			while(i >= 0 && s[i] != '/' && s[i] != '\\') i--;
			for(j = 0; i < strlen(s); j++)
				out[j] = s[i + j + 1];
			out[j] = '\0';
		}
	}*/

	int strcmpCaseInsensitive(const char str1[], const char str2[]) {
		int i = 0;
		int diff = 0;
		while(diff == 0 && i < strlen(str1) && i < strlen(str2)) {
			char lower1 = str1[i], lower2 = str2[i];
			if(str1[i] >= 65 && str1[i] <= 90) lower1 = str1[i] + 32;
			if(str2[i] >= 65 && str2[i] <= 90) lower2 = str2[i] + 32;
			diff = lower1 - lower2;
			i++;
		}
		if(diff == 0 && strlen(str1) != strlen(str2)) diff = strlen(str1) - strlen(str2);
		return diff;
	}

	void getRawFileName(char s[PATH_LENGTH], char out[]) {
		if(strlen(s) == 0) return;
		else {
			int i = strlen(s) - 1;
			while(i > 0 && s[i] != '.' && s[i] != '/' && s[i] != '\\') i--;
			if(s[i] == '/')
				for(int j = 0; i + 1 + j <= strlen(s); j++) out[j] = s[j + i + 1];
			else strcpy(out, s);
		}
	}


	bool isDirectory(const char path[]) {
		struct stat path_stat;
		if(stat(path, &path_stat) != 0) return false;
		return S_ISDIR(path_stat.st_mode);
	}

	bool isFileIgnored(const char path[]) {
		bool res = false;
		int t = 0;
		while(!res && t < IGNORED_NAMES_N) {
			int i = strlen(path) - 1, j = strlen(IGNORED_NAMES[t]) - 1;
			bool res_t = true;
			while(res_t && i >= 0 && j >= 0 && path[i] != '/' && path[i] != '\\') {
				if(path[i] != IGNORED_NAMES[t][j]) res_t = false;
				i--;
				j--;
			}

			if(res_t && j == -1 && (i == -1 || path[i] == '/' || path[i] == '\\') ) res = true; 
			else t++;
		}
		return res;
	}


//// CLASS

struct filename {
	char path[PATH_LENGTH];
	bool extensions[EXTENSIONS_NUMBER];
	filename *next;
};
typedef filename *p_filename;

//list of files, alphabetically ordered
class FileList {
	private:
		p_filename head;
		p_filename current;

		void addExtension(p_filename p, char ext[EXTENSION_LENGTH]) {
			for(int e = 0; e < EXTENSIONS_NUMBER; e++)
				if(strcmp(EXTENSIONS[e], ext) == 0) p->extensions[e] = true;
		}
	public:
		FileList() {
			head = NULL;
			current = NULL;
		}
		void insert(char *fullpath) {
			char path[NAME_LENGTH], extension[EXTENSION_LENGTH];
			getPathNoExtension(fullpath, path);
			getFileExtension(fullpath, extension);

			p_filename tmp = new filename;
			strcpy(tmp->path, path);
			addExtension(tmp, extension);

			//insert (in alphabetical order)
			if(head == NULL) {
				tmp->next = NULL;
				head = tmp;
			}
			else if(strcmp(head->path, path) == 0) addExtension(head, extension);
			else {
				p_filename p = head;
				while(p->next != NULL && strcmpCaseInsensitive(p->next->path, path) < 0) p = p->next;

				if(p->next != NULL && strcmp(p->next->path, path) == 0) addExtension(p->next, extension);
				else {	//if p->next == NULL || name < p->next->name
					tmp->next = p->next;
					p->next = tmp;
				}
			}
			current = head;
		}

		// PRINT
		void printO(FILE *out) {
			p_filename p = head;
			bool first = true;
			while(p != NULL) {
				if(p->extensions[EXTENSION_CPP]) {
					if(!first) fprintf(out, " ");
					else first = false;
					char rawName[NAME_LENGTH];
					getRawFileName(p->path, rawName);
					fprintf(out, "%s.o", rawName);
				}
				p = p->next;
			}
		}
		void printDebug() {
			p_filename p = head;
			while(p != NULL) {
				cout << p->path << " ";
				for(int i = 0; i < EXTENSIONS_NUMBER; i++) cout << p->extensions[i];
				cout << endl;
				p = p->next;
			}
		}

		// CURRENT
		void nextFile() {
			if(current != NULL) current = current->next;
		}
		void getCurrentPath(char str[]) {
			if(current == NULL) str[0] = '\0';
			else strcpy(str, current->path);
		}
		bool getCurrentExtension(unsigned int ext) {
			if(current == NULL || ext >= EXTENSION_LENGTH) return false;
			else return current->extensions[ext];
		}
};



//// MAIN CODE


void readFilenames(FileList &files, const char path[PATH_LENGTH])
{
	DIR *cur_dir = opendir(path);
	dirent *content = readdir(cur_dir);
	while(content != NULL)
	{
		char new_path[PATH_LENGTH] = "\0";
		if(strcmp(path, CURRENT_DIR) != 0) {
			strcat(new_path, path);
			strcat(new_path, "/");
		}
		strcat(new_path, content->d_name);

		if(content->d_name[0] != '.' && !isFileIgnored(content->d_name)) {
			if(isDirectory(new_path)) readFilenames(files, new_path);
			else files.insert(new_path);
		}

		content = readdir(cur_dir);
	}
	closedir(cur_dir);
}


void printMakefile(FileList &files, const char out[], const char project[])
{
	FILE *f_out = fopen(out, "w");

	fprintf(f_out, "%s: ", project);
	files.printO(f_out);
	fprintf(f_out, "\n\t%s ", COMPILE_COMMAND);
	files.printO(f_out);
	fprintf(f_out, " %s %s\n\n", LINK_PARAMETERS, project);

	char cur_file[PATH_LENGTH];
	files.getCurrentPath(cur_file);
	while(strlen(cur_file) != 0) {
		if(files.getCurrentExtension(EXTENSION_CPP)) {
			char cur_fileRaw[NAME_LENGTH];
			getRawFileName(cur_file, cur_fileRaw);
			if(files.getCurrentExtension(EXTENSION_HPP)) fprintf(f_out, "%s.o: %s.cpp %s.hpp\n", cur_fileRaw, cur_file, cur_file);
			else fprintf(f_out, "%s.o: %s.cpp\n", cur_fileRaw, cur_file);
			fprintf(f_out, "\t%s %s %s.cpp\n", COMPILE_COMMAND, COMPILE_PARAMETERS, cur_file);
		}
		files.nextFile();
		files.getCurrentPath(cur_file);
	}

	fprintf(f_out, "\n\n\n");
	fprintf(f_out, CLEAN_COMMAND, project, project);

	fclose(f_out);
}





int main(int argc, char *argv[])
{
	FileList files = FileList();
	readFilenames(files, CURRENT_DIR);
	//files.print();

	if(argc > 1) printMakefile(files, OUT_NAME, argv[1]);
	else printMakefile(files, OUT_NAME, PROJECT_NAME);
}