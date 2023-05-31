#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class FileWithRecords
{
private:
	fstream fileNumbers, fileNicknames;

	int *records;
	string *names;
	const int maxNumOfRecords = 10;

	string fileNameNumbers = "records.bin";
	string fileNameNicknames = "recordsNames.bin";

	void ClearFiles()
	{
		if (fileNumbers.is_open()) {
			fileNumbers.close();
			fileNumbers.open(fileNameNumbers, fstream::in | fstream::out);
		}
		if (fileNicknames.is_open()) {
			fileNicknames.close();
			fileNicknames.open(fileNameNicknames, fstream::in | fstream::out);
		}
	}

public:
	FileWithRecords()
	{
		fileNumbers.open(fileNameNumbers, fstream::in | fstream::out | fstream::app);
		fileNicknames.open(fileNameNicknames, fstream::in | fstream::out | fstream::app);

		records = new int[maxNumOfRecords];
		names = new string[maxNumOfRecords];

		for (int i = 0; i < maxNumOfRecords; i++)
		{
			if (!(fileNumbers >> records[i]))
				records[i] = 0;

			if (!(fileNicknames >> names[i]))
				names[i] = "Unknown";
		}

	}

	int* GetRecords()
	{
		return records;
	}

	string GetRecordString(int recordsNumber)
	{
		if (records[recordsNumber] != 0)
			return to_string(records[recordsNumber]) + " - " + names[recordsNumber];
		else
			return "-";
	}

	void SetNewRecord(int score, string nickname)
	{
		for (int i = 0; i < maxNumOfRecords; i++)
		{
			if (score > records[i])
			{
				for (int j = maxNumOfRecords - 1; j > i; j--)
				{
					names[j] = names[j - 1];
					records[j] = records[j - 1];
				}
				names[i] = nickname;
				records[i] = score;
				break;
			}
		}

		ClearFiles();
		for (int i = 0; i < maxNumOfRecords; i++)
		{
			fileNicknames << names[i] << endl;
			fileNumbers << records[i] << endl;
		}
	}

	~FileWithRecords()
	{
		fileNicknames.close();
		fileNumbers.close();
	}
};