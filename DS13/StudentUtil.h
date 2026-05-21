#pragma once
typedef struct Student
{
	unsigned int regNo;
	unsigned short group;
	char* name;
} Student, * PStudent;
PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*);