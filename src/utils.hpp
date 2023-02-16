/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:51:37 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/02/14 17:26:25 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pch.hpp"


#define GETCWD getcwd
#define CHDIR chdir

#define MAX_DIRECTORY_FILES     512
#define MAX_FILEPATH_LENGTH      512  
#define MAX_TEXT_BUFFER_LENGTH              1024        // Size of internal static buffers used on some functions:
                                                        // TextFormat();, TextSubtext();, TextToUpper();, TextToLower();, TextToPascal();, TextSplit();
#define MAX_TEXT_UNICODE_CHARS               512        // Maximum number of unicode codepoints: GetCodepoints();
#define MAX_TEXTSPLIT_COUNT                  128        // Maximum number of substrings to split: TextSplit();


#define GLSL(src); "#version 320 es\n" #src

#define DWORD					long
#define WORD					short
#define INT						int
#define ULONG					unsigned long
#define UINT					unsigned int
#define BOOL					int
#define LONG					long
#define	BYTE					unsigned char
#define FLOAT                   float


#define CONSOLE_COLOR_RESET "\033[0m"
#define CONSOLE_COLOR_GREEN "\033[1;32m"
#define CONSOLE_COLOR_RED "\033[1;31m"
#define CONSOLE_COLOR_PURPLE "\033[1;35m"
#define CONSOLE_COLOR_CYAN "\033[0;36m"







void Log(int severity, const char* fmt, ...);

std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters);
bool find_word(const std::string& haystack,const std::string& needle);
unsigned char *LoadFileData(const char *fileName, unsigned int *bytesRead);
bool SaveFileData(const char *fileName, void *data, unsigned int bytesToWrite);
char *LoadFileText(const char *fileName);
bool SaveFileText(const char *fileName, char *text);



//----------------------------------------------------------------------------------
// Text strings management functions
//----------------------------------------------------------------------------------
const char *strprbrk(const char *s, const char *charset);
unsigned int TextLength(const char *text);
const char *TextFormat(const char *text, ...);
int TextToInteger(const char *text);
int TextCopy(char *dst, const char *src);
bool TextIsEqual(const char *text1, const char *text2);
const char *TextSubtext(const char *text, int position, int length);
char *TextReplace(char *text, const char *replace, const char *by);
char *TextInsert(const char *text, const char *insert, int position);
const char *TextJoin(const char **textList, int count, const char *delimiter);
const char **TextSplit(const char *text, char delimiter, int *count);
void TextAppend(char *text, const char *append, int *position);
int TextFindIndex(const char *text, const char *find);
const char *TextToUpper(const char *text);
const char *TextToLower(const char *text);
const char *TextToPascal(const char *text);


//----------------------------------------------------------------------------------
// Files management functions
//----------------------------------------------------------------------------------

bool FileExists(const char *fileName);
bool DirectoryExists(const char *dirPath);
const char *GetFileExtension(const char *fileName);
const char *GetFileName(const char *filePath);
const char *GetFileNameWithoutExt(const char *filePath);
const char *GetDirectoryPath(const char *filePath);
const char *GetPrevDirectoryPath(const char *dirPath);
const char *GetWorkingDirectory(void);
void ClearDirectoryFiles(void);
char **GetDirectoryFiles(const char *dirPath, int *fileCount);
bool ChangeDirectory(const char *dir);
bool IsFileExtension(const char *fileName, const char *ext);
