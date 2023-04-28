#ifndef FILE_IF
#define FILE_IF

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <cstdio>
#include <type_traits>

#define MDEBUG 1

class file_reader
{
public:
	static constexpr int BUFFER_SIZE = 1024 * 4;

	static constexpr char end_of_file = 0;

	file_reader(std::string source_code)
	{
		p = fopen(source_code.c_str(), "r");
		file_len = fread(buffer, 1, BUFFER_SIZE, p);
		buffer[file_len] = 0;
		index = 0;
		fclose(p);
	}

	char read()// like getchar :)
	{
		char c = buffer[index++];
		if constexpr (MDEBUG) //just for scan buffer debug
		{
			if (c != 0)
				printf("%c", buffer[index]);
			else
				printf("\n\n");
		}
		return c;
	}

	char lookforward(int n)
	{
		return buffer[index + n];
	}

	void reback()
	{
		index--;
	}

	void dump()
	{
		for (int i = 0; buffer[i] != 0; i++) {
			printf("%c", buffer[i]);
		}
	}

private:
	FILE* p;
	char buffer[BUFFER_SIZE];
	int file_len;
	int index;
};

class file_writer
{

};

class file_if
{
public:
	file_if() = delete;
	
	file_if(std::string str) : reader(str) {}

	~file_if() = default;

	template<typename ty>
	ty& get_compoment()
	{
		if constexpr (std::is_same<ty, file_reader>()) {
			return reader;
		}
		else if constexpr (std::is_same<ty, file_writer>())
		{
			return writer;
		}
	}

private:
	file_reader reader;
	file_writer writer;
};

#endif
